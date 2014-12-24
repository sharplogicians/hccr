<?php
  /**
 * @file
 * This is to implement view functionality
 */

/**
 * Implements hook_views_data()
 */
function nodereview_views_data() {
  $data['nodereview']['table']['group'] = t('Node Review');
  $data['nodereview']['table']['join']['node'] = array(
    'left_field' => 'nid',
    'field' => 'nid',
  );

  $data['nodereview']['reviewed_nid'] = array(
    'title' => t('Reviewed Node'),
    'help' => t('The node which is reviewed.'),
    'relationship' => array( //this creates the relationship with node reviewed linking all available fields from the node table
      'base' => 'node',
      'field' => 'nid',
      'handler' => 'views_handler_relationship',
      'label' => t('Reviewed Node'),
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
      'numeric' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
      'numeric' => TRUE,
    ),

  );

  $data['nodereview']['reviews_count'] = array(
    'title' => t('Count of node reviews'),
    'help' => t('Count of node reviews'),
    'field' => array(
      'handler' => 'nodereview_count_reviews_views_handler_field',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  return $data;
}

/**
 * Implements of hook_views_handlers().
 */
function nodereview_views_handlers() {
  return array(
    'handlers' => array(
      'nodereview_count_reviews_views_handler_field' => array(
        'parent' => 'views_handler_field',
        'path' => drupal_get_path('module', 'nodereview') . '/views'
      ),
    ),
  );
}