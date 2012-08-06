<?php
/**
 * @file
 * Default views.
 */

/**
 * Implements hook_views_default_views().
 */
function commerce_reports_tax_views_default_views() {

  /**
   * Commerce reports tax: overview
   */
  $view = new view;
  $view->name = 'commerce_reports_tax_overview';
  $view->description = 'This view shows a cached tax report, the results below are not an up-to-date representation of the tax collected by your store. It is rather a snapshot of the situation when the report was last generated.';
  $view->tag = 'commerce_reports_tax';
  $view->base_table = 'commerce_reports_tax_rate_aggregate';
  $view->human_name = 'Tax reports';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Tax report: overview';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'access commerce tax reports';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'name' => 'name',
    'title' => 'title',
    'type' => 'type',
    'rate' => 'rate',
    'taxable' => 'taxable',
    'taxed' => 'taxed',
    'operations' => 'operations',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'title' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'type' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'rate' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'taxable' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'taxed' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'operations' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
    ),
  );
  $handler->display->display_options['style_options']['override'] = 1;
  $handler->display->display_options['style_options']['sticky'] = 0;
  $handler->display->display_options['style_options']['empty_table'] = 0;
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = FALSE;
  $handler->display->display_options['empty']['area']['content'] = 'There\'s no tax information available.';
  $handler->display->display_options['empty']['area']['format'] = 'filtered_html';
  $handler->display->display_options['empty']['area']['tokenize'] = 0;
  /* Field: Commerce Reports Tax Rate: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'commerce_reports_tax_rate';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'tax';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['exclude'] = TRUE;
  $handler->display->display_options['fields']['name']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['name']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['name']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['name']['alter']['external'] = 0;
  $handler->display->display_options['fields']['name']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['name']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['name']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['name']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['name']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['name']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['name']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['name']['alter']['html'] = 0;
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['name']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['name']['hide_empty'] = 0;
  $handler->display->display_options['fields']['name']['empty_zero'] = 0;
  $handler->display->display_options['fields']['name']['hide_alter_empty'] = 1;
  /* Field: Commerce Reports Tax Rate: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'commerce_reports_tax_rate';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['relationship'] = 'tax';
  $handler->display->display_options['fields']['title']['label'] = 'Tax name';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['title']['alter']['text'] = 'Total';
  $handler->display->display_options['fields']['title']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['title']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['title']['alter']['external'] = 0;
  $handler->display->display_options['fields']['title']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['title']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['title']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['title']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['title']['alter']['html'] = 0;
  $handler->display->display_options['fields']['title']['element_label_colon'] = 0;
  $handler->display->display_options['fields']['title']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['title']['hide_empty'] = 0;
  $handler->display->display_options['fields']['title']['empty_zero'] = 0;
  $handler->display->display_options['fields']['title']['hide_alter_empty'] = 1;
  /* Field: Commerce Reports Tax Rate: Type */
  $handler->display->display_options['fields']['type']['id'] = 'type';
  $handler->display->display_options['fields']['type']['table'] = 'commerce_reports_tax_rate';
  $handler->display->display_options['fields']['type']['field'] = 'type';
  $handler->display->display_options['fields']['type']['label'] = 'Jurisdiction';
  $handler->display->display_options['fields']['type']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['type']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['type']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['type']['alter']['external'] = 0;
  $handler->display->display_options['fields']['type']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['type']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['type']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['type']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['type']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['type']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['type']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['type']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['type']['alter']['html'] = 0;
  $handler->display->display_options['fields']['type']['element_label_colon'] = 0;
  $handler->display->display_options['fields']['type']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['type']['hide_empty'] = 0;
  $handler->display->display_options['fields']['type']['empty_zero'] = 0;
  $handler->display->display_options['fields']['type']['hide_alter_empty'] = 1;
  /* Field: Commerce Reports Tax Rate: Rate */
  $handler->display->display_options['fields']['rate']['id'] = 'rate';
  $handler->display->display_options['fields']['rate']['table'] = 'commerce_reports_tax_rate';
  $handler->display->display_options['fields']['rate']['field'] = 'rate';
  $handler->display->display_options['fields']['rate']['relationship'] = 'tax';
  $handler->display->display_options['fields']['rate']['label'] = 'Tax rate';
  $handler->display->display_options['fields']['rate']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['rate']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['rate']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['rate']['alter']['external'] = 0;
  $handler->display->display_options['fields']['rate']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['rate']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['rate']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['rate']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['rate']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['rate']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['rate']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['rate']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['rate']['alter']['html'] = 0;
  $handler->display->display_options['fields']['rate']['element_label_colon'] = 0;
  $handler->display->display_options['fields']['rate']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['rate']['hide_empty'] = 0;
  $handler->display->display_options['fields']['rate']['empty_zero'] = 0;
  $handler->display->display_options['fields']['rate']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['rate']['set_precision'] = 0;
  $handler->display->display_options['fields']['rate']['precision'] = '0';
  $handler->display->display_options['fields']['rate']['format_plural'] = 0;
  /* Field: Commerce Reports Tax Aggregate: Taxable amount */
  $handler->display->display_options['fields']['taxable']['id'] = 'taxable';
  $handler->display->display_options['fields']['taxable']['table'] = 'commerce_reports_tax_rate_aggregate';
  $handler->display->display_options['fields']['taxable']['field'] = 'taxable';
  $handler->display->display_options['fields']['taxable']['label'] = 'Total taxable amount';
  $handler->display->display_options['fields']['taxable']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['taxable']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['taxable']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['taxable']['alter']['external'] = 0;
  $handler->display->display_options['fields']['taxable']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['taxable']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['taxable']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['taxable']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['taxable']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['taxable']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['taxable']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['taxable']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['taxable']['alter']['html'] = 0;
  $handler->display->display_options['fields']['taxable']['element_label_colon'] = 0;
  $handler->display->display_options['fields']['taxable']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['taxable']['hide_empty'] = 0;
  $handler->display->display_options['fields']['taxable']['empty_zero'] = 0;
  $handler->display->display_options['fields']['taxable']['hide_alter_empty'] = 1;
  /* Field: Commerce Reports Tax Aggregate: Taxed */
  $handler->display->display_options['fields']['taxed']['id'] = 'taxed';
  $handler->display->display_options['fields']['taxed']['table'] = 'commerce_reports_tax_rate_aggregate';
  $handler->display->display_options['fields']['taxed']['field'] = 'taxed';
  $handler->display->display_options['fields']['taxed']['label'] = 'Total tax collected';
  $handler->display->display_options['fields']['taxed']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['taxed']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['taxed']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['taxed']['alter']['external'] = 0;
  $handler->display->display_options['fields']['taxed']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['taxed']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['taxed']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['taxed']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['taxed']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['taxed']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['taxed']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['taxed']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['taxed']['alter']['html'] = 0;
  $handler->display->display_options['fields']['taxed']['element_label_colon'] = 0;
  $handler->display->display_options['fields']['taxed']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['taxed']['hide_empty'] = 0;
  $handler->display->display_options['fields']['taxed']['empty_zero'] = 0;
  $handler->display->display_options['fields']['taxed']['hide_alter_empty'] = 1;
  /* Field: Commerce Reports Tax Aggregate: Operations */
  $handler->display->display_options['fields']['operations']['id'] = 'operations';
  $handler->display->display_options['fields']['operations']['table'] = 'commerce_reports_tax_rate_aggregate';
  $handler->display->display_options['fields']['operations']['field'] = 'operations';
  $handler->display->display_options['fields']['operations']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['external'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['operations']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['operations']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['html'] = 0;
  $handler->display->display_options['fields']['operations']['element_label_colon'] = 0;
  $handler->display->display_options['fields']['operations']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['operations']['hide_empty'] = 0;
  $handler->display->display_options['fields']['operations']['empty_zero'] = 0;
  $handler->display->display_options['fields']['operations']['hide_alter_empty'] = 1;
  /* Contextual filter: Commerce Reports Tax Aggregate: Report ID */
  $handler->display->display_options['arguments']['report_id']['id'] = 'report_id';
  $handler->display->display_options['arguments']['report_id']['table'] = 'commerce_reports_tax_rate_aggregate';
  $handler->display->display_options['arguments']['report_id']['field'] = 'report_id';
  $handler->display->display_options['arguments']['report_id']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['report_id']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['report_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['report_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['report_id']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['report_id']['break_phrase'] = 0;
  $handler->display->display_options['arguments']['report_id']['not'] = 0;

  /* Display: Attachment */
  $handler = $view->new_display('attachment', 'Attachment', 'aggregated_total');
  $handler->display->display_options['defaults']['group_by'] = FALSE;
  $handler->display->display_options['group_by'] = TRUE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = 'Tax name';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = 'Total';
  $handler->display->display_options['fields']['nothing']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['external'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['nothing']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['nothing']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['html'] = 0;
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = 0;
  $handler->display->display_options['fields']['nothing']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['nothing']['hide_empty'] = 0;
  $handler->display->display_options['fields']['nothing']['empty_zero'] = 0;
  $handler->display->display_options['fields']['nothing']['hide_alter_empty'] = 0;
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing_1']['id'] = 'nothing_1';
  $handler->display->display_options['fields']['nothing_1']['table'] = 'views';
  $handler->display->display_options['fields']['nothing_1']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing_1']['label'] = 'Jurisdiction';
  $handler->display->display_options['fields']['nothing_1']['alter']['text'] = ' ';
  $handler->display->display_options['fields']['nothing_1']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['nothing_1']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['nothing_1']['alter']['external'] = 0;
  $handler->display->display_options['fields']['nothing_1']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['nothing_1']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['nothing_1']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['nothing_1']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['nothing_1']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['nothing_1']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['nothing_1']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['nothing_1']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['nothing_1']['alter']['html'] = 0;
  $handler->display->display_options['fields']['nothing_1']['element_label_colon'] = 0;
  $handler->display->display_options['fields']['nothing_1']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['nothing_1']['hide_empty'] = 0;
  $handler->display->display_options['fields']['nothing_1']['empty_zero'] = 0;
  $handler->display->display_options['fields']['nothing_1']['hide_alter_empty'] = 0;
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing_2']['id'] = 'nothing_2';
  $handler->display->display_options['fields']['nothing_2']['table'] = 'views';
  $handler->display->display_options['fields']['nothing_2']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing_2']['label'] = 'Tax rate';
  $handler->display->display_options['fields']['nothing_2']['alter']['text'] = ' ';
  $handler->display->display_options['fields']['nothing_2']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['nothing_2']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['nothing_2']['alter']['external'] = 0;
  $handler->display->display_options['fields']['nothing_2']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['nothing_2']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['nothing_2']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['nothing_2']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['nothing_2']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['nothing_2']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['nothing_2']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['nothing_2']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['nothing_2']['alter']['html'] = 0;
  $handler->display->display_options['fields']['nothing_2']['element_label_colon'] = 0;
  $handler->display->display_options['fields']['nothing_2']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['nothing_2']['hide_empty'] = 0;
  $handler->display->display_options['fields']['nothing_2']['empty_zero'] = 0;
  $handler->display->display_options['fields']['nothing_2']['hide_alter_empty'] = 0;
  /* Field: Commerce Reports Tax Aggregate: Taxable amount */
  $handler->display->display_options['fields']['taxable']['id'] = 'taxable';
  $handler->display->display_options['fields']['taxable']['table'] = 'commerce_reports_tax_rate_aggregate';
  $handler->display->display_options['fields']['taxable']['field'] = 'taxable';
  $handler->display->display_options['fields']['taxable']['group_type'] = 'sum';
  $handler->display->display_options['fields']['taxable']['label'] = 'Total taxable amount';
  $handler->display->display_options['fields']['taxable']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['taxable']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['taxable']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['taxable']['alter']['external'] = 0;
  $handler->display->display_options['fields']['taxable']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['taxable']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['taxable']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['taxable']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['taxable']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['taxable']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['taxable']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['taxable']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['taxable']['alter']['html'] = 0;
  $handler->display->display_options['fields']['taxable']['element_label_colon'] = 0;
  $handler->display->display_options['fields']['taxable']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['taxable']['hide_empty'] = 0;
  $handler->display->display_options['fields']['taxable']['empty_zero'] = 0;
  $handler->display->display_options['fields']['taxable']['hide_alter_empty'] = 1;
  /* Field: Commerce Reports Tax Aggregate: Taxed */
  $handler->display->display_options['fields']['taxed']['id'] = 'taxed';
  $handler->display->display_options['fields']['taxed']['table'] = 'commerce_reports_tax_rate_aggregate';
  $handler->display->display_options['fields']['taxed']['field'] = 'taxed';
  $handler->display->display_options['fields']['taxed']['group_type'] = 'sum';
  $handler->display->display_options['fields']['taxed']['label'] = 'Total tax collected';
  $handler->display->display_options['fields']['taxed']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['taxed']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['taxed']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['taxed']['alter']['external'] = 0;
  $handler->display->display_options['fields']['taxed']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['taxed']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['taxed']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['taxed']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['taxed']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['taxed']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['taxed']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['taxed']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['taxed']['alter']['html'] = 0;
  $handler->display->display_options['fields']['taxed']['element_label_colon'] = 0;
  $handler->display->display_options['fields']['taxed']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['taxed']['hide_empty'] = 0;
  $handler->display->display_options['fields']['taxed']['empty_zero'] = 0;
  $handler->display->display_options['fields']['taxed']['hide_alter_empty'] = 1;
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing_3']['id'] = 'nothing_3';
  $handler->display->display_options['fields']['nothing_3']['table'] = 'views';
  $handler->display->display_options['fields']['nothing_3']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing_3']['label'] = 'Operations';
  $handler->display->display_options['fields']['nothing_3']['alter']['text'] = ' ';
  $handler->display->display_options['fields']['nothing_3']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['nothing_3']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['nothing_3']['alter']['external'] = 0;
  $handler->display->display_options['fields']['nothing_3']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['nothing_3']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['nothing_3']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['nothing_3']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['nothing_3']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['nothing_3']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['nothing_3']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['nothing_3']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['nothing_3']['alter']['html'] = 0;
  $handler->display->display_options['fields']['nothing_3']['element_label_colon'] = 0;
  $handler->display->display_options['fields']['nothing_3']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['nothing_3']['hide_empty'] = 0;
  $handler->display->display_options['fields']['nothing_3']['empty_zero'] = 0;
  $handler->display->display_options['fields']['nothing_3']['hide_alter_empty'] = 0;

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['header'] = FALSE;
  $handler->display->display_options['path'] = 'admin/commerce/reports/tax/%';

  $views[$view->name] = $view;
  
  /**
   * Commerce reports tax: details
   */
  $view = new view;
  $view->name = 'commerce_reports_tax_details';
  $view->description = 'This view shows detailed information about tax reports. Each entry represents the amount of collected tax per order grouped by tax type.';
  $view->tag = 'commerce_reports_tax';
  $view->base_table = 'commerce_reports_tax_rate_orders';
  $view->human_name = 'Tax reports (orders)';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Tax report: details';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'access commerce tax reports';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '50';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all'] = 0;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'report_id' => 'report_id',
    'title' => 'title',
    'type' => 'type',
    'rate' => 'rate',
    'order_number' => 'order_number',
    'taxable' => 'taxable',
    'taxed' => 'taxed',
    'view_order' => 'view_order',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'report_id' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'title' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'type' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'rate' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'order_number' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'taxable' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'taxed' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'view_order' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['override'] = 1;
  $handler->display->display_options['style_options']['sticky'] = 0;
  $handler->display->display_options['style_options']['empty_table'] = 0;
  /* Relationship: Commerce Reports Tax Order: Order ID */
  $handler->display->display_options['relationships']['order_id']['id'] = 'order_id';
  $handler->display->display_options['relationships']['order_id']['table'] = 'commerce_reports_tax_rate_orders';
  $handler->display->display_options['relationships']['order_id']['field'] = 'order_id';
  $handler->display->display_options['relationships']['order_id']['required'] = 0;
  /* Field: Commerce Reports Tax Order: Order number */
  $handler->display->display_options['fields']['order_number']['id'] = 'order_number';
  $handler->display->display_options['fields']['order_number']['table'] = 'commerce_order';
  $handler->display->display_options['fields']['order_number']['field'] = 'order_number';
  $handler->display->display_options['fields']['order_number']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['order_number']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['order_number']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['order_number']['alter']['external'] = 0;
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
  $handler->display->display_options['fields']['order_number']['link_to_order'] = 'admin';
  /* Field: Commerce Reports Tax Rate: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'commerce_reports_tax_rate';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['relationship'] = 'tax';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['title']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['title']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['title']['alter']['external'] = 0;
  $handler->display->display_options['fields']['title']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['title']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['title']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['title']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['title']['alter']['html'] = 0;
  $handler->display->display_options['fields']['title']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['title']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['title']['hide_empty'] = 0;
  $handler->display->display_options['fields']['title']['empty_zero'] = 0;
  $handler->display->display_options['fields']['title']['hide_alter_empty'] = 1;
  /* Field: Commerce Reports Tax Rate: Type */
  $handler->display->display_options['fields']['type']['id'] = 'type';
  $handler->display->display_options['fields']['type']['table'] = 'commerce_reports_tax_rate';
  $handler->display->display_options['fields']['type']['field'] = 'type';
  $handler->display->display_options['fields']['type']['relationship'] = 'tax';
  $handler->display->display_options['fields']['type']['label'] = 'Jurisdiction';
  $handler->display->display_options['fields']['type']['exclude'] = TRUE;
  $handler->display->display_options['fields']['type']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['type']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['type']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['type']['alter']['external'] = 0;
  $handler->display->display_options['fields']['type']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['type']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['type']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['type']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['type']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['type']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['type']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['type']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['type']['alter']['html'] = 0;
  $handler->display->display_options['fields']['type']['element_label_colon'] = 0;
  $handler->display->display_options['fields']['type']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['type']['hide_empty'] = 0;
  $handler->display->display_options['fields']['type']['empty_zero'] = 0;
  $handler->display->display_options['fields']['type']['hide_alter_empty'] = 1;
  /* Field: Commerce Reports Tax Rate: Rate */
  $handler->display->display_options['fields']['rate']['id'] = 'rate';
  $handler->display->display_options['fields']['rate']['table'] = 'commerce_reports_tax_rate';
  $handler->display->display_options['fields']['rate']['field'] = 'rate';
  $handler->display->display_options['fields']['rate']['relationship'] = 'tax';
  $handler->display->display_options['fields']['rate']['label'] = 'Tax rate';
  $handler->display->display_options['fields']['rate']['exclude'] = TRUE;
  $handler->display->display_options['fields']['rate']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['rate']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['rate']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['rate']['alter']['external'] = 0;
  $handler->display->display_options['fields']['rate']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['rate']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['rate']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['rate']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['rate']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['rate']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['rate']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['rate']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['rate']['alter']['html'] = 0;
  $handler->display->display_options['fields']['rate']['element_label_colon'] = 0;
  $handler->display->display_options['fields']['rate']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['rate']['hide_empty'] = 0;
  $handler->display->display_options['fields']['rate']['empty_zero'] = 0;
  $handler->display->display_options['fields']['rate']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['rate']['set_precision'] = 0;
  $handler->display->display_options['fields']['rate']['precision'] = '0';
  $handler->display->display_options['fields']['rate']['format_plural'] = 0;
  /* Field: Commerce Order: Order number */
  $handler->display->display_options['fields']['order_number']['id'] = 'order_number';
  $handler->display->display_options['fields']['order_number']['table'] = 'commerce_order';
  $handler->display->display_options['fields']['order_number']['field'] = 'order_number';
  $handler->display->display_options['fields']['order_number']['relationship'] = 'order_id';
  $handler->display->display_options['fields']['order_number']['label'] = 'Order';
  $handler->display->display_options['fields']['order_number']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['order_number']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['order_number']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['order_number']['alter']['external'] = 0;
  $handler->display->display_options['fields']['order_number']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['order_number']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['order_number']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['order_number']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['order_number']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['order_number']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['order_number']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['order_number']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['order_number']['alter']['html'] = 0;
  $handler->display->display_options['fields']['order_number']['element_label_colon'] = 0;
  $handler->display->display_options['fields']['order_number']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['order_number']['hide_empty'] = 0;
  $handler->display->display_options['fields']['order_number']['empty_zero'] = 0;
  $handler->display->display_options['fields']['order_number']['hide_alter_empty'] = 1;
  /* Field: Commerce Reports Tax Order: Taxable amount */
  $handler->display->display_options['fields']['taxable']['id'] = 'taxable';
  $handler->display->display_options['fields']['taxable']['table'] = 'commerce_reports_tax_rate_orders';
  $handler->display->display_options['fields']['taxable']['field'] = 'taxable';
  /* Field: Commerce Reports Tax Order: Taxed */
  $handler->display->display_options['fields']['taxed']['id'] = 'taxed';
  $handler->display->display_options['fields']['taxed']['table'] = 'commerce_reports_tax_rate_orders';
  $handler->display->display_options['fields']['taxed']['field'] = 'taxed';
  $handler->display->display_options['fields']['taxed']['label'] = 'Tax collected';
  $handler->display->display_options['fields']['taxed']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['taxed']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['taxed']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['taxed']['alter']['external'] = 0;
  $handler->display->display_options['fields']['taxed']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['taxed']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['taxed']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['taxed']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['taxed']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['taxed']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['taxed']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['taxed']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['taxed']['alter']['html'] = 0;
  $handler->display->display_options['fields']['taxed']['element_label_colon'] = 0;
  $handler->display->display_options['fields']['taxed']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['taxed']['hide_empty'] = 0;
  $handler->display->display_options['fields']['taxed']['empty_zero'] = 0;
  $handler->display->display_options['fields']['taxed']['hide_alter_empty'] = 1;
  /* Contextual filter: Commerce Reports Tax Order: ID */
  $handler->display->display_options['arguments']['report_id']['id'] = 'report_id';
  $handler->display->display_options['arguments']['report_id']['table'] = 'commerce_reports_tax_rate_orders';
  $handler->display->display_options['arguments']['report_id']['field'] = 'report_id';
  $handler->display->display_options['arguments']['report_id']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['report_id']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['report_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['report_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['report_id']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['report_id']['break_phrase'] = 0;
  $handler->display->display_options['arguments']['report_id']['not'] = 0;
  /* Contextual filter: Commerce Reports Tax Order: Tax rate */
  $handler->display->display_options['arguments']['tax']['id'] = 'tax';
  $handler->display->display_options['arguments']['tax']['table'] = 'commerce_reports_tax_rate_orders';
  $handler->display->display_options['arguments']['tax']['field'] = 'tax';
  $handler->display->display_options['arguments']['tax']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['tax']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['tax']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['tax']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['tax']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['tax']['glossary'] = 0;
  $handler->display->display_options['arguments']['tax']['limit'] = '0';
  $handler->display->display_options['arguments']['tax']['transform_dash'] = 0;
  $handler->display->display_options['arguments']['tax']['break_phrase'] = 0;

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'report_id' => 'report_id',
    'title' => 'title',
    'type' => 'type',
    'rate' => 'rate',
    'order_number' => 'order_number',
    'taxable' => 'taxable',
    'taxed' => 'taxed',
    'view_order' => 'view_order',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'report_id' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'title' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'type' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'rate' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'order_number' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'taxable' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'taxed' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'view_order' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['override'] = 1;
  $handler->display->display_options['style_options']['sticky'] = 0;
  $handler->display->display_options['style_options']['empty_table'] = 1;
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['header'] = FALSE;
  /* No results behavior: Commerce Reports Tax Order: Empty text */
  $handler->display->display_options['empty']['empty_text']['id'] = 'empty_text';
  $handler->display->display_options['empty']['empty_text']['table'] = 'commerce_reports_tax_rate_orders';
  $handler->display->display_options['empty']['empty_text']['field'] = 'empty_text';
  $handler->display->display_options['empty']['empty_text']['label'] = 'empty_text';
  $handler->display->display_options['defaults']['filters'] = FALSE;
  $handler->display->display_options['path'] = 'admin/commerce/reports/tax/%/%';

  $views[$view->name] = $view;
  
  return $views;
}
