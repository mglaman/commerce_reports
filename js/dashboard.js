jQuery(document).ready(function() {
  jQuery('.commerce-reports-dashboard-block .operations a.switchSection').click(function() {
    var block = jQuery(this).parents('.commerce-reports-dashboard-block');
    var selectedSection = jQuery(this).attr('data-section');
    
    var currentHeight = block.height();
    var currentWidth = block.width();
    
    var currentlyActive = block.find('.section:visible');
    var nextActive = block.find('.section[data-section=\'' + selectedSection + '\']');
    
    if ((currentlyActive && nextActive) && (currentlyActive[0] !=nextActive[0])) {
      var chartContainer = nextActive.find('.commerce_reports-chart');
      
      if (chartContainer) {
        var chart = Drupal.commerce_reports.charts[chartContainer.attr("id")];
        
        if (chart !== undefined) {
          if (chart.resize !== undefined) {
            chart.resize(currentWidth, currentHeight - 40);
          }
        }
      }
      
      nextActive.show();
      nextActive.height('auto');
      
      currentlyActive.hide();
    }
    
    block.height(currentHeight);
    block.width(currentWidth);
    
    block.find('.operations .switchSection').removeClass('activated');
    block.find('.operations .switchSection[data-section="' + selectedSection + '"]').addClass('activated');
    
    return false;
  });
});
