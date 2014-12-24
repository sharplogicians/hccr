<?php

/**
 * @file
 * Used to build the nodereview content type form
 */

/**
 * Implements of hook_access().
 *
 */
function nodereview_access($op, $node) {
  global $user;

  if ($op == 'create') {
    // Only users with permission to do so may create this node type.
    return user_access('submit reviews');

  }

  // Users who create a node may edit or delete it later, assuming they have the
  // necessary permissions.
  if ($op == 'update' || $op == 'delete') {
    if (user_access('administer reviews') || (user_access('edit own reviews') && ($user->uid == $node->uid))) {
      return TRUE;
    }
  }

  if ($op == 'view') {
    return user_access('read reviews');
  }
}

/**
 * Implements of hook_form().
 */
function nodereview_form($node, &$form_state) {
  // This is for the LOCAL_TASK version, node/nid/addreview
  if (empty($node->reviewed_nid)) {
    return array();
  }
  $type = node_type_get_type($node);

  $form = array();
  $form['reviewed_nid'] = array(
    '#type' => 'hidden',
    '#value' => (!empty($node->reviewed_nid)) ? $node->reviewed_nid : '',
  );

  $form['title'] = array(
    '#type' => 'textfield',
    '#title' => check_plain(t($type->title_label)),
    '#default_value' => (!empty($node->title)) ? $node->title : '',
    '#required' => TRUE,
    '#weight' => -50,
  );

  $reviewed_node = node_load((int)$node->reviewed_nid);

  $form['reviews']['#tree'] = TRUE;
  $form['reviews']['#weight'] = 0;

  $sql = "SELECT * FROM {nodereview_axes} 
          WHERE node_type = :type
          ORDER BY weight, tag";

  $result = db_query($sql, array(':type' => $reviewed_node->type));
  while ($record = $result->fetchObject()) {
    _nodereview_form_review($form, $record, $node);
  }

  // We'll use a single filter format for all textareas on the page
  //$form['filter'] = filter_process_format($node->format);
  return $form;
}

/**
 * Add the review axis to the node edit form
 *
 * @param $form
 *  The form object for the node edit form
 * @param $axis
 *  An object representing the axis for which to display the form component
 * @param $reviews
 *  An array of review objects from this node
 * @param $votes
 *  An array of votes (scores) for this review, keyed by axis name
 */
