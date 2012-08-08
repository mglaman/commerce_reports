<?php
/**
 * @file
 * Functions for batch processing tax reports.
 */
 
/**
 * Build the table of tax information.
 */
function _commerce_reports_tax_generate(&$context) {
  if (empty($context['sandbox'])) {
    $context['results'] = array(
      'orders' => array()
    );
    
    db_query("TRUNCATE {commerce_reports_tax}");
  
    $context['sandbox']['progress'] = 0;
    $context['sandbox']['current'] = 0;
    $context['sandbox']['max'] = db_query("SELECT COUNT(order_id) FROM {commerce_order} WHERE type = 'commerce_order' AND status IN (:order_statuses)ORDER BY order_id ASC", array(':order_statuses' => commerce_reports_tax_order_statuses()))->fetchColumn();
  }
    
  $order_ids = db_query("SELECT order_id FROM {commerce_order} WHERE type = 'commerce_order' AND status IN (:order_statuses) AND order_id > :current_order_id ORDER BY order_id ASC LIMIT 10", array(':order_statuses' => commerce_reports_tax_order_statuses(), ':current_order_id' => $context['sandbox']['current']))->fetchCol();
    
  if ($order_ids) {
    $orders = entity_load('commerce_order', $order_ids);

    // Iterate the orders and break each order down into its components.
    foreach ($orders as $order) {
      commerce_reports_tax_order_process($order);
      
      $context['results']['orders'][] = $order->order_id;
      $context['sandbox']['progress']++;
      $context['sandbox']['current'] = $order->order_id;
    }
  }
  
  // Report back to the user.
  if ($context['sandbox']['progress'] != $context['sandbox']['max']) {
    $context['finished'] = $context['sandbox']['progress'] / $context['sandbox']['max'];
  }
}

/**
 * Finishes the batch process and stores any remaining information.
 */
function _commerce_reports_tax_finished($success, $results, $operations) {
  if ($success) {
    drupal_set_message(t('Successfully generated tax report.'));
  }
  else {
    drupal_set_message(t('There was a problem whilst generating the tax report. The information might be incomplete or erroneous.'), 'error');
  }
}
