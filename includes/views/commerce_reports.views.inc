<?php

/**
 * Implements hook_views_handlers().
 */
function commerce_reports_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'commerce_reports') . '/includes/views',
    ),
    'handlers' => array(
      'commerce_reports_handler_field_productquantity' => array(
        'parent' => 'views_handler_field',
      ),
    ),
  );
}


/**
 * Implements hook_views_data().
 */
function commerce_reports_views_data_alter(&$data) {
  $data['commerce_order']['productquantity']['field'] = array(
    'handler' => 'commerce_reports_handler_field_productquantity',
    'title' => t('Product quantity'),
    'help' => t('Display the quantity of products in this order.'),
    'click sortable' => TRUE,
  );
}
