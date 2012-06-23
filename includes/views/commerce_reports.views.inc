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
      'commerce_reports_handler_field_date' => array(
        'parent' => 'views_handler_field',
      ),
    ),
  );
}

/**
 * Implements hook_views_plugins().
 */
function commerce_reports_views_plugins() {
  return array(
    'style' => array(
      'commerce_reports' => array(
        'title' => t('Commerce Reports'),
        'help' => t('Display the results as a chart.'),
        'handler' => 'commerce_reports_plugin_style_visualization',
        'uses options' => TRUE,
        'uses row plugin' => TRUE,
        'uses grouping' => FALSE,
        'type' => 'normal',
        'theme' => 'commerce_reports_visualization',
        'theme path' => drupal_get_path('module', 'commerce_reports') . '/theme',
        'theme file' => 'commerce_reports_visualization.theme.inc',
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
  
  $data['commerce_order']['sales_data'] = array(
    'title' => t('Sales data'),
    'help' => t('Field containing the date of the order, with the ability to filter on granularity.'),
    'real field' => 'created',
    'field' => array(
      'handler' => 'commerce_reports_handler_field_commerce_order_created',
      'click sortable' => TRUE,
    ),
  );
  
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

function commerce_reports_visualization_display($view, $name, $title, $type = 'block', $baseDisplay = 'default') {
  // Retrieve our base display
  $default = $view->display[$baseDisplay];
  
  // Add the display
  $handler = $view->new_display($type, $title, $name);
  
  // Disable the pager (show all items)
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  
  // Setup the custom style plugin
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'commerce_reports';
  
  // Set some general settings concerning fields
  $handler->display->display_options['defaults']['fields'] = FALSE;
  $handler->display->display_options['fields'] = $default->display_options['fields'];
  $handler->display->display_options['style_options']['info'] = $default->display_options['style_options']['info'];
  
  foreach ($handler->display->display_options['style_options']['info'] as &$field) {
    $field['separator'] = '';
  }
  
  foreach ($handler->display->display_options['fields'] as $name => &$field) {
    // All fields that are passed to the charting module should have at least a value.
    $field['hide_alter_empty'] = 1;
    $field['empty'] = '0';
    
    // Get rid of those nasty currency fields. We need raw data!
    if ((!empty($field['type'])) && strstr($field['type'], 'commerce_price')) {
      $field['type'] = 'commerce_reports_visualization';
    }
  }
  
  return $handler;
}

function commerce_reports_datetime_form($date) {
  $dt = new DateTime();
  $timestamp = mktime(0, 0, 0, $date['month'], $date['day'], $date['year']);
  
  $dt->setTimestamp($timestamp);
  
  return $dt;
}

