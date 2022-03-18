# -*- coding: utf-8 -*-
# file: ./examples/SpaCyProcessor_example.py
# date: 2022-03-17


import os
import keytext4py
from keytext4py import SpaCyProcessor
from keytext4py import utils


if __name__ == "__main__":
    text: str = utils.file2text("./text/zh1.txt")
    print("text:\n\t%s" % text)
    
    processor: SpaCyProcessor = SpaCyProcessor().init()
    print(processor.run(text, "zh"))
