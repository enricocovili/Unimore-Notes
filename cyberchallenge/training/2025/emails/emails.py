import string
import pathlib
import math

ex_name = "emails"
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


def compute(content):
    t_s = tuple(map(int, content[1].split()))
    f_s = tuple(map(int, content[2].split()))
    email_times = tuple(map(int, content[3].split()))

    tot_time = 0
    for ix, email_time in enumerate(email_times):
        print(f"computing email n{ix}")
        curr_time = email_time
        for t, f in zip(t_s, f_s):
            if curr_time < t:
                curr_time += t - curr_time
            else:
                curr_time += math.ceil(curr_time / t) * t - curr_time
            curr_time += f

        tot_time += curr_time
    return str(tot_time)


if __name__ == "__main__":
    dataset_path = pathlib.Path(f"{location}{ex_name}/dataset/input")
    for input_file in sorted(dataset_path.iterdir()):
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
