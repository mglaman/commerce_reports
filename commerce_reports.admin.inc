<?php

function commerce_reports_dashboard_page() {
  drupal_add_js(drupal_get_path('module', 'commerce_reports') .'/commerce_reports.dashboard.js', 'file');
  
  return array(
    commerce_reports_sales_dashboard_block(array(
      'title' => t('Sales overview'),
      'report' => array(
        'title' => t('Sales reports'),
        'path' => 'admin/commerce/reports/sales',
      ),
      'sections' => array(
        'today' => array(
          'module' => 'views',
          'block' => 'ff7824695a12b49a79aee7d394cbd917',
        ),
        'yesterday' => array(
          'module' => 'views',
          'block' => '1a260a710ed0ccc9e8175e7301e597fe',
        ),
        'month' => array(
          'module' => 'views',
          'block' => '724c01e6b3c93b66c793ff63f7402697',
        ),
      ),
    )),
    commerce_reports_sales_dashboard_block(array(
      'title' => t('Products'),
      'switchSections' => TRUE,
      'report' => array(
        'title' => t('Product reports'),
        'path' => 'admin/commerce/reports/products',
      ),
      'sections' => array(
        'revenue' => array(
          'title' => 'Revenue',
          'module' => 'views',
          'block' => 'commerce_reports_products-chart_revenue',
        ),
        'quantity' => array(
          'title' => 'Quantity',
          'module' => 'views',
          'block' => '31eccd6666389cf554f290e91ef9848a',
        ),
      ),
    )),
    commerce_reports_sales_dashboard_block(array(
      'title' => t('Sales'),
      'switchSections' => TRUE,
      'report' => array(
        'title' => t('Sales reports'),
        'path' => 'admin/commerce/reports/sales',
      ),
      'sections' => array(
        'year' => array(
          'title' => 'Year',
          'module' => 'views',
          'block' => 'cc437fbe6b867b448dc946fd925800a3',
        ),
        'month' => array(
          'title' => 'Month',
          'module' => 'views',
          'block' => '1127e4706efe2c1eb8537a65a644e572',
        ),
        'week' => array(
          'title' => 'Week',
          'module' => 'views',
          'block' => 'd70fc459675538d56c73a9f90574211a',
        ),
      ),
    )),
  );
}

/**
 * Dummy function that should be implemented to show overview.
 */
function commerce_reports_overview_page() {
  return array(
    commerce_reports_sales_block('ff7824695a12b49a79aee7d394cbd917'), // Today
    commerce_reports_sales_block('1a260a710ed0ccc9e8175e7301e597fe'), // Yesterday
    commerce_reports_sales_block('724c01e6b3c93b66c793ff63f7402697'), // Month-to-date
    commerce_reports_sales_block('commerce_reports_sales-chart'), // Year chart
    commerce_reports_sales_overview(),
    commerce_reports_customer_statistics()
  );
}

function commerce_reports_sales_block($id) {
  $block = block_load('views', $id);
  $render = module_invoke($block->module, 'block_view', $block->delta);

  return $render['content'];
}

function commerce_reports_sales_dashboard_block($options = array()) {
  $render = array(
    '#theme_wrappers' => array('commerce_reports_dashboard_block'),
    'title' => $options['title'],
    'report' => l($options['report']['title'], $options['report']['path']),
  );
  
  $sectionLinks = array();
  $first = reset(array_keys($options['sections']));
  
  foreach ($options['sections'] as $name => $information) {
    $block = block_load($information['module'], $information['block']);
    $block_render = module_invoke($block->module, 'block_view', $block->delta);
    
    $render['sections'][$name] = $block_render;
    
    if (!empty($options['switchSections'])) {
      $link = array(
        'title' => $information['title'],
        'href' => 'admin/commerce/reports/dashboard',
        'attributes' => array(
          'class' => array(
            'switchSection'
          ),
          'data-section' => $name,
        ),
      );

      if ($name === $first) {
        //$link['attributes']['class'][] = 'active';
      }
      
      $sectionLinks[] = $link;
    }
  }
  
  $render['operations'] = theme('links', array('links' => $sectionLinks, 'attributes' => array()));
  
  if (!empty($options['switchSections'])) {
    $render['visible'] = array($first);
  } else {
    $render['visible'] = array_keys($options['sections']);
  }
  
  return $render;
}

