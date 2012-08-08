<?php
/**
 * @file
 * Administrative forms.
 */
 
function commerce_reports_tax_form($form, &$form_state) {
  $form['generate'] = array(
    '#type' => 'submit',
    '#value' => t('Generate all tax information'),
    '#submit' => array('commerce_reports_tax_form_submit_generate'),
  );

  return $form;
}

/**
 * Submit handler that generate a tax report.
 *
 * Currently un-used, might come in handy later.
 */
function commerce_reports_tax_form_submit_generate($form, &$form_state) {
  commerce_reports_tax_generate();
}

function commerce_reports_tax_table() {
  $results = db_query("SELECT ctr.display_title AS title, crt.currency_code, SUM(crt.taxable) AS taxable, SUM(crt.taxed) AS taxed FROM {commerce_reports_tax} crt LEFT JOIN {commerce_tax_rate} ctr ON crt.tax_rate = ctr.name LEFT JOIN {commerce_order} co ON crt.order_id = co.order_id WHERE co.created > 0 GROUP BY crt.tax_rate, crt.currency_code");
  
  $rows = array();
  
  while ($result = $results->fetchAssoc()) {
    $rows[] = array($result['title'], commerce_currency_format($result['taxable'], $result['currency_code']), commerce_currency_format($result['taxed'], $result['currency_code']));
  }
  
  return array(
    '#theme' => 'table',
    '#header' => array(t('Tax rate'), t('Taxable'), t('Taxed')),
    '#rows' => $rows,
  );
}
