#include <cstdio>
#include <vector>
#include <cstdlib>
#include <thread>
#include "../include/measure.hpp"
#include "../include/utils.hpp"

// Insertion sort - helps making it faster for low sizes
void insertion_sort(std::vector<int> &v)
{
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

// Function to merge two sorted vectors
void merge(std::vector<int> &v, std::vector<int> &v1, std::vector<int> &v2)
{
    std::vector<int>::iterator i1 = v1.begin(), i2 = v2.begin(), j = v.begin();
    while (i1 != v1.end() && i2 != v2.end())
    {
        if (*i1 <= *i2)
        {
            *j = *i1;
            i1++;
            j++;
        }
        if (*i2 <= *i1)
        {
            *j = *i2;
            i2++;
            j++;
        }
    }
    while (i1 != v1.end())
    {
        *j = *i1;
        i1++;
        j++;
    }
    while (i2 != v2.end())
    {
        *j = *i2;
        i2++;
        j++; 
    }
}

// Function for normal merge sort
void merge_sort(std::vector<int> &v)
{
    size_t n = v.size();
    if (n < 2)
        return;
    
    size_t m = n / 2;
    std::vector<int> v1(v.begin(), v.begin() + m);
    std::vector<int> v2(v.begin() + m, v.end());
    merge_sort(v1);
    merge_sort(v2);
    merge(v, v1, v2);
}

// Improved merge sort -> insertion sort for small vectors.
void merge_sort_improved(std::vector<int> &v)
{
    size_t n = v.size();
    if (n < 2)
        return;
    if (n < 32)
        insertion_sort(v);
    
    size_t m = n / 2;
    std::vector<int> v1(v.begin(), v.begin() + m);
    std::vector<int> v2(v.begin() + m, v.end());
    merge_sort_improved(v1);
    merge_sort_improved(v2);
    merge(v, v1, v2);
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
    size_t N[] = {10'000'000, 20'000'000, 50'000'000, 100'000'000, 150'000'000,\
         200'000'000, 300'000'000, 400'000'000, 500'000'000};
    /*printf("Merge sort \n-------------------------------------\n");
    for (size_t n: N)
    {
        std::vector<int> v = generate(n);
        double t = measure(merge_sort, v);
        printf("n = %zu: \t %lf ms\n", n, t * 1000);
    }*/
    printf("Merge sort (improved)\n-------------------------------------\n");
    for (size_t n: N)
    {
        std::vector<int> v = generate(n);
        double t = measure(merge_sort_improved, v);
        printf("n = %zu: \t %lf ms\n", n, t * 1000);
    }
    printf("\n\n");
    return 0;
}