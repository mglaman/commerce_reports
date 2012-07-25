(function($) {

Drupal.commerce_reports = Drupal.commerce_reports || {};
Drupal.commerce_reports.charts = Drupal.commerce_reports.charts || {};

Drupal.behaviors.commerce_reports = {
  charts: [],
	attach: function(context) {
    $.each($(".commerce_reports-chart", context).not(".commerce_reports-processed"), function(idx, value) {
      var chart_id = $(value).attr("id");
      var chart = Drupal.settings.commerce_reports[chart_id];

      if (chart !== undefined) {
        switch (chart['library']) {
          case 'highcharts':
            Drupal.commerce_reports.charts[chart_id] = new Highcharts.Chart(chart.options);
            
            Drupal.commerce_reports.charts[chart_id].resize = function(width, height) {
              this.setSize(width, height, false);
            }
            break;
            
          case 'google_visualization':
            function drawChart() {
              var data = google.visualization.arrayToDataTable(chart.dataArray);
              if (data.getNumberOfRows() == 0) {
                var emptyRow = [];
                
                for (i = 0; i < data.getNumberOfColumns(); i ++) {
                  if (i > 0) {
                    data.z[i]['type'] = 'number';
                    
                    emptyRow.push(0);
                  } else {
                    emptyRow.push('');
                  }
                }
                
                data.addRow(emptyRow);
              }
              
              var chartElement = document.getElementById(chart.chart_id);
              
              switch (chart.type) {
                case 'line':
                  Drupal.commerce_reports.charts[chart_id] = new google.visualization.LineChart(chartElement);
                  break;
                  
                case 'pie':
                  Drupal.commerce_reports.charts[chart_id] = new google.visualization.PieChart(chartElement);
                  break;
                  
                case 'column':
                  Drupal.commerce_reports.charts[chart_id] = new google.visualization.ColumnChart(chartElement);
                  break;
                  
                case 'map':
                  chart.options['height'] = 600;
                  Drupal.commerce_reports.charts[chart_id] = new google.visualization.GeoMap(chartElement);
                  break;
              }
              
              if (Drupal.commerce_reports.charts[chart_id] !== undefined) {
                Drupal.commerce_reports.charts[chart_id].resize = function(width, height) {
                  if (width !== undefined) {
                    chart.options['width'] = width;
                  }
                  
                  if (height !== undefined) {
                    chart.options['height'] = height;
                  }
                  
                  this.draw(data, chart.options);
                }
            
                Drupal.commerce_reports.charts[chart_id].draw(data, chart.options);
              }
            }
            
            google.setOnLoadCallback(drawChart);
            
            break;
            
          default:
            // No idea
        }
        $(value).addClass("highcharts-processed");
      }
    })
  },
	detach: function(context) {
	}
};

})(jQuery);
