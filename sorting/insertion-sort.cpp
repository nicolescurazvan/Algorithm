#include <cstdio>
#include <vector>
#include <cstdlib>
#include "../include/measure.hpp"
#include "../include/utils.hpp"

void insertion_sort(std::vector<int> &v)
{
    /*
        int works just fine, but size_t is the standard and supports unsigned values
        up to 2^64 - 1, included, on 64-bit systems and modern compliers (C++11 or newer)
    */
    size_t n = v.size();
    for (size_t i = 1; i < n; i++)
    {
        size_t j = i;
        while (j > 0 && v[j - 1] > v[j])
        {
            swap(v[j - 1], v[j]);
            j--;
        }
    }
}

std::vector<int> generate(size_t n)
{
    std::vector<int> gen(n);
    srand(time(0));
    for (size_t i = 0; i < n; i++)
    {
        gen[i] = rand();
    }
    return gen;
}

int main()
{
    size_t N[] = {100, 1000, 5000, 10000, 20000, 40000, 60000, 80000};
    printf("Insertion sort \n-------------------------------------\n");
    for (size_t n: N)
    {
        std::vector<int> v = generate(n);
        double t = measure(insertion_sort, v);
        printf("n = %zu: \t %lf ms\n", n, t * 1000);
    }
    printf("\n\n");
    return 0;
}