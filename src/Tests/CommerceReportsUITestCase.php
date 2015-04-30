<?php

namespace Drupal\commerce_reports\Tests;

/**
 * Class CommerceReportsUITestCase
 */
class CommerceReportsUITestCase extends CommerceReportsBaseTestCase {

  public static function getInfo() {
    return array(
      'name' => 'Reports user interface',
      'description' => 'Test the reports user interface.',
      'group' => 'Commerce Reports',
    );
  }

  protected function _getLinks($label) {
    $links = $this->xpath('//a[normalize-space(text())=:label]', array(':label' => $label));

    return $links;
  }

  public function testMenuIntegration() {
    $this->drupalLogin($this->store_admin);

    $this->drupalGet('admin');
    $links = $this->_getLinks(t('Reports'));
    $this->assertEqual(count($links), 1, t("The correct amount of menu entries to 'Reports' was found on the administration page."));
    if ($links) {
      $attributes = reset($links)->attributes();
      $this->assertEqual($attributes['href'], '/?q=admin/reports', t('The menu entry points to the correct page.'));
    }

    $this->drupalGet('admin/commerce');
    $links = $this->_getLinks(t('Reports'));
    $this->assertEqual(count($links), 1, t("The correct amount of menu entries to 'Reports' was found on the store administration page."));
    if ($links) {
      $attributes = reset($links)->attributes();
      $this->assertEqual($attributes['href'], '/?q=admin/commerce/reports', t('The menu entry points to the correct page.'));
    }

    $this->drupalGet('admin/commerce/reports');
    $this->assertResponse(200, t('Reports admin can access reports.'));
  }

}
