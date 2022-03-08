/// file: Document_benchmark.h
/// date: 2022-03-10


#ifndef __DOCUMENT_BENCHMARK_H__
#define __DOCUMENT_BENCHMARK_H__


#include <vector>
#include <string>
#include <benchmark/benchmark.h>
#include "Document.h"

using namespace keytext4py_ext;


static void BENCHMARK_Document_AppendToken(
    benchmark::State& state) {
  const int32_t count = 500;
  Document doc;
  std::vector<std::string> words = {}; words.resize(count);
  std::vector<std::string> pos = {}; pos.resize(count);
  for (int32_t i = 0; i < count; ++i) {
    words.emplace_back("text_" + std::to_string(i));
    pos.emplace_back("pos_" + std::to_string(i)); 
  }

  int32_t i = 0;
  for (auto _ : state) {
    while (i++ < count) {
      doc.AppendToken(words[i], pos[i]);
    }
  }
}


#endif

