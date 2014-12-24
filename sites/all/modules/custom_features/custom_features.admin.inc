<?php

// $Id: custom_features.admin.inc, Exp $

/**
 * @file
 * Administrative page callbacks for the custom_features  module.
 */
function role_user_limit_admin_settings_form() {
//  global $user;
//  print_r(og_get_entity_groups());exit;
    // display contacts in each category
    $query = db_select('role', 'r');
    $query->fields('r');
    $query->condition('r.rid', 4, '>');
    $return = $query->execute();
    foreach ($return as $role) {
        $field_name = str_ireplace(' ', '_', strtolower($role->name));
        $field_name = str_ireplace('(', '', $field_name);
        $field_name = str_ireplace(')', '', $field_name);
        $form["$field_name"] = array(
            '#type' => 'textfield',
            '#title' => t($role->name),
            '#default_value' => variable_get("$field_name", 0),
            '#description' => t('Enter maximum number of users for ' . $role->name . '. 0 for unlimited.')
        );
    }
    return system_settings_form($form);
}

function contest_deadline_admin_settings_form() {

    $field_name = str_ireplace(' ', '_', strtolower('Contest Deadline'));
    $form["$field_name"] = array(
        '#type' => 'textfield',
        '#title' => t('Contest Deadline'),
        '#default_value' => variable_get("$field_name", 0),
        '#description' => t('Enter deadline date for entering into the Contest. 0 for unlimited.')
    );

    return system_settings_form($form);
}

//function sales_user_list() {
//    $r = db_query("SELECT u.uid, u.name, ca.coupon_id, uc.code FROM {users u LEFT JOIN users_roles ur ON u.uid = ur.uid LEFT JOIN coupon_association ca on u.uid = ca.uid Left join uc_coupons uc on ca.coupon_id = uc.cid} WHERE ur.rid = 11 OR ur.rid = 14");
//
//    $coupon = '<div class="coupon-association">';
//    $coupon .= '<div style="float: left; padding-bottom:5px; border-bottom: 3px solid #e3e3e3; width: 100%; font-size:16px;">
//                <div style="float:left;width:100%;margin-bottom:10px;">
//                <a href="admin/store/coupons/add" style="float:left;margin-right:15px;color:#28a8e2;">Add New Coupon</a>
//                <a href="admin/people/create" style="float:left;color: #28a8e2;">Add Sales User</a>
//                </div>
//                <div class="left" style="float:left;width:50%;">
//                <div style="margin-bottom:0px;text-decoration:none;float:left;color: #28a8e2;">Users</div>
//                </div>
//                <div class="right" style="float:left;width:50%;">
//                <div style="margin-bottom:0px;text-decoration:none;float:left;color: #28a8e2;">Coupon Code</div>
//                </div>
//                </div>';
//    foreach ($r as $ra) {
//        $coupon .= '<div style="float: left; padding:5px 0; border-bottom: 1px dashed #d2d2d2; width: 100%; font-size:16px;">
//                <div class="left" style="float:left;width:50%;">';
//        $coupon .= '<div class="data">';
//        $coupon .= $ra->name;
//        $coupon .= '</div>';
//        $coupon .= '</div>';
//        $coupon .= '<div class="right" style="float:left;width:50%;">
//                <div class="data">';
//        if (!isset($ra->coupon_id)) {
//            $coupon .= '<a href="coupon_code_list?uid=' . $ra->uid . '&width=500px&height=500px" class="colorbox-load" style="text-decoration:none;float:left;color: #28a8e2;">Associate Coupon</a>';
//        } else {
//            $coupon .= $ra->code;
//        }
//        $coupon .= '</div>
//                </div>
//                </div>';
//    }
//    $coupon .= '</div>';
//    $coupon .= '</div>';
//    return $coupon;
//}
//
//function coupon_code_list() {
//    $uid = $_GET['uid'];
//    $coupon_code = db_query("SELECT code, cid FROM uc_coupons WHERE cid NOT IN (SELECT coupon_id FROM coupon_association) ");
//    $coupon .= '<div id="code">
//                 <div style="float:left;border-bottom:2px solid #cccccc;width:100%;">
//                 <div style="float:left;width:100%;color:black;font-size: 16px;font-weight: bold;">
//                 Coupon code
//                 </div>
//                 </div>';
//    $i = 1;
//    foreach ($coupon_code as $coupon_code_result) {
//        $coupon .= '<div style="float:left;border-bottom:1px dotted #cccccc;width:46%;padding:5px 2%;">
//                 <div style="float:left;width:100%;color: black;font-size: 16px;">';
//        $coupon .= $i . ". " . '<a href="associate_coupon_code_with_user?uid=' . $uid . '&cid=' . $coupon_code_result->cid . '" style="text-decoration:none;color: #28a8e2;">' . $coupon_code_result->code . '</a>';
//        $coupon .= '</div>
//                 </div>';
//        $i++;
//    }
//    $coupon .= '</div>';
//    print $coupon;
//}
//
//function associate_coupon_code_with_user() {
//    $uid = $_GET['uid'];
//    $cid = $_GET['cid'];
//    $result = db_query("INSERT INTO {coupon_association} (uid, coupon_id) VALUES ($uid, $cid)");
//    drupal_goto("sales_user_list");
//}

