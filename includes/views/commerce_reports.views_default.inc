<?php

/**
 * Views for commerce orders for report displays.
 */

/**
 * Implements hook_views_default_views().
 */
function commerce_reports_views_default_views() {
    
    $view = new view;
    $view->name = 'order_report';
    $view->description = 'Display a list of orders for the store admin.';
    $view->tag = 'commerce';
    $view->base_table = 'commerce_order';
    $view->human_name = 'Order Report';
    $view->core = 0;
    $view->api_version = '3.0-alpha1';
    $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
    
    /* Display: Defaults */
    $handler = $view->new_display('default', 'Defaults', 'default');
    $handler->display->display_options['title'] = 'Orders';
    $handler->display->display_options['access']['type'] = 'perm';
    $handler->display->display_options['access']['perm'] = 'administer commerce_order entities';
    $handler->display->display_options['cache']['type'] = 'none';
    $handler->display->display_options['query']['type'] = 'views_query';
    $handler->display->display_options['query']['options']['query_comment'] = FALSE;
    $handler->display->display_options['exposed_form']['type'] = 'basic';
    $handler->display->display_options['pager']['type'] = 'full';
    $handler->display->display_options['pager']['options']['items_per_page'] = 50;
    $handler->display->display_options['style_plugin'] = 'table';
    $handler->display->display_options['style_options']['columns'] = array(
      'order_number' => 'order_number',
      'created' => 'created',
      'commerce_customer_address' => 'commerce_customer_address',
      'name' => 'name',
      'commerce_order_total' => 'commerce_order_total',
      'status' => 'status',
      'operations' => 'operations',
    );
    $handler->display->display_options['style_options']['default'] = 'created';
    $handler->display->display_options['style_options']['info'] = array(
      'order_number' => array(
        'sortable' => 1,
        'default_sort_order' => 'asc',
        'align' => '',
        'separator' => '',
      ),
      'created' => array(
        'sortable' => 1,
        'default_sort_order' => 'asc',
        'align' => '',
        'separator' => '',
      ),
      'commerce_customer_address' => array(
        'sortable' => 0,
        'default_sort_order' => 'asc',
        'align' => '',
        'separator' => '',
      ),
      'name' => array(
        'sortable' => 1,
        'default_sort_order' => 'asc',
        'align' => '',
        'separator' => '',
      ),
      'commerce_order_total' => array(
        'sortable' => 1,
        'default_sort_order' => 'asc',
        'align' => '',
        'separator' => '',
      ),
      'status' => array(
        'sortable' => 1,
        'default_sort_order' => 'asc',
        'align' => '',
        'separator' => '',
      ),
      'operations' => array(
        'align' => '',
        'separator' => '',
      ),
    );
    $handler->display->display_options['style_options']['override'] = 1;
    $handler->display->display_options['style_options']['sticky'] = 0;
    $handler->display->display_options['style_options']['order'] = 'desc';
    /* Header: Commerce Order: Product Quantities by Month */
    $handler->display->display_options['header']['products_qty_monthly_line']['id'] = 'products_qty_monthly_line';
    $handler->display->display_options['header']['products_qty_monthly_line']['table'] = 'commerce_order';
    $handler->display->display_options['header']['products_qty_monthly_line']['field'] = 'products_qty_monthly_line';
    $handler->display->display_options['header']['products_qty_monthly_line']['alter']['alter_text'] = 0;
    $handler->display->display_options['header']['products_qty_monthly_line']['alter']['make_link'] = 0;
    $handler->display->display_options['header']['products_qty_monthly_line']['alter']['absolute'] = 0;
    $handler->display->display_options['header']['products_qty_monthly_line']['alter']['external'] = 0;
    $handler->display->display_options['header']['products_qty_monthly_line']['alter']['replace_spaces'] = 0;
    $handler->display->display_options['header']['products_qty_monthly_line']['alter']['trim_whitespace'] = 0;
    $handler->display->display_options['header']['products_qty_monthly_line']['alter']['nl2br'] = 0;
    $handler->display->display_options['header']['products_qty_monthly_line']['alter']['word_boundary'] = 1;
    $handler->display->display_options['header']['products_qty_monthly_line']['alter']['ellipsis'] = 1;
    $handler->display->display_options['header']['products_qty_monthly_line']['alter']['strip_tags'] = 0;
    $handler->display->display_options['header']['products_qty_monthly_line']['alter']['trim'] = 0;
    $handler->display->display_options['header']['products_qty_monthly_line']['alter']['html'] = 0;
    $handler->display->display_options['header']['products_qty_monthly_line']['element_label_colon'] = 1;
    $handler->display->display_options['header']['products_qty_monthly_line']['element_default_classes'] = 1;
    $handler->display->display_options['header']['products_qty_monthly_line']['hide_empty'] = 0;
    $handler->display->display_options['header']['products_qty_monthly_line']['empty_zero'] = 0;
    $handler->display->display_options['header']['products_qty_monthly_line']['hide_alter_empty'] = 0;
    /* Header: Commerce Order: Product Sales by Month */
    $handler->display->display_options['header']['products_sales_monthly_bar']['id'] = 'products_sales_monthly_bar';
    $handler->display->display_options['header']['products_sales_monthly_bar']['table'] = 'commerce_order';
    $handler->display->display_options['header']['products_sales_monthly_bar']['field'] = 'products_sales_monthly_bar';
    $handler->display->display_options['header']['products_sales_monthly_bar']['label'] = 'products_sales_monthly_bar';
    $handler->display->display_options['header']['products_sales_monthly_bar']['empty'] = 0;
    /* Header: Commerce Order: Product Sales Percentages */
    $handler->display->display_options['header']['products_percent_monthly_pie']['id'] = 'products_percent_monthly_pie';
    $handler->display->display_options['header']['products_percent_monthly_pie']['table'] = 'commerce_order';
    $handler->display->display_options['header']['products_percent_monthly_pie']['field'] = 'products_percent_monthly_pie';
    $handler->display->display_options['header']['products_percent_monthly_pie']['alter']['alter_text'] = 0;
    $handler->display->display_options['header']['products_percent_monthly_pie']['alter']['make_link'] = 0;
    $handler->display->display_options['header']['products_percent_monthly_pie']['alter']['absolute'] = 0;
    $handler->display->display_options['header']['products_percent_monthly_pie']['alter']['external'] = 0;
    $handler->display->display_options['header']['products_percent_monthly_pie']['alter']['replace_spaces'] = 0;
    $handler->display->display_options['header']['products_percent_monthly_pie']['alter']['trim_whitespace'] = 0;
    $handler->display->display_options['header']['products_percent_monthly_pie']['alter']['nl2br'] = 0;
    $handler->display->display_options['header']['products_percent_monthly_pie']['alter']['word_boundary'] = 1;
    $handler->display->display_options['header']['products_percent_monthly_pie']['alter']['ellipsis'] = 1;
    $handler->display->display_options['header']['products_percent_monthly_pie']['alter']['strip_tags'] = 0;
    $handler->display->display_options['header']['products_percent_monthly_pie']['alter']['trim'] = 0;
    $handler->display->display_options['header']['products_percent_monthly_pie']['alter']['html'] = 0;
    $handler->display->display_options['header']['products_percent_monthly_pie']['element_label_colon'] = 1;
    $handler->display->display_options['header']['products_percent_monthly_pie']['element_default_classes'] = 1;
    $handler->display->display_options['header']['products_percent_monthly_pie']['hide_empty'] = 0;
    $handler->display->display_options['header']['products_percent_monthly_pie']['empty_zero'] = 0;
    $handler->display->display_options['header']['products_percent_monthly_pie']['hide_alter_empty'] = 0;
    /* No results behavior: Global: Text area */
    $handler->display->display_options['empty']['text']['id'] = 'text';
    $handler->display->display_options['empty']['text']['table'] = 'views';
    $handler->display->display_options['empty']['text']['field'] = 'area';
    $handler->display->display_options['empty']['text']['empty'] = FALSE;
    $handler->display->display_options['empty']['text']['content'] = 'No orders for this time period';
    $handler->display->display_options['empty']['text']['format'] = 'plain_text';
    $handler->display->display_options['empty']['text']['tokenize'] = 0;
    /* Relationship: Commerce Order: Owner */
    $handler->display->display_options['relationships']['uid']['id'] = 'uid';
    $handler->display->display_options['relationships']['uid']['table'] = 'commerce_order';
    $handler->display->display_options['relationships']['uid']['field'] = 'uid';
    $handler->display->display_options['relationships']['uid']['required'] = 0;
    /* Relationship: Commerce Order: Referenced customer profile */
    $handler->display->display_options['relationships']['commerce_customer_billing_profile_id']['id'] = 'commerce_customer_billing_profile_id';
    $handler->display->display_options['relationships']['commerce_customer_billing_profile_id']['table'] = 'field_data_commerce_customer_billing';
    $handler->display->display_options['relationships']['commerce_customer_billing_profile_id']['field'] = 'commerce_customer_billing_profile_id';
    $handler->display->display_options['relationships']['commerce_customer_billing_profile_id']['required'] = 0;
    /* Field: Commerce Order: Order number */
    $handler->display->display_options['fields']['order_number']['id'] = 'order_number';
    $handler->display->display_options['fields']['order_number']['table'] = 'commerce_order';
    $handler->display->display_options['fields']['order_number']['field'] = 'order_number';
    $handler->display->display_options['fields']['order_number']['alter']['alter_text'] = 0;
    $handler->display->display_options['fields']['order_number']['alter']['make_link'] = 0;
    $handler->display->display_options['fields']['order_number']['alter']['absolute'] = 0;
    $handler->display->display_options['fields']['order_number']['alter']['external'] = 0;
    $handler->display->display_options['fields']['order_number']['alter']['replace_spaces'] = 0;
    $handler->display->display_options['fields']['order_number']['alter']['trim_whitespace'] = 0;
    $handler->display->display_options['fields']['order_number']['alter']['nl2br'] = 0;
    $handler->display->display_options['fields']['order_number']['alter']['word_boundary'] = 1;
    $handler->display->display_options['fields']['order_number']['alter']['ellipsis'] = 1;
    $handler->display->display_options['fields']['order_number']['alter']['strip_tags'] = 0;
    $handler->display->display_options['fields']['order_number']['alter']['trim'] = 0;
    $handler->display->display_options['fields']['order_number']['alter']['html'] = 0;
    $handler->display->display_options['fields']['order_number']['element_label_colon'] = 1;
    $handler->display->display_options['fields']['order_number']['element_default_classes'] = 1;
    $handler->display->display_options['fields']['order_number']['hide_empty'] = 0;
    $handler->display->display_options['fields']['order_number']['empty_zero'] = 0;
    $handler->display->display_options['fields']['order_number']['hide_alter_empty'] = 0;
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
    $handler->display->display_options['fields']['created']['alter']['strip_tags'] = 0;
    $handler->display->display_options['fields']['created']['alter']['trim'] = 0;
    $handler->display->display_options['fields']['created']['alter']['html'] = 0;
    $handler->display->display_options['fields']['created']['element_label_colon'] = 1;
    $handler->display->display_options['fields']['created']['element_default_classes'] = 1;
    $handler->display->display_options['fields']['created']['hide_empty'] = 0;
    $handler->display->display_options['fields']['created']['empty_zero'] = 0;
    $handler->display->display_options['fields']['created']['hide_alter_empty'] = 0;
    $handler->display->display_options['fields']['created']['date_format'] = 'long';
    /* Field: Commerce Order: Order total */
    $handler->display->display_options['fields']['commerce_order_total']['id'] = 'commerce_order_total';
    $handler->display->display_options['fields']['commerce_order_total']['table'] = 'field_data_commerce_order_total';
    $handler->display->display_options['fields']['commerce_order_total']['field'] = 'commerce_order_total';
    $handler->display->display_options['fields']['commerce_order_total']['label'] = 'Total';
    $handler->display->display_options['fields']['commerce_order_total']['alter']['alter_text'] = 0;
    $handler->display->display_options['fields']['commerce_order_total']['alter']['make_link'] = 0;
    $handler->display->display_options['fields']['commerce_order_total']['alter']['absolute'] = 0;
    $handler->display->display_options['fields']['commerce_order_total']['alter']['external'] = 0;
    $handler->display->display_options['fields']['commerce_order_total']['alter']['nl2br'] = 0;
    $handler->display->display_options['fields']['commerce_order_total']['alter']['word_boundary'] = 1;
    $handler->display->display_options['fields']['commerce_order_total']['alter']['ellipsis'] = 1;
    $handler->display->display_options['fields']['commerce_order_total']['alter']['strip_tags'] = 0;
    $handler->display->display_options['fields']['commerce_order_total']['alter']['trim'] = 0;
    $handler->display->display_options['fields']['commerce_order_total']['alter']['html'] = 0;
    $handler->display->display_options['fields']['commerce_order_total']['element_label_colon'] = 1;
    $handler->display->display_options['fields']['commerce_order_total']['element_default_classes'] = 1;
    $handler->display->display_options['fields']['commerce_order_total']['hide_empty'] = 0;
    $handler->display->display_options['fields']['commerce_order_total']['empty_zero'] = 0;
    $handler->display->display_options['fields']['commerce_order_total']['click_sort_column'] = 'amount';
    $handler->display->display_options['fields']['commerce_order_total']['type'] = 'commerce_price_formatted_amount';
    $handler->display->display_options['fields']['commerce_order_total']['settings'] = array(
      'calculation' => FALSE,
    );
    $handler->display->display_options['fields']['commerce_order_total']['field_api_classes'] = 0;
    /* Field: Commerce Order: Order status */
    $handler->display->display_options['fields']['status']['id'] = 'status';
    $handler->display->display_options['fields']['status']['table'] = 'commerce_order';
    $handler->display->display_options['fields']['status']['field'] = 'status';
    $handler->display->display_options['fields']['status']['alter']['alter_text'] = 0;
    $handler->display->display_options['fields']['status']['alter']['make_link'] = 0;
    $handler->display->display_options['fields']['status']['alter']['absolute'] = 0;
    $handler->display->display_options['fields']['status']['alter']['external'] = 0;
    $handler->display->display_options['fields']['status']['alter']['nl2br'] = 0;
    $handler->display->display_options['fields']['status']['alter']['word_boundary'] = 1;
    $handler->display->display_options['fields']['status']['alter']['ellipsis'] = 1;
    $handler->display->display_options['fields']['status']['alter']['strip_tags'] = 0;
    $handler->display->display_options['fields']['status']['alter']['trim'] = 0;
    $handler->display->display_options['fields']['status']['alter']['html'] = 0;
    $handler->display->display_options['fields']['status']['element_label_colon'] = 1;
    $handler->display->display_options['fields']['status']['element_default_classes'] = 1;
    $handler->display->display_options['fields']['status']['hide_empty'] = 0;
    $handler->display->display_options['fields']['status']['empty_zero'] = 0;
    /* Sort criterion: Commerce Order: Created date */
    $handler->display->display_options['sorts']['created']['id'] = 'created';
    $handler->display->display_options['sorts']['created']['table'] = 'commerce_order';
    $handler->display->display_options['sorts']['created']['field'] = 'created';
    $handler->display->display_options['sorts']['created']['exposed'] = TRUE;
    $handler->display->display_options['sorts']['created']['expose']['label'] = 'Created date';
    $handler->display->display_options['sorts']['created']['granularity'] = 'minute';
    /* Filter criterion: Commerce Order: Order state */
    $handler->display->display_options['filters']['state']['id'] = 'state';
    $handler->display->display_options['filters']['state']['table'] = 'commerce_order';
    $handler->display->display_options['filters']['state']['field'] = 'state';
    $handler->display->display_options['filters']['state']['operator'] = 'not in';
    $handler->display->display_options['filters']['state']['value'] = array(
      'cart' => 'cart',
      'checkout' => 'checkout',
    );
    $handler->display->display_options['filters']['state']['expose']['label'] = 'Order state';
    $handler->display->display_options['filters']['state']['expose']['use_operator'] = 1;
    $handler->display->display_options['filters']['state']['expose']['operator'] = 'state_op';
    $handler->display->display_options['filters']['state']['expose']['identifier'] = 'state';
    $handler->display->display_options['filters']['state']['expose']['reduce'] = 0;
    /* Filter criterion: Commerce Order: Created date */
    $handler->display->display_options['filters']['created']['id'] = 'created';
    $handler->display->display_options['filters']['created']['table'] = 'commerce_order';
    $handler->display->display_options['filters']['created']['field'] = 'created';
    $handler->display->display_options['filters']['created']['operator'] = 'between';
    $handler->display->display_options['filters']['created']['exposed'] = TRUE;
    $handler->display->display_options['filters']['created']['expose']['operator_id'] = 'created_op';
    $handler->display->display_options['filters']['created']['expose']['label'] = 'Created date between';
    $handler->display->display_options['filters']['created']['expose']['operator'] = 'created_op';
    $handler->display->display_options['filters']['created']['expose']['identifier'] = 'created';
    $handler->display->display_options['filters']['created']['expose']['remember'] = 1;
    $handler->display->display_options['filters']['created']['expose']['multiple'] = FALSE;
    
    /* Display: Admin page */
    $handler = $view->new_display('page', 'Admin page', 'admin_page');
    $handler->display->display_options['path'] = 'admin/commerce/reports';
    $handler->display->display_options['menu']['type'] = 'normal';
    $handler->display->display_options['menu']['title'] = 'Reports';
    $handler->display->display_options['menu']['weight'] = '50';
    $handler->display->display_options['menu']['name'] = 'management';
    $handler->display->display_options['tab_options']['type'] = 'normal';
    $handler->display->display_options['tab_options']['title'] = 'Reports';
    $handler->display->display_options['tab_options']['description'] = 'Manage orders in the store.';
    $handler->display->display_options['tab_options']['weight'] = '';
    $handler->display->display_options['tab_options']['name'] = 'management';

    $views[$view->name] = $view;
    
    return $views;
}
