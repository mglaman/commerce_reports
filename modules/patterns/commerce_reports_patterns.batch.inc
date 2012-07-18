<?php

function commerce_reports_patterns_tidlist($min_support, &$context) {
  if (empty($context['sandbox'])) {
    $context['sandbox']['product_sku'] = db_query('SELECT sku, COUNT(li.line_item_id) AS support FROM {commerce_product} p LEFT JOIN {commerce_line_item} li ON p.sku = li.line_item_label GROUP BY sku HAVING support >= :min_support', array(':min_support' => $min_support))->fetchCol();
    
    $context['sandbox']['progress'] = 0;
    $context['sandbox']['max'] = count($context['sandbox']['product_sku']);
    
    $context['results'] = array(
      'frequent_sets' => array(
        1 => array(
          array(
            'prefix' => array(),
            'sets' => array(),
          ),
        ),
      ),
    );
  }
  
  $sku = $context['sandbox']['product_sku'][$context['sandbox']['progress']];
  $context['results']['frequent_sets'][1][0]['sets'][] = array(
    'items' => array($sku),
    'tidlist' => db_query("SELECT order_id FROM {commerce_line_item} WHERE line_item_label = :sku", array(':sku' => $sku))->fetchCol()
  );

  $context['sandbox']['progress'] ++;
  
  if ($context['sandbox']['progress'] != $context['sandbox']['max']) {
    $context['finished'] = $context['sandbox']['progress'] / $context['sandbox']['max'];
  }
}

function commerce_reports_patterns_mine($min_support, &$context) {
  if (empty($context['sandbox'])) {
    $context['sandbox']['set_length'] = 2;
  }
  
  $length = $context['sandbox']['set_length'];
  $context['results']['frequent_sets'][$length] = array();
  
  $prev_length = $length - 1;
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
        
        if (count($candidate['tidlist']) >= $min_support) {
          $new_items = array_diff($candidate['items'], $partition_prefix);
          $prefix = array_merge($partition_prefix, array(reset($new_items)));

          _commerce_reports_patterns_add_set($context['results']['frequent_sets'][$length], $prefix, $candidate);
        }
      }
    }
  }
  
  $context['sandbox']['set_length'] ++;
  
  if (count($context['results']['frequent_sets'][$length])) {
    $context['finished'] = 0;
    $context['message'] = 'Finished generating frequent itemsets with length ' . $length;
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
  } else {
    drupal_set_message(t('There was a problem generating frequent itemsets.'), 'error');
  }
}
