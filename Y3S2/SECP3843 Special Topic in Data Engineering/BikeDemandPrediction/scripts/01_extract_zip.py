import zipfile
import os

zip_folder = "data/trip/zip"
output_folder = "data/trip/csv"

os.makedirs(output_folder, exist_ok=True)

for file in os.listdir(zip_folder):
    if file.endswith(".zip"):
        zip_path = os.path.join(zip_folder, file)

        print(f"Extracting: {file}")

        with zipfile.ZipFile(zip_path, "r") as zip_ref:
            zip_ref.extractall(output_folder)

print("DONE: All ZIP files extracted.")