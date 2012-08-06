<?php
/**
 * @file
 * Views integration.
 */
 
/**
 * Implements hook_views_handlers().
 */
function commerce_reports_tax_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'commerce_reports_tax') . '/includes/views',
    ),
    'handlers' => array(
      'commerce_reports_tax_handler_field_operations' => array(
        'parent' => 'views_handler_field',
      ),
    ),
  );
}

/**
 * Implements hook_views_data()
 */
function commerce_reports_tax_views_data() {
  $data = array();
  
  /**
   * commerce_reports_tax_rate
   * Cached information about the different cache types.
   */
  $data['commerce_reports_tax_rate']['table']['group']  = t('Commerce Reports Tax Rate');
  $data['commerce_reports_tax_rate']['table']['join'] = array(
    'commerce_reports_tax_rate_aggregate' => array (
      'left_field' => 'report_id',
      'field' => 'report_id',
      'extra' => 'commerce_reports_tax_rate.name = commerce_reports_tax_rate_aggregate.tax',
    ),
    'commerce_reports_tax_rate_orders' => array (
      'left_field' => 'report_id',
      'field' => 'report_id',
      'extra' => 'commerce_reports_tax_rate.name = commerce_reports_tax_rate_orders.tax',
    ),
  );
  
  // Expose the tax rate.
  $data['commerce_reports_tax_rate']['name'] = array(
    'title' => t('Name'),
    'help' => t('The machine-name of the tax rate.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  
  // Expose the tax rate.
  $data['commerce_reports_tax_rate']['type'] = array(
    'title' => t('Type'),
    'help' => t('The administrative title of the type of the tax rate.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  
  // Expose the administrative title of the tax rate.
  $data['commerce_reports_tax_rate']['title'] = array(
    'title' => t('Title'),
    'help' => t('The administrative title of the tax rate.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  
  // Expose the percentage used to calculate the tax.
  $data['commerce_reports_tax_rate']['rate'] = array(
    'title' => t('Rate'),
    'help' => t('The percentage used to calculate the tax.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'float' => TRUE,
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_numeric',
    ),
  );
  
  /**
   * commerce_reports_tax_rate_aggregate
   * Cached information about the tax collected on orders.
   */
  $data['commerce_reports_tax_rate_aggregate']['table']['group']  = t('Commerce Reports Tax Aggregate');

  $data['commerce_reports_tax_rate_aggregate']['table']['base'] = array(
    'field' => 'report_id',
    'title' => t('Commerce Reports Aggregate Tax Rate'),
    'help' => t('The aggregated results of all collected taxes on all orders.'),
    'access query tag' => 'commerce_reports_access',
  );
  
  // Expose the Report ID.
  $data['commerce_reports_tax_rate_aggregate']['report_id'] = array(
    'title' => t('Report ID'),
    'help' => t('The unique internal identifier of the report.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
  );

  // Expose the tax rate.
  $data['commerce_reports_tax_rate_aggregate']['tax'] = array(
    'title' => t('Tax rate'),
    'help' => t('The machine-name of the tax rate.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  
  // Expose the taxable amount.
  $data['commerce_reports_tax_rate_aggregate']['taxable'] = array(
    'title' => t('Taxable amount'),
    'help' => t('The taxable amount of the order.'),
    'field' => array(
      'handler' => 'commerce_payment_handler_field_amount',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  // Expose the taxed amount.
  $data['commerce_reports_tax_rate_aggregate']['taxed'] = array(
    'title' => t('Taxed'),
    'help' => t('The amount of tax on the order of a specific type.'),
    'field' => array(
      'handler' => 'commerce_payment_handler_field_amount',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  
  $data['commerce_reports_tax_rate_aggregate']['operations'] = array(
    'title' => t('Operations'),
    'help' => t('Operations for tax rate aggregates.'),
    'field' => array(
      'handler' => 'commerce_reports_tax_handler_field_operations',
    ),
  );
  
  /**
   * commerce_reports_tax_rate_orders
   * Cached information about the tax collected on orders.
   */
  // Base information.
  $data['commerce_reports_tax_rate_orders']['table']['group']  = t('Commerce Reports Tax Order');

  $data['commerce_reports_tax_rate_orders']['table']['base'] = array(
    'field' => 'report_id',
    'title' => t('Commerce Reports Order Tax Rate'),
    'help' => t('The results of all collected taxes on all orders.'),
    'access query tag' => 'commerce_reports_access',
  );
  
  // Expose the Report ID.
  $data['commerce_reports_tax_rate_orders']['report_id'] = array(
    'title' => t('ID'),
    'help' => t('The unique internal identifier of the report.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
  );

  // Expose the tax rate.
  $data['commerce_reports_tax_rate_orders']['tax'] = array(
    'title' => t('Tax rate'),
    'help' => t('The machine-name of the tax rate.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  
  // Expose the Order ID.
  $data['commerce_reports_tax_rate_orders']['order_id'] = array(
    'title' => t('Order ID', array(), array('context' => 'a drupal commerce order')),
    'help' => t('The unique internal identifier of the order.'),
    'field' => array(
      'handler' => 'commerce_order_handler_field_order',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'commerce_order_handler_argument_order_order_id',
      'name field' => 'order_number',
      'numeric' => TRUE,
      'validate type' => 'order_id',
    ),
    'relationship' => array(
      'handler' => 'views_handler_relationship',
      'base' => 'commerce_order',
      'field' => 'order_id',
      'label' => t('Order', array(), array('context' => 'a drupal commerce order')),
    ),
  );
  
  $data['commerce_reports_tax_rate_orders']['taxable'] = array(
    'title' => t('Taxable amount'),
    'help' => t('The taxable amount of the order.'),
    'field' => array(
      'handler' => 'commerce_payment_handler_field_amount',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  $data['commerce_reports_tax_rate_orders']['taxed'] = array(
    'title' => t('Taxed'),
    'help' => t('The amount of tax on the order of a specific type.'),
    'field' => array(
      'handler' => 'commerce_payment_handler_field_amount',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  
  $data['commerce_reports_tax_rate_orders']['empty_text'] = array(
    'title' => t('Empty text'),
    'help' => t('Displays an appropriate empty text message for reports.'),
    'area' => array(
      'handler' => 'commerce_reports_tax_handler_area_empty_text',
    ),
  );

  return $data;
}

/**
 * Implements hook_views_post_render().
 */
function commerce_reports_tax_views_post_render(&$view, &$output, &$cache) {
  if ($view->tag == 'commerce_reports_tax') {
    $breadcrumb = array(
      l(t('Home'), '<front>'),
      l(t('Administration'), 'admin'),
      l(t('Store'), 'admin/commerce'),
      l(t('Reports'), 'admin/commerce/reports'),
      l(t('Tax reports'), 'admin/commerce/reports/tax'),
    );
    
    if (($view->name == 'commerce_reports_tax_details') && (!empty($view->args[0]))) {
      $breadcrumb[] = l(t('Overview'), 'admin/commerce/reports/tax/' . $view->args[0]);
    }
    
    drupal_set_breadcrumb($breadcrumb);
  }
}
