<?php

/**
 * Dummy function that should be implemented to show overview.
 */
function commerce_reports_sales() {
  return commerce_reports_sales_statistics();
}

/**
 * Page callback for general statistics page.
 */
function commerce_reports_sales_statistics() {
  $totalCustomers = db_select('commerce_customer_profile', 'ccp')
    ->fields('ccp', array('uid'))
    ->countQuery()
    ->execute()
    ->fetchColumn();
  
  $newCustomersToday = db_select('commerce_customer_profile', 'ccp')
    ->fields('ccp', array('uid'))
    ->condition('created', strtotime('-1 day', REQUEST_TIME), '>=')
    ->countQuery()
    ->execute()
    ->fetchColumn();
                        
  $onlineCustomersQuery = db_select('commerce_customer_profile', 'ccp')
    ->fields('ccp', array('uid'));
  $onlineCustomersQuery->rightJoin('sessions', 's', 's.uid = ccp.uid');
  $onlineCustomers = $onlineCustomersQuery->fields('s', array('uid'))
    ->distinct()
    ->countQuery()
    ->execute()
    ->fetchColumn();
    
  $rows = array(
    array(t('Customers total'), $totalCustomers),
    array(t('New customers today'), $newCustomersToday),
    array(t('Online customers'), $onlineCustomers),
  );
    
  return array(
    '#theme' => 'table',
    '#rows' => $rows,
    '#header' => array(array('data' => t('Statistics'), 'width' => '50%'), null),
    '#empty' => t('You did not add parts to this task.'),
  );
}
