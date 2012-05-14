<?php

/**
 * Create a CCYY-WW field so that we can count product orders by week.
 */
class commerce_reports_handler_field_timestamp_ccyyww extends views_handler_field {
  function query() {
    $this->ensure_my_table();
    $params = $this->options['group_type'] != 'group' ? array('function' => $this->options['group_type']) : array();

    $field_name = views_date_sql_format('Y-W', $this->table_alias . '.' . $this->real_field);

    $alias = sprintf("%s_%s_timestamp_ccyyww", $this->table_alias, $this->real_field);
    $this->field_alias = $this->query->add_field(NULL, $field_name, $alias, $params);

    $this->query->add_groupby($alias); // This seems unnecessary

    $this->add_additional_fields();
  }
}
