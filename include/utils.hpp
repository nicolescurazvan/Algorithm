template <typename T>
void swap(T &a, T &b)
{
    T x = a;
    a = b;
    b = x;
}