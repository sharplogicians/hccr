<?php

/**
 * @file
 * Provide a views handlers for nodereview data fields.
 */

class nodereview_count_reviews_views_handler_field extends views_handler_field_numeric {
  function construct() {
    parent::construct();
    $this->field_alias = 'reviews_count';
  }

  function query() {
    $this->ensure_my_table();
    $join = new views_join();
    $join->construct('nodereview', 'node', 'nid', 'reviewed_nid');
    $alias = $this->query->add_relationship('nodereview', $join, 'node');
    $this->query->add_table('nodereview', $alias);
    // Add the field.
    $this->query->add_field('nodereview', 'nid', $this->field_alias, array('count' => TRUE));

  }
}
