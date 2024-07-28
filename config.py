import json
import os
from pathlib import Path
import typer

APP_NAME = "obs3dian"
SETUP_FILE_NAME = "config.json"
APP_DIR_PATH = typer.get_app_dir(APP_NAME)


def save_config(json_data: dict):
    app_dir_path = Path(APP_DIR_PATH)  # create app setting folder
    aws_access_key_id = os.getenv("AWS_ACCESS_KEY_ID")
    aws_secret_access_key = os.getenv("AWS_SECRET_ACCESS_KEY")
    json_data = {
        "profile_name": "default",
        "aws_access_key": aws_access_key_id,
        "aws_secret_key": aws_secret_access_key,
        "bucket_name": "obs3dian",
        "output_folder_path": "./output",
        "image_folder_path": "./",
    }

    if not app_dir_path.exists():
        app_dir_path.mkdir()

    config_path = app_dir_path / SETUP_FILE_NAME
    with config_path.open("w") as f:
        json.dump(json_data, f)  # write config.json

    print(f"save config file in {config_path}")
