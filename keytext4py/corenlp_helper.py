# -*- coding: utf-8 -*- 
# file: corenlp_helper.py
# date: 2022-02-25


import os
import stanza
from typing import List, Dict, Tuple, Union
from stanza.server import CoreNLPClient
from stanza.protobuf.CoreNLP_pb2 import Document


def register_corenlp_path(corenlp_root: str) -> None:
    corenlp_root = os.path.abspath(corenlp_root)
    os.environ['CORENLP_HOME'] = corenlp_root


def init_corenlp(
        target_dir: str, 
        ext_lang: Union[List[str], str]="chinese", 
        version: str="4.4.0", 
        force: bool=False
) -> None:
    corenlp_root: str = os.path.abspath(target_dir)
    stanza.install_corenlp(corenlp_root)

    ext_lang_: List[str] = []
    if isinstance(ext_lang, str):
        ext_lang_ = [ext_lang]
    else:
        ext_lang_ = ext_lang

    for lang in ext_lang_:
        stanza.download_corenlp_models(
            model=lang, version=version, 
            dir=corenlp_root, force=force)

    register_corenlp_path(corenlp_root)


def get_corenlp_client(
        properties, # e.g., 'zh'
        preload: bool=True, 
        annotators: List[str] = ['tokenize', 'ssplit', 'pos'], 
        be_quiet: bool=True
) -> CoreNLPClient:
    corenlp_client: CoreNLPClient = CoreNLPClient(
        annotators=annotators, 
        timeout=30000, memory='6G', 
        properties=properties, be_quiet=be_quiet)

    if preload:
        corenlp_client.annotate("")
    return corenlp_client


def get_token_info(
        corenlp_client: CoreNLPClient, text: str
) -> List[Tuple[str, str] ]:
    """
    [[Token, POS]....[Token, POS]]
    """
    token_info: List[List[str] ] = []
    doc: Document = corenlp_client.annotate(text)
    for i, sent in enumerate(doc.sentence):
        for j, token in enumerate(sent.token):
            token_info.append((token.word, token.pos))
    return token_info


def lang2property(lang: str) -> str:
    if lang == "chinese":
        return "zh"


def langs2properities(langs: List[str]) -> str:
    return ",".join([lang2property(x) for x in langs])
