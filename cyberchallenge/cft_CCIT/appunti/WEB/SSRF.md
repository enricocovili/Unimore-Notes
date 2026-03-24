### **Server-Side Request Forgery (SSRF)**

**SSRF** occurs when an attacker induces a server-side application to make HTTP requests to an arbitrary domain of the attacker's choosing. Essentially, the attacker uses the vulnerable server as a "proxy" to attack internal systems that are protected by firewalls and not reachable from the external internet. By manipulating a URL parameter that the server fetches, an attacker can pivot into the internal network to scan ports, access metadata services, or interact with internal APIs.

---

**Practical Examples:http://::1/get_flag.php**

- **Accessing Cloud Metadata:** On AWS/GCP, internal metadata is stored at a non-routable IP.
    
    - _Normal:_ `https://example.com/proxy?url=https://legal-site.com`
        
    - _Attack:_ `https://example.com/proxy?url=http://169.254.169.254/latest/meta-data/iam/security-credentials/`
        
    - **Result:** The server fetches its own secret access keys and hands them to the attacker.
        
- **Internal Port Scanning:** Testing if internal services (like databases or admin panels) are active.
    
    - _Attack:_ `https://example.com/view-page?url=http://127.0.0.1:8080` or `http://192.168.1.1:22`
        
    - **Result:** Error messages or response times reveal if a service is running on that internal port.
        
- **Interacting with Local Services:** Many internal tools (like Redis or Memcached) don't require authentication because they assume the network is "safe."
    
    - _Attack:_ `https://example.com/api/fetch?url=http://localhost:6379/`
        
    - **Result:** The attacker may be able to run commands to flush the database or change configurations.
