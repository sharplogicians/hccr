<?php

/**
 * @file
 * This is to implement theme functions for nodereview module
 */

/**
 * Implementation of theme_nodereview_configure_axes()
 * We declare this function to theme the axes in table
 * format
 */
function theme_nodereview_configure_axes($vars) {
  $form = $vars['form'];
  $rows = array();
  $output = '';
  foreach (element_children($form['axes']) as $key) {
    $row = array();
    // Strip out the labels on each form element, since they're redundant with the header
    $form['axes'][$key]['use']['#title'] = '';
    $form['axes'][$key]['tag']['#title'] = '';
    $form['axes'][$key]['description']['#title'] = '';
    $form['axes'][$key]['description_required']['#title'] = '';
    $form['axes'][$key]['weight']['#title'] = '';

    $row[] = drupal_render($form['axes'][$key]['aid']) . drupal_render($form['axes'][$key]['use']);
    $row[] = drupal_render($form['axes'][$key]['tag']);
    $row[] = drupal_render($form['axes'][$key]['description']);
    $row[] = drupal_render($form['axes'][$key]['description_required']);
    $row[] = drupal_render($form['axes'][$key]['weight']);
    $rows[] = array(
      'data' => $row,
      'id' => 'nodereview-row-' . $key,
      'class' => array('draggable', 'tabledrag-leaf'),
    );


  }

  $header = array('Use', 'Name', 'Description', 'Require Vote Comments', 'Weight');

  // This is how we get the table to be "inside" the fieldset
  $form['axes']['#children'] = theme('table', array('header' => $header, 'rows' => $rows, 'attributes' => array('id' => 'nodereview-axes')));

  //OPTIONS: drupal_add_tabledrag($table_id, $action, $relationship, $group, $subgroup = NULL, $source = NULL, $hidden = TRUE, $limit = 0);
  drupal_add_tabledrag('nodereview-axes', 'order', 'group', 'weight', NULL, NULL, FALSE);

  $output .= drupal_render_children($form);
  return $output;
}

/**
 * Implementation of  theme_nodereview_review_body
 * We declare this function to theme the full node
 * view
 *
 */
function theme_nodereview_review_body($vars) {
  $review = $vars['review'];
  $maxrating_proportion = round(($review->score / 100) * NODEREVIEW_MAXRATING);

  $fivestar = '';
  $title = $review->tag;
  if (NODEREVIEW_FIVESTAR_ENABLE) {
    $fivestar_args = array('rating' => $review->score, 'stars' => 5, 'tag' => $review->tag);
    $fivestar = theme('fivestar_static', $fivestar_args);
  }
  elseif (NODEREVIEW_LABEL_ENABLE) {
    $title .= ' ' . variable_get('nodereview_rating_label' . $maxrating_proportion, '');
  }
  else {
    $title .= ': ' . $maxrating_proportion . '/' . NODEREVIEW_MAXRATING;
  }

  $output = '<h3>' . $title . '</h3><div class="content">' . $fivestar . $review->review . '</div>';

  return $output;
}

/**
 * Implementation of  theme_nodereview_review_preview
 * We declare this function to theme the node preview
 *
 */
function theme_nodereview_review_preview($vars) {
  $review = $vars['review'];
  $maxrating_proportion = round(($review->score / 100) * NODEREVIEW_MAXRATING);
  $title = $review->tag;
  $fivestar = '';
  if (NODEREVIEW_FIVESTAR_ENABLE) {
    $fivestar_args = array(
      'rating' => $review->score,
      'stars' => 5,
      'tag' => $review->tag
    );
    $fivestar = theme('fivestar_static', $fivestar_args);
  }
  elseif (NODEREVIEW_LABEL_ENABLE) {
    $title = ' '
             . variable_get('nodereview_rating_label' . $maxrating_proportion, '');
  }
  else {
    $title = ': '
             . $maxrating_proportion . '/' . NODEREVIEW_MAXRATING;
  }
  $output = '<h3>'
            . $title
            . '</h3><div class="content">'
            . $fivestar
            . check_markup($review->review /* . $node->format*/)
            . '</div>';

  return $output;
}

/**
 * Implementation of  theme_nodereview_teaser
 * We declare this function to theme the node teaser
 * view
 *
 */
function theme_nodereview_teaser($vars) {
  $node = $vars['node'];
  $output = '';
  static $header;

  // Presumably teaser will be called multiple times on different nodes
  // on the same page, so static cache the static strings
  if (empty($header)) {
    $header = array(t('axis'), t('score'), t('review'));
  }

  $maxrating_proportion = round(($node->review->score / 100) * NODEREVIEW_MAXRATING);
  $row = array();
  $row[] = $node->review->tag;
  if (NODEREVIEW_FIVESTAR_ENABLE) {
    $fivestar_args = array('rating' => $node->review->score, 'stars' => 5, 'tag' => $node->review->tag);
    $row[] = theme('fivestar_static', $fivestar_args, NODEREVIEW_MAXRATING);
  }
  elseif (NODEREVIEW_LABEL_ENABLE) {
    $row[] = variable_get('nodereview_rating_label' . $maxrating_proportion, '');
  }
  else {
    $row[] = $maxrating_proportion . '/' . NODEREVIEW_MAXRATING;
  }
  $row[] = truncate_utf8($node->review->review, 50, TRUE, TRUE);
  $rows[] = $row;

  $output .= theme('table', array('header' => $header, 'rows' => $rows, 'attributes' => array('class' => array('review-teaser'))));
  return $output;
}
