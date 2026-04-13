import string
import pathlib

ex_name = "aliens"
location = "./training/2025/"

ALPHABET = string.ascii_letters + string.digits


def load_input(filename: str):
    with open(filename) as f:
        return f.readlines()


def check(result_file: str, correct_file: str):
    with open(result_file) as f:
        results = f.readlines()
    with open(correct_file) as f:
        correct_result = f.readlines()

    return results == correct_result


def write_result(result, input_file):
    out_file = f"{location}{ex_name}/results/{input_file.replace('input', 'output')}"
    with open(out_file, "w") as f:
        f.write(result)
    return out_file


def rotate_string(string, x):
    new_string = ""
    for char in string:
        new_string += ALPHABET[(ALPHABET.index(char) + x) % len(ALPHABET)]
    return new_string


def compute(content):
    res = ""
    for ix, row in enumerate(content[1:]):  # skipping first row as useless
        print(f"computing operation {ix}")
        elements = row.strip().split(" ")
        command = elements[0]
        if command == "del":
            if len(res) > 0:
                res = res[0:-1]
        elif command == "add":
            res = res + elements[1]
        elif command == "swap":
            new_res = ""
            for char in res:
                if char == elements[1]:
                    new_res += elements[2]
                elif char == elements[2]:
                    new_res += elements[1]
                else:
                    new_res += char
        elif command == "rot":
            res = rotate_string(res, int(elements[1]))

    return res


if __name__ == "__main__":
    dataset_path = pathlib.Path(f"{location}{ex_name}/dataset/input")
    for input_file in dataset_path.iterdir():
        if input_file.is_file():
            print(f"computing file {input_file.name}")
            result = compute(load_input(input_file.absolute()))
            result_file = write_result(result, input_file.name)
            if check(
                result_file,
                f"{location}{ex_name}/dataset/output/{input_file.name.replace('input', 'output')}",
            ):
                print(f"{input_file.name} è ok")
            else:
                print(f"{input_file.name} not ok")
