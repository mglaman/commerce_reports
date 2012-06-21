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
?>
<div id="<?php print $chart_id; ?>" class="commerce_reports-chart"></div>
