from pwn import *
import re
import logging
import time

logging.basicConfig(level=logging.INFO, format="[%(levelname)s] %(message)s")

r = remote("piecewise.challs.cyberchallenge.it", 9110)

try:
    while True:
        # Read until the end of the prompt (adjust "stuff)" if the text varies)
        data = r.recvline(timeout=5).decode().strip()
        print(f"\n[+] Received: {data}")

        if "partial flag" in data.lower():
            continue

        if "full flag" in data.lower():
            logging.info("Full flag received! Ending interaction.")
            break

        if "empty" in data:
            # send empty input for the empty challenge
            # logging.info("Sending empty input")
            r.send(b"\n")
            time.sleep(0.1)
            continue

        # Regex to capture: Number, Bits (32/64), and Endianness (little/big)
        match = re.search(r"number (\d+) as a (\d+)-bit (\w+)-endian", data)

        if match:
            num = int(match.group(1))
            bits = int(match.group(2))
            endian = match.group(3)

            # Pack and send
            if bits == 64:
                payload = p64(num, endian=endian)
            else:
                payload = p32(num, endian=endian)

            # logging.info(f"Sending {bits}-bit {endian}: {num} -> {payload.hex()}")
            r.send(payload)
            time.sleep(0.1)  # Small delay to ensure server processes the input
        else:
            break

except EOFError:
    logging.info("Connection closed by server.")
