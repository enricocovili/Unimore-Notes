**Command Injection** occurs when an application passes unsafe user-supplied data (forms, cookies, HTTP headers) to a system shell. An attacker can use shell **metacharacters** to bypass the intended command and execute arbitrary operating system commands with the privileges of the application.

**Special Characters & Delimiters:**

- **`;` (Semicolon):** Executes the first command, then the second.
    
- **`&` (Background):** Runs the command in the background.
    
- **`&&` (AND):** Runs the second command only if the first succeeds.
    
- **`||` (OR):** Runs the second command only if the first fails.
    
- **`|` (Pipe):** Passes the output of the first command as input to the second.
    
- **`` ` `` (Backtick) or `$( )`:** Inline execution (replaces the string with the command's output).
    
- **`\n` (Newline):** Breaks the line to start a new command (often bypasses simple regex filters).
    

**The Attack Scenario:**

Imagine a "Network Utility" page that lets you ping an IP address.

- **Expected Input:** `8.8.8.8`
    
- **Server Command:** `ping -c 4 8.8.8.8`
    

**The Injection:** An attacker inputs: `8.8.8.8; cat /etc/passwd`

- **Final Command:** `ping -c 4 8.8.8.8; cat /etc/passwd`
    
- **Result:** The server pings the IP, then immediately displays the system's user file in the browser.

Another powerful way to validate a command injection is to issue a DNS pingback 
➢ DNS queries are powerful because they are hardly blacklisted on firewall 
To create a DNS bin, it is possible to use http://requestbin.net/dns or http://dnsbin.zhack.ca/