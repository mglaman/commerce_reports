<?php

function commerce_reports_patterns_tidlist($min_support, &$context) {
  if (empty($context['sandbox'])) {
    $context['sandbox']['product_sku'] = db_query('SELECT sku, COUNT(li.line_item_id) AS support FROM {commerce_product} p LEFT JOIN {commerce_line_item} li ON p.sku = li.line_item_label GROUP BY sku HAVING support >= :min_support', array(':min_support' => $min_support))->fetchCol();
    
    $context['sandbox']['progress'] = 0;
    $context['sandbox']['max'] = count($context['sandbox']['product_sku']);
    
    $context['results'] = array(
      'tidlist' => array(),
    );
  }
  
  $sku = $context['sandbox']['product_sku'][$context['sandbox']['progress']];
  $context['results']['tidlist'][$sku] = db_query("SELECT order_id FROM {commerce_line_item} WHERE line_item_label = :sku", array(':sku' => $sku))->fetchCol();

  $context['sandbox']['progress'] ++;
  
  if ($context['sandbox']['progress'] != $context['sandbox']['max']) {
    $context['finished'] = $context['sandbox']['progress'] / $context['sandbox']['max'];
  }
}

function commerce_reports_patterns_finished($success, $results, $operations) {
  if ($success) {
    dpm($results);
  } else {
    drupal_set_message(t('There was a problem generating frequent itemsets.'), 'error');
  }
}
