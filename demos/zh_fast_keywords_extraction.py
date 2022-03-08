# -*- coding: utf-8 -*-
# file: rule_base_keywords_extraction.py
# date: 2022-02-25


import os
import textwrap 
import keytext4py
from typing import List, Tuple
from functools import reduce
from keytext4py import corenlp_helper
from keytext4py import utils
#from keytext4py_ext_cpp import keywords_by_pos
from keytext4py import fast_keywords
from keytext4py import CoreNLPProcessor
from stanza.server import CoreNLPClient


if __name__ == "__main__":
    zh_text: str = utils.file2text("./text/zh1.txt")
    text_processor: CoreNLPProcessor = CoreNLPProcessor().init()

    doc_ana: List[List[Tuple[str, str] ] ] = text_processor.run(zh_text)
    doc_tokens: List[Tuple[str, str] ] = reduce(
        lambda a, b: a + b, doc_ana)

    keywords = fast_keywords(doc_tokens, 
        pos_bucketing=True, top_k=8, 
        min_word_len=2 * 3 # Since each ZH char takes 3 bytes
    )
    
    print("text:")
    print(textwrap.fill(zh_text[:512] + "...\n", width=32))

    print("\nkey-words:")
    for keyword in keywords:
        print("{}: {}".format(
            f"{keyword[0]:>10}", keyword[1]))
