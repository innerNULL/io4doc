/// file: benchmarking.cpp
/// date: 2022-03-10


#include <benchmark/benchmark.h>
#include "./Sentence_benchmark.h"
#include "./Document_benchmark.h"


BENCHMARK(BENCHMARK_Sentence_AppendToken500);
BENCHMARK(BENCHMARK_Sentence_AppendToken1000); 
BENCHMARK(BENCHMARK_Sentence_AppendToken2000); 
BENCHMARK(BENCHMARK_Sentence_AppendToken5000); 
BENCHMARK(BENCHMARK_Sentence_AppendToken10000); 
BENCHMARK(BENCHMARK_Sentence_AppendToken100000);
BENCHMARK(BENCHMARK_Sentence_AppendToken500000);

BENCHMARK(BENCHMARK_Document_AppendToken);


BENCHMARK_MAIN();
