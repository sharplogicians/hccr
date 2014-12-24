<?php
/**

 * @file

 * Zen theme's implementation to display a node.

 *

 * Available variables:

 * - $title: the (sanitized) title of the node.

 * - $content: An array of node items. Use render($content) to print them all,

 *   or print a subset such as render($content['field_example']). Use

 *   hide($content['field_example']) to temporarily suppress the printing of a

 *   given element.

 * - $user_picture: The node author's picture from user-picture.tpl.php.

 * - $date: Formatted creation date. Preprocess functions can reformat it by

 *   calling format_date() with the desired parameters on the $created variable.

 * - $name: Themed username of node author output from theme_username().

 * - $node_url: Direct url of the current node.

 * - $display_submitted: Whether submission information should be displayed.

 * - $submitted: Submission information created from $name and $date during

 *   template_preprocess_node().

 * - $classes: String of classes that can be used to style contextually through

 *   CSS. It can be manipulated through the variable $classes_array from

 *   preprocess functions. The default values can be one or more of the

 *   following:

 *   - node: The current template type, i.e., "theming hook".

 *   - node-[type]: The current node type. For example, if the node is a

 *     "Blog entry" it would result in "node-blog". Note that the machine

 *     name will often be in a short form of the human readable label.

 *   - node-teaser: Nodes in teaser form.

 *   - node-preview: Nodes in preview mode.

 *   - view-mode-[mode]: The view mode, e.g. 'full', 'teaser'...

 *   The following are controlled through the node publishing options.

 *   - node-promoted: Nodes promoted to the front page.

 *   - node-sticky: Nodes ordered above other non-sticky nodes in teaser

 *     listings.

 *   - node-unpublished: Unpublished nodes visible only to administrators.

 *   The following applies only to viewers who are registered users:

 *   - node-by-viewer: Node is authored by the user currently viewing the page.

 * - $title_prefix (array): An array containing additional output populated by

 *   modules, intended to be displayed in front of the main title tag that

 *   appears in the template.

 * - $title_suffix (array): An array containing additional output populated by

 *   modules, intended to be displayed after the main title tag that appears in

 *   the template.

 *

 * Other variables:

 * - $node: Full node object. Contains data that may not be safe.

 * - $type: Node type, i.e. story, page, blog, etc.

 * - $comment_count: Number of comments attached to the node.

 * - $uid: User ID of the node author.

 * - $created: Time the node was published formatted in Unix timestamp.

 * - $classes_array: Array of html class attribute values. It is flattened

 *   into a string within the variable $classes.

 * - $zebra: Outputs either "even" or "odd". Useful for zebra striping in

 *   teaser listings.

 * - $id: Position of the node. Increments each time it's output.

 *

 * Node status variables:

 * - $view_mode: View mode, e.g. 'full', 'teaser'...

 * - $teaser: Flag for the teaser state (shortcut for $view_mode == 'teaser').

 * - $page: Flag for the full page state.

 * - $promote: Flag for front page promotion state.

 * - $sticky: Flags for sticky post setting.

 * - $status: Flag for published status.

 * - $comment: State of comment settings for the node.

 * - $readmore: Flags true if the teaser content of the node cannot hold the

 *   main body content. Currently broken; see http://drupal.org/node/823380

 * - $is_front: Flags true when presented in the front page.

 * - $logged_in: Flags true when the current user is a logged-in member.

 * - $is_admin: Flags true when the current user is an administrator.

 *

 * Field variables: for each field instance attached to the node a corresponding

 * variable is defined, e.g. $node->body becomes $body. When needing to access

 * a field's raw values, developers/themers are strongly encouraged to use these

 * variables. Otherwise they will have to explicitly specify the desired field

 * language, e.g. $node->body['en'], thus overriding any language negotiation

 * rule that was previously applied.

 *

 * @see template_preprocess()

 * @see template_preprocess_node()

 * @see zen_preprocess_node()

 * @see template_process()

 */
global $user;
global $base_url;
$node_author = user_load($node->uid);
?>
<style>
    .title
    {
        display:none;
    }
    .block
    {
        margin-bottom: 0;
    }
</style>
<div class="node-hcf">



    <div class="columns">
<!--        <div class="main">
            <div class="logo-image">        
                <?php
