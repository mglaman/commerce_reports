<?php
/**
 * @file
 * Settings form.
 */

/**
 * Settings form for commerce_reports.
 */
function commerce_reports_settings_form($form, &$form_state) {
  module_load_include('inc', 'commerce_reports', 'commerce_reports.visualization');
  
  $options = array();
  foreach (commerce_reports_visualization() as $name => $information) {
    if ($information['enabled']) {
      $options[$name] = $information['title'];
    }
  }
  
  $form['library'] = array(
    '#type' => 'select',
    '#title' => t('Preferred charting library'),
    '#options' => $options,
    '#description' => t('Your charting library of preference will be used when generating charts (as long as it offers support for the requested type). The available options are the charting libraries detected on your system, please refer to the help section for more information about enabling more libraries.'),
    '#default_value' => variable_get('commerce_reports_visualization', 'gva'),
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );
  
  return $form;
}

/**
 * Submit handler for commerce_reports settings form.
 */
function commerce_reports_settings_form_submit($form, &$form_state) {
  variable_set('commerce_reports_visualization', $form_state['values']['library']);
  
  drupal_set_message(t('Reports settings saved.'));
}
