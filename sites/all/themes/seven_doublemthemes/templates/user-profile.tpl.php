<?php
/**

 * @file

 * Default theme implementation to present all user profile data.

 *

 * This template is used when viewing a registered member's profile page,

 * e.g., example.com/user/123. 123 being the users ID.

 *

 * Use render($user_profile) to print all profile items, or print a subset

 * such as render($user_profile['user_picture']). Always call

 * render($user_profile) at the end in order to print all remaining items. If

 * the item is a category, it will contain all its profile items. By default,

 * $user_profile['summary'] is provided, which contains data on the user's

 * history. Other data can be included by modules. $user_profile['user_picture']

 * is available for showing the account picture.

 *

 * Available variables:

 *   - $user_profile: An array of profile items. Use render() to print them.

 *   - Field variables: for each field instance attached to the user a

 *     corresponding variable is defined; e.g., $account->field_example has a

 *     variable $field_example defined. When needing to access a field's raw

 *     values, developers/themers are strongly encouraged to use these

 *     variables. Otherwise they will have to explicitly specify the desired

 *     field language, e.g. $account->field_example['en'], thus overriding any

 *     language negotiation rule that was previously applied.

 *

 * @see user-profile-category.tpl.php

 *   Where the html is handled for the group.

 * @see user-profile-item.tpl.php

 *   Where the html is handled for each item in the group.

 * @see template_preprocess_user_profile()

 */
//echo '<pre/>';print_r($user_profile);exit;
$uid = arg(1);
global $base_url;
global $user;

if (arg(0) == 'user' && is_numeric($uid)) {
    $account = user_load($uid);
    $gid = og_get_groups_by_user($account);
    foreach ($gid as $g) {
        $group = node_load($g);
    }
}

$hcf_user = user_load($user->uid);
$gid = og_get_groups_by_user($hcf_user);
foreach ($gid as $g) {
    $ungroup = node_load($g);
//    $ungroup2=og_get_entity_groups($entity_type = 'user', $entity = NULL, $states = array(OG_STATE_ACTIVE));
//    print_r($ungroup2);
//    exit();
}
?>

<style>
    .tabs {

        display:none;
    }
    .title{
        display:none;
    }
    .profile .title{
        display:block;
    }
</style>

<div class="profile"<?php print $attributes; ?>>
<!--    <div class="logo-image">        
        <?php
