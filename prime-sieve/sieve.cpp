#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <thread>
#include <chrono>

// Sum function for any type of integers
template <typename T>
size_t sum(std::vector<T> vec, size_t n)
{
    size_t s = 0;
    for (size_t i = 0; i < n; i++)
        s += vec[i];
    return s;
}

//-----------------------------------------
// Eratosthenes
void basic_sieve1(std::vector<size_t> &primes, size_t limit)
{
    std::vector<char> check(limit + 1, 1);
    size_t i, j;
    for (i = 2; i * i <= limit; i++)
    {
        if (check[i] == 1)
        {
            for (j = i * i; j <= limit; j += i)
                check[j] = 0;
        }
    }
    for (i = 2; i <= limit; i++)
    {
        if (check[i] == 1)
            primes.push_back(i);
    }
}

// Sieving
void sieve1(const std::vector<size_t> &primes, std::vector<char> &seg, size_t low, size_t high)
{
    size_t len = high - low;
    std::fill(seg.begin(), seg.begin() + len, 1);
    for (size_t p: primes)
    {
        size_t i = (p - low % p) % p;
        for (; i < len; i += p)
        {
            seg[i] = 0;
        }
    }
}

// Segmented sieve: single thread
size_t segment_sieve1(size_t n, size_t base)
{
    std::vector<size_t> base_primes;
    basic_sieve1(base_primes, base);
    size_t count = base_primes.size();

    size_t len = base, low = base + 1, high;
    std::vector<char> seg(len);
    while (low <= n)
    {
        high = std::min(low + len, n + 1);
        sieve1(base_primes, seg, low, high);
        count += sum(seg, high - low);
        low = high;
    }

    return count;
}

// Segmented sieve: multi-thread
size_t segment_sieve1_mt(size_t n, size_t base, int thr)
{
    // Generate the base primes
    std::vector<size_t> base_primes;
    basic_sieve1(base_primes, base);
    size_t count = base_primes.size();

    // Define the parallelism
    auto segment = [] (std::vector<size_t> &primes, size_t low, size_t len, size_t step, size_t n, size_t &count)
    {
        count = 0;
        std::vector<char> seg(len);
        while (low <= n)
        {
            size_t high = std::min(low + len, n + 1);
            sieve1(primes, seg, low, high);
            count += sum(seg, high - low);
            low += step;
        }
        return count;
    };
    std::vector<size_t> cnt(thr, 0);
    std::vector<std::thread> threads;
    for (int i = 1; i <= thr; i++)
        threads.emplace_back(segment, std::ref(base_primes), base * i + 1, base, thr * base, n, std::ref(cnt[i-1]));

    // Execute
    for (int i = 0; i < thr; i++)
        threads[i].join();

    for (int i = 0; i < thr; i++)
        count += cnt[i];

    return count;
}



//-----------------------------------------
// Eliminate even numbers from the beginning

// Eratosthenes
void basic_sieve2(std::vector<size_t> &primes, size_t limit)
{
    size_t s = (limit - 1) / 2;
    std::vector<char> check(s + 1, 1);
    size_t i, j;
    for (i = 1; 2 * i * (i + 1) <= s; i++)
    {
        if (check[i] == 1)
        {
            for (j = 2 * i * (i + 1); j <= s; j += 2 * i + 1)
                check[j] = 0;
        }
    }
    for (i = 1; i <= s; i++)
    {
        if (check[i] == 1)
            primes.push_back(2 * i + 1);
    }
}

// Sieving
void sieve2(const std::vector<size_t> &primes, std::vector<char> &seg, size_t low, size_t high)
{
    size_t len = (high - low) / 2;
    std::fill(seg.begin(), seg.begin() + len, 1);
    for (size_t p: primes)
    {
        size_t s = (p - low % p) % p;
        if (s % 2 == 1)
            s += p;
        for (size_t i = s / 2; i < len; i += p)
        {
            seg[i] = 0;
        }
    }
}

