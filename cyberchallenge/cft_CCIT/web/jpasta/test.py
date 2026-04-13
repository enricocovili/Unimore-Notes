import requests

# Create a session
session = requests.Session()

# set cookie "session" to a random value
session.cookies.set(
    "session",
    "eyJ1c2VybmFtZSI6ImVucmlfdGVzdCJ9.aZ854g.M0Te_Vbsp_uuFw70cSTv2lXSl18",
    domain="denominative-stalky-jeannine.ngrok-free.dev",
)

session.get("http://denominative-stalky-jeannine.ngrok-free.dev/jpasta")
print(session.get("http://jpasta.challs.cyberchallenge.it/list"))

# Close session
session.close()
