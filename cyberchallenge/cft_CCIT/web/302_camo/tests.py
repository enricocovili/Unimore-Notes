import requests

session = requests.Session()
# set PHPSESSID cookie to a random value
session.cookies.set("PHPSESSID", "e26ac535c5a6a85abcc983441fcb9429")

page = session.get("http://302camo.challs.cyberchallenge.it/index.php")

print(page.text)
