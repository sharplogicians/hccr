<?php

/**
 * @file
 * this is the deafult view
 */

/**
 * Implements of hook_views_default_views().
 */
function nodereview_views_default_views() {
  $view = new view;
  $view->name = 'review_list';
  $view->description = 'A list of teasers for reviews of a given node';
  $view->tag = 'nodereview';
  $view->base_table = 'node';
  $view->human_name = '';
  $view->core = 0;
  $view->api_version = '3.0-alpha1';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Defaults */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->display->display_options['title'] = 'Reviews';
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'node';
  $handler->display->display_options['row_options']['links'] = 1;
  $handler->display->display_options['row_options']['comments'] = 0;
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['text']['id'] = 'area';
  $handler->display->display_options['empty']['text']['table'] = 'views';
  $handler->display->display_options['empty']['text']['field'] = 'area';
  $handler->display->display_options['empty']['text']['empty'] = FALSE;
  $handler->display->display_options['empty']['text']['content'] = 'No reviews have been submitted.  Maybe you should be the first?';
  $handler->display->display_options['empty']['text']['format'] = '1';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['link_to_node'] = 1;
  /* Field: Content: Updated date */
  $handler->display->display_options['fields']['changed']['id'] = 'changed';
  $handler->display->display_options['fields']['changed']['table'] = 'node';
  $handler->display->display_options['fields']['changed']['field'] = 'changed';
  $handler->display->display_options['fields']['changed']['label'] = 'Updated';
  /* Sort criterion: Content: Updated date */
  $handler->display->display_options['sorts']['changed']['id'] = 'changed';
  $handler->display->display_options['sorts']['changed']['table'] = 'node';
  $handler->display->display_options['sorts']['changed']['field'] = 'changed';
  $handler->display->display_options['sorts']['changed']['order'] = 'DESC';
  /* Contextual filter: Node Review: Reviewed Node */
  $handler->display->display_options['arguments']['reviewed_nid']['id'] = 'reviewed_nid';
  $handler->display->display_options['arguments']['reviewed_nid']['table'] = 'nodereview';
  $handler->display->display_options['arguments']['reviewed_nid']['field'] = 'reviewed_nid';
  $handler->display->display_options['arguments']['reviewed_nid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['reviewed_nid']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['reviewed_nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['reviewed_nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['reviewed_nid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['reviewed_nid']['specify_validation'] = 1;
  $handler->display->display_options['arguments']['reviewed_nid']['validate']['type'] = 'php';
  $handler->display->display_options['arguments']['reviewed_nid']['validate_options']['code'] = '$node = node_load($argument);
return variable_get(\'nodereview_use_\' . $node->type, 0) !== 0;';
  $handler->display->display_options['arguments']['reviewed_nid']['break_phrase'] = 0;
  $handler->display->display_options['arguments']['reviewed_nid']['not'] = 0;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'nodereview' => 'nodereview',
  );
  $handler->display->display_options['filters']['type']['expose']['operator'] = FALSE;

  /* Display: Reviews */
  $handler = $view->new_display('page', 'Reviews', 'page_1');
  $handler->display->display_options['path'] = 'node/%/reviews';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Reviews';
  $handler->display->display_options['menu']['weight'] = '0';


  $views[$view->name] = $view;
  return $views;
}
