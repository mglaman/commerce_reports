<?php

/**
 * Implements hook_views_default_views_alter()
 */
function commerce_reports_visualization_views_default_views_alter(&$views) {
  $sales = $views['commerce_reports_sales'];
  $customers = $views['commerce_reports_customers'];
  $products = $views['commerce_reports_products'];
  
  commerce_reports_visualization($sales);
  commerce_reports_visualization($customers);
  commerce_reports_visualization($products);
}

function commerce_reports_visualization($view, $type = 'block') {
  $default = $view->display['default'];
  
  $handler = $view->new_display($type, 'Chart', 'chart');
  
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
    
    // Get rid of those nasty 
    $field['type'] = 'commerce_price_raw_amount';
  }
}

/**
 * Implements hook_views_plugins().
 */
function commerce_reports_visualization_views_plugins() {
  return array(
    'style' => array(
      'commerce_reports' => array(
        'title' => t('Commerce Reports'),
        'help' => t('Display the results as a chart.'),
        'handler' => 'commerce_reports_visualization_plugin_style',
        'uses options' => TRUE,
        'uses row plugin' => TRUE,
        'uses grouping' => FALSE,
        'type' => 'normal',
        'theme' => 'commerce_reports_visualization',
        'theme path' => drupal_get_path('module', 'commerce_reports_visualization') . '/theme',
        'theme file' => 'commerce_reports_visualization.theme.inc',
      ),
    ),
  );
}
