<?php

/**
 * @file
 * Hooks provided by Contextual module.
 */

/**
 * @addtogroup hooks
 * @{
 */

/**
 * Alter a contextual links element before it is rendered.
 *
 * This hook is invoked by contextual_pre_render_links(). The renderable array
 * of #type 'contextual_links', containing the entire contextual links data that
 * is passed in by reference. Further links may be added or existing links can
 * be altered.
 *
 * @param $element
 *   A renderable array representing the contextual links.
 * @param $items
 *   An associative array containing the original contextual link items, as
 *   generated by menu_contextual_links(), which were used to build
 *   $element['#links'].
 *
 * @see hook_menu_contextual_links_alter()
 * @see contextual_pre_render_links()
 * @see contextual_element_info()
 */
function hook_contextual_links_view_alter(&$element, $items) {
  // Add another class to all contextual link lists to facilitate custom
  // styling.
  $element['#attributes']['class'][] = 'custom-class';
}

/**
 * @} End of "addtogroup hooks".
 */