// Segmented sieve: single thread
size_t segment_sieve2(size_t n, size_t base)
{
    std::vector<size_t> base_primes;
    basic_sieve2(base_primes, base);
    size_t count = base_primes.size();

    size_t len = base / 2, low = base + 1, high;
    std::vector<char> seg(len);
    while (low <= n)
    {
        high = std::min(low + base, n + 1);
        sieve2(base_primes, seg, low, high);
        count += sum(seg, high - low);
        low = high;
    }

    return count;
}

// Segmented sieve: multi-thread
size_t segment_sieve2_mt(size_t n, size_t base, int thr)
{
    // Generate the base primes
    std::vector<size_t> base_primes;
    basic_sieve2(base_primes, base);
    size_t count = base_primes.size();

    // Define the parallelism
    auto segment = [] (std::vector<size_t> &primes, size_t low, size_t len, size_t step, size_t n, size_t &count)
    {
        count = 0;
        std::vector<char> seg(len);
        while (low <= n)
        {
            size_t high = std::min(low + len, n + 1);
            sieve1(primes, seg, low, high);
            count += sum(seg, high - low);
            low += step;
        }
        return count;
    };
    std::vector<size_t> cnt(thr, 0);
    std::vector<std::thread> threads;
    for (int i = 1; i <= thr; i++)
        threads.emplace_back(segment, std::ref(base_primes), base * i + 1, base, thr * base, n, std::ref(cnt[i-1]));

    // Execute
    for (int i = 0; i < thr; i++)
        threads[i].join();

    for (int i = 0; i < thr; i++)
        count += cnt[i];

    return count;
}


//-----------------------------------
// Benchmark
template<typename T, typename... Args>
void measure(std::ofstream &fout, std::string label, T (*func)(Args...), Args... args)
{
    auto start = std::chrono::steady_clock::now();
    T val = func(args...);
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> t = end - start;
    fout << label << ":  " << val << " (in " << t.count() << " seconds)\n";
    std::cout << label << "\n";
}
int main()
{
    std::ofstream fout("result.txt");
    size_t N[] = {1'000'000'000, 2'000'000'000, 3'000'000'000, 4'000'000'000,\
        6'000'000'000, 8'000'000'000, 10'000'000'000, 12'000'000'000, 16'000'000'000,\
        20'000'000'000, 24'000'000'000};
    size_t base = 200'000;
    int threads = std::thread::hardware_concurrency();

    for (size_t n: N)
    {
        std::cout << "n = " << n << std::endl;
        fout << "n = " << n << std::endl;

        std::string label = "Segmented sieve";
        measure<size_t, size_t, size_t>(fout, label, segment_sieve1, n, base);
        label = "Parallel segmented sieve (all physical cores)";
        measure<size_t, size_t, size_t, int>(fout, label, segment_sieve1_mt, n, base, 12);
        label = "Parallel segmented sieve (hyperthreading)";
        measure<size_t, size_t, size_t, int>(fout, label, segment_sieve1_mt, n, base, 24);
        label = "Odd segmented sieve";
        measure<size_t, size_t, size_t>(fout, label, segment_sieve2, n, base);
        label = "Parallel odd segmented sieve (all physical cores)";
        measure<size_t, size_t, size_t, int>(fout, label, segment_sieve2_mt, n, base, 12);
        label = "Parallel odd segmented sieve (hyperthreading)";
        measure<size_t, size_t, size_t, int>(fout, label, segment_sieve2_mt, n, base, 24);

        std::cout << std::endl;
        fout << std::endl;
    }
/*
    size_t n = 300'000'000;
    std::vector<size_t> primes1, primes2;

    auto start = std::chrono::steady_clock::now();
    basic_sieve1(primes1, n);
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> t = end - start;
    std::cout << primes1.size() << " " << t.count() << "\n";

    start = std::chrono::steady_clock::now();
    basic_sieve2(primes2, n);
    end = std::chrono::steady_clock::now();
    t = end - start;
    std::cout << primes2.size() << " " << t.count() << "\n";
*/


    fout.close();
    return 0;
}
