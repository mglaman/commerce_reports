<?php

function commerce_reports_patterns_form($form, &$form_state) {
  $form['min_support'] = array(
    '#type' => 'textfield',
    '#title' => t('Minimum support'),
    '#description' => t('The minimum support should be a decimal between 0 and 1 that indicates what the minimum relative amount of transactions an item set requires to be frequent.'),
    '#size' => 6,
  );
  $form['min_confidence'] = array(
    '#type' => 'textfield',
    '#title' => t('Minimum confidence'),
    '#description' => t('The minimum confidence should be a decimal between 0 and 1 that indicates the chance of occurence a rule should minimally have.'),
    '#size' => 6,
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Generate'),
  );
  
  return $form;
}

function commerce_reports_patterns_form_validate($form, &$form_state) {
  $min_support = (float) $form_state['values']['min_support'];
  $min_confidence = (float) $form_state['values']['min_confidence'];
  
  if (($min_support <= 0) || ($min_support >= 1)) {
    form_set_error('min_support', t('The minimum support should be a value between 0 and 1.'));
  }
  if (($min_confidence <= 0) || ($min_confidence >= 1)) {
    form_set_error('min_confidence', t('The minimum confidence should be a value between 0 and 1.'));
  }
}

function commerce_reports_patterns_form_submit($form, &$form_state) {
  $min_support = (float) $form_state['values']['min_support'];
  $min_confidence = (float) $form_state['values']['min_confidence'];
  
  $batch = array(
    'title' => t('Association rule mining'),
    'operations' => array(
      array('commerce_reports_patterns_load', array($min_support)),
      array('commerce_reports_patterns_frequent_itemset', array()),
      array('commerce_reports_patterns_association_rules', array($min_confidence)),
    ),
    'finished' => 'commerce_reports_patterns_finished',
    'file' => drupal_get_path('module', 'commerce_reports_patterns') . '/commerce_reports_patterns.batch.inc',
  );
  
  batch_set($batch);
}

function commerce_reports_patterns_view() {
  return array(
    _commerce_reports_patterns_view(3),
    _commerce_reports_patterns_view(2)
  );
}

function _commerce_reports_patterns_view($size) {
  $query = db_query("SELECT if_clause, then_clause, confidence FROM {commerce_reports_patterns} WHERE size = :size ORDER BY confidence DESC LIMIT 10", array(':size' => $size));
  
  $rules = array();
  while ($result = $query->fetchAssoc()) {
    $rules[] = array(
      theme('item_list', array(
        'items' => unserialize($result['if_clause']),
      )),
      theme('item_list', array(
        'items' => unserialize($result['then_clause']),
      )),
      round($result['confidence'] * 100) . '%'
    );
  }
  
  return array(
    '#theme' => 'table',
    '#rows' => $rules,
    '#header' => array(t('Antecedent'), t('Consequent'), t('Chance')),
  );
}
