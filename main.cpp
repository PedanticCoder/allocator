#include "mylist.h"
#include "logging_allocator.h"
#include "math_functions.h"

#include <iostream>
#include <map>

struct hard
{
    int fi;
    int fa;

    hard() {}

    hard(int fi, int fa)
        : fi(fi), fa(fa) {}

//    hard(const hard&) = delete;

//    hard(hard&&) noexcept = delete;

    ~hard() {}
};

int main()
{
    auto m_Map = std::map<int, hard>{};

    for(int i = 0; i < 10; ++i) {
        int fi = fibonacciGen(i, 10);
        int fa = factorialGen(i);
        m_Map.emplace(i, hard(fi, fa));
    }

    for(const auto& elem : m_Map) {
        std::cout << elem.second.fi << " "
                  << elem.second.fa
                  << std::endl;
    }

    auto m_limitedMap = std::map<int, hard, std::less<int>, logging_allocator<std::pair<const int, hard>, 10>::rebind<std::_Rb_tree_node<std::pair<const int, hard>>>::other>{};

    for(int i = 0; i < 10; ++i) {
        int fi = fibonacciGen(i, 10);
        int fa = factorialGen(i);
        m_limitedMap.emplace(i, hard(fi, fa));
    }

    for(const auto& elem : m_limitedMap) {
        std::cout << elem.second.fi << " "
                  << elem.second.fa
                  << std::endl;
    }

    auto m_list = myList<hard>{};

    for(int i = 0; i < 10; ++i) {
        int fi = fibonacciGen(i, 10);
        int fa = factorialGen(i);
        m_list.push_back(hard(fi, fa));
    }

    for(int i = 0; i < 10; ++i) {
        std::cout << m_list[i].fi << " "
                  << m_list[i].fa
                  << std::endl;
    }

    auto m_limitedList = myList<hard, logging_allocator<hard, 10>::rebind<myList<hard>::Node>::other>{};

    for(int i = 0; i < 10; ++i) {
        int fi = fibonacciGen(i, 10);
        int fa = factorialGen(i);
        m_limitedList.push_back(hard(fi, fa));
    }

    for(int i = 0; i < 10; ++i) {
        std::cout << m_list[i].fi << " "
                  << m_list[i].fa
                  << std::endl;
    }

    return 0;
}

