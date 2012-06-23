jQuery(document).ready(function() {
  jQuery('.commerce-reports-dashboard-block .operations a.switchSection').click(function() {
    var block = jQuery(this).parents('.commerce-reports-dashboard-block');
    var selectedSection = jQuery(this).attr('data-section');
    var currentHeight = block.height();
    var currentWidth = block.width();
    
    block.find('.section').each(function(i, section) {
      if (jQuery(section).attr('data-section') == selectedSection) {
        jQuery(section).show();
        var chartContainer = jQuery(section).find('.commerce_reports-chart');
        
        if (chartContainer.length == 1) {
          var chart = Drupal.commerce_reports.charts[chartContainer.attr("id")];
          var chartHeight = chartContainer.height();
          
          if (chart !== undefined) {
            if (chart.resize !== undefined) {
              chart.resize(currentWidth, chartHeight);
            }
          }
        }
        
        jQuery(section).height('auto');
      } else if (jQuery(section).is(':visible')) {
        block.height(currentHeight);
        jQuery(section).hide();
      }
    });
    
    block.find('.operations .switchSection').removeClass('active');
    block.find('.operations .switchSection[data-section="' + selectedSection + '"]').addClass('active');
    
    return false;
  });
});
