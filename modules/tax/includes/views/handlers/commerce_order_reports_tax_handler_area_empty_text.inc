<?php
/**
 * @file
 * Contains commerce_reports_tax_handler_area_empty_text.
 */

/**
 * Area handler to display the empty text message for reports.
 */
class commerce_reports_tax_handler_area_empty_text extends views_handler_area {

  function option_definition() {
    $options = parent::option_definition();

    // Undefine the empty option.
    unset($options['empty']);

    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    // Don't display a form element for the undefined empty option.
    unset($form['empty']);
  }

  public function render($empty = FALSE) {
    return t('It seems this tax report does not contain any information, you can change its parameters or regenerate it on the <a href="!url">overview</a> page.', array('!url' => check_url(url('admin/commerce/reports/tax'))));
  }
}
