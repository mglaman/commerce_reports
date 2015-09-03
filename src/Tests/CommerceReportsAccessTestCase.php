<?php
/**
 * Created by PhpStorm.
 * User: mglaman
 * Date: 9/3/15
 * Time: 7:05 AM
 */

namespace Drupal\commerce_reports\Tests;


class CommerceReportsAccessTestCase extends CommerceReportsBaseTestCase {
  public static function getInfo() {
    return array(
      'name' => 'Reports user access',
      'description' => 'Tests permission access with results.',
      'group' => 'Commerce Reports',
    );
  }

  function setUp() {
    parent::setUp();
    variable_set('configurable_timezones', 0);
  }


  public function testCustomerReportAsMarketingUser() {
    $this->createOrders();
    $customers = $this->createdCustomersData();
    $this->switchUser($this->marketing_user);

    $report = views_get_view_result('commerce_reports_customers', 'page');

    $this->assertEqual(count($report), min(count($customers), 10), t('The amount of customers (%reported) that is reported (%generated) upon is correct.', array('%reported' => count($report), '%generated' => count($customers))));

    foreach ($report as $line) {
      $uid = $line->uid;

      $orders = $line->commerce_order_users_order_id;
      $revenue = $line->commerce_order_users__field_data_commerce_order_total_commer;
      $average = $line->commerce_order_users__field_data_commerce_order_total_commer_2;

      $this->assertFalse(empty($customers[$uid]), t('The customer %uid that is reported upon exists.', array('%uid' => $uid)));

      if (!empty($customers[$uid])) {
        $this->assertEqual($customers[$uid]['orders'], $orders, t('The reported amount of orders %reported matches the generated amount of orders %generated.', array('%reported' => $orders, '%generated' => $customers[$uid]['orders'])));
        // $this->assertEqual($customers[$uid]['products'], $products, t('The reported amount of line items %reported matches the generated amount of line items %generated.', array('%reported' => $products, '%generated' => $customers[$uid]['products'])));
        $this->assertEqual($customers[$uid]['revenue'], $revenue, t('The reported revenue %reported matches the generated revenue %generated.', array('%reported' => $revenue, '%generated' => $customers[$uid]['revenue'])));
      }
    }
  }

  public function testProductReportAsMarketingUser() {
    $this->createOrders();
    $products = $this->createdProductsData();
    $this->switchUser($this->marketing_user);

    $report = views_get_view_result('commerce_reports_products', 'default');

    $this->assertEqual(count($report), min(count($products), 10), t('The amount of products (%reported) that is reported (%generated) upon is correct.', array('%reported' => count($report), '%generated' => count($products))));

    foreach ($report as $line) {
      $sku = $line->commerce_product_field_data_commerce_product_sku;
      $quantity = $line->commerce_line_item_quantity;
      $revenue = $line->field_data_commerce_total_commerce_total_amount;

      $this->assertFalse(empty($products[$sku]), t('The product %sku that is reported upon exists.', array('%sku' => $sku)));

      if (!empty($products[$sku])) {
        $this->assertEqual($products[$sku]['quantity'], $quantity, t('The reported quantity %reported matches the generated quantity %generated.', array('%sku' => $sku, '%reported' => $quantity, '%generated' => $products[$sku]['quantity'])));
        $this->assertEqual($products[$sku]['revenue'], $revenue, t('The reported revenue %reported matches the generated revenue %generated.', array('%sku' => $sku, '%reported' => $revenue, '%generated' => $products[$sku]['revenue'])));
      }
    }
  }

  public function testSalesReportAsMarketingUser() {
    $this->createOrders();
    $sales = $this->createdOrdersData();
    $this->switchUser($this->marketing_user);

    $report = views_get_view_result('commerce_reports_sales', 'page');

    foreach ($report as $line) {
      $created = $this->getOrderCreated($line);

      if (empty($sales[$created])) {
        $this->assertTrue(empty($line->order_id) && empty($line->commerce_order_total) && empty($line->commerce_order_total_1), t('There was no unintented activity.'));
      }
      else {
        $orders = $sales[$created]['orders'];
        $revenue = $sales[$created]['revenue'];
        $average = (int) floor($revenue / $orders);

        $this->assertEqual($line->order_id, $orders, t('The right amount of orders was reported.'));
        $this->assertEqual($line->field_data_commerce_order_total_commerce_order_total_amount, $revenue, t('The right amount of revenue was reported.'));
        $this->assertEqual((int) floor($line->field_data_commerce_order_total_commerce_order_total_amount_1), $average, t('The right average of revenue was reported.'));
      }
    }
  }

  protected function getOrderCreated($line) {
    return $line->_field_data['order_id_1']['entity']->created;
  }
}
