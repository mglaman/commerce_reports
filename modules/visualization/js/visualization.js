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
            break;
            
          case 'google_visualization':
            console.log(chart);
            function drawChart() {
              var data = google.visualization.arrayToDataTable(chart.dataArray);
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
                  
              }
              
              if (Drupal.commerce_reports.charts[chart_id] !== undefined) {
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
