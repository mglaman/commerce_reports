<?php

/**
 * Views for commerce orders for report displays.
 */

/**
 * Implements hook_views_default_views().
 *
 * Includes:
 * - Sales report
 * - Top selling
 * - Payment gateway
 */
function commerce_reports_views_default_views() {

  /**
   * Commerce reports: Top selling
   */
  $view = new view;
  $view->name = 'top_selling';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'commerce_line_item';
  $view->human_name = 'Top selling';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
  
  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Top selling';
  $handler->display->display_options['group_by'] = TRUE;
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(
    3 => '3',
  );
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'table';
  /* Relationship: Commerce Line Item: Order ID */
  $handler->display->display_options['relationships']['order_id']['id'] = 'order_id';
  $handler->display->display_options['relationships']['order_id']['table'] = 'commerce_line_item';
  $handler->display->display_options['relationships']['order_id']['field'] = 'order_id';
  $handler->display->display_options['relationships']['order_id']['required'] = 1;
  /* Relationship: Commerce Line item: Referenced product */
  $handler->display->display_options['relationships']['commerce_product_product_id']['id'] = 'commerce_product_product_id';
  $handler->display->display_options['relationships']['commerce_product_product_id']['table'] = 'field_data_commerce_product';
  $handler->display->display_options['relationships']['commerce_product_product_id']['field'] = 'commerce_product_product_id';
  $handler->display->display_options['relationships']['commerce_product_product_id']['required'] = 1;
  /* Field: Commerce Product: SKU */
  $handler->display->display_options['fields']['sku']['id'] = 'sku';
  $handler->display->display_options['fields']['sku']['table'] = 'commerce_product';
  $handler->display->display_options['fields']['sku']['field'] = 'sku';
  $handler->display->display_options['fields']['sku']['relationship'] = 'commerce_product_product_id';
  $handler->display->display_options['fields']['sku']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['sku']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['sku']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['sku']['alter']['external'] = 0;
  $handler->display->display_options['fields']['sku']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['sku']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['sku']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['sku']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['sku']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['sku']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['sku']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['sku']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['sku']['alter']['html'] = 0;
  $handler->display->display_options['fields']['sku']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['sku']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['sku']['hide_empty'] = 0;
  $handler->display->display_options['fields']['sku']['empty_zero'] = 0;
  $handler->display->display_options['fields']['sku']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['sku']['link_to_product'] = 0;
  /* Field: COUNT(Commerce Line Item: Line item ID) */
  $handler->display->display_options['fields']['line_item_id']['id'] = 'line_item_id';
  $handler->display->display_options['fields']['line_item_id']['table'] = 'commerce_line_item';
  $handler->display->display_options['fields']['line_item_id']['field'] = 'line_item_id';
  $handler->display->display_options['fields']['line_item_id']['group_type'] = 'count';
  $handler->display->display_options['fields']['line_item_id']['label'] = 'Sold';
  $handler->display->display_options['fields']['line_item_id']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['line_item_id']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['line_item_id']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['line_item_id']['alter']['external'] = 0;
  $handler->display->display_options['fields']['line_item_id']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['line_item_id']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['line_item_id']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['line_item_id']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['line_item_id']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['line_item_id']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['line_item_id']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['line_item_id']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['line_item_id']['alter']['html'] = 0;
  $handler->display->display_options['fields']['line_item_id']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['line_item_id']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['line_item_id']['hide_empty'] = 0;
  $handler->display->display_options['fields']['line_item_id']['empty_zero'] = 0;
  $handler->display->display_options['fields']['line_item_id']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['line_item_id']['format_plural'] = 0;
  /* Sort criterion: COUNT(Commerce Line Item: Line item ID) */
  $handler->display->display_options['sorts']['line_item_id']['id'] = 'line_item_id';
  $handler->display->display_options['sorts']['line_item_id']['table'] = 'commerce_line_item';
  $handler->display->display_options['sorts']['line_item_id']['field'] = 'line_item_id';
  $handler->display->display_options['sorts']['line_item_id']['group_type'] = 'count';
  $handler->display->display_options['sorts']['line_item_id']['order'] = 'DESC';
  /* Filter criterion: Commerce Line Item: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'commerce_line_item';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'product' => 'product',
  );
  /* Filter criterion: Commerce Order: Order state */
  $handler->display->display_options['filters']['state']['id'] = 'state';
  $handler->display->display_options['filters']['state']['table'] = 'commerce_order';
  $handler->display->display_options['filters']['state']['field'] = 'state';
  $handler->display->display_options['filters']['state']['relationship'] = 'order_id';
  $handler->display->display_options['filters']['state']['value'] = array(
    'pending' => 'pending',
    'completed' => 'completed',
  );
  
  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'admin/commerce/reports/topselling';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Top selling';
  $handler->display->display_options['menu']['description'] = 'View top selling products.';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  
  $views[$view->name] = $view;


  /**
   * Commerce reports: Gateways
   */
  $view = new view;
  $view->name = 'commerce_reports_gateways';
  $view->description = 'View payment gateway usage breakdown.';
  $view->tag = 'commerce_reports';
  $view->base_table = 'commerce_payment_transaction';
  $view->human_name = 'Payment gateway usage';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Payment gateways';
  $handler->display->display_options['group_by'] = TRUE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'table';
  /* Field: COUNT(Commerce Payment Transaction: Transaction ID) */
  $handler->display->display_options['fields']['transaction_id']['id'] = 'transaction_id';
  $handler->display->display_options['fields']['transaction_id']['table'] = 'commerce_payment_transaction';
  $handler->display->display_options['fields']['transaction_id']['field'] = 'transaction_id';
  $handler->display->display_options['fields']['transaction_id']['group_type'] = 'count';
  /* Field: Commerce Payment Transaction: Payment method */
  $handler->display->display_options['fields']['payment_method']['id'] = 'payment_method';
  $handler->display->display_options['fields']['payment_method']['table'] = 'commerce_payment_transaction';
  $handler->display->display_options['fields']['payment_method']['field'] = 'payment_method';
  $handler->display->display_options['fields']['payment_method']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['payment_method']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['payment_method']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['payment_method']['alter']['external'] = 0;
  $handler->display->display_options['fields']['payment_method']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['payment_method']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['payment_method']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['payment_method']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['payment_method']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['payment_method']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['payment_method']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['payment_method']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['payment_method']['alter']['html'] = 0;
  $handler->display->display_options['fields']['payment_method']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['payment_method']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['payment_method']['hide_empty'] = 0;
  $handler->display->display_options['fields']['payment_method']['empty_zero'] = 0;
  $handler->display->display_options['fields']['payment_method']['hide_alter_empty'] = 1;
  /* Filter criterion: Commerce Payment Transaction: Status */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'commerce_payment_transaction';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = array(
    'success' => 'success',
  );
  
  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'admin/commerce/reports/payment-gateways';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Payment gateways';
  $handler->display->display_options['menu']['description'] = 'View breakdown of payment gateway usage.';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;

  $views[$view->name] = $view;


  /**
   * Commerce Reports: Sales totals
   */
  $view = new view;
  $view->name = 'commerce_reports_salestotals';
  $view->description = 'View commerce daily and monthly sales totals.';
  $view->tag = 'commerce_reports';
  $view->base_table = 'commerce_order';
  $view->human_name = 'Sales totals';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
  
  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Sales totals';
  $handler->display->display_options['group_by'] = TRUE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'access commerce reports';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'order_id' => 'order_id',
    'line_item_label' => 'line_item_label',
    'quantity' => 'quantity',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'order_id' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'line_item_label' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'quantity' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['override'] = 1;
  $handler->display->display_options['style_options']['sticky'] = 0;
  $handler->display->display_options['style_options']['empty_table'] = 0;
  /* Relationship: Commerce Order: Referenced line item */
  $handler->display->display_options['relationships']['commerce_line_items_line_item_id']['id'] = 'commerce_line_items_line_item_id';
  $handler->display->display_options['relationships']['commerce_line_items_line_item_id']['table'] = 'field_data_commerce_line_items';
  $handler->display->display_options['relationships']['commerce_line_items_line_item_id']['field'] = 'commerce_line_items_line_item_id';
  $handler->display->display_options['relationships']['commerce_line_items_line_item_id']['required'] = 0;
  /* Field: Commerce Order: Created day timestamp (CCYYMMDD) */
  $handler->display->display_options['fields']['created_timestamp_ccyymmdd']['id'] = 'created_timestamp_ccyymmdd';
  $handler->display->display_options['fields']['created_timestamp_ccyymmdd']['table'] = 'commerce_order';
  $handler->display->display_options['fields']['created_timestamp_ccyymmdd']['field'] = 'created_timestamp_ccyymmdd';
  $handler->display->display_options['fields']['created_timestamp_ccyymmdd']['label'] = 'Date';
  $handler->display->display_options['fields']['created_timestamp_ccyymmdd']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['created_timestamp_ccyymmdd']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['created_timestamp_ccyymmdd']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['created_timestamp_ccyymmdd']['alter']['external'] = 0;
  $handler->display->display_options['fields']['created_timestamp_ccyymmdd']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['created_timestamp_ccyymmdd']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['created_timestamp_ccyymmdd']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['created_timestamp_ccyymmdd']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['created_timestamp_ccyymmdd']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['created_timestamp_ccyymmdd']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['created_timestamp_ccyymmdd']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['created_timestamp_ccyymmdd']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['created_timestamp_ccyymmdd']['alter']['html'] = 0;
  $handler->display->display_options['fields']['created_timestamp_ccyymmdd']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['created_timestamp_ccyymmdd']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['created_timestamp_ccyymmdd']['hide_empty'] = 0;
  $handler->display->display_options['fields']['created_timestamp_ccyymmdd']['empty_zero'] = 0;
  $handler->display->display_options['fields']['created_timestamp_ccyymmdd']['hide_alter_empty'] = 1;
  /* Field: SUM(Commerce Line Item: Quantity) */
  $handler->display->display_options['fields']['quantity']['id'] = 'quantity';
  $handler->display->display_options['fields']['quantity']['table'] = 'commerce_line_item';
  $handler->display->display_options['fields']['quantity']['field'] = 'quantity';
  $handler->display->display_options['fields']['quantity']['relationship'] = 'commerce_line_items_line_item_id';
  $handler->display->display_options['fields']['quantity']['group_type'] = 'sum';
  $handler->display->display_options['fields']['quantity']['label'] = 'Products sold';
  $handler->display->display_options['fields']['quantity']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['quantity']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['quantity']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['quantity']['alter']['external'] = 0;
  $handler->display->display_options['fields']['quantity']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['quantity']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['quantity']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['quantity']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['quantity']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['quantity']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['quantity']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['quantity']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['quantity']['alter']['html'] = 0;
  $handler->display->display_options['fields']['quantity']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['quantity']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['quantity']['hide_empty'] = 0;
  $handler->display->display_options['fields']['quantity']['empty_zero'] = 0;
  $handler->display->display_options['fields']['quantity']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['quantity']['set_precision'] = 1;
  $handler->display->display_options['fields']['quantity']['precision'] = '0';
  $handler->display->display_options['fields']['quantity']['format_plural'] = 0;
  /* Field: SUM(Commerce Line item: Total) */
  $handler->display->display_options['fields']['commerce_total']['id'] = 'commerce_total';
  $handler->display->display_options['fields']['commerce_total']['table'] = 'field_data_commerce_total';
  $handler->display->display_options['fields']['commerce_total']['field'] = 'commerce_total';
  $handler->display->display_options['fields']['commerce_total']['relationship'] = 'commerce_line_items_line_item_id';
  $handler->display->display_options['fields']['commerce_total']['group_type'] = 'sum';
  $handler->display->display_options['fields']['commerce_total']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['commerce_total']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['commerce_total']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['commerce_total']['alter']['external'] = 0;
  $handler->display->display_options['fields']['commerce_total']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['commerce_total']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['commerce_total']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['commerce_total']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['commerce_total']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['commerce_total']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['commerce_total']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['commerce_total']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['commerce_total']['alter']['html'] = 0;
  $handler->display->display_options['fields']['commerce_total']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['commerce_total']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['commerce_total']['hide_empty'] = 0;
  $handler->display->display_options['fields']['commerce_total']['empty_zero'] = 0;
  $handler->display->display_options['fields']['commerce_total']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['commerce_total']['click_sort_column'] = 'amount';
  $handler->display->display_options['fields']['commerce_total']['type'] = 'commerce_price_formatted_amount';
  $handler->display->display_options['fields']['commerce_total']['settings'] = array(
    'calculation' => FALSE,
  );
  $handler->display->display_options['fields']['commerce_total']['group_column'] = 'amount';
  $handler->display->display_options['fields']['commerce_total']['group_columns'] = array(
    'currency_code' => 'currency_code',
  );
  $handler->display->display_options['fields']['commerce_total']['field_api_classes'] = 0;
  /* Sort criterion: Commerce Order: Created date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'commerce_order';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  $handler->display->display_options['sorts']['created']['granularity'] = 'day';
  /* Filter criterion: Commerce Order: Order state */
  $handler->display->display_options['filters']['state']['id'] = 'state';
  $handler->display->display_options['filters']['state']['table'] = 'commerce_order';
  $handler->display->display_options['filters']['state']['field'] = 'state';
  $handler->display->display_options['filters']['state']['value'] = array(
    'pending' => 'pending',
    'completed' => 'completed',
  );
  /* Filter criterion: Commerce Line Item: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'commerce_line_item';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['relationship'] = 'commerce_line_items_line_item_id';
  $handler->display->display_options['filters']['type']['value'] = array(
    'product' => 'product',
  );
  
  /* Display: Daily */
  $handler = $view->new_display('page', 'Daily', 'daily');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Daily sales summary';
  $handler->display->display_options['path'] = 'admin/commerce/reports/salestotals/day';
  $handler->display->display_options['menu']['type'] = 'default tab';
  $handler->display->display_options['menu']['title'] = 'Daily sales';
  $handler->display->display_options['menu']['description'] = 'View daily sales summary.';
  $handler->display->display_options['menu']['weight'] = '1';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['tab_options']['type'] = 'normal';
  $handler->display->display_options['tab_options']['title'] = 'Sales totals';
  $handler->display->display_options['tab_options']['description'] = 'View daily and monthly sales totals.';
  $handler->display->display_options['tab_options']['weight'] = '0';
  $handler->display->display_options['tab_options']['name'] = 'management';
  
  /* Display: Monthly */
  $handler = $view->new_display('page', 'Monthly', 'monthly');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Monthly sales summary';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Commerce Order: Created month timestamp (CCYYMM) */
  $handler->display->display_options['fields']['created_timestamp_ccyymm']['id'] = 'created_timestamp_ccyymm';
  $handler->display->display_options['fields']['created_timestamp_ccyymm']['table'] = 'commerce_order';
  $handler->display->display_options['fields']['created_timestamp_ccyymm']['field'] = 'created_timestamp_ccyymm';
  $handler->display->display_options['fields']['created_timestamp_ccyymm']['label'] = 'Month';
  $handler->display->display_options['fields']['created_timestamp_ccyymm']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['created_timestamp_ccyymm']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['created_timestamp_ccyymm']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['created_timestamp_ccyymm']['alter']['external'] = 0;
  $handler->display->display_options['fields']['created_timestamp_ccyymm']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['created_timestamp_ccyymm']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['created_timestamp_ccyymm']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['created_timestamp_ccyymm']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['created_timestamp_ccyymm']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['created_timestamp_ccyymm']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['created_timestamp_ccyymm']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['created_timestamp_ccyymm']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['created_timestamp_ccyymm']['alter']['html'] = 0;
  $handler->display->display_options['fields']['created_timestamp_ccyymm']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['created_timestamp_ccyymm']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['created_timestamp_ccyymm']['hide_empty'] = 0;
  $handler->display->display_options['fields']['created_timestamp_ccyymm']['empty_zero'] = 0;
  $handler->display->display_options['fields']['created_timestamp_ccyymm']['hide_alter_empty'] = 1;
  /* Field: SUM(Commerce Line Item: Quantity) */
  $handler->display->display_options['fields']['quantity']['id'] = 'quantity';
  $handler->display->display_options['fields']['quantity']['table'] = 'commerce_line_item';
  $handler->display->display_options['fields']['quantity']['field'] = 'quantity';
  $handler->display->display_options['fields']['quantity']['relationship'] = 'commerce_line_items_line_item_id';
  $handler->display->display_options['fields']['quantity']['group_type'] = 'sum';
  $handler->display->display_options['fields']['quantity']['label'] = 'Products sold';
  $handler->display->display_options['fields']['quantity']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['quantity']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['quantity']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['quantity']['alter']['external'] = 0;
  $handler->display->display_options['fields']['quantity']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['quantity']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['quantity']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['quantity']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['quantity']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['quantity']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['quantity']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['quantity']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['quantity']['alter']['html'] = 0;
  $handler->display->display_options['fields']['quantity']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['quantity']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['quantity']['hide_empty'] = 0;
  $handler->display->display_options['fields']['quantity']['empty_zero'] = 0;
  $handler->display->display_options['fields']['quantity']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['quantity']['set_precision'] = 1;
  $handler->display->display_options['fields']['quantity']['precision'] = '0';
  $handler->display->display_options['fields']['quantity']['format_plural'] = 0;
  /* Field: SUM(Commerce Line item: Total) */
  $handler->display->display_options['fields']['commerce_total']['id'] = 'commerce_total';
  $handler->display->display_options['fields']['commerce_total']['table'] = 'field_data_commerce_total';
  $handler->display->display_options['fields']['commerce_total']['field'] = 'commerce_total';
  $handler->display->display_options['fields']['commerce_total']['relationship'] = 'commerce_line_items_line_item_id';
  $handler->display->display_options['fields']['commerce_total']['group_type'] = 'sum';
  $handler->display->display_options['fields']['commerce_total']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['commerce_total']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['commerce_total']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['commerce_total']['alter']['external'] = 0;
  $handler->display->display_options['fields']['commerce_total']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['commerce_total']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['commerce_total']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['commerce_total']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['commerce_total']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['commerce_total']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['commerce_total']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['commerce_total']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['commerce_total']['alter']['html'] = 0;
  $handler->display->display_options['fields']['commerce_total']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['commerce_total']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['commerce_total']['hide_empty'] = 0;
  $handler->display->display_options['fields']['commerce_total']['empty_zero'] = 0;
  $handler->display->display_options['fields']['commerce_total']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['commerce_total']['click_sort_column'] = 'amount';
  $handler->display->display_options['fields']['commerce_total']['type'] = 'commerce_price_formatted_amount';
  $handler->display->display_options['fields']['commerce_total']['settings'] = array(
    'calculation' => FALSE,
  );
  $handler->display->display_options['fields']['commerce_total']['group_column'] = 'amount';
  $handler->display->display_options['fields']['commerce_total']['group_columns'] = array(
    'currency_code' => 'currency_code',
  );
  $handler->display->display_options['fields']['commerce_total']['field_api_classes'] = 0;
  $handler->display->display_options['path'] = 'admin/commerce/reports/salestotals/month';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Monthly sales';
  $handler->display->display_options['menu']['description'] = 'View monthly sales summary.';
  $handler->display->display_options['menu']['weight'] = '3';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  
  /* Display: Weekly */
  $handler = $view->new_display('page', 'Weekly', 'weekly');
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Commerce Order: Created week timestamp (CCYYWW) */
  $handler->display->display_options['fields']['created_timestamp_ccyyww_1']['id'] = 'created_timestamp_ccyyww_1';
  $handler->display->display_options['fields']['created_timestamp_ccyyww_1']['table'] = 'commerce_order';
  $handler->display->display_options['fields']['created_timestamp_ccyyww_1']['field'] = 'created_timestamp_ccyyww';
  $handler->display->display_options['fields']['created_timestamp_ccyyww_1']['label'] = 'Week';
  $handler->display->display_options['fields']['created_timestamp_ccyyww_1']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['created_timestamp_ccyyww_1']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['created_timestamp_ccyyww_1']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['created_timestamp_ccyyww_1']['alter']['external'] = 0;
  $handler->display->display_options['fields']['created_timestamp_ccyyww_1']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['created_timestamp_ccyyww_1']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['created_timestamp_ccyyww_1']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['created_timestamp_ccyyww_1']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['created_timestamp_ccyyww_1']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['created_timestamp_ccyyww_1']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['created_timestamp_ccyyww_1']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['created_timestamp_ccyyww_1']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['created_timestamp_ccyyww_1']['alter']['html'] = 0;
  $handler->display->display_options['fields']['created_timestamp_ccyyww_1']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['created_timestamp_ccyyww_1']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['created_timestamp_ccyyww_1']['hide_empty'] = 0;
  $handler->display->display_options['fields']['created_timestamp_ccyyww_1']['empty_zero'] = 0;
  $handler->display->display_options['fields']['created_timestamp_ccyyww_1']['hide_alter_empty'] = 1;
  /* Field: SUM(Commerce Line Item: Quantity) */
  $handler->display->display_options['fields']['quantity']['id'] = 'quantity';
  $handler->display->display_options['fields']['quantity']['table'] = 'commerce_line_item';
  $handler->display->display_options['fields']['quantity']['field'] = 'quantity';
  $handler->display->display_options['fields']['quantity']['relationship'] = 'commerce_line_items_line_item_id';
  $handler->display->display_options['fields']['quantity']['group_type'] = 'sum';
  $handler->display->display_options['fields']['quantity']['label'] = 'Products sold';
  $handler->display->display_options['fields']['quantity']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['quantity']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['quantity']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['quantity']['alter']['external'] = 0;
  $handler->display->display_options['fields']['quantity']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['quantity']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['quantity']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['quantity']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['quantity']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['quantity']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['quantity']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['quantity']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['quantity']['alter']['html'] = 0;
  $handler->display->display_options['fields']['quantity']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['quantity']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['quantity']['hide_empty'] = 0;
  $handler->display->display_options['fields']['quantity']['empty_zero'] = 0;
  $handler->display->display_options['fields']['quantity']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['quantity']['set_precision'] = 1;
  $handler->display->display_options['fields']['quantity']['precision'] = '0';
  $handler->display->display_options['fields']['quantity']['format_plural'] = 0;
  /* Field: SUM(Commerce Line item: Total) */
  $handler->display->display_options['fields']['commerce_total']['id'] = 'commerce_total';
  $handler->display->display_options['fields']['commerce_total']['table'] = 'field_data_commerce_total';
  $handler->display->display_options['fields']['commerce_total']['field'] = 'commerce_total';
  $handler->display->display_options['fields']['commerce_total']['relationship'] = 'commerce_line_items_line_item_id';
  $handler->display->display_options['fields']['commerce_total']['group_type'] = 'sum';
  $handler->display->display_options['fields']['commerce_total']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['commerce_total']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['commerce_total']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['commerce_total']['alter']['external'] = 0;
  $handler->display->display_options['fields']['commerce_total']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['commerce_total']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['commerce_total']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['commerce_total']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['commerce_total']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['commerce_total']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['commerce_total']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['commerce_total']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['commerce_total']['alter']['html'] = 0;
  $handler->display->display_options['fields']['commerce_total']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['commerce_total']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['commerce_total']['hide_empty'] = 0;
  $handler->display->display_options['fields']['commerce_total']['empty_zero'] = 0;
  $handler->display->display_options['fields']['commerce_total']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['commerce_total']['click_sort_column'] = 'amount';
  $handler->display->display_options['fields']['commerce_total']['type'] = 'commerce_price_formatted_amount';
  $handler->display->display_options['fields']['commerce_total']['settings'] = array(
    'calculation' => FALSE,
  );
  $handler->display->display_options['fields']['commerce_total']['group_column'] = 'amount';
  $handler->display->display_options['fields']['commerce_total']['group_columns'] = array(
    'currency_code' => 'currency_code',
  );
  $handler->display->display_options['fields']['commerce_total']['field_api_classes'] = 0;
  $handler->display->display_options['path'] = 'admin/commerce/reports/salestotals/weekly';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Weekly sales';
  $handler->display->display_options['menu']['description'] = 'View weekly sales totals.';
  $handler->display->display_options['menu']['weight'] = '2';
  $handler->display->display_options['menu']['context'] = 0;
  
  $views[$view->name] = $view;
    
  return $views;
}
