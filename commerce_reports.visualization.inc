<?php

function commerce_reports_library($type = FALSE) {
  $libraries = commerce_reports_visualization();
  $library = variable_get('commerce_reports_visualization', 'gva');
  
  if (!empty($libraries[$library]) && !empty($libraries[$library]['enabled']) && !empty($libraries[$library]['callback'])) {
    return $libraries[$library];
  } else {
    return reset($libraries);
  }
}

function commerce_reports_visualization() {
  static $info;
  
  if (empty($cache)) {
    $info = array();
    
    $info['gva'] = array(
      'title' => t('Google Visualization API'),
      'enabled' => TRUE,
      'callback' => 'commerce_reports_gva',
    );
    
    $info['highcharts'] = array(
      'title' => t('Highcharts'),
      'enabled' => FALSE,
      'callback' => 'commerce_reports_highcharts',
    );
    
    if (module_exists('libraries')) {
      module_load_include('module', 'libraries', 'libraries');
      $path = libraries_get_path('highcharts');
      
      $info['highcharts']['enabled'] = !empty($path);
    }
  }
  
  return $info;
}

