<?php
if (isset($_REQUEST['admin'])) {
    setcookie('admin', $_REQUEST['admin'], time() + 3600, '/');
    file_put_contents('./admin_cookie.txt', $_REQUEST['admin']);
    echo "Cookie saved successfully";
} else {
    echo "No admin parameter provided";
}
?>