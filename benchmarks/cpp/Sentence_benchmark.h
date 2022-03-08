/// file: Sentence_benchmark.h
/// date: 2022-03-10


#ifndef __SENTENCE_BENCHMARK_H__
#define __SENTENCE_BENCHMARK_H__


#include <vector>
#include <string>
#include <benchmark/benchmark.h>
#include "Sentence.h"

using namespace keytext4py_ext;


static void BENCHMARK_Sentence_AppendToken500(
    benchmark::State& state) {
  const int32_t count = 500;
  Sentence sent;
  std::vector<Token> tokens = {};
  for (int32_t i = 0; i < count; ++i) {
    std::string text = "text_" + std::to_string(i);
    std::string pos = "pos_" + std::to_string(i);
    tokens.emplace_back(Token({
        id: (uint64_t)(i + 1), 
        text: text, 
        pos: pos}));
  }

  int32_t i = 0;
  for (auto _ : state) {
    while (i++ < count) {
      sent.AppendToken(&(tokens[i]));
    }
  }
}


static void BENCHMARK_Sentence_AppendToken1000(
    benchmark::State& state) {
  const int32_t count = 1000;
  Sentence sent;
  std::vector<Token> tokens = {};
  for (int32_t i = 0; i < count; ++i) {
    std::string text = "text_" + std::to_string(i);
    std::string pos = "pos_" + std::to_string(i);
    tokens.emplace_back(Token({
        id: (uint64_t)(i + 1), 
        text: text, 
        pos: pos}));
  }

  int32_t i = 0;
  for (auto _ : state) {
    while (i++ < count) {
      sent.AppendToken(&(tokens[i]));
    }
  }
}


static void BENCHMARK_Sentence_AppendToken2000(
    benchmark::State& state) {
  const int32_t count = 2000;
  Sentence sent;
  std::vector<Token> tokens = {};
  for (int32_t i = 0; i < count; ++i) {
    std::string text = "text_" + std::to_string(i);
    std::string pos = "pos_" + std::to_string(i);
    tokens.emplace_back(Token({
        id: (uint64_t)(i + 1), 
        text: text, 
        pos: pos}));
  }

  int32_t i = 0;
  for (auto _ : state) {
    while (i++ < count) {
      sent.AppendToken(&(tokens[i]));
    }
  }
}


static void BENCHMARK_Sentence_AppendToken5000(
    benchmark::State& state) {
  const int32_t count = 5000;
  Sentence sent;
  std::vector<Token> tokens = {};
  for (int32_t i = 0; i < count; ++i) {
    std::string text = "text_" + std::to_string(i);
    std::string pos = "pos_" + std::to_string(i);
    tokens.emplace_back(Token({
        id: (uint64_t)(i + 1), 
        text: text, 
        pos: pos}));
  }

  int32_t i = 0;
  for (auto _ : state) {
    while (i++ < count) {
      sent.AppendToken(&(tokens[i]));
    }
  }
}


static void BENCHMARK_Sentence_AppendToken10000(
    benchmark::State& state) {
  const int32_t count = 10000;
  Sentence sent;
  std::vector<Token> tokens = {};
  for (int32_t i = 0; i < count; ++i) {
    std::string text = "text_" + std::to_string(i);
    std::string pos = "pos_" + std::to_string(i);
    tokens.emplace_back(Token({
        id: (uint64_t)(i + 1), 
        text: text, 
        pos: pos}));
  }

  int32_t i = 0;
  for (auto _ : state) {
    while (i++ < count) {
      sent.AppendToken(&(tokens[i]));
    }
  }
}


static void BENCHMARK_Sentence_AppendToken100000(
    benchmark::State& state) {
  const int32_t count = 100000;
  Sentence sent;
  std::vector<Token> tokens = {};
  for (int32_t i = 0; i < count; ++i) {
    std::string text = "text_" + std::to_string(i);
    std::string pos = "pos_" + std::to_string(i);
    tokens.emplace_back(Token({
        id: (uint64_t)(i + 1), 
        text: text, 
        pos: pos}));
  }

  int32_t i = 0;
  for (auto _ : state) {
    while (i++ < count) {
      sent.AppendToken(&(tokens[i]));
    }
  }
}


static void BENCHMARK_Sentence_AppendToken500000(
    benchmark::State& state) {
  const int32_t count = 500000;
  Sentence sent;
  std::vector<Token> tokens = {};
  for (int32_t i = 0; i < count; ++i) {
    std::string text = "text_" + std::to_string(i);
    std::string pos = "pos_" + std::to_string(i);
    tokens.emplace_back(Token({
        id: (uint64_t)(i + 1), 
        text: text, 
        pos: pos}));
  }

  int32_t i = 0;
  for (auto _ : state) {
    while (i++ < count) {
      sent.AppendToken(&(tokens[i]));
    }
  }
}


#endif

