<?php

function commerce_reports_dashboard() {
  drupal_add_js(drupal_get_path('module', 'commerce_reports') .'/commerce_reports.dashboard.js', 'file');
  
  return array(
    commerce_reports_sales_dashboard_block(array(
      'title' => t('Overview'),
      'report' => array(
        'title' => t('Sales reports'),
        'path' => 'admin/commerce/reports/sales',
      ),
      'sections' => array(
        'today' => array(
          'module' => 'views',
          'block' => 'ff7824695a12b49a79aee7d394cbd917',
        ),
        'yesterday' => array(
          'module' => 'views',
          'block' => '1a260a710ed0ccc9e8175e7301e597fe',
        ),
        'month' => array(
          'module' => 'views',
          'block' => '724c01e6b3c93b66c793ff63f7402697',
        ),
      ),
    )),
    commerce_reports_sales_dashboard_block(array(
      'title' => t('Sales'),
      'switchSections' => TRUE,
      'report' => array(
        'title' => t('Sales reports'),
        'path' => 'admin/commerce/reports/sales',
      ),
      'sections' => array(
        'year' => array(
          'title' => 'Year',
          'module' => 'views',
          'block' => 'cc437fbe6b867b448dc946fd925800a3',
        ),
        'month' => array(
          'title' => 'Month',
          'module' => 'views',
          'block' => '1127e4706efe2c1eb8537a65a644e572',
        ),
        'week' => array(
          'title' => 'Week',
          'module' => 'views',
          'block' => 'd70fc459675538d56c73a9f90574211a',
        ),
      ),
    )),
    commerce_reports_sales_dashboard_block(array(
      'title' => t('Customers'),
      'width' => 33,
      'report' => array(
        'title' => t('Customer reports'),
        'path' => 'admin/commerce/reports/customers',
      ),
      'sections' => array(
        'revenue' => array(
          'module' => 'views',
          'block' => 'f3f98e42ba2d4d3103b95e9199cf48fe',
        ),
      ),
    )),
    commerce_reports_sales_dashboard_block(array(
      'title' => t('Products'),
      'switchSections' => TRUE,
      'width' => 33,
      'report' => array(
        'title' => t('Product reports'),
        'path' => 'admin/commerce/reports/products',
      ),
      'sections' => array(
        'revenue' => array(
          'title' => 'Revenue',
          'module' => 'views',
          'block' => 'commerce_reports_products-chart_revenue',
        ),
        'quantity' => array(
          'title' => 'Quantity',
          'module' => 'views',
          'block' => '31eccd6666389cf554f290e91ef9848a',
        ),
      ),
    )),
    commerce_reports_sales_dashboard_block(array(
      'title' => t('Statistics'),
      'width' => 33,
      'sections' => array(
        'customers' => array(
          'module' => 'commerce_reports',
          'block' => 'commerce_reports_customers',
          'width' => '100',
        ),
        'sales' => array(
          'module' => 'commerce_reports',
          'block' => 'commerce_reports_sales',
          'width' => '100',
        ),
      ),
    )),
  );
}

function commerce_reports_sales_dashboard_block($options = array()) {
  $render = array(
    '#theme_wrappers' => array('commerce_reports_dashboard_block'),
    '#title' => $options['title'],
    '#report' => !empty($options['report']) ? l($options['report']['title'], $options['report']['path']) : NULL,
    '#width' => !empty($options['width']) ? $options['width'] : NULL,
  );
  
  $sectionLinks = array();
  $first = reset(array_keys($options['sections']));
  
  foreach ($options['sections'] as $name => $information) {
    $block = block_load($information['module'], $information['block']);
    $block_render = module_invoke($block->module, 'block_view', $block->delta);
    
    $render['sections'][$name] = $block_render;
    $render['sections'][$name]['#width'] = !empty($information['width']) ? $information['width'] : NULL;
    
    if (!empty($options['switchSections'])) {
      $link = array(
        'title' => $information['title'],
        'href' => 'admin/commerce/reports/dashboard',
        'attributes' => array(
          'class' => array(
            'switchSection'
          ),
          'data-section' => $name,
        ),
      );

      if ($name === $first) {
        $link['attributes']['class'][] = 'active';
      }
      
      $sectionLinks[] = $link;
    }
  }
  
  $render['#operations'] = theme('links', array('links' => $sectionLinks, 'attributes' => array()));
  
  if (!empty($options['switchSections'])) {
    $render['#visible'] = array($first);
  } else {
    $render['#visible'] = array_keys($options['sections']);
  }
  
  return $render;
}

