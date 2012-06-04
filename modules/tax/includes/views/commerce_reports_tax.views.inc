<?php

/**
 * Implements hook_views_data()
 */
function commerce_reports_tax_views_data() {
  $data = array();

  // Base information.
  $data['commerce_reports_tax']['table']['group']  = t('Commerce Reports Tax');

  $data['commerce_reports_tax']['table']['base'] = array(
    'field' => 'order_id',
    'title' => t('Commerce Reports Tax'),
    'help' => t('The tax breakdown of a Commerce Order.'),
    'access query tag' => 'commerce_reports_access',
  );
  $data['commerce_reports_tax']['table']['entity type'] = 'commerce_order';

  // Expose the Order ID.
  $data['commerce_reports_tax']['order_id'] = array(
    'title' => t('Order ID', array(), array('context' => 'a drupal commerce order')),
    'help' => t('The unique internal identifier of the order.'),
    'field' => array(
      'handler' => 'commerce_order_handler_field_order',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'commerce_order_handler_argument_order_order_id',
      'name field' => 'order_number',
      'numeric' => TRUE,
      'validate type' => 'order_id',
    ),
    'relationship' => array(
      'handler' => 'views_handler_relationship',
      'base' => 'commerce_order',
      'field' => 'order_id',
      'label' => t('Order', array(), array('context' => 'a drupal commerce order')),
    ),
  );

  // Expose the created date.
  $data['commerce_reports_tax']['created'] = array(
    'title' => t('Order created date'),
    'help' => t('The date the order was created.'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_date',
    ),
  );

  // Expose the transaction currency.
  $data['commerce_reports_tax']['currency_code'] = array(
    'title' => t('Currency'),
    'help' => t('The currency of the transaction.'),
    'field' => array(
      'handler' => 'commerce_payment_handler_field_currency_code',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'commerce_payment_handler_filter_currency_code',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  // Expose each of the taxes
  foreach (commerce_tax_rates() as $name => $rate) {
    $data['commerce_reports_tax'][$name] = array(
      'title' => $rate['display_title'],
      'help' => t('The @tax on the order.', array('@tax' =>  $rate['display_title'])),
      'field' => array(
        'handler' => 'commerce_payment_handler_field_amount',
        'click sortable' => TRUE,
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
    );
  }

  return $data;
}
