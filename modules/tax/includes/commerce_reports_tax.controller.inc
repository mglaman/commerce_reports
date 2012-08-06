<?php
/**
 * @file
 * Entity controller for Tax entities.
 */

class CommerceReportsTaxEntityController extends DrupalCommerceEntityController {

  public function create(array $values = array()) {
    global $user;

    $values += array(
      'report_id' => NULL,
      'title' => '',
      'created' => '',
      'changed' => '',
      'order_statuses' => array('completed', 'pending'),
      'start' => REQUEST_TIME - 31556926,
      'end' => REQUEST_TIME,
      'detailled' => '',
    );

    return parent::create($values);
  }
  
  public function save($report, DatabaseTransaction $transaction = NULL) {
    if (!isset($transaction)) {
      $transaction = db_transaction();
      $started_transaction = TRUE;
    }
    
    try {
      if (is_array($report->start)) {
        $report->start = mktime(0, 0, 0, $report->start['month'], $report->start['day'], $report->start['year']);
      }
      
      if (is_array($report->end)) {
        $report->end = mktime(0, 0, 0, $report->end['month'], $report->end['day'], $report->end['year']);
      }

      // Determine if we will be inserting a new report.
      $report->is_new = empty($report->report_id);

      // Set the timestamp fields.
      if (empty($report->created)) {
        $report->created = REQUEST_TIME;
      }

      $report->changed = REQUEST_TIME;
      
      $result = parent::save($report, $transaction);
      if (empty($result)) {
        throw new Exception();
      }

      return $result;
    }
    catch (Exception $e) {
      if (!empty($started_transaction)) {
        $db_transaction->rollback();
        watchdog_exception($this->entityType, $e);
      }
      throw $e;
    }
  }
  
  public function delete($ids, DatabaseTransaction $transaction = NULL) {
    $entities = $ids ? $this->load($ids) : FALSE;
    if (!$entities) {
      return;
    }
    
    if (!isset($transaction)) {
      $transaction = db_transaction();
      $started_transaction = TRUE;
    }
    
    try {
      commerce_reports_tax_report_clear_multiple($entities);
      
      $result = parent::delete($ids, $transaction);
      if (empty($result)) {
        throw new Exception();
      }
      
      return TRUE;
    }
    catch (Exception $e) {
      if (!empty($started_transaction)) {
        $db_transaction->rollback();
        watchdog_exception($this->entityType, $e);
      }
      throw $e;
    }
  }
  
  public function attachLoad(&$queried_reports, $revision_id = FALSE) {
    foreach ($queried_reports as $report_id => &$report) {
      $report->order_statuses = unserialize($report->order_statuses);
    }

    // Call the default attachLoad() method. This will add fields and call
    // hook_user_load().
    parent::attachLoad($queried_reports, $revision_id);
  }
  
}
