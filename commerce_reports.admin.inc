<?php

/**
 * Dummy function that should be implemented to show overview.
 */
function commerce_reports_overview_page() {
  return array(
    commerce_reports_sales_block('ff7824695a12b49a79aee7d394cbd917'), // Today
    commerce_reports_sales_block('1a260a710ed0ccc9e8175e7301e597fe'), // Yesterday
    commerce_reports_sales_block('724c01e6b3c93b66c793ff63f7402697'), // Month-to-date
    commerce_reports_sales_overview(),
    commerce_reports_customer_statistics()
  );
}

function commerce_reports_sales_block($id) {
  $block = block_load('views', $id);
  $array = module_invoke($block->module, 'block_view', $block->delta);
  
  $content = $array['content'];
  
  return $content;
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
