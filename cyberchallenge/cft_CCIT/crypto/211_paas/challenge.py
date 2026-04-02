#!/usr/bin/env python3

import signal
import os
from secret import flag, primes
from Crypto.Util.number import bytes_to_long
import random

TIMEOUT = 300

assert("FLAG" in os.environ)
FLAG = os.environ["FLAG"]
assert(FLAG.startswith("CCIT{"))
assert(FLAG.endswith("}"))

assert len(primes) == 500  # just a precomputed list to generate keys faster
e = 65537


def get_pubkey():
    p, q = 1, 1
    while p == q:
        p = random.choice(primes)
        q = random.choice(primes)
    return p*q


def handle():
    while True:
        print("What do you want to do?")
        print("1. Get encrypted flag")
        print("2. Encrypt something")
        choice = int(input("> "))
        if choice == 1:
            n = get_pubkey()
            ct = pow(bytes_to_long(flag), e, n)
            print(f"N: {n}")
            print(f"Ciphertext: {ct}")
        elif choice == 2:
            try:
                msg = int(input("> "))
                n = get_pubkey()
                ct = pow(msg, e, n)
                print(f"N: {n}")
                print(f"Ciphertext: {ct}")
            except:
                print("Please provide an integer as the message.")


if __name__ == "__main__":
    signal.alarm(TIMEOUT)
    handle()
