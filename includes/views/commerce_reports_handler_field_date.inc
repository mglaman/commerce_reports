<?php

/**
 * Create a CCYY-WW field so that we can count product orders by week.
 */
class commerce_reports_handler_field_commerce_order_created extends views_handler_field {

  var $formats = array(
  	'Y-m' => 'Monthly', 
  	'Y-W' => 'Weekly', 
  	'Y-m-d' => 'Daily',
  );
  
  var $intervals = array(
  	'Y-m' => 'P1M', 
  	'Y-W' => 'P1W', 
  	'Y-m-d' => 'P1D',
  );

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
    
    $form['startDate'] = array(
      '#type' => 'date',
      '#title' => t('Start date'),
      '#default_value' => array(),
    );
    
    $form['endDate'] = array(
      '#type' => 'date',
      '#title' => t('End date'),
      '#default_value' => array(),
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

  /**
   * Adds the date to the query. 
   * Adds GROUP BY and ORDER BY clause.
   */
  function query() {
    $this->ensure_my_table();
    
    $this->field_alias = sprintf("%s_%s_granularity", $this->table_alias, $this->real_field);
    
    $params = $this->options['group_type'] != 'group' ? array('function' => $this->options['group_type']) : array();
    $this->query->add_orderby($this->table_alias, $this->real_field, 'DESC', $this->field_alias, $params);
    
    $field_name = views_date_sql_format($this->getGranularity(), $this->table_alias.'.'.$this->real_field);
    $this->query->add_groupby($field_name);

    $this->add_additional_fields();
  }
  
  function render($values) {
    $dt = $this->get_value($values);
    $value = $dt->format($this->getGranularity());
    
    return $this->sanitize_value($value);
  }
  
  /**
   * Interpolates the missing dates linearly.
   */
  function post_execute(&$values) {
  	$retrieved = $values;
  	$values = array();
  	
  	$totalRetrieved = count($retrieved);
  	
  	for ($i = $totalRetrieved - 1; $i >= 0; $i --) {
  		$item = $retrieved[$i];
  		
  		$timestamp = new DateTime();
      $timestamp->setTimestamp($item->{$this->field_alias});
      $this->normalize($timestamp);
      
      $item->{$this->field_alias} = $timestamp;
  		$values[] = $item;
  		
  		$current = clone $timestamp;
  		
  		if ($i != 0) {
	  		$nextItem = $retrieved[$i - 1];
        
        $next = new DateTime();
        $next->setTimestamp($nextItem->{$this->field_alias});
        $this->normalize($next);
	  		
	  		$interval = new DateInterval($this->intervals[$this->getGranularity()]);
	  		$current->add($interval);
	  		
		  	$period = new DatePeriod($current, $interval, $next);
		  	
		  	foreach ($period as $dt) {
		  		$value = (object) array($this->field_alias => $dt);
		  		
		  		$values[] = $value;
		  	}
	  	}
  	}
  	
  	$values = array_reverse($values);
  }
  
  function normalize(DateTime $dt) {
    $dt->setTime(0, 0);
    
    switch ($this->getGranularity()) {
      case "Y-m":
        $dt = $dt->modify("first day of this month");
        
        break;
      case "Y-W":
        $dt = $dt->modify("first day of this week");
        
        break;
      case "Y-m-d":
        break;
    }
    
    return $dt;
  }
  
}
