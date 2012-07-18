<?php

function commerce_reports_patterns_load($min_support, &$context) {
  if (empty($context['sandbox'])) {
    $total_transactions = db_query('SELECT COUNT(order_id) FROM commerce_order')->fetchField();
    $min_transactions = (int) floor($total_transactions * $min_support);
    
    $context['results'] = array(
      'total_transactions' => $total_transactions,
      'minimum_transactions' => $min_transactions,
      'frequent_sets' => array(
        1 => array(
          array(
            'prefix' => array(),
            'sets' => array(),
          ),
        ),
      ),
    );
    
    $context['sandbox']['products'] = db_query('SELECT sku, COUNT(li.line_item_id) AS occurences FROM {commerce_product} p LEFT JOIN {commerce_line_item} li ON p.sku = li.line_item_label GROUP BY sku HAVING occurences >= :min_occurences ORDER BY occurences DESC', array(':min_occurences' => $min_transactions))->fetchAll();
    
    $context['sandbox']['progress'] = 0;
    $context['sandbox']['max'] = count($context['sandbox']['products']);
  }
  
  $product = $context['sandbox']['products'][$context['sandbox']['progress']];
  
  if ($product) {
    $context['results']['frequent_sets'][1][0]['sets'][] = array(
      'items' => array($product->sku),
      'tidlist' => db_query("SELECT order_id FROM {commerce_line_item} WHERE line_item_label = :sku", array(':sku' => $product->sku))->fetchCol()
    );
  }

  $context['sandbox']['progress'] ++;
  
  if ($context['sandbox']['progress'] < $context['sandbox']['max']) {
    $context['finished'] = $context['sandbox']['progress'] / $context['sandbox']['max'];
  } else {
    if (!count($context['results']['frequent_sets'][1][0]['sets'])) {
      unset($context['results']['frequent_sets'][1]);
    }
  }
}

function commerce_reports_patterns_mine(&$context) {
  if (empty($context['sandbox'])) {
    $context['sandbox']['set_length'] = 2;
  }
  
  $length = $context['sandbox']['set_length'];
  $prev_length = $length - 1;
  if (empty($context['results']['frequent_sets'][$prev_length])) {
    return;
  }
  
  $context['results']['frequent_sets'][$length] = array();
  $prev_partitions =& $context['results']['frequent_sets'][$prev_length];
  
  foreach ($prev_partitions as &$partition) {
    $partition_prefix = $partition['prefix'];
    
    $partition_itemset =& $partition['sets'];
    $partition_itemset_count = count($partition_itemset);
    
    $sets = array();
    
    for ($a = 0; $a < $partition_itemset_count; $a ++) {
      for ($b = $a + 1; $b < $partition_itemset_count; $b ++) {
        $a_set =& $partition_itemset[$a];
        $b_set =& $partition_itemset[$b];
        
        $candidate = array(
          'items' => array_unique(array_merge($a_set['items'], $b_set['items'])),
          'tidlist' => array_intersect($a_set['tidlist'], $b_set['tidlist']),
        );
        
        $occurences = count($candidate['tidlist']);
        
        if ($occurences >= $context['results']['minimum_transactions']) {
          $new_items = array_diff($candidate['items'], $partition_prefix);
          $prefix = array_merge($partition_prefix, array(reset($new_items)));

          _commerce_reports_patterns_add_set($context['results']['frequent_sets'][$length], $prefix, $candidate);
        }
      }
    }
  }
  
  $context['sandbox']['set_length'] ++;
  
  if ($count = count($context['results']['frequent_sets'][$length])) {
    $context['finished'] = 0;
    $context['message'] = t('Generated %count frequent item sets with length %length', array('%count' => $count, '%length' => $length));
  } else {
    unset($context['results']['frequent_sets'][$length]);
  }
}

function _commerce_reports_patterns_add_set(&$partitions, $prefix, $set) {
  sort($prefix);
  
  foreach ($partitions as &$partition) {
    if ($partition['prefix'] == $prefix) {
      $partition['sets'][] = $set;
      
      return;
    }
  }
  
  $partitions[] = array(
    'prefix' => $prefix,
    'sets' => array($set),
  );
}

function commerce_reports_patterns_finished($success, $results, $operations) {
  if ($success) {
    drupal_set_message(t('Successfully finished mining frequent itemsets, the largest set contained %length items.', array('%length' => count($results['frequent_sets']))));
  }
  else {
    drupal_set_message(t('There was a problem generating frequent itemsets.'), 'error');
  }
}
