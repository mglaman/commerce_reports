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
      'commerce_reports_handler_field_timestamp_ccyymm' => array(
        'parent' => 'views_handler_field',
      ),
      'commerce_reports_handler_field_timestamp_ccyymmdd' => array(
        'parent' => 'views_handler_field',
      ),
      'commerce_reports_handler_field_timestamp_ccyyww' => array(
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

  $data['commerce_order']['created_timestamp_ccyymm']['field'] = array(
    'title' => t('Created month timestamp (CCYYMM)'),
    'handler' => 'commerce_reports_handler_field_timestamp_ccyymm',
    'click sortable' => TRUE,
    'real field' => 'created',
    'help' => t('Display the date in CCYY-MM format, ideal for GROUP BY.'),
  );

  $data['commerce_order']['created_timestamp_ccyymmdd']['field'] = array(
    'title' => t('Created day timestamp (CCYYMMDD)'),
    'handler' => 'commerce_reports_handler_field_timestamp_ccyymmdd',
    'click sortable' => TRUE,
    'real field' => 'created',
    'help' => t('Display the date in CCYY-MM-DD format, ideal for GROUP BY.'),
  );

  $data['commerce_order']['created_timestamp_ccyyww']['field'] = array(
    'title' => t('Created week timestamp (CCYYWW)'),
    'handler' => 'commerce_reports_handler_field_timestamp_ccyyww',
    'click sortable' => TRUE,
    'real field' => 'created',
    'help' => t('Display the date in CCYY-WW format, ideal for GROUP BY.'),
  );
}
