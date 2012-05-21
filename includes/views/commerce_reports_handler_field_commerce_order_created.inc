<?php

/**
 * Create a CCYY-WW field so that we can count product orders by week.
 */
class commerce_reports_handler_field_commerce_order_created extends views_handler_field {

  protected $formats = null;
  
  function construct() {
    parent::construct();
    
    $this->formats = array('Y-m' => t('Montly'), 'Y-W' => t('Weekly'), 'Y-m-d' => t('Daily'));
    
    $this->real_field = 'created';
  }

  function query() {
    $this->ensure_my_table();
    
    $format = $this->options['timestamp_format'];
    $params = $this->options['group_type'] != 'group' ? array('function' => $this->options['group_type']) : array();

    $field_name = views_date_sql_format($format, $this->table_alias.'.'.$this->real_field);

    $alias = sprintf("%s_%s_timestamp", $this->table_alias, $this->real_field);
    $this->field_alias = $this->query->add_field(NULL, $field_name, $alias, $params);

    if ($this->options['group_type'] == 'group') {
      $this->query->add_groupby($alias);
    }

    $this->add_additional_fields();
  }
  
  function option_definition() {
    $options = parent::option_definition();
    
    $options['timestamp_format'] = array(
      'default' => ''
    );
    
    return $options;
  }
  
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    
    $form['timestamp_format'] = array(
      '#type' => 'radios',
      '#title' => t('Timestamp format'),
      '#options' => $this->formats,
      '#default_value' => $this->options['timestamp_format']
    );
  }
  
}
