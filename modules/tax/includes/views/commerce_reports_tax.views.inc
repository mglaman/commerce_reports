<?php

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
  
  $data['commerce_reports_tax']['table']['base'] = array(
    'field' => 'report_id',
    'title' => t('Commerce Reports Tax Rate'),
    'help' => t('The tax rates applied on the system when the report was generated.'),
    'access query tag' => 'commerce_reports_access',
  );
  
  // Expose the Report ID.
  $data['commerce_reports_tax_rate']['report_id'] = array(
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
  
  // Expose the administrative title of the tax rate.
  $data['commerce_reports_tax_rate']['rate'] = array(
    'title' => t('Rate'),
    'help' => t('The percentage used to calculate the tax.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
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
   * commerce_reports_tax
   * Cached information about the tax collected on orders.
   */
  // Base information.
  $data['commerce_reports_tax']['table']['group']  = t('Commerce Reports Tax');

  $data['commerce_reports_tax']['table']['base'] = array(
    'field' => 'report_id',
    'title' => t('Commerce Reports Tax'),
    'help' => t('The cached tax breakdown of a Commerce Order.'),
    'access query tag' => 'commerce_reports_access',
  );
  //$data['commerce_reports_tax']['table']['entity type'] = 'commerce_order';
  
  // Expose the Report ID.
  $data['commerce_reports_tax']['report_id'] = array(
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

  // Expose the Order ID.
  $data['commerce_reports_tax']['order_id'] = array(
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

  // Expose the tax rate.
  $data['commerce_reports_tax']['tax'] = array(
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
    'relationship' => array(
      'handler' => 'views_handler_relationship',
      'base' => 'commerce_reports_tax_rate',
      'base field' => 'name',
      'label' => t('Cached tax rate'),
    ),
  );
  
  $data['commerce_reports_tax']['taxable'] = array(
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

  $data['commerce_reports_tax']['taxed'] = array(
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

  return $data;
}
