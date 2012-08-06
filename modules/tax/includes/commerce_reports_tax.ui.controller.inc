<?php
/**
 * @file
 * UI Controller for Tax entities.
 */
 
class CommerceReportsTaxUIController extends EntityDefaultUIController {

  public function operationForm($form, &$form_state, $entity, $op) {
    switch ($op) {
      case 'generate':
        $label = entity_label($this->entityType, $entity);
        $confirm_question = t('Are you sure you want to generate the %label tax report? All previous generated data for this report will be deleted.', array('%label' => $label));
        return confirm_form($form, $confirm_question, $this->path);
        
      default:
        return parent::operationForm($form, $form_state, $entity, $op);
    }
  }
  
  public function applyOperation($op, $entity) {
    switch ($op) {
      case 'generate':
        commerce_reports_tax_generate($entity);
        batch_process('admin/commerce/reports/tax');
        
      default:
        return parent::applyOperation($op, $entity);
    }
  }

  public function overviewTable($conditions = array()) {
    $entities = entity_load($this->entityType, FALSE, $conditions);
    ksort($entities);
    
    $rows = array();
    foreach ($entities as $entity) {
      $additional_cols = array(
        format_date($entity->start, 'custom', 'l j F o'),
        format_date($entity->end, 'custom', 'l j F o'),
        theme('item_list', array(
          'items' => $entity->order_statuses,
        )),
      );

      $rows[] = $this->overviewTableRow($conditions, entity_id($this->entityType, $entity), $entity, $additional_cols);
    }
    // Assemble the right table header.
    $header = array(t('Title'), t('Start date'), t('End date'), t('Order statuses'));
    // Add operations with the right colspan.
    $field_ui = !empty($this->entityInfo['bundle of']) && module_exists('field_ui');
    $colspan = 4;
    $colspan = $field_ui ? $colspan + 2 : $colspan;
    $header[] = array('data' => t('Operations'), 'colspan' => $colspan);

    $render = array(
      '#theme' => 'table',
      '#header' => $header,
      '#rows' => $rows,
      '#empty' => t('None.'),
    );
    return $render;
  }
  
  protected function overviewTableRow($conditions, $id, $entity, $additional_cols = array()) {
    $entity_uri = entity_uri($this->entityType, $entity);

    $row[] = array('data' => array(
      '#theme' => 'entity_ui_overview_item',
      '#label' => entity_label($this->entityType, $entity),
      '#name' => FALSE,
      '#url' => $entity_uri,
      '#entity_type' => $this->entityType),
    );

    // Add in any passed additional cols.
    foreach ($additional_cols as $col) {
      $row[] = $col;
    }

    $colspan = 4;

    $row[] = l(t('view'), $entity_uri['path']);
    $row[] = l(t('edit'), $this->path . '/manage/' . $id);
    $row[] = l(t('delete'), $this->path . '/manage/' . $id . '/delete');
    $row[] = l(t('generate'), $this->path . '/manage/' . $id . '/generate');

    return $row;
  }
  
}
