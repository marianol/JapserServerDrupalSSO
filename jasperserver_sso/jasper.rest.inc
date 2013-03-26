<?php
/**
 * @file
 * This file includes Helper Functions for accesing the Jasperserver REST API
 *
 */
define('JRS_HOST', 'localhost');
define('JRS_PORT', '8080');
define('JRS_BASE', '/jasperserver-pro'); // Pro

define('JRS_BASE_URL', 'http://' . JRS_HOST . ':' . JRS_PORT . JRS_BASE . '/'); 

define('JS_REST_URL', JRS_BASE_URL . 'rest/');
define('JS_RESTV2_URL', JRS_BASE_URL . 'rest_v2/');


function jasperservet_sso_curl_set_opts($curl_opts) {

}

function jasperserver_sso_rest_post($service, $data, $japserRestUrl = JS_REST_URL , $headers=array()) {
    
  $requestData = http_build_query($data);
  
  $headers[] = 'Content-Length: '.strlen($requestData);
  
  $curl_opts = array();
  $curl_opts[CURLOPT_CUSTOMREQUEST] = 'POST';
  $curl_opts[CURLOPT_HTTPHEADER] = $headers;
  $curl_opts[CURLOPT_POSTFIELDS] = $requestData;

  return jasperserver_sso_rest_doRequest($japserRestUrl . $service, $curl_opts);
 }

function jasperserver_sso_rest_doRequest($url, $curl_opts) {
  $std_opts = array(
    CURLOPT_RETURNTRANSFER => true,  // return result instead of echoing
    CURLOPT_SSL_VERIFYPEER => false, // stop cURL from verifying the peer's certificate
    CURLOPT_FOLLOWLOCATION => true,  // follow redirects, Location: headers
    CURLOPT_MAXREDIRS      => 10,    // but dont redirect more than 10 times
    //CURLOPT_FILE         => '/dev/null', // saving cookies
    CURLOPT_HEADER         => true   // Get headers
  );
 
  $curl = curl_init($url);
  
  foreach ($std_opts  as $opt => $val)
      curl_setopt($curl, $opt, $val); 
   
  foreach ($curl_opts  as $opt => $val)
      curl_setopt($curl, $opt, $val);
  
  $response['body'] = curl_exec($curl);
  $response['metadata'] = curl_getinfo($curl);
  curl_close($curl);
  
  return $response;
 }