/**
 * Generates table with sales overview data.
 */
function commerce_reports_sales_overview() {
  $month = commerce_reports_get_date('first day of this month midnight', t('Month-to-date'));
  $monthly = commerce_reports_sales_data($month['timestamp']);
  $sales = array();
  
  $daysInMonth = format_date($month['timestamp'], 'custom', 't');
  $monthlyAverage = array();
  foreach ($monthly as $currency => $row) {
    $monthlyAverage[$currency] = array(
      'count' => round($row['count'] / $daysInMonth, 2),
      'sum' => round($row['sum'] / $daysInMonth),
    );
  }
  $monthlyAverageFormatted = commerce_reports_sales_format($monthlyAverage, array('combined' => t('Daily average for @month', array('@month' => format_date($month['timestamp'], 'custom', 'F o')))));
  $sales = array_merge($sales, $monthlyAverageFormatted);
  
  $remainingDaysInMonth = $daysInMonth - format_date($month['timestamp'], 'custom', 'j');
  $monthlyProjected = array();
  foreach ($monthly as $currency => $row) {
    $monthlyProjected[$currency] = array(
      'count' => round($monthly[$currency]['count'] + $monthlyAverage[$currency]['count'] * $remainingDaysInMonth, 2),
      'sum' => round($monthly[$currency]['sum'] + $monthlyAverage[$currency]['sum'] * $remainingDaysInMonth),
    );
  }
  $monthlyProjectedFormatted = commerce_reports_sales_format($monthlyProjected, array('combined' => t('Projected totals for @month', array('@month' => format_date($month['timestamp'], 'custom', 'F o')))));
  $sales = array_merge($sales, $monthlyProjectedFormatted);
  
  return array(
    '#theme' => 'table',
    '#rows' => $sales,
    '#header' => array(t('Sales Data'), t('Number of Orders'), t('Total Revenue'), t('Average Order')),
  );
}

/**
 * Generates table with customer statistics.
 */
function commerce_reports_customer_statistics() {
  $statistics = array();
  
  $totalRevenueQuery = db_select('commerce_payment_transaction', 'cpt')
    ->fields('cpt', array('currency_code'));
  $totalRevenueQuery->addExpression('SUM(amount)', 'amount');
  $totalRevenue = $totalRevenueQuery->execute();
  
  while ($result = $totalRevenue->fetch()) {
    $statistics[] = array(t('Total revenue'), commerce_currency_format($result->amount, $result->currency_code));
  }
    
  $totalCustomers = db_select('commerce_customer_profile', 'ccp')
    ->fields('ccp', array('uid'))
    ->countQuery()
    ->execute()
    ->fetchColumn();
  
  $newCustomersToday = db_select('commerce_customer_profile', 'ccp')
    ->fields('ccp', array('uid'))
    ->condition('created', strtotime('-1 day', REQUEST_TIME), '>=')
    ->countQuery()
    ->execute()->fetchColumn();
                        
  $onlineCustomersQuery = db_select('commerce_customer_profile', 'ccp')
    ->fields('ccp', array('uid'));
  $onlineCustomersQuery->rightJoin('sessions', 's', 's.uid = ccp.uid');
  $onlineCustomers = $onlineCustomersQuery->fields('s', array('uid'))
    ->distinct()
    ->countQuery()
    ->execute()->fetchColumn();
    
  $statistics = array_merge($statistics,
    array(
      array(t('Customers total'), $totalCustomers),
      array(t('New customers today'), $newCustomersToday),
      array(t('Online customers'), $onlineCustomers),
    )
  );
  
  return array(
    '#theme' => 'table',
    '#rows' => $statistics,
    '#header' => array(array('data' => t('Statistics'), 'width' => '50%'), null),
  );
}
