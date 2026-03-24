**Example:**

Imagine a website that displays images using a URL like this:

`https://example.com/view_image?name=profile.jpg`

The server-side code might look for the file at: `/var/www/images/profile.jpg`.

An attacker could change the URL to:

`https://example.com/view_image?name=../../../../etc/passwd`

|**Type**|**Application Logic**|**Attacker Input**|**Final Path Resolved**|
|---|---|---|---|
|**Full Plain**|`$input`|`/etc/passwd`|`/etc/passwd`|
|**Prepended**|`/images/` + `$input`|`../../etc/passwd`|`/etc/passwd`|
|**Appended**|`/images/` + `$input` + `.png`|`../../etc/passwd%00`|`/etc/passwd`|
