<?php
/**
 * @file
 * The helper functions for the visualization part of the module.
 */

/**
 * Returns the name of the library that should be used to render a chart.
 *
 * Optionally one can pass a chart type to get the best library available for that type.
 */
function commerce_reports_library($type = FALSE) {
  $libraries = commerce_reports_visualization();
  $library = variable_get('commerce_reports_visualization', 'gva');
  
  if (!empty($libraries[$library]) && !empty($libraries[$library]['enabled']) && 
    !empty($libraries[$library]['callback']) && (!empty($type) && in_array($type, $libraries[$library]['types']))) {
    return $libraries[$library];
  }
  else {
    return reset($libraries);
  }
}

/**
 * Returns an associative array with all known charting libraries.
 */
function commerce_reports_visualization() {
  static $info;
  
  if (empty($cache)) {
    $info = array();
    
    $info['gva'] = array(
      'title' => t('Google Visualization API'),
      'enabled' => TRUE,
      'callback' => 'commerce_reports_gva',
      'types' => array('line', 'column', 'pie', 'map'),
    );
    
    $info['highcharts'] = array(
      'title' => t('Highcharts'),
      'enabled' => FALSE,
      'callback' => 'commerce_reports_highcharts',
      'types' => array('line', 'column', 'pie'),
    );
    
    if (module_exists('libraries')) {
      module_load_include('module', 'libraries', 'libraries');
      $path = libraries_get_path('highcharts');
      
      $info['highcharts']['enabled'] = !empty($path);
    }
  }
  
  return $info;
}

