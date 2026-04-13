#!/usr/bin/env python3

import signal
import os
from secret import flag, random_messages
from Crypto.Util.number import bytes_to_long, getPrime
import random

TIMEOUT = 300

assert len(random_messages) == 2
e = 5
possible_messages = random_messages + [flag]
random.shuffle(possible_messages)


def get_pubkey():
    return getPrime(512) * getPrime(512)


def handle():
    while True:
        print("What do you want to do?")
        print("1. See first ciphertext")
        print("2. See second ciphertext")
        print("3. See third cipehrtext")
        choice = int(input("> "))

        if 1 <= choice <= 3:
            n = get_pubkey()
            ct = pow(bytes_to_long(possible_messages[choice - 1].encode()), e, n)
            print(f"N: {n}")
            print(f"Ciphertext: {ct}")
        else:
            print("Please provide an integer as the message.")


if __name__ == "__main__":
    signal.alarm(TIMEOUT)
    handle()