function admin_sales_report() {
    $elements = drupal_get_form("products_sold_by_users_date_range");
    $form = drupal_render($elements);
    if (isset($_SESSION['start_date']) && isset($_SESSION['end_date'])) {
        $start_date = $_SESSION['start_date'];
        $end_date = $_SESSION['end_date'];
        unset($_SESSION['start_date']);
        unset($_SESSION['end_date']);
        $unix_start_date = strtotime($start_date . '00:00');
        $unix_end_date = strtotime($end_date . '23:59:59');
    } else {
        $day = date("d");
        if ($day >= 14) {
            $current_month = date("m");
            $next_month = $current_month + 1;
            $current_year = date("Y");
            $start_date = $current_year . "/" . $current_month . "/" . "14";
            $end_date = $current_year . "/" . $next_month . "/" . "13";
            $unix_start_date = strtotime($start_date . '00:00');
            $unix_end_date = strtotime($end_date . '23:59:59');
        } else {
            $current_month = date("m");
            $previous_month = $current_month - 1;
            $current_year = date("Y");
            $start_date = $current_year . "/" . $previous_month . "/" . "14";
            $end_date = $current_year . "/" . $current_month . "/" . "13";
            $unix_start_date = strtotime($start_date . '00:00');
            $unix_end_date = strtotime($end_date . '23:59:59');
        }
    }
    $uid = db_query("SELECT u.uid from users u LEFT JOIN users_roles ur ON u.uid = ur.uid LEFT JOIN role r on r.rid = ur.rid WHERE (r.name = 'Sales Associate' OR r.name = 'Sales Manager')");
    $coupon = '<div class="products-sold" style="float:left;width:100%;">';
    $coupon .= $form;
    $coupon .= '<div style="float:left;width:100%;font-size:16px;margin-bottom:10px;">The result shown below starts from <strong>' . $start_date . '</strong> and Ends at <strong>' . $end_date . '</strong></div>';
    $coupon .= '<div style="float: left; padding-bottom:5px; border-bottom: 3px solid #e3e3e3; width: 100%; font-size:16px;">
                <div style="float:left;width:20%;min-height:24px;">
                <div style="margin-bottom:0px;text-decoration:none;float:left;color: #28a8e2;">Position</div>
                </div>
                <div style="float:left;width:20%;min-height:24px;">
                <div style="margin-bottom:0px;text-decoration:none;float:left;color: #28a8e2;">Users</div>
                </div>
                <div style="float:left;width:10%;min-height:24px;">
                <div style="margin-bottom:0px;text-decoration:none;float:left;color: #28a8e2;">Sales</div>
                </div>
                <div style="float:left;width:15%;min-height:24px;">
                <div style="margin-bottom:0px;text-decoration:none;float:left;color: #28a8e2;">Products Total</div>
                </div>
                <div style="float:left;width:10%;min-height:24px;">
                <div style="margin-bottom:0px;text-decoration:none;float:left;color: #28a8e2;">SM</div>
                </div>
                <div style="float:left;width:10%;min-height:24px;">
                <div style="margin-bottom:0px;text-decoration:none;float:left;color: #28a8e2;">SA</div>
                </div>
                <div style="float:left;width:15%;min-height:24px;">
                <div style="margin-bottom:0px;text-decoration:none;float:left;color: #28a8e2;">SM Name</div>
                </div>
                </div>';
    foreach ($uid as $user) {
        $coupon_query = db_query("SELECT sr.uid, u.uid as purchaser_id, r.name as rname from invitations_by_sr sr INNER JOIN users u on sr.email = u.mail LEFT JOIN users_roles ur ON sr.uid = ur.uid LEFT JOIN role r on r.rid = ur.rid WHERE sr.uid = $user->uid");
        $count = $coupon_query->rowCount();
        $parent_name = '';
        $sales_count = 0;
        $total = 0;
        $sm_incent = 0;
        $sa_incent = 0;
        if ($count > 0) {
            foreach ($coupon_query as $coupon_query_result) {
                $query = db_query("SELECT order_total FROM uc_orders
                       WHERE (order_status = 'completed' OR order_status = 'payment_received') AND uid =" . $coupon_query_result->purchaser_id . "
                       AND created BETWEEN $unix_start_date AND $unix_end_date");
                $query_count = $query->rowCount();
                $sales_count += $query_count;
                $user_name = db_query("SELECT uid, name FROM users WHERE uid = " . $coupon_query_result->uid);
                $user_name_result = $user_name->fetchObject();
                    foreach ($query as $query_result) {
                        $total += $query_result->order_total;
                }
            }
            if ($coupon_query_result->rname == "Sales Manager") {
                $sm_incent = ($total / 100) * 50;
                $sa_incent = 0;
            } else if ($coupon_query_result->rname == "Sales Associate") {
                $sm_incent = ($total / 100) * 10;
                $sa_incent = ($total / 100) * 40;
                $parent_name = relation_get_related_entity('user', $user_name_result->uid);
            }
            $coupon .= '<div style="float: left; padding:5px 0; border-bottom: 1px dashed #d2d2d2; width: 100%; font-size:16px;">
                        <div style="float:left;width:20%;min-height:24px;">';
            $coupon .= '<div class="data">';
            $coupon .= $coupon_query_result->rname;
            $coupon .= '</div>
                        </div>';
            $coupon .= '<div style="float:left;width:20%;min-height:24px;">
                        <div class="data">
                        <a style="color: #28a8e2;" href="complete_sales_report?uid=' . $coupon_query_result->uid . '">';
            $coupon .= $user_name_result->name;
            $coupon .= '</a>
                        </div>
                        </div>';
            $coupon .= '<div style="float:left;width:10%;min-height:24px;">
                        <div class="data">';
            $coupon .= $sales_count;
            $coupon .= '</div>
                        </div>';
            $coupon .= '<div style="float:left;width:15%;min-height:24px;">
                        <div class="data">';
            $coupon .= $total;
            $coupon .= '</div>
                        </div>';
            $coupon .= '<div style="float:left;width:10%;min-height:24px;">
                        <div class="data">';
            $coupon .= $sm_incent;
            $coupon .= '</div>
                        </div>';
            $coupon .= '<div style="float:left;width:10%;min-height:24px;">
                        <div class="data">';
            $coupon .= $sa_incent;
            $coupon .= '</div>
                        </div>';
            $coupon .= '<div style="float:left;width:15%;min-height:24px;">
                        <div class="data">';
            $coupon .= $parent_name->name;
            $coupon .= '</div>
                        </div>
                        </div>';
        }
    }
    $coupon .= '</div>
                </div>';
    return $coupon;
}

function products_sold_by_users_date_range() {
    $form['start_date'] = array(
        '#title' => t('Start Date'),
        '#date_format' => 'Y/m/d',
        '#date_year_range' => '-40:+30',
        '#type' => 'date_popup',
        '#required' => TRUE,
        '#prefix' => '<div class="products-sold-form-item">',
        '#suffix' => '</div>'
    );
    $form['end_date'] = array(
        '#title' => t('End Date'),
        '#date_format' => 'Y/m/d',
        '#date_year_range' => '-40:+30',
        '#type' => 'date_popup',
        '#required' => TRUE,
        '#prefix' => '<div class="products-sold-form-item">',
        '#suffix' => '</div>'
    );
    $form['submit'] = array(
        '#type' => 'submit',
        '#value' => 'Submit',
        '#prefix' => '<div class="products-sold-form-button">',
        '#suffix' => '</div>'
    );
    $form['#submit'][] = 'products_sold_by_users_date_range_form_submit';
    return $form;
}

function products_sold_by_users_date_range_form_submit($form, &$form_state) {
//    echo '<pre/>';print_r($form_state);exit;
    $_SESSION['start_date'] = $form_state['input']['start_date']['date'];
    $_SESSION['end_date'] = $form_state['input']['end_date']['date'];
    $form_state['redirect'] = 'admin_sales_report';
}