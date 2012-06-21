<?php

/**
 * @file
 * Template file returns HTML for Commerce Reports Visualization.
 *
 * @param $chart
 *
 * @return
 *   The chart div, ready for the highchart JS to render to.
 *
 * @see theme_highcharts_chart()
 *
 * @todo is this file necessary since we have a theme function?
 */
 
  static $js_added = false;
  if (!$js_added) {
    drupal_add_js(drupal_get_path('module', 'commerce_reports_visualization') . '/js/visualization.js', array('scope' => 'footer'));
    // Flag common JS loaded status.
    $js_added = TRUE;
  }
?>
<div id="<?php print $chart_id; ?>" class="commerce_reports-chart"></div>
