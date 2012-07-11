<?php

/**
 * Generates table with sales overview data.
 */
function commerce_reports_sales() {
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
    '#header' => array(array('data' => t('Sales Data')), array('data' => t('Number of Orders')), array('data' => t('Total Revenue'))),
  );
}

/**
 * Generates table with customer statistics.
 */
function commerce_reports_customers() {
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

function commerce_reports_get_date($date, $label) {
  $timestamp = strtotime($date);
  
  $info = array(
    'timestamp' => $timestamp,
    'absolute' => format_date($timestamp, 'commerce_reports'),
    'relative' => $date,
    'label' => $label,
  );
  
  $info['combined'] = $info['label'] . ', ' . $info['absolute'];
  
  return $info;
}

function commerce_reports_sales_data($start = 0) {
  $sales = array();
  
  $query = db_select('commerce_payment_transaction', 'cpt')
    ->fields('cpt', array('currency_code'))
    ->condition('created', $start, '>=');
    
  $query->addExpression('SUM(amount)', 'sum');
  $query->addExpression('AVG(amount)', 'average');
  $query->addExpression('COUNT(*)', 'count');
  
  $result = $query->execute();
  
  while ($row = $result->fetchAssoc()) {
    $currency = $row['currency_code'];
    unset($row['currency_code']);

    if (empty($row['average'])) $row['average'] = 0;
    
    $sales[$currency] = $row;
  }
  
  return $sales;
}

function commerce_reports_sales_format($data, $dateInfo, $style = 'combined') {
  $sales = array();
  
  foreach ($data as $currency => $row) {
    $sales[] = array($dateInfo[$style], $row['count'], commerce_currency_format($row['sum'], $currency));
  }
  
  return $sales;
}

function commerce_reports_customer_map() {
  $query = db_select('field_data_commerce_customer_address', 'ca');
  $query->addField('ca', 'commerce_customer_address_country', 'country');
  $query->groupBy('country')
    ->addExpression('COUNT(*)', 'count');
  $query->condition('bundle', 'billing');
    
  $result = $query->execute();
  
  $options = array(
    'title' => 'Customer map',
    'fields' => array(
      'country' => array(
        'label' => t('Country'),
      ),
      'count' => array(
        'enabled' => TRUE,
        'label' => t('Amount'),
      ),
    ),
    'xAxis' => array(
      'labelField' => 'country',
    ),
    'data' => $result->fetchAll(PDO::FETCH_ASSOC),
    'type' => 'map',
    'height' => '400px',
  );
  
  return array(
    '#theme' => 'commerce_reports_visualization',
    '#options' => $options,
  );
}
