<?php
/**
 * @file
 * Contains commerce_reports_tax_handler_field_operations.
 */
 
class commerce_reports_tax_handler_field_operations extends views_handler_field {

  function query() {
    $this->ensure_my_table();
    
    $join = new views_join();
    $join->construct('commerce_reports_tax_rate_orders', $this->table, 'report_id', 'report_id', $this->table . '.tax = orders.tax');
    
    $this->query->add_relationship('orders', $join, $this->table);
    $this->field_alias = $this->query->add_field('orders', 'order_id', '', array('function' => 'count'));
    
    $this->report_id_alias = $this->query->add_field($this->table, 'report_id');
    $this->tax_alias = $this->query->add_field($this->table, 'tax');
  }
  
  function render($values) {
    $count = $values->{$this->field_alias};
    
    if (empty($count)) {
      return '';
    }
    else {
      return t('<a href="@order-details-page">View orders (%order-count)</a>', array('@order-details-page' => url('admin/commerce/reports/tax/' . $values->{$this->report_id_alias} . '/' . $values->{$this->tax_alias}), '%order-count' => $count));
    }
  }
  
}
