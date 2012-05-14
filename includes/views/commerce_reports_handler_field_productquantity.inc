<?php

/**
 * Field handler to get the quantity of products in an order.
 */
class commerce_reports_handler_field_productquantity extends views_handler_field {
  function query() {
  }
  
  function render($values) {
    return isset($this->items['productquantity'][$values->order_id]) ?
      $this->items['productquantity'][$values->order_id] : 0.00;
  }
  
  function pre_query() {
    $query = db_select('commerce_line_item', 'li')
      ->fields('li', array('order_id'))
      ->condition('type', 'product')
      ->groupBy('order_id');
    $query->addExpression('SUM(quantity)', 'quantity');
    $res = $query->execute();
    $rows = $res->fetchAllAssoc('order_id', PDO::FETCH_ASSOC);
    
    $map = array();
    foreach ($rows as $order_id => $row) {
      $map[$order_id] = $row['quantity'];
    }
    $this->items['productquantity'] = $map;
  }
}
