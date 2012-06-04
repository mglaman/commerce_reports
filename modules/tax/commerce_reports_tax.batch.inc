<?php

function _commerce_reports_tax_create(&$context) {
  $context['message'] = t('Preparing to extract tax information from orders and generate report.');
  
  // If we are re-generating, clear the data from the previous report.
  db_query('TRUNCATE {commerce_reports_tax}');
  
  // Retrieve the different configured rates for later usage.
  $rates = array();
  foreach (commerce_tax_rates() as $rate) {
    $rates[$rate['price_component']] = $rate['name'];
  }
  
  // Create query object that will be used in the next step.
  
  // It should contain all the parameters like order status
  // and time period that the report should reflect.
  $query = new EntityFieldQuery();
  $query
    ->entityCondition('entity_type', 'commerce_order')
    ->propertyCondition('status', 'completed')
    ->entityOrderBy('entity_id', 'ASC');
  
  $context['results'] = array(
    'rates' => $rates,
    'query' => $query,
    'orders' => array()
  );
}

/**
 * Build the table of tax information.
 *
 * TODO You should be able to generate multiple reports, and it should be able to store these next to each other.
 * TODO All of these reports should be able to be generated with different parameters, like period and entity_type.
 * TODO Make actual use of the Batch API.
 */
function _commerce_reports_tax_generate(&$context) {
  if (empty($context['sandbox'])) {
    $context['sandbox']['progress'] = 0;
    $context['sandbox']['current'] = 0;
    
    $maxQuery = clone $context['results']['query'];
    $context['sandbox']['max'] = $maxQuery
      ->count()
      ->execute();
  }
  
  watchdog('commerce_reports_tax', print_r($context['sandbox'], true));
  
  $rates =& $context['results']['rates'];
  $query = clone $context['results']['query'];

  // As the order of the query is ascending, we just add an extra condition that filters all the previous orders out.
  // We also limit the query to a certain amount of orders for this iteration.
  $result = $query
    ->entityCondition('entity_id', $context['sandbox']['current'], '>')
    ->range(0, 1)
    ->execute();
    
  if ($result) {
    $orders = entity_load('commerce_order', array_keys($result['commerce_order']));

    // Iterate the orders and break each order down into its components.
    $taxes = array();
    foreach ($orders as $order) {
      $wrapper = entity_metadata_wrapper('commerce_order', $order);
      $order_data = $wrapper->commerce_order_total->data->value();

      // Add the taxes
      foreach ($order_data['components'] as $component) {
        if (array_key_exists($component['name'], $rates)) {
          // Build the new record for the tax table.
          $row = new stdClass;
          // Report_id is a dummy field at this moment. In the future we want to be able to distinguish different reports.
          $row->report_id = 1;
          $row->order_id = $wrapper->order_id->value();
          $row->tax = $rates[$component['name']];
          $row->amount = (int) $component['price']['amount'];
          
          // Write the record.
          drupal_write_record('commerce_reports_tax', $row);
        }
      }
      
      $context['results']['orders'][] = $row->order_id;
      $context['sandbox']['progress']++;
      $context['sandbox']['current'] = $row->order_id;
    }
  }
  
  // Report back to the user.
  if ($context['sandbox']['progress'] != $context['sandbox']['max']) {
    $context['finished'] = $context['sandbox']['progress'] / $context['sandbox']['max'];
  }
}

function _commerce_reports_tax_finished($success, $results, $operations) {
  watchdog('commerce_reports_tax', print_r($results['orders'], true));
}
