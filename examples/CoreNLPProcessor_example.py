# -*- coding: utf-8 -*-
# file: CoreNLPProcessor_example.py
# date: 2022-03-08


import os
import keytext4py
from keytext4py import CoreNLPProcessor
from keytext4py import utils


if __name__ == "__main__":
    text: str = utils.file2text("./text/zh1.txt")
    print("text:\n\t%s" % text)
    
    processor: CoreNLPProcessor = CoreNLPProcessor().init()
    print(processor.run(text))
