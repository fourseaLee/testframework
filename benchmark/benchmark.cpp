#include <celero/Celero.h>
#include <cmath>
#include <cstdlib>
#include "easylogging++.h"

INITIALIZE_EASYLOGGINGPP


CELERO_MAIN;

// 运行一个自动的基线。  
// Celero 保证能提供足够的采样来得到一个合理的测量结果
BASELINE(CeleroBenchTest, Baseline, 0, 7100000)
{
	celero::DoNotOptimizeAway(static_cast<float>(sin(3.14159265)));
}

// 运行一个自动测试。  
// Celero 保证能提供足够的采样来得到一个合理的测量结果
BENCHMARK(CeleroBenchTest, Complex1, 0, 7100000)
{
	celero::DoNotOptimizeAway(static_cast<float>(sin(fmod(rand(), 3.14159265))));
}

// 运行一个手动测试。这是对一个样本进行每秒 7100000 次操作。
// Celero 保证能提供足够的采样来得到一个合理的测量结果。
BENCHMARK(CeleroBenchTest, Complex2, 1, 7100000)
{
	celero::DoNotOptimizeAway(static_cast<float>(sin(fmod(rand(), 3.14159265))));
}

// 运行一个手动测试。这是对 60 个样本进行每秒 7100000 次操作。
// Celero 保证能提供足够的采样来得到一个合理的测量结果。
BENCHMARK(CeleroBenchTest, Complex3, 60, 7100000)
{
	celero::DoNotOptimizeAway(static_cast<float>(sin(fmod(rand(), 3.14159265))));
}
