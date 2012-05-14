<?php

/**
 * Views for commerce orders for report displays.
 */

/**
 * Implements hook_views_default_views().
 */
function commerce_reports_segmentation_views_default_views() {
  
  /**
   * Commerce Reports: Sales data
   */
  $view = new view;
  $view->name = 'commerce_reports_salesdata';
  $view->description = 'Raw sales data with segmentation flags, suitable for export.';
  $view->tag = 'commerce_reports';
  $view->base_table = 'commerce_order';
  $view->human_name = 'Sales data';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
  
  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Sales data';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'access commerce reports';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'table';
  /* Field: Commerce Order: Order ID */
  $handler->display->display_options['fields']['order_id']['id'] = 'order_id';
  $handler->display->display_options['fields']['order_id']['table'] = 'commerce_order';
  $handler->display->display_options['fields']['order_id']['field'] = 'order_id';
  /* Field: Commerce Order: Created date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'commerce_order';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = 'Created';
  $handler->display->display_options['fields']['created']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['created']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['created']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['created']['alter']['external'] = 0;
  $handler->display->display_options['fields']['created']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['created']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['created']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['created']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['created']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['created']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['created']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['created']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['created']['alter']['html'] = 0;
  $handler->display->display_options['fields']['created']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['created']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['created']['hide_empty'] = 0;
  $handler->display->display_options['fields']['created']['empty_zero'] = 0;
  $handler->display->display_options['fields']['created']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['created']['date_format'] = 'custom';
  $handler->display->display_options['fields']['created']['custom_date_format'] = 'U';
  /* Field: Commerce Order: Product quantity */
  $handler->display->display_options['fields']['productquantity']['id'] = 'productquantity';
  $handler->display->display_options['fields']['productquantity']['table'] = 'commerce_order';
  $handler->display->display_options['fields']['productquantity']['field'] = 'productquantity';
  $handler->display->display_options['fields']['productquantity']['label'] = 'Products';
  $handler->display->display_options['fields']['productquantity']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['productquantity']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['productquantity']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['productquantity']['alter']['external'] = 0;
  $handler->display->display_options['fields']['productquantity']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['productquantity']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['productquantity']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['productquantity']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['productquantity']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['productquantity']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['productquantity']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['productquantity']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['productquantity']['alter']['html'] = 0;
  $handler->display->display_options['fields']['productquantity']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['productquantity']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['productquantity']['hide_empty'] = 0;
  $handler->display->display_options['fields']['productquantity']['empty_zero'] = 0;
  $handler->display->display_options['fields']['productquantity']['hide_alter_empty'] = 1;
  /* Field: Commerce Order: Order total */
  $handler->display->display_options['fields']['commerce_order_total']['id'] = 'commerce_order_total';
  $handler->display->display_options['fields']['commerce_order_total']['table'] = 'field_data_commerce_order_total';
  $handler->display->display_options['fields']['commerce_order_total']['field'] = 'commerce_order_total';
  $handler->display->display_options['fields']['commerce_order_total']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['commerce_order_total']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['commerce_order_total']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['commerce_order_total']['alter']['external'] = 0;
  $handler->display->display_options['fields']['commerce_order_total']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['commerce_order_total']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['commerce_order_total']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['commerce_order_total']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['commerce_order_total']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['commerce_order_total']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['commerce_order_total']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['commerce_order_total']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['commerce_order_total']['alter']['html'] = 0;
  $handler->display->display_options['fields']['commerce_order_total']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['commerce_order_total']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['commerce_order_total']['hide_empty'] = 0;
  $handler->display->display_options['fields']['commerce_order_total']['empty_zero'] = 0;
  $handler->display->display_options['fields']['commerce_order_total']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['commerce_order_total']['click_sort_column'] = 'amount';
  $handler->display->display_options['fields']['commerce_order_total']['type'] = 'commerce_price_raw_amount';
  $handler->display->display_options['fields']['commerce_order_total']['field_api_classes'] = 0;
  /* Field: Commerce Order: Flags */
  $handler->display->display_options['fields']['field_order_flags']['id'] = 'field_order_flags';
  $handler->display->display_options['fields']['field_order_flags']['table'] = 'field_data_field_order_flags';
  $handler->display->display_options['fields']['field_order_flags']['field'] = 'field_order_flags';
  $handler->display->display_options['fields']['field_order_flags']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_order_flags']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_order_flags']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_order_flags']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_order_flags']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_order_flags']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_order_flags']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_order_flags']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_order_flags']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_order_flags']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_order_flags']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_order_flags']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_order_flags']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_order_flags']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_order_flags']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_order_flags']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_order_flags']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_order_flags']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_order_flags']['type'] = 'taxonomy_term_reference_plain';
  $handler->display->display_options['fields']['field_order_flags']['group_rows'] = 1;
  $handler->display->display_options['fields']['field_order_flags']['delta_offset'] = '0';
  $handler->display->display_options['fields']['field_order_flags']['delta_reversed'] = 0;
  $handler->display->display_options['fields']['field_order_flags']['delta_first_last'] = 0;
  $handler->display->display_options['fields']['field_order_flags']['field_api_classes'] = 0;
  /* Filter criterion: Commerce Order: Order state */
  $handler->display->display_options['filters']['state']['id'] = 'state';
  $handler->display->display_options['filters']['state']['table'] = 'commerce_order';
  $handler->display->display_options['filters']['state']['field'] = 'state';
  $handler->display->display_options['filters']['state']['value'] = array(
    'pending' => 'pending',
    'completed' => 'completed',
  );
  
  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'admin/commerce/reports/salesdata';
  
  /* Display: Export */
  $handler = $view->new_display('views_data_export', 'Export', 'export');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['style_plugin'] = 'views_data_export_csv';
  $handler->display->display_options['path'] = 'admin/commerce/reports/salesdata/export';
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
  );
  
  $views[$view->name] = $view;
    
  return $views;
}