//                if (isset($node->field_logo_image['und'][0]['uri'])) {
//                    $image_url = $node->field_logo_image['und'][0]['uri'];
//                }
//                $image_uri_with_style = image_style_url('hair_style', $image_url);
//                print l('<img src="' . $image_uri_with_style . '"/>', file_create_url($image_url), array('html' => TRUE, 'attributes' => array("class" => "colorbox", "rel" => "hairstyles")));
                ?>      
            </div>
        </div>-->


        <div class="main">
            <div class="pimage">
                <?php
                if (isset($node->field_image_of_facility['und'][0]['uri'])) {
                    $image_url = $node->field_image_of_facility['und'][0]['uri'];
                }
                $image_uri_with_style = image_style_url('hcf', $image_url);
                print l('<img src="' . $image_uri_with_style . '" alt="' . $node->title . '" />', file_create_url($image_url), array('html' => TRUE, 'attributes' => array("class" => "colorbox", "rel" => "hairstyles")));
                ?>
            </div>
            <div class="custom-title">           
                <?php print$node->title ?>            
            </div>
            <!--      <div class="group">         
            <?php
//            $userid = $node->uid;
//            $query = db_select("users", "us");
//            $query->fields("us", array("name"));
//            $query->where("uid=" . $userid);
//            $result = $query->execute()->fetchField();
//            print $result;
            ?>
            </div>-->

        </div>

        <div class="main">
            <?php
            if (array_key_exists("8",$node_author->roles) || array_key_exists("15",$node_author->roles) || array_key_exists("16",$node_author->roles)) {
                ?>
                <div class="location-node">
                    <?php
                    $block = module_invoke('gmap_location', 'block_view', 0);
                    print render($block['content']);
                    ?>
                </div>
            <?php } ?>
            <div class="group">
                <div class="mar-city">
                    <label>Marketing Cities:</label>
                    <div class="value">
                        <?php
                        if (count($node->field_marketing_city['und']) > 0) {
                            print '<ul>';
                            foreach ($node->field_marketing_city['und'] as $city) {
                                print '<li>' . $city['taxonomy_term']->name . ' </li>';
                            }
                            print '</ul>';
                        }
                        ?>  
                    </div>
                </div>

                <div class="a-l">
                    <label>Address:</label>
                </div>

                <div class="group2">
                    <div class="value">

                        <?php
                        if (isset($content['locations']['#locations'][0]['street'])) {

                            print$content['locations']['#locations'][0]['street'];
                        }
                        ?>

                    </div>
                    <div class="value">
                        <div class="city">

                            <?php
                            if (isset($content['locations']['#locations'][0]['city'])) {

                                print$content['locations']['#locations'][0]['city'];
                            }
                            ?>

                        </div>
                        <div class="state">
                            <?php
                            if (isset($content['locations']['#locations'][0]['province_name'])) {
                                print$content['locations']['#locations'][0]['province_name'];
                            }
                            ?>
                        </div>
                        <div class="postal-code">
                            <?php
                            if (isset($content['locations']['#locations'][0]['postal_code'])) {

                                print$content['locations']['#locations'][0]['postal_code'];
                            }
                            ?>
                        </div>
                    </div>
                    <div class="value">
                        <?php
                        if (isset($content['locations']['#locations'][0]['country_name'])) {

                            print$content['locations']['#locations'][0]['country_name'];
                        }
                        ?>
                    </div>
                </div>

                <div class="telephone">
                    <label>Telephone:</label>
                    <div class="value">
                        <?php
                        print $node->field_telephone_number['und'][0]['value'];
                        ?>
                    </div>
                </div>

                <?php
                if (array_key_exists("8",$node_author->roles) || array_key_exists("15",$node_author->roles) || array_key_exists("16",$node_author->roles)) {
                    ?>
                    <div class="visit-links">
                        <?php
                        if (isset($node->field_visit_website['und'][0]['value'])) {
                            ?>
                            <a href="<?php print $node->field_visit_website['und'][0]['value']; ?>" target="_blank">
                                Company Website
                            </a>
                        <?php } ?>
                    </div>

                    <div class="visit-links">
                        <?php
                        if (isset($node->field_book_online['und'][0]['value'])) {
                            ?>
                            <a href="<?php print $node->field_book_online['und'][0]['value']; ?>" target="_blank">
                                Book Online
                            </a>
                        <?php } ?>
                    </div>
                <?php } ?>
            </div>
        </div>
        <div class="main">
            <div class="custom-title">           
                Hours of Operation           
            </div>
            <div class="m-t">
                <div class="hours-of-operation">
                    <label>Monday:</label>
                    <div class="value">
                        <div class="value-1">
                            <?php
                            print $node->field_monday['und'][0]['value_formatted'];
                            ?>
                        </div>
                        <div class="value-2">
                            <?php
                            print $node->field_monday['und'][0]['value2_formatted'];
                            ?>
                        </div>
                    </div>
                </div>
                <div class="hours-of-operation">
                    <label>Tuesday:</label>
                    <div class="value">
                        <div class="value-1">
                            <?php
                            print $node->field_tuesday['und'][0]['value_formatted'];
                            ?>
                        </div>
                        <div class="value-2">
                            <?php
                            print $node->field_tuesday['und'][0]['value2_formatted'];
                            ?>
                        </div>
                    </div>
                </div>
                <div class="hours-of-operation">
                    <label>Wednesday:</label>
                    <div class="value">
                        <div class="value-1">
                            <?php
                            print $node->field_wednesday['und'][0]['value_formatted'];
                            ?>
                        </div>
                        <div class="value-2">
                            <?php
                            print $node->field_wednesday['und'][0]['value2_formatted'];
                            ?>
                        </div>
                    </div>
                </div>
                <div class="hours-of-operation">
                    <label>Thursday:</label>
                    <div class="value">
                        <div class="value-1">
                            <?php
                            print $node->field_thursday['und'][0]['value_formatted'];
                            ?>
                        </div>
                        <div class="value-2">
                            <?php
                            print $node->field_thursday['und'][0]['value2_formatted'];
                            ?>
                        </div>
                    </div>
                </div>
            </div>
            <div class="f-s">
                <div class="hours-of-operation">
                    <label>Friday:</label>
                    <div class="value">
                        <div class="value-1">
                            <?php
                            print $node->field_friday['und'][0]['value_formatted'];
                            ?>
                        </div>
                        <div class="value-2">
                            <?php
                            print $node->field_friday['und'][0]['value2_formatted'];
                            ?>
                        </div>
                    </div>
                </div>
                <div class="hours-of-operation">
                    <label>Saturday:</label>
                    <div class="value">
                        <div class="value-1">
                            <?php
                            print $node->field_saturday['und'][0]['value_formatted'];
                            ?>
                        </div>
                        <div class="value-2">
                            <?php
                            print $node->field_saturday['und'][0]['value2_formatted'];
                            ?>
                        </div>
                    </div>
                </div>
                <div class="hours-of-operation">
                    <label>Sunday:</label>
                    <div class="value">
                        <div class="value-1">
                            <?php
                            print $node->field_sunday['und'][0]['value_formatted'];
                            ?>
                        </div>
                        <div class="value-2">
                            <?php
                            print $node->field_sunday['und'][0]['value2_formatted'];
                            ?>
                        </div>
                    </div>
                </div>
            </div>
        </div>
    </div>

    <?php
    if ($node->body != Null) {
        $text = trim($node->body['und'][0]['value']);
        ?>
        <div class="main">
            <div class="description">
                <div class="custom-title">           
                    Description           
                </div>
                <span class="value">
                    <?php print $text; ?>
                </span>
            </div>
        </div>
    <?php } ?>


    <?php
    global $user;

    $uid = $user->uid;
    if ($node->uid == $uid) {
        ?>
        <div class="main">
            <div class="edit-node">
                <a href="<?php print $base_url ?>/node/add/services">
                    <img src="<?php print $base_url; ?>/sites/all/themes/seven_doublemthemes/images/services.png" alt="Add Service" />
                </a>
            </div>
        </div>
    <?php } ?>


    <?php
    $group_id = og_get_entity_groups($entity_type = 'user', $entity = NULL, $states = array(OG_STATE_ACTIVE));
    foreach ($group_id['node'] as $group) {
        if ($node->nid == $group && $node->uid != $user->uid) {
            ?>
            <div class="main">
                <div class="edit-node">
                    <?php print l('<img src=" ' . $base_url . '/sites/all/themes/seven_doublemthemes/images/dhcf.png" />', 'disassociate-hcp', array('query' => array('group_type' => "node", 'gid' => $node->nid, 'entity_type' => "user", 'etid' => $user->uid), 'html' => TRUE, 'attributes' => array('onclick' => "return disassociate_hcp();"))) ?>
                </div>
            </div>
            <?php
        }
    }
    ?>





    <?php
    $block = module_invoke('views', 'block_view', 'og_members-block_1');
    if ($block) {
        ?>
        <div class="main">
            <div id="block-views-og-members-block-1">
                <h2 class="block-title">Hair Care Professionals</h2>
                <?php print render($block); ?>
            </div>
        </div>
    <?php }
    ?>



</div>