//        if (isset($group->field_logo_image['und'][0]['uri'])) {
//            $image_url = $group->field_logo_image['und'][0]['uri'];
//        }
//        $image_uri_with_style = image_style_url('hair_style', $image_url);
//        print l('<img src="' . $image_uri_with_style . '"/>', file_create_url($image_url), array('html' => TRUE, 'attributes' => array("class" => "colorbox", "rel" => "hairstyles")));
        ?>      
    </div>-->
    <div class="title"><?php print $user_profile['field_fname']['#object']->field_fname['und'][0]['value'] . " " . $user_profile['field_lname']['#object']->field_lname['und'][0]['value'] ?></div>
    <div class="picture-wrapper"><?php print $user_profile['user_picture']['#markup'] ?></div>

    <?php
    print render($user_profile);
    if ($group->nid != 0) {
        ?>

        <div class="user-location">
            <label>Location</label>
            <div class="value">
                <?php print $group->locations[0]['street']; ?>
            </div>
            <div class="value">
                <div id="city">
                    <?php print $group->locations[0]['city']; ?>
                </div>
                <div id="province">
                    <?php print $group->locations[0]['province_name']; ?>
                </div>
                <div id="postal_code">
                    <?php print $group->locations[0]['postal_code']; ?>
                </div>
            </div>
            <div class="value">
                <?php print $group->locations[0]['country_name']; ?>
            </div>
        </div>
    <?php } ?>

    <div class="profile-buttons">

        <div class="stylist-message">
            <a href="?inline=true#prod-preview" class="colorbox-inline">
                <img src="<?php print $base_url; ?>/sites/all/themes/seven_doublemthemes/images/msgme.png" alt="Message Me" />
            </a>
        </div>


        <?php
        if ($user->uid == $uid) {
            ?>
            <div class="stylist-update-profile">
                <a href="<?php print $base_url ?>/user/<?php print $uid ?>/edit">
                    <img src="<?php print $base_url; ?>/sites/all/themes/seven_doublemthemes/images/update_profile.png" alt="Update Profile" />
                </a>
            </div>
        <?php } ?>


        <?php
        $query = db_select("users_roles", "ur");
        $query->fields("ur", array("rid"));
        $query->where("uid=" . $user->uid);
        $result = $query->execute()->fetchField();
        if ($result == 3 || $result == 4 || $result == 5 || $result == 8) {
//            $query = db_select("node", "node");
//            $query->fields("node", array("uid"));
//            $query->where("uid=" . $user->uid);
//            $query->where("type='hair_care_facility'");
//            $results = $query->execute()->fetchField();
//            if ($ungroup->nid != 0 && $user->uid == $uid && $results == 0) {
//                
            ?>
            <!--<div class="stylist-message">-->
            <?php // print l('<img src="' . $base_url . '/sites/all/themes/seven_doublemthemes/images/dhcf.png" />', 'disassociate-from-hcf', array('query' => array('group_type' => "node", 'gid' => $ungroup->nid, 'entity_type' => "user", 'etid' => $user->uid), 'html' => TRUE, 'attributes' => array('onclick' => "return disassociate_from_hcf();")))  ?>
            <!--</div>-->
            <?php
//            }else 
            if ($ungroup->nid == 0 && $user->uid == $uid) {
                $membership_status = db_select("request_status", "rs");
                $membership_status->fields("rs", array("uid"));
                $membership_status->where("uid=" . $user->uid);
                $membership_status_result = $membership_status->execute()->fetchField();
                $num_rows = $membership_status->execute();
                $count = $num_rows->rowCount();
                if ($count == 0) {
                    ?>
                    <div class="stylist-message">
                        <a href="?inline=true#groups" class="colorbox-inline" style="text-decoration:none;float:left;">
                            <img src="<?php print $base_url; ?>/sites/all/themes/seven_doublemthemes/images/addehcf.png" />
                        </a>
                        <div style="margin-left:42px;font-size: 16px;float:left;padding:10px 0;">OR</div>
                    </div>
                    <div class="stylist-update-profile">
                        <a href="<?php print $base_url ?>/node/add/hair-care-facility">
                            <img src="<?php print $base_url; ?>/sites/all/themes/seven_doublemthemes/images/addhcf.png" />
                        </a>
                    </div>
                <?php } else if ($count == 1) {
                    ?>
                    <div class="stylist-message">
                    <?php print l('Cancel Membership Request', 'cancel_membership_request', array('query' => array('uid' => $user->uid), 'attributes' => array('style' => "color:#115892;text-decoration:none;font-size:16px;"))); ?>
                    </div>
                    <?php
                }
            }
        }
        ?>

        <div class="stylist-mark-friend">
            <?php
            $account = menu_get_object('user');
            print flag_create_link('friend', $account->uid);
            ?>
        </div>
    </div>


    <div class="user-gmap" style="float:left;width:100%;">
        <?php
        $latitude = $group->locations[0]['latitude'];
        $longitude = $group->locations[0]['longitude'];
        if ($latitude != 0 || $longitude != 0) {
            $marker = 'Whatever you want the marker to be.';
            print gmap_simple_map($latitude, $longitude, '', $marker, 'default');
        }
        ?>
    </div>
</div>
<div style="display: none;">
    <div id="prod-preview">
        <?php
        require_once drupal_get_path('module', 'contact') . '/contact.pages.inc';
        //print_r(drupal_get_form('contact_personal_form', $uid));
        $form = drupal_render(drupal_get_form('contact_personal_form', user_load($uid)));
        print $form;
        ?>
    </div>

    <div id="groups">
        <div>
            <div style="float:left;border-bottom:2px solid #cccccc;width:500px;padding:10px 5px;">
                <div style="float:left;width:250px;margin-right:20px;color:black;font-size: 16px;font-weight: bold;">
                    Group Name
                </div>
                <div style="float:left;width:200px;color:black;font-size: 16px;font-weight: bold;">
                    Owner Name
                </div>
            </div>
        </div>
        <?php
        $group_ids = og_get_all_group();
        foreach ($group_ids as $group_ids) {
            $groups = db_select("node", "node");
            $groups->fields("node", array("nid"));
            $groups->fields("node", array("title"));
            $groups->fields("node", array("uid"));
            $groups->where("nid=" . $group_ids);
            $groups_result = db_query($groups);
            foreach ($groups_result as $groups_result) {
                $groups_owner = db_select("users", "us");
                $groups_owner->fields("us", array("name"));
                $groups_owner->where("uid=" . $groups_result->uid);
                $owner_name = $groups_owner->execute()->fetchField();
                ?>
                <div>
                    <div style="float:left;border-bottom:1px dotted #cccccc;width:500px;padding:5px;">
                        <div style="float:left;width:250px;margin-right:20px;color: #28a8e2;;font-size: 16px;font-weight: bold;">
        <?php print l($groups_result->title, 'request_membership', array('query' => array('group_type' => "node", 'gid' => $groups_result->nid, 'entity_type' => "user", 'etid' => $user->uid), 'attributes' => array('style' => "color:#28a8e2;text-decoration:none;"))); ?>
                        </div>
                        <div style="float:left;width:200px;font-size: 16px;font-weight: bold;">
        <?php echo $owner_name; ?>
                        </div>
                    </div>
                </div>
                <?php
            }
        }
        ?>
    </div>

</div>




