<?php
/**
 * @file
 * Theme file for the visualization part of the module.
 */

/**
 * Preprocess function for commerce_reports_visualization function.
 *
 * Used by both regular calls to theme() and the commerce_reports_visualization Views handler.
 */
function template_preprocess_commerce_reports_visualization(&$vars) {
  $options = $vars['options'];
  
  if (!empty($vars['view'])) {
    $view = $vars['view'];
    
    // Fields
    foreach ($view->field as $name => $field) {
      $options['fields'][$name]['label'] = $field->options['label'];
    }
    
    // Title.
    if (empty($options['title'])) {
      $options['title'] = $view->human_name;
    }
    
    // Data
    $data = $view->style_plugin->rendered_fields;
  }
  else {
    $data = $options['data'];
  }

  if (!empty($options['xAxis']['invert'])) {
    $data = array_reverse($data);
  }
  
  $vars['chart_id'] = 'commerce_reports_' . uniqid();
  
  module_load_include('inc', 'commerce_reports', 'commerce_reports.visualization');
  $library = commerce_reports_library($options['type']);
  call_user_func($library['callback'], $vars['chart_id'], $data, $options);
  
  /**
   * Load javascript.
   */
  static $js_added = FALSE;
  if (!$js_added) {
    drupal_add_js(drupal_get_path('module', 'commerce_reports') . '/js/visualization.js', array('scope' => 'footer'));
    
    $js_added = TRUE;
  }
}

/**
 * Render a chart using Google Visualization API.
 */
function commerce_reports_gva($chart_id, $data = array(), $options = array()) {
  /**
   * Chart options
   */
  $chart_options = array(
    'title' => $options['title'],
    'width' => !empty($options['width']) ? $options['width'] : '100%',
    'height' => !empty($options['height']) ? $options['height'] : '100%',
  );
  
  switch ($options['type']) {
    case 'map':
      $chart_options['dataMode'] = !empty($options['dataMode']) ? $options['dataMode'] : 'regions';
      break;
  }
  
  /**
   * Prepare table array with data.
   */
  $table_data = array();
  
  // Add header row first.
  $header = array();
  
  if (!empty($options['xAxis']['labelField'])) {
    $header[] = $options['fields'][$options['xAxis']['labelField']]['label'];
  }
  
  foreach ($options['fields'] as $name => $column) {
    if (!empty($column['enabled'])) {
      $header[] = $column['label'];
    }
  }
  
  $table_data[] = $header;
  
  // Then add data, row per row.
  foreach ($data as $row) {
    $table_row = array();
    
    if (!empty($options['xAxis']['labelField'])) {
      $table_row[] = check_plain(strip_tags((string) $row[$options['xAxis']['labelField']]));
    }
    
    foreach ($options['fields'] as $name => $column) {
      if (!empty($column['enabled'])) {
        $value = (int) $row[$name];

        $table_row[] = $value;
      }
    }
    
    $table_data[] = $table_row;
  }
  
  $information = array(
    'library' => 'google_visualization',
    'type' => $options['type'],
    'options' => $chart_options,
    'dataArray' => $table_data,
    'chart_id' => $chart_id,
  );
  
  // Add Drupal.settings for this chart.
  drupal_add_js(array('commerce_reports' => array($chart_id => $information)), array('type' => 'setting'));
  
  /**
   * Load library
   */
  static $js_added = array();
  if (empty($js_added['file'])) {
    drupal_add_js('https://www.google.com/jsapi', 'external');
    
    $js_added['file'] = TRUE;
  }
  
  if (in_array($options['type'], array('line', 'column', 'pie')) && empty($js_added['corechart'])) {
    drupal_add_js('google.load("visualization", "1", {packages:["corechart"]});', array('type' => 'inline'));
    
    $js_added['corechart'] = TRUE;
  }
  elseif (in_array($options['type'], array('map')) && empty($js_added['geomap'])) {
    drupal_add_js('google.load("visualization", "1", {packages:["geomap"]});', array('type' => 'inline'));
    
    $js_added['geomap'] = TRUE;
  }
}

/**
 * Render a chart using Highcharts.
 */
function commerce_reports_highcharts($chart_id, $data = array(), $options = array()) {
  /**
   * Chart options.
   */
  $highchart = new stdClass();

  // Chart.
  $highchart->chart = (object) array(
    'plotBackgroundColor' => NULL,
    'plotBorderWidth' => NULL,
    'plotShadow' => FALSE,
  );
  
  // Set title
  $highchart->title->text = $options['title'];
  
  $x_axis = array();
  if (!empty($options['xAxis']['labelField'])) {
    foreach ($data as $row) {
      $x_axis[] = check_plain(strip_tags((string) $row[$options['xAxis']['labelField']]));
    }
  }
  
  if (!empty($x_axis)) {
    $highchart->xAxis = (object) array(
      'categories' => $x_axis,
    );
  }
  
  if (!empty($options['yAxis']['title'])) {
    $highchart->yAxis = (object) array(
      'title' => (object) array(
        'text' => $options['yAxis']['title'],
      ),
    );
  }
  
  // Series.
  $highchart->series = array();
  foreach ($options['fields'] as $name => $column) {
    if (!empty($column['enabled'])) {
      $serie = new stdClass();
      $serie->name = $column['label'];
      $serie->type = $options['type'];
      
      $serie->data = array();
      foreach ($data as $row) {
        $value = (int) $row[$name];
        
        if (!empty($column['enabled'])) {
          $serie->data[] = (object) array('name' => check_plain(strip_tags($row[$options['xAxis']['labelField']])), 'y' => $value);
        }
        else {
          $serie->data[] = $value;
        }
      }
      
      $highchart->series[] = $serie;
    }
  }
  
  $highchart->plotOptions->pie = (object) array(
    'allowPointSelect' => TRUE,
    'cursor' => 'pointer',
    'dataLabels' => (object) array(
      'enabled' => TRUE,
    ),
    'showInLegend' => TRUE,
  );
  $highchart->plotOptions->bar = (object) array(
    'dataLabels' => (object) array(
      'enabled' => TRUE,
    ),
  );

  $highchart->credits->enabled = FALSE;
  
  /**
   * Chart rendering
   */
  $highchart->chart->renderTo = $chart_id;
  
  $information = array(
    'library' => 'highcharts',
    'options' => $highchart,
  );
  
  // Add Drupal.settings for this chart.
  drupal_add_js(array('commerce_reports' => array($chart_id => $information)), array('type' => 'setting'));
  
  /**
   * Load library
   */
  static $js_added = FALSE;
  if (!$js_added) {
    module_load_include('module', 'libraries', 'libraries');
    $path = libraries_get_path('highcharts');
    drupal_add_js($path . '/js/highcharts.js');
    
    $js_added = TRUE;
  }
}
