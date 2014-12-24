<?php /** * @file * Zen theme's implementation to display a node. * * Available variables: * - $title: the (sanitized) title of the node. * - $content: An array of node items. Use render($content) to print them all, *   or print a subset such as render($content['field_example']). Use *   hide($content['field_example']) to temporarily suppress the printing of a *   given element. * - $user_picture: The node author's picture from user-picture.tpl.php. * - $date: Formatted creation date. Preprocess functions can reformat it by *   calling format_date() with the desired parameters on the $created variable. * - $name: Themed username of node author output from theme_username(). * - $node_url: Direct url of the current node. * - $display_submitted: Whether submission information should be displayed. * - $submitted: Submission information created from $name and $date during *   template_preprocess_node(). * - $classes: String of classes that can be used to style contextually through *   CSS. It can be manipulated through the variable $classes_array from *   preprocess functions. The default values can be one or more of the *   following: *   - node: The current template type, i.e., "theming hook". *   - node-[type]: The current node type. For example, if the node is a *     "Blog entry" it would result in "node-blog". Note that the machine *     name will often be in a short form of the human readable label. *   - node-teaser: Nodes in teaser form. *   - node-preview: Nodes in preview mode. *   - view-mode-[mode]: The view mode, e.g. 'full', 'teaser'... *   The following are controlled through the node publishing options. *   - node-promoted: Nodes promoted to the front page. *   - node-sticky: Nodes ordered above other non-sticky nodes in teaser *     listings. *   - node-unpublished: Unpublished nodes visible only to administrators. *   The following applies only to viewers who are registered users: *   - node-by-viewer: Node is authored by the user currently viewing the page. * - $title_prefix (array): An array containing additional output populated by *   modules, intended to be displayed in front of the main title tag that *   appears in the template. * - $title_suffix (array): An array containing additional output populated by *   modules, intended to be displayed after the main title tag that appears in *   the template. * * Other variables: * - $node: Full node object. Contains data that may not be safe. * - $type: Node type, i.e. story, page, blog, etc. * - $comment_count: Number of comments attached to the node. * - $uid: User ID of the node author. * - $created: Time the node was published formatted in Unix timestamp. * - $classes_array: Array of html class attribute values. It is flattened *   into a string within the variable $classes. * - $zebra: Outputs either "even" or "odd". Useful for zebra striping in *   teaser listings. * - $id: Position of the node. Increments each time it's output. * * Node status variables: * - $view_mode: View mode, e.g. 'full', 'teaser'... * - $teaser: Flag for the teaser state (shortcut for $view_mode == 'teaser'). * - $page: Flag for the full page state. * - $promote: Flag for front page promotion state. * - $sticky: Flags for sticky post setting. * - $status: Flag for published status. * - $comment: State of comment settings for the node. * - $readmore: Flags true if the teaser content of the node cannot hold the *   main body content. Currently broken; see http://drupal.org/node/823380 * - $is_front: Flags true when presented in the front page. * - $logged_in: Flags true when the current user is a logged-in member. * - $is_admin: Flags true when the current user is an administrator. * * Field variables: for each field instance attached to the node a corresponding * variable is defined, e.g. $node->body becomes $body. When needing to access * a field's raw values, developers/themers are strongly encouraged to use these * variables. Otherwise they will have to explicitly specify the desired field * language, e.g. $node->body['en'], thus overriding any language negotiation * rule that was previously applied. * * @see template_preprocess() * @see template_preprocess_node() * @see zen_preprocess_node() * @see template_process() */ ?>
<?php
$nid = arg(1);
global $base_url;
if (arg(0) == 'node' && is_numeric($nid)) {
    $hcf_node = node_load($nid);
    $gid = og_get_entity_groups('node', $hcf_node);
    foreach ($gid as $g) {
        $group = node_load($g);
    }
}
//echo '<pre/>';
//print_r($group);
//exit;
?>
<style>
    .tabs
    {
        display:none;
    }
    .block
    {
        margin-bottom: 0;
    }
</style>



<div class="node-hairstyle"> 
    <div class="columns">
<!--        <div class="main">
            <div class="logo-image">        
                <?php
//                if (isset($group->field_logo_image['und'][0]['uri'])) {
//                    $image_url = $group->field_logo_image['und'][0]['uri'];
//                }
//                $image_uri_with_style = image_style_url('hair_style', $image_url);
//                print l('<img src="' . $image_uri_with_style . '"/>', file_create_url($image_url), array('html' => TRUE, 'attributes' => array("class" => "colorbox", "rel" => "hairstyles")));
                ?>      
            </div>
        </div>-->
        <div class="main">
            <div class="column1">      
                <div class="pimage">        
                    <?php
                    if (isset($node->field_primary_image['und'][0]['uri'])) {
                        $image_url = $node->field_primary_image['und'][0]['uri'];
                    }
                    $image_uri_with_style = image_style_url('hair_style', $image_url);
                    print l('<img src="' . $image_uri_with_style . '" alt="' . $node->title . '" />', file_create_url($image_url), array('html' => TRUE, 'attributes' => array("class" => "colorbox", "rel" => "hairstyles")));
                    ?>      
                </div>      
                <div class="group">        
                    <!--                <div class="made-by">
                                        <label>By:</label>
                                        <div class="made-by-link">
                    <?php
//                        $userlink = $node->name;
//                        $result = strtolower(str_replace(' ', '', $node->name));
//                        print l($userlink, $result);
                    ?> 
                                        </div>
                                    </div>                  
                                    <div class="hcf-title">    
                                        <label>From:</label>
                                        <div class="hcf-title-link">
                    <?php
