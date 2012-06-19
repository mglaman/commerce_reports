jQuery(document).ready(function() {
  jQuery('.commerce-reports-dashboard-block .operations a.switchSection').click(function() {
    var block = jQuery(this).parents('.commerce-reports-dashboard-block');
    var selectedSection = jQuery(this).attr('data-section');
    var currentHeight = block.height();
    var currentWidth = block.width();
    
    block.find('.section').each(function(i, section) {
      if (jQuery(section).attr('data-section') == selectedSection) {
        jQuery(section).show();
        var chartContainer = jQuery(section).find('.highcharts-chart');
        
        if (chartContainer.length == 1) {
          var chart = Drupal.highcharts.charts[chartContainer.attr("id")];
          var chartHeight = chartContainer.height();
          
          if (chart !== undefined) {
            chart.setSize(currentWidth, chartHeight, false);
          }
        }
        
        jQuery(section).height('auto');
      } else if (jQuery(section).is(':visible')) {
        block.height(currentHeight);
        jQuery(section).hide();
      }
    });
    
    return false;
  });
});
