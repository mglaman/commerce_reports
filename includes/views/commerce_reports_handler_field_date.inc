<?php

/**
 * Create a CCYY-WW field so that we can count product orders by week.
 */
class commerce_reports_handler_field_commerce_order_created extends views_handler_field {

  var $formats = array('Y-m' => 'Monthly', 'Y-W' => 'Weekly', 'Y-m-d' => 'Daily');

  function option_definition() {
    $options = parent::option_definition();
    
    $options['exposed'] = array(
      'default' => FALSE,
    );
    
    $options['default_granularity'] = array(
      'default' => FALSE,
    );
    
    return $options;
  }
  
  function can_expose() {
    return TRUE;
  }
  
  function exposed_form(&$form, &$form_state) {
    if (empty($this->options['exposed'])) {
      return;
    }
    
    $form['granularity'] = array(
      '#type' => 'select',
      '#title' => t('Granularity'),
      '#options' => $this->formats,
      '#default_value' => $this->options['default_granularity']
    );
  }
  
  function accept_exposed_input($input) {
    if (empty($this->options['exposed'])) {
      return;
    }
    
    if (!empty($input['granularity']) && in_array($input['granularity'], array_keys($this->formats))) {
      $this->granularity = $input['granularity'];
      
      return TRUE;
    }
    
    return FALSE;
  }
  
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    
    $form['exposed'] = array(
      '#type' => 'checkbox',
      '#title' => t('Expose this filter to visitors, to allow them to change it'),
      '#default_value' => $this->options['exposed']
    );
    
    $form['default_granularity'] = array(
      '#type' => 'select',
      '#title' => t('Default granularity'),
      '#options' => $this->formats,
      '#default_value' => $this->options['default_granularity']
    );
  }
  
  function getGranularity() {
    if (!empty($this->options['exposed']) && !empty($this->granularity)) {
      return $this->granularity;
    }
    
    return $this->options['default_granularity'];
  }

  function query() {
    $this->ensure_my_table();
    
    $alias = sprintf("%s_%s_granularity", $this->table_alias, $this->real_field);
    
    $field_name = views_date_sql_format($this->getGranularity(), $this->table_alias.'.'.$this->real_field);
    $params = $this->options['group_type'] != 'group' ? array('function' => $this->options['group_type']) : array();

    $this->field_alias = $this->query->add_field(NULL, $field_name, $alias, $params);
    
    if ($this->options['group_type'] == 'group') {
      $this->query->add_groupby($field_name);
    }

    $this->add_additional_fields();
  }
  
}
