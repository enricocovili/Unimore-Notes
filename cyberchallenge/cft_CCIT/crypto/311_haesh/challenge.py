#!/usr/bin/env python3

import signal
import os
from Crypto.Cipher import AES
from Crypto.Util.Padding import pad
import string
import random
import sys

TIMEOUT = 300

assert("FLAG" in os.environ)
FLAG = os.environ["FLAG"]
assert(FLAG.startswith("CCIT{"))
assert(FLAG.endswith("}"))

alph = string.ascii_lowercase + string.ascii_uppercase + string.digits


def get_string(N):
    return ''.join(random.choice(alph) for _ in range(N)).encode()


def hash(s):
    s = pad(s, 32)
    blocks = [s[i:i+16] for i in range(0, len(s), 16)]
    value = blocks[0]
    for block in blocks[1:]:
        cipher = AES.new(block, AES.MODE_ECB)
        value = cipher.encrypt(value)
    return value.hex()


def handle():
    for _ in range(10):
        s = get_string(32)
        h = hash(s)
        print(f"Give me a collision for ({s}, {h}) [in hex]")
        s2 = bytes.fromhex(input("> ").strip())
        if hash(s2) == h and s2 != s:
            print("Yay")
        else:
            print("Nope")
            exit()

    print(FLAG)


if __name__ == "__main__":
    signal.alarm(TIMEOUT)
    handle()
