<?php

/**
 * Implements hook_views_default_views().
 */
function commerce_reports_tax_views_default_views() {
  $views = array();

  $view = new view;
  $view->name = 'commerce_reports_tax';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'commerce_reports_tax';
  $view->human_name = 'Commerce Reports Tax';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Tax';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'access commerce reports';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'table';
  /* Field: Commerce Reports Tax: Order created date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'commerce_reports_tax';
  $handler->display->display_options['fields']['created']['field'] = 'created';
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
  $handler->display->display_options['fields']['created']['date_format'] = 'medium';
  /* Field: Commerce Reports Tax: Order ID */
  $handler->display->display_options['fields']['order_id']['id'] = 'order_id';
  $handler->display->display_options['fields']['order_id']['table'] = 'commerce_reports_tax';
  $handler->display->display_options['fields']['order_id']['field'] = 'order_id';
  /* Field: Commerce Reports Tax: Currency */
  $handler->display->display_options['fields']['currency_code']['id'] = 'currency_code';
  $handler->display->display_options['fields']['currency_code']['table'] = 'commerce_reports_tax';
  $handler->display->display_options['fields']['currency_code']['field'] = 'currency_code';
  $handler->display->display_options['fields']['currency_code']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['currency_code']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['currency_code']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['currency_code']['alter']['external'] = 0;
  $handler->display->display_options['fields']['currency_code']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['currency_code']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['currency_code']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['currency_code']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['currency_code']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['currency_code']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['currency_code']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['currency_code']['alter']['html'] = 0;
  $handler->display->display_options['fields']['currency_code']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['currency_code']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['currency_code']['hide_empty'] = 0;
  $handler->display->display_options['fields']['currency_code']['empty_zero'] = 0;
  $handler->display->display_options['fields']['currency_code']['hide_alter_empty'] = 0;
  /* Filter criterion: Commerce Reports Tax: Order created date */
  $handler->display->display_options['filters']['created']['id'] = 'created';
  $handler->display->display_options['filters']['created']['table'] = 'commerce_reports_tax';
  $handler->display->display_options['filters']['created']['field'] = 'created';
  $handler->display->display_options['filters']['created']['operator'] = 'between';
  $handler->display->display_options['filters']['created']['exposed'] = TRUE;
  $handler->display->display_options['filters']['created']['expose']['operator_id'] = 'created_op';
  $handler->display->display_options['filters']['created']['expose']['label'] = 'Order date';
  $handler->display->display_options['filters']['created']['expose']['operator'] = 'created_op';
  $handler->display->display_options['filters']['created']['expose']['identifier'] = 'created';
  $handler->display->display_options['filters']['created']['expose']['multiple'] = FALSE;

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'admin/commerce/reports/tax';

  $views[$view->name] = $view;

  return $views;
}

/**
 * Implements hook_views_default_views_alter().
 */
function commerce_reports_tax_views_default_views_alter() {
  foreach (commerce_tax_rates() as $name => $rate) {
    $handler->display->display_options['fields'][$name]['id'] = $name;
    $handler->display->display_options['fields'][$name]['table'] = 'commerce_reports_tax';
    $handler->display->display_options['fields'][$name]['field'] = $name;
  }
}
