#include <benchmark/benchmark.h>

#include "steg.hpp"

static void BM_str_ASCII2Binary(benchmark::State &state)
{
    steg::message_t msg("c++");

    for (auto _ : state)
    {
        msg.binary();
    }
}

static void BM_str_Binary2ASCII(benchmark::State &state)
{
    for (auto _ : state)
    {
        steg::message::from_binary("011000110010101100101011");
    }
}

// Register the function as a benchmark
BENCHMARK(BM_str_ASCII2Binary);
BENCHMARK(BM_str_Binary2ASCII);