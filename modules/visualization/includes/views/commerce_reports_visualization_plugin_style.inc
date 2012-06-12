<?php

/**
 * Style plugin uses views ui to configure views data for rendering charts.
 *
 * @ingroup views_style_plugins
 */
class commerce_reports_visualization_plugin_style extends views_plugin_style {

	function init(&$view, &$display, $options = NULL) {
		parent::init($view, $display, $options);
		
	}

  // Set default options
  function option_definition() {
    $options = parent::option_definition();
    
    $options['fields'] = array('default' => array());
    $options['xAxis'] = array('default' => '');
    $options['invertXAxis'] = array('default' => FALSE);
    
    return $options;
  }
  
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    
    $fields = $this->display->handler->get_field_labels();
    
    foreach ($fields as $field => $column) {
      $handler = $this->display->handler->handlers['field'][$field];
      
      $form['fields'][$field] = array(
        '#type' => 'fieldset',
        '#title' => $field,
        '#collapsible' => TRUE,
        '#collapsed' => empty($this->options['fields'][$field]),
      );
      
      $form['fields'][$field]['type'] = array(
        '#type' => 'select',
        '#title' => t('Chart type'),
        '#options' => array(
          'line' => 'Line chart',
          'pie' => 'Pie chart',
        ),
        '#default_value' => $this->options['fields'][$field]['type'],
        '#empty_value' => FALSE,
      );

      $form['fields'][$field]['label'] = array(
        '#type' => 'select',
        '#title' => t('Label column'),
        '#options' => $fields,
        '#default_value' => $this->options['fields'][$field]['label'],
        '#empty_value' => FALSE,
        '#dependency' => array('style_options', 'fields', $field, 'type'),
      );
      
      if ($handler->click_sortable()) {
        $form['fields'][$field]['sort'] = array(
          '#type' => 'select',
          '#title' => t('Sort'),
          '#options' => array(
            'DESC' => t('Descending'),
            'ASC' => t('Ascending'),
          ),
          '#default_value' => $this->options['fields'][$field]['sort'],
          '#empty_value' => FALSE,
        );
      }
    }
    
    $form['xAxis'] = array(
      '#type' => 'select',
      '#title' => t('X-axis labels'),
      '#options' => $fields,
      '#default_value' => $this->options['xAxis'],
      '#empty_value' => FALSE,
    );
    
    $form['invertXAxis'] = array(
      '#type' => 'checkbox',
      '#title' => t('Should the x-axis get inverted?'),
      '#default_value' => $this->options['invertXAxis'],
    );
  }
  
  function build_sort() {
    foreach ($this->options['fields'] as $field => $option) {
      $handler = $this->display->handler->handlers['field'][$field];
      
      if ($option['sort'] && $handler->click_sortable()) {
        $handler->click_sort($option['sort']);
      }
    }
    
    return FALSE;
  }

  function options_validate(&$form, &$form_state) {
    // Implement if needed.
  }

  function options_submit(&$form, &$form_state) {
    // Implement if needed.
  }

}

