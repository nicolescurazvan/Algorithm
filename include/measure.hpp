#include <chrono>
using namespace std::chrono;

// Function to measure single-threaded functions
template <typename T>
double measure(void (*func)(T&), T& arg)
{
    steady_clock::time_point start = steady_clock::now();
    func(arg);
    steady_clock::time_point end = steady_clock::now();
    auto t = duration<double>(end - start);
    return t.count();
}

// Function to measure multi-threaded functions
template <typename T>
double measure_mt(void (*func)(int, T&), T& arg, int threads)
{
    steady_clock::time_point start = steady_clock::now();
    func(arg, threads);
    steady_clock::time_point end = steady_clock::now();
    auto t = duration<double>(end - start);
    return t.count();
}