function _nodereview_form_review(&$form, $axis, $node) {

  $average_rating = round(NODEREVIEW_MAXRATING / 2) * 10;

  for ($i = 1; $i < (NODEREVIEW_MAXRATING + 1); $i++) {
    $option_value = round(($i / NODEREVIEW_MAXRATING) * 100);
    if (NODEREVIEW_LABEL_ENABLE) {
      $options[$option_value] = variable_get('nodereview_rating_label' . $i, '');
    }
    else {
      $options[$option_value] = $i;
    }
  }

  $form['reviews'][$axis->aid] = array(
    '#type' => 'fieldset',
    '#title' => (!empty($axis->tag)) ? $axis->tag : '',
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['reviews'][$axis->aid]['score'] = array(
    '#type' => 'select',
    '#title' => t('Score'),
    '#options' => $options,
    '#default_value' => (!empty($node->review->score)) ? $node->review->score
      : $average_rating,
    '#description' => $axis->description,
    '#required' => TRUE,
  );
  
  if (NODEREVIEW_FIVESTAR_ENABLE) {
    $form['reviews'][$axis->aid]['score']['#type'] = 'fivestar';
    $form['reviews'][$axis->aid]['score']['#stars'] = NODEREVIEW_MAXRATING;
  }

  // the #required field now looks at the field we've added to the database indicating whether
  // or not a description/comments are required per axis
  $form['reviews'][$axis->aid]['review'] = array(
    '#type' => 'textarea',
    '#title' => t('Review'),
    '#default_value' => (!empty($node->review->review)) ? $node->review->review
      : '',
    '#required' => $axis->description_required,
  );

}

/**
 * Implements of hook_validate().
 */
function nodereview_validate($node, $form, &$form_state) {
  $review_count = db_query("SELECT Count(*) FROM {node} WHERE nid = :nid", array(':nid' => $node->reviewed_nid))->fetchObject();

  if (!$node->reviewed_nid || !$review_count) {
    // There is no such node, so error
    form_set_error('reviewed_nid', t('The node you are trying to review does not exist.'));
  }
  if (!empty($node->reviews)) {
    foreach ($node->reviews as $aid => $review) {
      if (!$review['score']) {
        form_set_error('', t('You must enter a score for every axis.'));
      }
      //updates so that if there is no review and a view is required that the form won't validate
      if (empty($review['review'])) {
        form_set_error('', t('You must enter a review for every axis.'), NULL);
      }
    }
  }
}

/**
 * Implements of hook_load().
 */
function nodereview_load($nodes) {
  foreach ($nodes as &$node) {
    $node->reviewed_nid = db_query("SELECT reviewed_nid FROM {nodereview} WHERE nid = :nid", array(':nid' => $node->nid))->fetchField();
    $reviewed_node = node_load($node->reviewed_nid);
    // And now get the actual review info.  The numeric scores are stored with voteapi,
    // while textual reviews are in our own auxiliary table.  We need to merge them properly
    $criteria = array(
      'entity_type' => 'node',
      'entity_id' => $reviewed_node->nid,
      'uid' => $node->uid,
    );
    $votes_obj = votingapi_select_votes($criteria);
    foreach ($votes_obj as $vote) {
      $votes[trim($vote['tag'])] = $vote;
    }

    $query = db_select('nodereview_reviews', 'nr');
    $query->join('nodereview_axes', 'na', 'nr.aid=na.aid');
    $query->fields('nr', array('aid', 'review'));
    $query->fields('na', array('tag'));
    $query->condition('nid', (int)$node->nid);
    $node->review = (object)$query->execute()->fetchAssoc();

    $node->review->score = $votes[trim($node->review->tag)]['value'];
  }
}

/**
 * Implements of hook_insert().
 */
function nodereview_insert($node) {
  db_insert('nodereview')
    ->fields(array('nid', 'reviewed_nid'))
    ->values(array(
                    'nid' => $node->nid,
                    'reviewed_nid' => $node->reviewed_nid,
                  ))
    ->execute();

  nodereview_save_reviews($node);
}

/**
 * Implements of hook_update().
 */
function nodereview_update($node) {
  // Table name no longer needs {}
  db_update('nodereview')
    ->fields(array(
                  'reviewed_nid' => $node->reviewed_nid,
                ))
    ->condition('nid', $node->nid, '=')
    ->execute();

  // Delete and rebuild the textual reviews, but the votingapi takes care of overwriting old values
  db_delete('nodereview_reviews')
    ->condition('nid', $node->nid, '=')
    ->execute();

  nodereview_save_reviews($node);
}

/**
 * This function implements save a node of type nodereview
 * @param $node
 * @return void
 */
function nodereview_save_reviews($node) {
  $votes = array();

  $reviewed_nid = db_query("SELECT type FROM {node} WHERE nid = :nid", array(':nid' => $node->reviewed_nid))->fetchObject();

  $axes = nodereview_list_axes($reviewed_nid->type);
  if (!empty($node->reviews)) {
    foreach ($node->reviews as $aid => $review) {
      // Save the text review
      db_insert('nodereview_reviews')
        ->fields(array('nid', 'aid', 'review'))
        ->values(array(
                        'nid' => (int)$node->nid,
                        'aid' => (int)$aid,
                        'review' => check_plain($review['review']),
                      ))
        ->execute();
      // And use the votingapi to save the score
      $votes[] = array('value' => $review['score'], 'tag' => $axes[$aid], 'entity_type' => 'node', 'entity_id' => $node->reviewed_nid);

    }
  }
  votingapi_set_votes($votes);
}

/**
 * Implements of hook_delete().
 */
function nodereview_delete($node) {

  db_delete('nodereview')
    ->condition('nid', $node->nid, '=')
    ->execute();

  db_delete('nodereview_reviews')
    ->condition('nid', $node->nid, '=')
    ->execute();

  $criteria = array(
    'entity_type' => 'node',
    'entity_id' => $node->reviewed_nid,
    'uid' => $node->uid,
  );

  $vote_obj = votingapi_select_votes($criteria);
  // Delete the votes in the votingapi associated with this node
  votingapi_delete_votes($vote_obj);
  votingapi_recalculate_results('node', $node->reviewed_nid);
}

/**
 * Implements of hook_view().
 */
function nodereview_view($node, $view_mode) {
  // Previews are just plain ugly, because the $node object is not really a node
  // but a mutated $_POST.  It has to be handled completely differently.
  if (!empty($node->op) && $node->op == 'Preview') {
    // We have to load in our axis data, which the $_POST doesn't have but we need
    $query = db_select('nodereview_axes', 'na');
    $query->join('node', 'n', 'na.node_type=n.type');
    $query->fields('na', array('tag', 'aid'));
    $query->condition('n.nid', (int)$node->reviewed_nid);
    $node->review->tag = $query->execute()->fetchField();
    $node->review->tag = trim($node->review->tag);
    $node->review->score = (int) ($_POST['reviews'][1]['score']);
    $node->review->review = check_plain($_POST['reviews'][1]['review']);

    $node->content['review'][$node->review->tag] = array(
      '#markup' => theme('nodereview_review_preview', array('review' => $node->review, 'node' => $node)),
    );
  }
  else {
    // Do a markup check on the fields
    $node->review->review = check_markup($node->review->review);
    if ($view_mode == 'teaser') {
      $node->content['review'] = array(
        '#markup' => theme('nodereview_teaser', array('node' => $node)),
      );
    }
    else {
      $node->content['review'][$node->review->tag] = array(
        '#markup' => theme('nodereview_review_body', array('review' => $node->review, 'node' => $node)),
      );
    }

  }
  return $node;
}
