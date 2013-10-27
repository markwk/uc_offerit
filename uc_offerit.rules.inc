<?php

function uc_offerit_rules_action_info() {
  return array (
    'uc_offerit_send_postback_request' => array (
      'label' => t('Send postback request for a order'),
      'group' => t('Offer It'),
      'parameter' => array (
        'order' => array (
          'label' => t('Order'),
          'type' => 'uc_order',
        )
      )
    ),
    /*'uc_offerit_send_postback_request_for_recurring_order' => array (
      'label' => t('Send postback request for a recurring order'),
      'group' => t('Offer It'),
      'parameter' => array (
        'recurring_fee' => array (
          'label' => t('Recurring fee'),
          'type' => 'uc_recurring_fee',
        )
      )
    )*/
  );
}

function uc_offerit_send_postback_request ($order) {
  $url = uc_offerit_create_postback_url($order);
  if ($url) {
    $result = drupal_http_request($url);
    watchdog('uc_offerit', print_r($result, true));
  }
}

//we do not need this action since previous action works on both order simple and recurring
/*function uc_offerit_send_postback_request_for_recurring_order ($recurring_fee) {
  $order = uc_order_load($recurring_fee->original_order_id);
  dpm($order);
  $url = uc_offerit_create_postback_url($order);
  if ($url) {
    $params = explode('?', $url);
    $result = drupal_http_request($params[0], array('data' => $params[1]));
    watchdog('uc_offerit', print_r($result, true));
  }
}*/

function uc_offerit_rules_condition_info() {
  return array (
    'uc_offerit_compare_offerid_and_matching_product' => array (
      'label' => t('Check matching of order products and offerID'),
      'group' => 'OfferIt',
      'parameter' => array (
        'order' => array (
          'label' => t('Order'),
          'type' => 'uc_order',
        )
      )
    )
  );
}

function uc_offerit_compare_offerid_and_matching_product($order) {
  $products = uc_offerit_get_matching_products($order);
  return !empty($products);
}