<?php

function template_preprocess_commerce_reports_visualization(&$vars) {
  $view = $vars['view'];
  $options = $vars['options'];
  
  $fields = $view->field;

  if (!empty($options['xAxis']['invert'])) {
    $data = array_reverse($view->style_plugin->rendered_fields);
  } else {
    $data = $view->style_plugin->rendered_fields;
  }

  // Title.
  $title = $view->human_name;
  
  $vars['chart_id'] = 'commerce_reports_' . uniqid();

  commerce_reports_highchart($vars['chart_id'], $title, $fields, $data, $options);
  //commerce_reports_gva($vars['chart_id'], $title, $fields, $data, $options);
  
  /**
   * Load javascript.
   */
  static $js_added = false;
  if (!$js_added) {
    drupal_add_js(drupal_get_path('module', 'commerce_reports') . '/js/visualization.js', array('scope' => 'footer'));
    
    $js_added = TRUE;
  }
}

function commerce_reports_gva($chart_id, $title, $fields = array(), $data = array(), $options = array()) {
  /**
   * Chart options
   */
  $chartOptions = array(
    'title' => $title,
  );
  
  /**
   * Prepare table array with data.
   */
  $dataTable = array();
  
  // Add header row first.
  $headerRow = array();
  
  if (!empty($options['xAxis']['labelField'])) {
    $field = $fields[$options['xAxis']['labelField']];
      
    $headerRow[] = $field->options['label'];
  }
  
  foreach ($options['fields'] as $name => $column) {
    if (!empty($column['enabled'])) {
      $field = $fields[$name];
      
      $headerRow[] = $field->options['label'];
    }
  }
  
  $dataTable[] = $headerRow;
  
  // Then add data, row per row.
  foreach ($data as $row) {
    $field = $fields[$name];
    $dataRow = array();
    
    if (!empty($options['xAxis']['labelField'])) {
      $dataRow[] = check_plain(strip_tags((string) $row[$options['xAxis']['labelField']]));
    }
    
    foreach ($options['fields'] as $name => $column) {
      if (!empty($column['enabled'])) {
        $value = (int) $row[$name];

        $dataRow[] = $value;
      }
    }
    
    $dataTable[] = $dataRow;
  }
  
  $information = array(
    'library' => 'google_visualization',
    'type' => $options['type'],
    'options' => $chartOptions,
    'dataArray' => $dataTable,
    'chart_id' => $chart_id,
  );
  
  // Add Drupal.settings for this chart.
  drupal_add_js(array('commerce_reports' => array($chart_id => $information)), array('type' => 'setting'));
  
  /**
   * Load library
   */
  static $js_added = FALSE;
  if (!$js_added) {
    drupal_add_js('https://www.google.com/jsapi', 'external');
    drupal_add_js('google.load("visualization", "1", {packages:["corechart"]});', array('type' => 'inline'));
    
    $js_added = TRUE;
  }
}

function commerce_reports_highchart($chart_id, $title, $fields = array(), $data = array(), $options = array()) {
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
  $highchart->title->text = $title;
  
  $xAxis = array();
  if (!empty($options['xAxis']['labelField'])) {
    foreach ($data as $row) {
      $xAxis[] = check_plain(strip_tags((string) $row[$options['xAxis']['labelField']]));
    }
  }
  
  if (!empty($xAxis)) {
    $highchart->xAxis = (object) array(
      'categories' => $xAxis,
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
      $field = $fields[$name];
      
      $serie = new StdClass();
      $serie->name = $field->options['label'];    
      $serie->type = $options['type'];
      
      $serie->data = array();
      foreach ($data as $row) {
        $value = (int) $row[$name];
        
        if (!empty($column['enabled'])) {
          $serie->data[] = (object) array('name' => check_plain(strip_tags($row[$options['xAxis']['labelField']])), 'y' => $value);
        } else {
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

  // Add highchart options object methods, which can't be passed through Drupal.settings.
  //drupal_add_js("Drupal.settings.commerce_reports.{$chart_id}.tooltip.formatter = function() {return '<b>'+ this.name +'</b>: '+ this.y;}", array('type' => 'inline'));
  
  /**
   * Load library
   */
  static $js_added = FALSE;
  if (!$js_added) {
    module_load_include('module', 'libraries', 'libraries');
    $path = libraries_get_path('highcharts');
    
    if (!empty($path)) {
      drupal_add_js($path . '/js/highcharts.js');
      
      $js_added = TRUE;
    }
  }
}
