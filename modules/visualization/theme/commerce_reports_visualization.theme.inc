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
  
  $highchart = new stdClass();

  // Chart.
  $highchart->chart = (object) array(
    'plotBackgroundColor' => NULL,
    'plotBorderWidth' => NULL,
    'plotShadow' => FALSE,
  );

  // Title.
  $highchart->title->text = $view->human_name;

  // Tooltip.
  // Normally formatter is a function callback. For now we'll make it a string.
  $highchart->tooltip->formatter = "function() {return '<b>'+ this.name +'</b>: '+ this.y;}";
  
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
        
        //if (!empty($column['label']) && ($serie->type == 'pie')) {
          $serie->data[] = (object) array('name' => check_plain(strip_tags($row[$column['label']])), 'y' => $value);
        //} else {
        //  $serie->data[] = $value;
        //}
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

  $vars['chart'] = $highchart;
}
