(function($) {

Drupal.commerce_reports = Drupal.commerce_reports || {};
Drupal.commerce_reports.charts = Drupal.commerce_reports.charts || {};

Drupal.behaviors.commerce_reports = {
  charts: [],
	attach: function(context) {
    $.each($(".commerce_reports-chart", context).not(".commerce_reports-processed"), function(idx, value) {
      chart_id = $(value).attr("id");
      var settings = Drupal.settings.commerce_reports[chart_id];
      if (settings !== undefined) {
        
        var settings = Drupal.settings.commerce_reports[chart_id];
        if (settings !== undefined) {
          // Create the chart.
          Drupal.commerce_reports.charts[chart_id] = new Highcharts.Chart(settings);
          $(value).addClass("highcharts-processed");
        }
      }
    })
  },
	detach: function(context) {
	}
};

})(jQuery);
