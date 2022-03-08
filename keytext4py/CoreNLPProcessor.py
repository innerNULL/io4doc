# -*- coding: utf-8 -*-
# file: CoreNLPProcessor.py
# date: 2022-03-08


import os
import stanza
from typing import TypeVar, Type, Dict, Any, Final, Union, List, Tuple
from stanza.server import CoreNLPClient
from stanza.protobuf.CoreNLP_pb2 import Document

from .TextProcessor import TextProcessor
from . import utils
from . import corenlp_helper


T = TypeVar('T', bound='CoreNLPProcessor')


DEFAULT_CORENLP_DIR: Final[str] = os.path.join(
    utils.get_user_cache(), "_keytext4py", "_corenlp")

DEFAULT_EXT_LANGS: Final[Union[List[str], str] ] = "chinese"

DEFAULT_CORENLP_VERSION: Final[str] = "4.4.0"

DEFAULT_ANNOTATORS: Final[List[str] ] = ['tokenize', 'ssplit', 'pos']


class CoreNLPProcessor(TextProcessor):
    def __init__(self, 
            corenlp_dir: str=DEFAULT_CORENLP_DIR, 
            ext_langs: Union[List[str], str]=DEFAULT_EXT_LANGS, 
            annotators: List[str]=DEFAULT_ANNOTATORS):
        super().__init__()
       
        self._corenlp_client: CoreNLPClient = None 
        self._corenlp_dir: str = os.path.abspath(corenlp_dir)
        self._ext_langs: List[str] = \
                [ext_langs] if isinstance(ext_langs, str) else ext_langs
        self._corenlp_version: str = DEFAULT_CORENLP_VERSION
        self._annotators: List[str] = annotators

    def init(self, force: bool=False) -> T:
        stanza.install_corenlp(self._corenlp_dir)

        for lang in self._ext_langs:
            stanza.download_corenlp_models(
                model=lang, version=self._corenlp_version, 
                dir=self._corenlp_dir, force=force)

        os.environ['CORENLP_HOME'] = self._corenlp_dir

        self._corenlp_client = corenlp_helper.get_corenlp_client(
            properties=corenlp_helper.langs2properities(self._ext_langs), 
            preload=True, 
            annotators=self._annotators, 
            be_quiet=True)
        return self

    def run(self, text: str) -> List[List[Tuple[str, str] ] ]:
        """
        The output data structure is:
        
        Document, which is a list of lists:
            [sentences_0, ... , sentences_n]
        
        Sentence, which is a list of tuples:
            [word_0, ... , word_m]
        
        Word, which is a tuple:
            [word, pos, ...]
        """
        output: List[List[Tuple[str, str] ] ] = []

        doc: Document = self._corenlp_client.annotate(text)
        for i, sent in enumerate(doc.sentence):
            curr_sent: List[Tuple[str, str] ] = []
            for j, token in enumerate(sent.token):
                curr_sent.append((token.word, token.pos))
            output.append(curr_sent)
        return output


