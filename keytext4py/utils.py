# -*- coding: utf-8 -*-
# file: utils.py
# date: 2022-02-27


import os


def file2text(path: str) -> str:
    return open(path, "r")\
            .read()\
            .strip("\n")\
            .strip(" ")

def get_user_root() -> str:
    return os.popen("cd ~ && pwd").read().strip("\n")


def get_user_cache() -> str:
    return os.path.join(
        get_user_root(), ".cache")
