<?php


function _commerce_reports_tax_create(&$context) {
  // Clear the database
  db_query('TRUNCATE {commerce_reports_tax}');
}

/**
 * Build the table of tax information.
 *
 * TODO You should be able to generate multiple reports, and it should be able to store these next to each other.
 * TODO All of these reports should be able to be generated with different parameters, like period and entity_type.
 * TODO Make actual use of the Batch API.
 */
function _commerce_reports_tax_generate(&$context) {
  // Key the rates
  $rates = array();
  foreach (commerce_tax_rates() as $rate) {
    $rates[$rate['price_component']] = $rate['name'];
  }

  // Load all completed orders in the system
  $query = new EntityFieldQuery;
  $result = $query
    ->entityCondition('entity_type', 'commerce_order')
    ->propertyCondition('status', 'completed')
    ->execute();
    
  if ($result) {
    $orders = entity_load('commerce_order', array_keys($result['commerce_order']));

    // Iterate the orders and break each order down into its components
    $taxes = array();
    foreach ($orders as $order) {
      $wrapper = entity_metadata_wrapper('commerce_order', $order);
      $order_data = $wrapper->commerce_order_total->data->value();

      // Add the taxes
      foreach ($order_data['components'] as $component) {
        if (array_key_exists($component['name'], $rates)) {
          // Build the new record for the tax table.
          $row = new stdClass;
          $row->order_id = $wrapper->order_id->value();
          $row->tax = $rates[$component['name']];
          $row->amount = (int) $component['price']['amount'];
          
          // Write the record
          drupal_write_record('commerce_reports_tax', $row);
        }
      }
      
    }
    
    drupal_set_message(t('Finished rebuilding the tax report table.'));
  } else {
    drupal_set_message(t("There weren't any orders to report on."));
  }
}

function _commerce_reports_tax_finished($success, $results, $operations) {
}
