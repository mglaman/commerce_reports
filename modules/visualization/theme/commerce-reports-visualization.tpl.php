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
 
  highcharts_render($chart);
?>
<div id="<?php print $chart->chart->renderTo; ?>" class="highcharts-chart"></div>
