import string
import pathlib

ex_name = "keyboard"
location = "./training/2025/"


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
    res = ""
    for row in content[2:]:  # skip first two
        if row.strip().isdigit():
            continue  # useless row
        res += str(tuple(set(string.ascii_lowercase) - set(row))[0]) + "\n"
    return res


if __name__ == "__main__":
    dataset_path = pathlib.Path(f"{location}{ex_name}/dataset/input")
    for input_file in dataset_path.iterdir():
        if input_file.is_file():
            result = compute(load_input(input_file.absolute()))
            result_file = write_result(result, input_file.name)
            if check(
                result_file,
                f"{location}{ex_name}/dataset/output/{input_file.name.replace('input', 'output')}",
            ):
                print(f"{input_file.name} è ok")
            else:
                print(f"{input_file.name} not ok")
