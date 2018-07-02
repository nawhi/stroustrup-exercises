#include <initializer_list>
#include <algorithm>

class vector {
    size_t sz;
    double* elem;
public:
    vector(size_t s): sz{s}, elem{new double[s]} 
    {
        for (size_t i = 0; i<sz; ++i)
            elem[i] = 0.0;
    }

    vector(std::initializer_list<double> lst)
        :sz{lst.size()}, elem{new double[sz]}
    {
        std::copy(lst.begin(), lst.end(), elem);
    }
};

int main()
{
    vector v1 {3};   // [3.0]
    vector v1 = {3}; // [3.0]
    vector v(3);     // [0.0, 0.0, 0.0]
}