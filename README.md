# Algorithm

A catalog for various computer science and mathematical algorithms, implemented in C++. 
It's my first attempt to create such a place. Also, there is a script that compiles and 
benchmarks each algorithm from a category, writes the results in a text file and then 
the executables are removed. It's a small educational tool which also serves as a draft 
for my future mini-projects and projects.

Everything is compiled using the GCC (g++ since it's C++) and the `-O3` optimization flag
(the strongest optimization currently available, for maximum performance gains). 

---

### Categories:
* Dedekind function counting (boolean functions where changing an argument from 0 to 1 
    can't change the result from 1 to 0)
* Graph routing (shortest route in a graph)
* Integer factorization
* Matrix multiplication
* Pattern search
* Prime number sieve (segmented sieve) - finding prime numbers up to a limit
* Sorting algorithms (stable and unstable)

---

### Preparing the environment (Ubuntu-based Linux distributions and WSL)

`sudo apt install -y build-essential git`
