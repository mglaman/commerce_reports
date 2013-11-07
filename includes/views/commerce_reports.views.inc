<?php
/**
 * @file
 * Integrates Views with Commerce Reports.
 */

/**
 * Implements hook_views_data_alter().
 */
function commerce_reports_views_data_alter(&$data) {
  $data['users']['uid_commerce_orders'] = array(
    'relationship' => array(
      'title' => t('Orders'),
      'help' => t("Relate this user to his or hers orders."),
      'handler' => 'views_handler_relationship',
      'base' => 'commerce_order',
      'base field' => 'uid',
      'field' => 'uid',
      'label' => t('Order'),
    ),
  );
}

/**
 * Implements hook_views_query_alter().
 *
 * Provides basic support for multiple currencies.
 */
function commerce_reports_views_query_alter(&$view, &$query) {
  if ($view->tag == 'commerce_reports') {
    foreach ($query->fields as &$field) {
      if ($field['field'] == 'commerce_total_currency_code') {
        unset($field['function']);
      }
    }
  }
}
