<?php

class commerce_reports_handler_field_commerce_order_created extends views_handler_field {

  var $granularities = array(
  	'Y-m' => array(
  	  'label' => 'Monthly',
  	  'interval' => 'P1M',
  	  'relative' => 'first day of this month',
  	  'displayFormat' => 'F Y',
  	),
  	'o-W' => array(
  	  'label' => 'Weekly',
  	  'interval' => 'P1W',
  	  'relative' => 'this week'
  	),
  	'Y-m-d' => array(
  	  'label' => 'Daily',
  	  'interval' => 'P1D',
  	),
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
      '#options' => $this->options(),
      '#default_value' => $this->options['default_granularity']
    );
    
    $timestamp = REQUEST_TIME - 60*60*24*30;
    
    $form['startDate'] = array(
      '#type' => 'date',
      '#title' => t('Start date'),
      '#default_value' => array(
        'day' => format_date($timestamp, 'custom', 'j'),
        'month' => format_date($timestamp, 'custom', 'n'),
        'year' => format_date($timestamp, 'custom', 'Y'),
      ),
    );
    
    $form['endDate'] = array(
      '#type' => 'date',
      '#title' => t('End date'),
      '#default_value' => array(),
    );
  }
  
  function accept_exposed_input($input) {
    if (empty($this->options['exposed'])) {
      return TRUE;
    }
    
    if (!empty($input['granularity']) && in_array($input['granularity'], array_keys($this->options()))) {
      $this->granularity = $input['granularity'];
    } else{
      return FALSE;
    }
    
    if (is_array($input['startDate']) && is_array($input['endDate'])) {
      $now = new DateTime();
      
      $start = commerce_reports_datetime_form($input['startDate']);
      $end = commerce_reports_datetime_form($input['endDate']);
    } else {
      return FALSE;
    }
    
    if ($end > $start) {
      $this->startDate = $start;
      $this->endDate = $end;
    } else {
      return FALSE;
    }
    
    $this->toFirstDay($this->startDate);
    $this->toFirstDay($this->endDate);
    
    return TRUE;
  }
  
  function toFirstDay(DateTime $dt) {
    $dt->setTime(0, 1);
    
    if (!empty($this->granularities[$this->getFormat()]['relative'])) {
      $dt->modify($this->granularities[$this->getFormat()]['relative']);
    }
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
      '#options' => $this->options(),
      '#default_value' => $this->options['default_granularity']
    );
  }
  
  function options() {
    static $cache;
    
    if (empty($cache)) {
      $cache = array();
      
      foreach ($this->granularities as $format => $data) {
        $cache[$format] = $data['label'];
      }
    }
    
    return $cache;
  }
  
  function getFormat() {
    if (!empty($this->options['exposed']) && !empty($this->granularity)) {
      return $this->granularity;
    }
    
    return $this->options['default_granularity'];
  }
  
  function getInterval() {
    return new DateInterval($this->granularities[$this->getFormat()]['interval']);
  }

  /**
   * Adds the date to the query. 
   * Adds GROUP BY and ORDER BY clause.
   */
  function query() {
    $this->ensure_my_table();
    
    $this->field_alias = sprintf("%s_%s_granularity", $this->table_alias, $this->real_field);
    
    // Adding the field to teh order by clause automatically adds it to the query.
    // We sort the results in an descending order, because this is expected in the interpolation algorithm.
    $params = $this->options['group_type'] != 'group' ? array('function' => $this->options['group_type']) : array();
    $this->query->add_orderby($this->table_alias, $this->real_field, 'DESC', $this->field_alias, $params);
    
    // We group by the field using a SQL function to transform the timestamp to certain formats.
    // This way the database does the aggregation for us.
    $field_name = views_date_sql_format($this->getFormat(), $this->table_alias.'.'.$this->real_field);
    $this->query->add_groupby($field_name);
    
    // Add the interval boundaries if they're defined.
    if (!empty($this->startDate) && !empty($this->endDate)) {
      $this->query->add_where_expression(0, "{$this->real_field} BETWEEN {$this->startDate->getTimestamp()} AND {$this->endDate->getTimestamp()}");
    }

    $this->add_additional_fields();
  }
  
  function render($values) {
    $dt = $this->get_value($values);
    
    $format = $this->getFormat();
    if (!empty($this->granularities[$format]['displayFormat'])) {
      $format = $this->granularities[$format]['displayFormat'];
    }
    
    $value = format_date($dt->getTimestamp(), 'custom', $format);
    
    return $this->sanitize_value($value);
  }
  
  /**
   * Interpolates the missing dates linearly.
   */
  function post_execute(&$values) {
    $totalRetrieved = count($values);
    
    if ($totalRetrieved == 0) {
      return;
    }
    
  	$retrieved = $values;
  	$values = array();
  	
  	// Create the interval using the chosen granularity. 
	  $interval = $this->getInterval();
	  
	  foreach ($retrieved as &$record) {
	    $timestamp = new DateTime();
      $timestamp->setTimestamp($record->{$this->field_alias});
      $this->toFirstDay($timestamp);
      
      $record->{$this->field_alias} = $timestamp;
	  }
  	
  	// First see if the returned data contains the requested date interval.
  	// If not, add these boundaries and let the interpolation logic do the rest.
  	
  	// Check if start date is included.
  	if (end($retrieved)->{$this->field_alias} > $this->startDate) {
  	  $value = (object) array($this->field_alias => $this->startDate);
  	  
      $totalRetrieved = array_push($retrieved, $value);
  	}
  	
  	// Check if end date is included.
  	if (reset($retrieved)->{$this->field_alias} < $this->endDate) {
  	  $value = (object) array($this->field_alias => clone $this->endDate);
  	  
      $totalRetrieved = array_unshift($retrieved, $value);
  	}
  	
  	// Next we run through all the results and we change the UNIX timestamps integer into DateTime objects.
  	// This is easy for processing. Note that we loop backwards through the array of results.
  	for ($i = $totalRetrieved - 1; $i >= 0; $i --) {
  		$item = $retrieved[$i];
  		$values[] = $item;
  		
  		// We always interpolate between two dates. If we have arrived at the start of the array,
  		// interpolation isn't necessary anymore.
  		if ($i != 0) {
    		// In PHP, objects are passed by reference. We clone the current timestamp to use 
    		// it in the interpolation algorithm.
    		$current = clone $item->{$this->field_alias};
  		
  		  // Get the next result item.
	  		$nextItem = $retrieved[$i - 1];
        $next = clone $nextItem->{$this->field_alias};

	  		// DatePeriod includes the starting date, but not the ending date.
	  		// Add one interval to avoid double date entries. This is why we clone the timestamp.
	  		$current->add($interval);
	  		
	  		// Linear interpolation between the two dates.
		  	$period = new DatePeriod($current, $interval, $next);

		  	foreach ($period as $dt) {
		  		$value = (object) array($this->field_alias => $dt);
		  		
		  		$values[] = $value;
		  	}
	  	}
  	}
  	
  	$values = array_reverse($values);
  }
  
}
