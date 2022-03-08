# -*- coding: utf-8 -*-
# file: stanza_helper.py
# date: 2022-03-01


import stanza
from stanza.pipeline.core import Pipeline
from typing import List, Tuple


#TODO@20220308
class DocProcessor(object):
    def __init__(self, 
            lang: str, 
            tasks: str='tokenize,mwt,pos'):
        self._core: Pipeline = Pipeline(
            lang=lang, processors=tasks)

    def parsing(self, 
            doc: str
    )  -> List[List[Tuple[str, str] ] ]:
        result: List[List[Tuple[str, str] ] ] = []
        return result
