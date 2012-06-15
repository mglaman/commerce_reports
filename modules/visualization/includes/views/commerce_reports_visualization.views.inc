<?php

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
