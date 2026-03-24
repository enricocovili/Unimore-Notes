### **Cross-Site Request Forgery (CSRF)**

**CSRF** (pronounced _sea-surf_) is an attack that forces an authenticated user to execute unwanted actions on a web application in which they are currently logged in. Unlike XSS, which aims to steal data, CSRF aims to **change data** or state. The attack works because the browser automatically includes all cookies (including session cookies) with every request to a specific domain, even if that request originates from a different, malicious site.

---
### **The Attack Scenario**

Imagine you are logged into your bank at `bank.com`. An attacker wants to trick you into transferring money to their account.

1. **The Malicious Site:** The attacker hosts a website (`evil-site.com`) containing a hidden form or a malicious script.
    
2. **The Trigger:** You visit `evil-site.com` while your bank session is still active in another tab.
    
3. **The Request:** The malicious site automatically submits a request to your bank:
    
    - `POST https://bank.com/transfer?amount=1000&to=attacker_acct`
        
4. **The Execution:** Your browser sees the request to `bank.com`, attaches your valid session cookie, and sends it. The bank sees a "valid" request from you and processes the transfer.
---
### **Key Characteristics**

- **Reliance on State:** CSRF only works on actions that change state (e.g., changing a password, deleting a post, or making a purchase).
    
- **Cookie-Based Auth:** It exploits the browser's default behavior of sending credentials automatically.
    
- **Blind Execution:** The attacker cannot see the response from the server; they only know the request was sent.
### **Common Payloads**

- **GET-based CSRF:** Using an `<img>` tag to trigger a request.
    
    HTML ```
    <img src="https://bank.com/transfer?amount=1000&to=attacker" style="display:none;">```
    
- **POST-based CSRF:** Using a hidden form that auto-submits via JavaScript.

```
   <form id="csrfForm" action="https://social-media.com/delete-account" method="POST"> <input type="hidden" name="confirm" value="true">
   </form>
   <script>document.getElementById('csrfForm').submit();</script>
```
