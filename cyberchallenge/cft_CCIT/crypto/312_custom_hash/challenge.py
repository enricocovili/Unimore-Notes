#!/usr/bin/env python3

import signal
import os
from Crypto.Util.number import bytes_to_long
import string
import random

TIMEOUT = 300

# assert("FLAG" in os.environ)
# FLAG = os.environ["FLAG"]
# assert(FLAG.startswith("CCIT{"))
# assert(FLAG.endswith("}"))

FLAG = "CCIT{fake_flag_for_testing_purpose_only}"

alph = string.ascii_lowercase + string.ascii_uppercase + string.digits


def get_string(N):
    return ''.join(random.choice(alph) for _ in range(N)).encode()


def hash(s):
    bit_length = 256
    mult = 29008345376429296421127069579326784975588683454888105667218923842498450714902
    value = 38620319698752530836186304306399858496785977807021948335880851689582380908251
    if len(s) % 2 == 1:
        s = s + b'\x00'
    splitted_input = [s[i:i+2] for i in range(0, len(s), 2)]
    for x in splitted_input:
        value ^= (0x1337+bytes_to_long(x))
        value *= mult
        value %= 2**bit_length
    return hex(value)[2:].rjust(bit_length//4, '0')


def handle():
    for _ in range(10):
        s = get_string(32)
        h = hash(s)
        print(f"Give me a collision for ({s}, {h})")
        s2 = input("> ").strip().encode()
        if hash(s2) == h and s2 != s:
            print("Yay")
        else:
            print("Nope")
            exit()

    print(FLAG)


if __name__ == "__main__":
    signal.alarm(TIMEOUT)
    handle()