//                        if (isset($content["og_group_ref"][0]["#href"])) {
//                            $current_path = $content["og_group_ref"][0]["#href"];
//                        } $Link = $content["og_group_ref"][0]["#title"];
//                        print l($Link, $current_path);
                    ?>
                                        </div>
                                    </div> -->
                    <div class="rating">
                        <?php
                        $query = db_select("field_data_field_enter_the_contest", "contest");
                        $query->fields("contest", array("field_enter_the_contest_value"));
                        $query->where("entity_id=" . $node->nid);
                        $result = $query->execute()->fetchField();
                        if ($result == 1) {
                            print render($content['field_rate_content']);
                        }
                        ?>
                    </div>
                </div>    
            </div>    
            <div class="column2">


                <div class="row">
                    <div class="group"> 
                        <label>Gender: </label>        
                        <span class="value"><?php print$node->field_gender['und'][0]['taxonomy_term']->name; ?></span>      
                    </div>      
                    <div class="group">        
                        <label>Skin tone: </label>        
                        <span class="value"><?php print$node->field_skin_tone['und'][0]['taxonomy_term']->name; ?></span>      
                    </div> 
                </div>
                <div class="row">
                    <div class="group">        
                        <label>Hair texture: </label>        
                        <span class="value"><?php print$node->field_hair_texture['und'][0]['taxonomy_term']->name; ?></span>      
                    </div>   
                    <div class="group">        
                        <label>Hair type: </label>        
                        <span class="value"><?php print$node->field_hair_type['und'][0]['taxonomy_term']->name; ?></span>      
                    </div> 
                </div>
                <div class="row">
                    <div class="group">        
                        <label>Hair density: </label>        
                        <span class="value"><?php print$node->field_hair_density['und'][0]['taxonomy_term']->name; ?></span>      
                    </div>      
                    <div class="group">        
                        <label>Hair length: </label>        
                        <span class="value"><?php print$node->field_hair_length['und'][0]['taxonomy_term']->name; ?></span>      
                    </div> 
                </div>
                <div class="row">
                    <div class="group" style="width:100%;">        
                        <label>Hair color:</label>        
                        <span class="value">            
                            <?php
                            if (count($node->field_hair_color['und']) > 0) {
                                print '<ul>';
                                foreach ($node->field_hair_color['und'] as $color) {
                                    print '<li>' . $color['taxonomy_term']->name . ' <li>';
                                } print'<ul>';
                            }
                            ?>
                        </span>      
                    </div>
                </div>


                <?php
                if (count($node->field_marketing_city['und']) > 0) {
                    ?>
                    <div class="row">
                        <div class="group" style="width:100%;">
                            <label>Marketing cities:</label>
                            <span class="value">        
                                <?php
                                print '<ul>';
                                foreach ($node->field_marketing_city['und'] as $city) {
                                    print '<li>' . $city['taxonomy_term']->name . ' </li>';
                                }
                                print '</ul>';
                                ?>        
                            </span>      
                        </div> 
                    </div>
                <?php } ?>


                <?php
                if (count($node->field_products_used['und']) > 0) {
                    ?>
                    <div class="row" style="border-bottom:none;">
                        <div class="group" style="width:100%;">
                            <label>Products Used: </label>


                            <span class="value">
                                <?php
                                print'<ul>';
                                foreach ($node->field_products_used['und'] as $products_used) {
                                    print '<li>' . $products_used['taxonomy_term']->name . ' </li>';
                                }
                                print '</ul>';
                                ?>
                            </span>      
                        </div> 
                    </div>
                <?php } ?>

            </div>
        </div>
        <?php
        if (count($node->field_other_images['und']) > 0) {
            ?>
            <div class="main">
                <div class="other-images-and-title">
                    <div class="custom-title">Additional Images
                    </div>
                    <div class="other-images">    
                        <?php
                        if (count($node->field_other_images['und']) > 0) {

                            print '<ul>';
                            foreach ($node->field_other_images['und'] as $thumb) {
                                $thumb_uri_with_style = image_style_url('thumbnail', $thumb['uri']);
                                print '<li>          ' . l('<img src="' . $thumb_uri_with_style . '"  />', file_create_url($thumb['uri']), array('html' => TRUE, 'attributes' => array("class" => "colorbox", "rel" => "hairstyles"))) . '          </li>';
                            } print '</ul>';
                        } else {
                            
                        }
                        ?>  
                    </div>
                </div>
            </div>
        <?php } ?>

        <?php
        if ($node->body != Null) {
            $text = trim($node->body['und'][0]['value']);
            ?>
            <div class="main">
                <div class="description">
                    <div class="custom-title">Description </div>
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
                    <a href="<?php print $base_url ?>/node/<?php print $node->nid; ?>/edit" ">
                        <img src="<?php print $base_url; ?>/sites/all/themes/seven_doublemthemes/images/update-hairstyle-node.png" alt="Update Profile" />
                    </a>
                </div>
            </div>
        <?php } ?>


        <?php
        global $user;

        $uid = $user->uid;
        if ($uid == 1 && $node->uid != $uid) {
            ?>
            <div class="main">
                <div class="edit-node">
                    <a href="?inline=true#prod-preview" class="colorbox-inline">
                        <img src="<?php print $base_url; ?>/sites/all/themes/seven_doublemthemes/images/msgme.png" alt="Message Me" />
                    </a>
                </div>
            </div>
            <?php
        }
        ?>

    </div>  



</div>
<div style="display: none;">
    <div id="prod-preview">
        <?php
        require_once drupal_get_path('module', 'contact') . '/contact.pages.inc';
//print_r(drupal_get_form('contact_personal_form', $uid));
        $form = drupal_render(drupal_get_form('contact_personal_form', user_load($node->uid)));
        print $form;
        ?>
    </div>

</div>