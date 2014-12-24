<?php


/**
 * @file
 * Administration page callbacks for the nodereview module.
 *
 */


/**
 * Form builder. Configure nodereview node types.
 *
 * @ingroup forms
 *
 */

function nodereview_configure_axes($form, &$form_state, $type, $name) {

  drupal_set_title(t('Reviews for %type nodes', array('%type' => check_plain($name))), PASS_THROUGH);

  $form['use'] = array(
    '#type' => 'fieldset',
    '#title' => t('Reviews'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['use']['node_type'] = array('#type' => 'hidden', '#value' => $type);

  $form['use']['guide'] = array(
    '#type' => 'textarea',
    '#title' => t('Usage Guide to the User'),
    '#return_value' => 1,
    '#default_value' => variable_get('nodereview_guide_' . $type, ''),
    '#description' => t('Instructions to users for how to use this review.  These will be shown on the "Add Review" page. Note that if you have help text defined on admin/settings/content-types/nodereview, this value will override it.'),
  );

  $form['use']['embed'] = array(
    '#type' => 'checkbox',
    '#title' => t('Embed the node reviews within the node content being reviewed.'),
    '#description' => t('Embed the node review form within the actual node content being reviewed instead of using a seperate menu tab'),
    '#default_value' => variable_get('nodereview_embed_' . $type, 0),
    '#return_value' => 1,
  );

  $form['axes'] = array(
    '#type' => 'fieldset',
    '#title' => t('Review Axes'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#tree' => TRUE,
  );

  // We'll store field information in its own table
  $sql = "SELECT aid, tag, description, description_required, weight 
          FROM {nodereview_axes} 
          WHERE node_type = :type 
          ORDER BY weight";

  $result = db_query($sql, array(':type' => $type));

  $axes = array();

  while ($record = $result->fetchObject()) {
    $axes[] = _nodereview_configure_axis($record);
  }

  $record = new stdClass();
  $record->aid = 0;
  $record->node_type = $type;

  $axes[] = _nodereview_configure_axis($record);

  $form['axes'] += $axes;

  $form['submit'] = array('#type' => 'submit', '#value' => t('Save'));
  return $form;

}


/**
 * Handle submission of the nodereview node type axes
 * form and saving of the data to the database.
 *
 */

function nodereview_configure_axes_submit($form, $form_state) {
  $form_values = $form_state['values'];
  // Save whether or not we're reviewing this node type
  // variable_set('nodereview_use_' . $form_values['node_type'], $form_values['use']);
  variable_set('nodereview_guide_' . $form_values['node_type'], $form_values['guide']);

  //save whether or not this axis should be embedded in the node content
  variable_set('nodereview_embed_' . $form_values['node_type'], $form_values['embed']);

  // Regardless, save the user's data, just in case they may want it later
  foreach ($form_values['axes'] as $axis) {
    if ($axis['aid'] && $axis['use']) {
      // Update an existing axis
      $axis['description'] = check_plain($axis['description']);

      //this ensures any changes to the required description checkbox get recorded when updating the admin page
      // Table name no longer needs {}
      db_update('nodereview_axes')
        ->fields(array(
                      'tag' => $axis['tag'],
                      'description' => $axis['description'],
                      'description_required' => $axis['description_required'],
                      'weight' => $axis['weight'],
                    ))
        ->condition('aid', $axis['aid'], '=')
        ->execute();

    }
    elseif ($axis['aid'] && !$axis['use']) {
      // Delete an existing axis
      db_delete('nodereview_axes')
        ->condition('aid', $axis['aid'], '=')
        ->execute();
    }
    elseif ($axis['use'] && !$axis['aid']) {
      // Create a new axis
      $axis['description'] = check_plain($axis['description']);

      db_insert('nodereview_axes')
        ->fields(array('node_type', 'tag', 'description', 'weight', 'description_required'))
        ->values(array(
                      'node_type' => $form_values['node_type'],
                      'tag' => $axis['tag'],
                      'description' => $axis['description'],
                      'weight' => $axis['weight'],
                      'description_required' => $axis['description_required'],
                    ))
        ->execute();
    }
    else {
      // Doesn't exist and don't use, so just ignore
    }
  }
}


/**
 * Form builder. To build additional axes on submit.
 *
 * @ingroup forms
 *
 */
function _nodereview_configure_axis($record) {
  $form['aid'] = array(
    '#type' => 'hidden',
    '#value' => (!empty($record->aid)) ? $record->aid : '',
  );
  $form['use'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use axis'),
    '#return_value' => 1,
    '#default_value' => (boolean)($record->aid),
    '#description' => t(''),
  );
  $form['tag'] = array(
    '#type' => 'textfield',
    '#title' => t('name'),
    '#return_value' => 1,
    '#default_value' => (!empty($record->tag)) ? $record->tag : '',
    '#size' => 30,
  );
  $form['description'] = array(
    '#type' => 'textarea',
    '#title' => t('description'),
    '#return_value' => 1,
    '#default_value' => (!empty($record->description)) ? $record->description : '',
    '#rows' => 2,
  );
  $form['description_required'] = array(
    '#type' => 'checkbox',
    '#title' => t('require a vote description'),
    '#return_value' => 1,
    '#default_value' => (!empty($record->description_required))
      ? $record->description_required : '',
    '#description' => t(''),
  );
  $form['weight'] = array(
    '#type' => 'weight',
    '#title' => t('weight'),
    '#delta' => 50,
    '#default_value' => (!empty($record->weight)) ? $record->weight : '',
    '#attributes' => array('class' => array('weight')),
  );

  return $form;
}


/**
 * We use this function in place of hook_settings(), because hook_settings()
 * isn't fancy enough to support what we need to do.
 *
 */
function nodereview_configure() {

  $form = array();
  $default = array();
  foreach (node_type_get_types() as $type => $info) {
    if ($info->type != 'nodereview') {
      $options[$type] = $info->name;
      if (variable_get('nodereview_use_' . $type, 0)) {
        $default[] = $type;
      }
    }
  }

  $form['nodereview'] = array(
    '#type' => 'fieldset',
    '#title' => t('Review types'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );
  $form['nodereview']['types'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Reviewable content types'),
    '#default_value' => $default,
    '#options' => $options,
    '#description' => t('Specify which content types can be reviewed.'),
  );

  $rating_options['normal'] = 'Normal (Numerical Ratings, eg. 1 to 10)';
  $rating_options['label'] = 'Label (Word Ratings, Good, Better, ...)';
  if (module_exists('fivestar')) {
    $rating_options['fivestar'] = 'Five Star Rating';
  }

  $form['ratings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Ratings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#tree' => TRUE,
  );
  $form['ratings']['maxrating'] = array(
    '#type' => 'textfield',
    '#title' => t('Maximum Rating'),
    '#default_value' => (NODEREVIEW_MAXRATING) ? NODEREVIEW_MAXRATING : 5,
    '#description' => t('Allowed values: 1 to 100'),
  );

  $form['ratings']['type'] = array(
    '#type' => 'radios',
    '#title' => t('Type of ratings'),
    '#default_value' => variable_get('nodereview_rating_type', 'normal'),
    '#options' => $rating_options,
    '#description' => t(''),
  );

  $form['labels'] = array(
    '#type' => 'fieldset',
    '#title' => t('Labels'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#tree' => TRUE,
  );

  for ($i = 1; $i < (NODEREVIEW_MAXRATING + 1); $i++) {
    $form['labels']['label' . $i] = array(
      '#type' => 'textfield',
      '#title' => t('Label for rating ' . $i),
      '#size' => 30,
      '#default_value' => variable_get('nodereview_rating_label' . $i, ''),
      '#description' => t(''),
    );
  }
  /*
  if (module_exists('fivestar')) {
    $form['ratings']['enable'] = array(
      '#type' => 'checkbox',
      '#title' => t('Use Fivestar for reviews'),
      '#default_value' => variable_get('nodereview_fivestar_enable', 0),
      '#description' => t('Enabling Fivestar for reviews will replace select list options with a JavaScript star display.'),
    );

    $form['fivestar'] = array(
      '#type' => 'fieldset',
      '#title' => t('Fivestar options'),
      '#collapsible' => FALSE,
      '#collapsed' => FALSE,
      '#tree' => TRUE,
    );
    $form['fivestar']['stars'] = array(
      '#type' => 'select',
      '#title' => t('Number of stars'),
      '#options' => drupal_map_assoc(range(1, 10)),
      '#default_value' => NODEREVIEW_MAXRATING,
    );
  }
  */
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  return $form;
}

/**
 * @param $form
 * @param $form_state
 * @return void
 */
function nodereview_configure_submit($form, $form_state) {
  $form_values = $form_state['values'];
  if (($form_values['ratings']['maxrating'] > 100) || !is_numeric($form_values['ratings']['maxrating'])) {
    $maxrating = 5;
    drupal_set_message(t('Your maximum value not allowed.'), 'error', TRUE);
  }
  else {
    $maxrating = $form_values['ratings']['maxrating'];
  }
  variable_set('nodereview_maxrating', $maxrating);
  variable_set('nodereview_rating_type', $form_values['ratings']['type']);

  for ($i = 1; $i < (NODEREVIEW_MAXRATING + 1); $i++) {
    variable_set('nodereview_rating_label' . $i, $form_values['labels']['label' . $i]);
  }
  foreach ($form_values['types'] as $type => $checked) {
    variable_set('nodereview_use_' . $type, (bool)$checked);
  }
  cache_clear_all();
  menu_rebuild();

}

