<?php
// $Id$

/**
 * @file
 * Builds placeholder replacement tokens for nodereview-related data.
 */

/**
 * Implements of hook_token_info().
 */
function nodereview_token_info() {

  $type = array(
    'name' => t('NodeReviews'),
    'description' => t('Tokens related to individual content items, or "nodereviews".'),
    'needs-data' => 'nodereview',
  );

  $node['node-reviewed-nid'] = array(
    'name' => t('Reviewed Node ID'),
    'description' => t('The reviewed node id. This will only appear for nodereview type nodes.'),
  );
  $node['node-reviewed-path-alias'] = array(
    'name' => t('Reviewed Node Path'),
    'description' => t('The reviewed node path. This will only appear for nodereview type nodes.'),
  );
  $node['node-reviewed-title-raw'] = array(
    'name' => t('Reviewed Node Title'),
    'description' => t('Title of the reviewed node. This will only appear for nodereview type nodes.'),
  );

  return array(
    'types' => array(
      'nodereview' => $type,
    ),
    'tokens' => array(
      'node' => $node,
    ),
  );
}

/**
 * Implements of hook_tokens().
 */
function nodereview_tokens($type, $tokens, array $data = array(), array $options = array()) {
  $replacements = array();

  if ($type == 'node' && !empty($data['node'])) {
    $node = $data['node'];

    foreach ($tokens as $name => $original) {

      switch ($name) {
        case 'node-reviewed-nid':
          $replacements[$original] = $node->nid;
          break;

        case 'node-reviewed-path-alias':
          $replacements[$original] = drupal_get_path_alias('node/' . $node->nid);
          break;

        case 'node-reviewed-title-raw':
          $replacements[$original] = $node->title;
          break;
      }
    }
  }

  return $replacements;
}