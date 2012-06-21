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
  
  // Add highcharts library JS.
  module_load_include('module', 'libraries', 'libraries');
  $path = libraries_get_path('highcharts');
  if (!empty($path)) {
    drupal_add_js($path . '/js/highcharts.js');
  }
  
  $vars['chart_id'] = 'commerce_reports_' . uniqid();

  commerce_reports_highchart($vars['chart_id'], $title, $fields, $data, $options);
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
  foreach ($data as $row) {
    if (!empty($options['xAxis']['labelField'])) {
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
    if (!empty($column['type'])) {
      $field = $fields[$name];
      
      $serie = new StdClass();
      $serie->name = $field->options['label'];    
      $serie->type = $column['type'];
      
      $serie->data = array();
      foreach ($data as $row) {
        $value = (int) $row[$name];
        
        if (!empty($column['label'])) {
          $serie->data[] = (object) array('name' => check_plain(strip_tags($row[$column['label']])), 'y' => $value);
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
  // Pass this chart ID by reference to the options object.
  $highchart->chart->renderTo = $chart_id;
  // Add Drupal.settings for this chart.
  drupal_add_js(array('commerce_reports' => array($chart_id => $highchart)), array('type' => 'setting'));

  // Add highchart options object methods, which can't be passed through Drupal.settings.
  drupal_add_js("Drupal.settings.highcharts.{$chart_id}.tooltip.formatter = function() {return '<b>'+ this.name +'</b>: '+ this.y;}", array('type' => 'inline'));
}
