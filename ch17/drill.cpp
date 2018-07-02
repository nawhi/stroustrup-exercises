#include <iostream>
#include <cstdio>
#include <iterator>
#include <vector>
#include <numeric>
#include <functional>
#include <cmath>
#include <algorithm>

using std::begin;
using std::end;

void ints()
{
    int* a = new int[10];
    for (int i=0; i<10; ++i)
        std::cout << a[i] << std::endl;
    
    delete[] a;

}


void print_array10(std::ostream& os, int* a)
{
    for (int i=0; i<10; ++i)
        os << *(a+i) << std::endl;
}

void print_array(std::ostream& os, int* a, int n)
{
    for (int i=0; i<n; ++i)
        os << *(a+i) << std::endl;  
}

void arrays()
{
    int a[] = {100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110};
    print_array10(std::cout, a);
    
    int* b = new int[10];
    print_array10(std::cout, b);

    int* c = new int[11];
    for (int i = 100; i < 112; ++i)
        c[i-100] = i;
    print_array(std::cout, c, 11);
}

void vectors(int size)
{
    std::vector<int> v(size);
    std::iota(begin(v), end(v), 100);
    
    for (auto& i: v)
        std::cout << i << std::endl;
    std::cout << std::endl;
}

void ptrs()
{
    int n = 7;
    int* p1 = &n;
    std::cout << p1 << "  " << *p1 << std::endl;
    int* p2 = new int[7];
    for (int i=0; i<7; ++i)
        p2[i] = pow(2, i);

    int* p3 = p2;
    p1 = p2;
    p3 = p2;
    std::cout << p3 << "  " << *p3 << std::endl;
    std::cout << p3 << "  " << *p3 << std::endl;

    delete[] p2;
}

void print_array(std::ostream& os, int* a, int size, std::string name)
{
    os << name << "=[";
    for (int i=0; i<size; ++i)
        os << *a << ((i==size-1) ? "" : ", ");
    os << "]" << std::endl;
}

void copy_arrays()
{
    int* p1 = new int[7];
    for (int i=0; i<7; ++i)
        *p1++ = pow(2, i);
    
    int* p2 = new int[7];
    std::copy(p1, p1+7, p2);

    print_array(std::cout, p1, 7, "p1");
    print_array(std::cout, p2, 7, "p2");

}


template<typename T>
void print_vec(std::ostream& os, std::vector<T> v, std::string name)
{
    os << name << "=[";
    std::for_each(begin(v), end(v), 
        [&os, &v] (const T& i) { os << i << (i==v.back() ? "" : ", "); });
    os << "]" << std::endl;
}

void copy_vectors()
{
    std::vector<int> v1(10);
    std::generate(begin(v1), end(v1), [n = 0]() mutable { return pow(2, n++); });

    std::vector<int> v2(10);
    std::copy(begin(v1), end(v1), begin(v2));

    print_vec<int>(std::cout, v1, "v1");
    print_vec<int>(std::cout, v2, "v2");

}

int main()
{
    // vectors(10);
    // vectors(11);
    // vectors(20);
    // copy_arrays();
    copy_vectors();
    copy_arrays();
    return 0;
}