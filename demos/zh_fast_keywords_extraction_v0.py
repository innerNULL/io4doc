# -*- coding: utf-8 -*-
# file: rule_base_keywords_extraction.py
# date: 2022-02-25


import os
import keytext4py
from typing import List, Tuple
from keytext4py import corenlp_helper
from keytext4py import utils
#from keytext4py_ext_cpp import keywords_by_pos
from keytext4py import fast_keywords
from stanza.server import CoreNLPClient


if __name__ == "__main__":
    corenlp_helper.init_corenlp(
        os.path.join(utils.get_user_cache(), "_keytext4py", "_corenlp"))
    corenlp_client: CoreNLPClient = \
            corenlp_helper.get_corenlp_client(properties="zh")
    zh_text: str = utils.file2text("./text/zh1.txt")
    token_info: List[Tuple[str, str] ] = \
            corenlp_helper.get_token_info(
                corenlp_client, zh_text)

    kw: List[Tuple[str, float] ] = fast_keywords(
        token_info, pos_bucketing=True, top_k=10, 
        min_word_len=2 * 3) # Each chinese char in c++ takes 3 byte

    print("text:")
    print(zh_text[:512] + "...\n")
    print("keywords:")
    print(kw)
