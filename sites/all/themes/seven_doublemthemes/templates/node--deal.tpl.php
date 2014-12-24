<?php
global $base_url;
$uid = $node->uid;
$account = user_load($uid);
$gid = og_get_groups_by_user($account);
foreach ($gid as $g) {
    $group = node_load($g);
    ?>
    <div class="node-deal"> 
        <div class="deal-main">
            <div class="deal-main-inner">
                <div class="image"> 
                    <?php
                    if (isset($node->field_dimage['und'][0]['uri'])) {
                        $image_url = $node->field_dimage['und'][0]['uri'];
                    }
                    $image_uri_with_style = image_style_url('hair_style', $image_url);
                    print l('<img src="' . $image_uri_with_style . '" alt="' . $node->title . '" />', file_create_url($image_url), array('html' => TRUE, 'attributes' => array("class" => "colorbox", "rel" => "hairstyles"))); //echo '<pre/>';//print_r($node);//exit();         
//               echo '<pre/>';print_r($node);exit();
                    ?> 
                </div>      
                <!--        <div class="group">        
                            <div class="made-by">
                                <label>By:</label>
                                <div class="made-by-link">
                <?php
//                    $userlink = $node->name;
//                    $result = strtolower(str_replace(' ','',$node->name));
//                    print l($userlink, $result);
                ?>  
                                </div>
                            </div>                  
                            <div class="hcf-title">    
                                <label>From:</label>
                                <div class="hcf-title-link">
                <?php
//            $link = " " . $group->title . " ";
//            $search = array(' the ', ' a ', ' an ', ' as ', ' at ', ' before ', ' but ', ' by ', ' for ', ' from ', ' is ', ' in ', ' into ',  ' like ', ' of ', ' off ', ' on ', ' onto ', ' per ', ' since ', ' than ', ' this ', ' that ', ' to ', ' up ', ' via ', ' with ', ' ');
//            foreach($search as $s){
//            $link = strtolower(str_replace($s,' ',$link));
//            }
//            $link = str_replace(' ','',$link);
//            print l($group->title,$link);
            }
            ?>
                            </div>
                        </div> 
            
                    </div>       -->
        </div>
    </div>

    <div class="deal-others">
        <?php if (count($node->field_marketing_city['und']) > 0) { ?>
            <label class="deal-label1">Marketing cities:</label>
            <div class="deal-value1">
                <?php
                print '<ul>';
                foreach ($node->field_marketing_city['und'] as $city) {
                    print '<li>' . $city['taxonomy_term']->name . '</li>';
                }
                print '</ul>';
                ?>
            </div>
        <?php } ?>
    </div>

    <div class="deal-others">
        <label class="deal-label1">Telephone number:</label>
        <div class="deal-value1">
            <?php
            print $group->field_telephone_number['und'][0]['value'];
            ?>
        </div>
    </div>

    <div class="deal-others">
        <?php if (isset($node->field_expiration_date['und'][0]['value'])) { ?>
            <label class="deal-label1">Expiration Date:</label>
            <div class="deal-value1">
                <?php
//                print $node->field_expiration_date['und'][0]['value'];
                echo format_date(strtotime($node->field_expiration_date['und'][0]['value']), 'long', '', 'Europe/America');
                ?>
            </div>
        <?php } ?>
    </div>

    <div class="deal-others">
        <?php if (isset($node->field_deal_description['und'][0]['value'])) { ?>
            <label class="deal-label">Deal Information:</label>
            <div class="deal-value">
                <?php
                print $node->field_deal_description['und'][0]['value'];
                ?>
            </div>
        <?php } ?>
    </div>

    <div class="deal-others">
        <?php if (isset($node->field_deal_information['und'][0]['value'])) { ?>
            <label class="deal-label">Deal Description:</label>
            <div class="deal-value">
                <?php
                print $node->field_deal_information['und'][0]['value'];
                ?>
            </div>
        <?php } ?>
    </div>


    <div class="deal-message">
        <a href="?inline=true#prod-preview" class="colorbox-inline">
            <img src="<?php print $base_url; ?>/sites/all/themes/seven_doublemthemes/images/msgme.png" alt="Message Me" />
        </a>
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

</div>