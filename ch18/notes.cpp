#include <initializer_list>
#include <algorithm>
#include <cstdio>
#include <string>

void sizes(char ch, int i, int* p)
{
    printf("size of char is %ld %ld\n", sizeof(char), sizeof(ch));
    printf("size of int is %ld %ld\n", sizeof(int), sizeof(i));
    printf("size of int* (%p) is %ld %ld\n", (void*)p, sizeof(int*), sizeof(p));
}

void memory()
{

    char c = 'f';
    auto* p = &c;

    // Pointer doesn't know how many elements it points to
    for (int i = 0; i< 20; ++i)
        printf("%c\n", *(p+i));

    // So this will compile and run ...
    *(p+0xFF) = 'd';
    printf("%c\n", *(p+0xFF));

    // .. and then mysteriously crash later on or do something odd
    
    double* p0; // pointer to undefined location
    *p0 = 3.5;  // write to undefined location
                // - probably a segfault

    /*
     * Compilers often have a 'debug mode' where they initialise
     * everything to a predictable value. 
     * So code like this will run in debug builds but crash
     * in opt
     */
    bool handled;
    if (handled) {
        // ...
    }

    double d = 3.5; // allocate 1 double on the heap
    delete &d; // frees the memory - delete expects a pointer
    
    double* dp = new double[4]; // allocate 4 doubles on the heap
    delete[] dp; // frees memory for all 4 doubles

    int* np = nullptr;
    delete np; // fine - nothing to do
    delete np; // multiple deletes fine too

    void* pp = nullptr;
    delete pp; // compiler warning: deleting void* is undefined

    
    // a void* points to memory without knowing what 
    // resides in that memory
    // Can't instantiate an object of type void

}

/*
 * Linked list stuff
 */
struct Link {
    std::string value;
    Link* prev;
    Link* next;
    Link(const std::string& v, Link* p = nullptr, Link* n = nullptr)
        : value{v}, prev{p}, next{n} {}
};

Link* insert(Link* p, Link* n)
{
    if (!n)
        return p;
    if (!p)
        return n;
    n–>succ = p;
    if (p->prev)
        p–>prev–>succ = n;
    n–>prev = p–>prev;
    p–>prev = n;
    return n;
}

/*
 * Get around pointers being dumb / low level by using higher-level
 * collections classes like std::vector
 * A vector knows its size and can prevent out-of-range access
 */

class vector {
    size_t sz;
    double* elem;
public:
    vector(size_t s): sz{s}, elem{new double[s]} 
    {
        for (size_t i = 0; i<sz; ++i)
            elem[i] = 0.0;
    }

    vector(std::initializer_list<double> lst /* NB: pass by VALUE */)
        :sz{lst.size()}, elem{new double[sz]}
    {
        std::copy(lst.begin(), lst.end(), elem);
    }

    ~vector()
    {
        delete[] elem;
    }

    int size() const { return sz; }

    double get(int n) const { return elem[n]; }
    double set(int n, double v) { elem[n] = v; }
};

int main()
{
    memory();
    char c = '\0';
    int i = 305698;
    sizes(c, i, &i);


    // vector v1 {3};   // [3.0]
    // vector v2 = {3}; // [3.0]
    // vector v3(3);     // [0.0, 0.0, 0.0]

    vector v4(3);
    // v4.set(2, 2.2);
}