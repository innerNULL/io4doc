# -*- coding: utf-8 -*-
# file: SpaCyProcessor.py
# date: 2022-03-17


import sys
import os
import spacy
from typing import TypeVar, Type, Dict, Any, Final, Union, List, Tuple
from spacy.language import Language
from spacy.tokens.doc import Doc

from .TextProcessor import TextProcessor


DEFAULT_LANGS: Final[Union[List[str], str] ] = ["zh", "en"]

LANGS2DEPS: Final[Dict[str, str] ] = {
        "zh": "zh_core_web_sm", 
        "en": "en_core_web_sm"}


class SpaCyProcessor(TextProcessor):
    def __init__(self, 
            langs: Union[List[str], str]=DEFAULT_LANGS, 
            pipline: List[str]=['sentencizer']):
        self._core: Dict[str, Language] = {}
        self._langs: List[str] = [langs] if isinstance(langs, str) else langs


    def init(self):
        for lang in self._langs:
            download_cmd: str = "{} -m spacy download {} -vvv".format(
                    sys.executable, LANGS2DEPS[lang])
            try:
                exec("import {}".format(LANGS2DEPS[lang]))
                print("module '{}' already exists".format(
                    LANGS2DEPS[lang]))
            except:
                print("downloading module '{}'".format(
                    LANGS2DEPS[lang]))
                os.system(download_cmd)

            self._core[lang] = spacy.load(LANGS2DEPS[lang])

        return self

    def run(self, text: str, lang: str="en") -> List[List[Tuple[str, str] ] ]:
        output: List[List[Tuple[str, str] ] ] = []

        doc: Doc = self._core[lang](text)
        for i, sent in enumerate(doc.sents):
            curr_sent: List[Tuple[str, str] ] = []
            for j, token in enumerate(sent):
                curr_sent.append((token.text, token.pos_))
            output.append(curr_sent)
        print(output)
        return output

