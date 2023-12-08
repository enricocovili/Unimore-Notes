import os

# Set the path to the directory containing your files
directory_path = "./Geometria"

# Get a list of files in the directory
files = os.listdir(directory_path)

# Iterate through the files and rename them
for file in files:
    # Extract the file extension
    old_name, extension = os.path.splitext(file)
    old_name

    if extension not in [".md", ".pdf"]:
        continue

    # get previous index
    old_index = old_name.split(".")[0]

    # Create the new index (two digits)
    new_index = old_index.zfill(2)

    # Create the new file name
    new_name = old_name.replace(old_index, new_index) + extension

    # Create the full paths for the old and new names
    old_path = os.path.join(directory_path, old_name + extension)
    new_path = os.path.join(directory_path, new_name)

    # Rename the file
    os.rename(old_path, new_path)
    print(f"Renamed: {old_name} -> {new_name}")
