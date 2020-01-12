#include "logging_allocator.h"
#include "math_functions.h"
#include "mylist.h"

#include <iostream>
#include <map>

struct hard
{
    int fi;
    int fa;

    hard() {}

    hard(int fi, int fa)
        : fi(fi), fa(fa) {}

    //hard(const hard&) = delete;

    //hard(hard&&) noexcept = delete;

    ~hard() {}
};

std::ostream& operator<< (std::ostream& out, const hard &hard_) {
    out << hard_.fi << ' ' << hard_.fa << std::endl;
    return out;
}

int main()
{
    auto m_Map = std::map<int, hard>{};

    for(int i = 0; i < 10; ++i) {
        int fi = fibonacciGen(i, 10);
        int fa = factorialGen(i);
        m_Map.try_emplace(i, fi, fa);
    }

    for(const auto& elem : m_Map) {
        std::cout << elem.second.fi << " "
                  << elem.second.fa
                  << std::endl;
    }

    auto m_customAllocMap = std::map<int, hard, std::less<int>, logging_allocator<std::pair<const int, hard>, 10>>{};

    for(int i = 0; i < 10; ++i) {
        int fi = fibonacciGen(i, 10);
        int fa = factorialGen(i);
        m_customAllocMap.try_emplace(i, fi, fa);
    }

    for(const auto& elem : m_customAllocMap) {
        std::cout << elem.second.fi << " "
                  << elem.second.fa
                  << std::endl;
    }

    myList<hard> listDefault;

    for(int i = 0; i < 10; ++i) {
        int fi = fibonacciGen(i, 10);
        int fa = factorialGen(i);
        //listDefault.push_back(hard(fi, fa));
        listDefault.emplaceBack(fi, fa);
    }

    myList<hard>::iterator it;

    for (it=listDefault.cbegin(); it!=listDefault.cend(); ++it) {
        std::cout << *it;
    }
    std::cout << std::endl;

    auto m_customAllocList = myList<hard, logging_allocator<hard, 10>>{};

    for(int i = 0; i < 10; ++i) {
        int fi = fibonacciGen(i, 10);
        int fa = factorialGen(i);
        //m_customAllocList.push_back(hard(fi, fa));
        m_customAllocList.emplaceBack(fi, fa);
    }

    myList<hard, logging_allocator<hard, 10>>::iterator it2;

    for (it2=m_customAllocList.cbegin(); it2!=m_customAllocList.cend(); ++it2) {
        std::cout << *it2;
    }
    std::cout << std::endl;

    // Test for copy ctor with same allocator types
    std::cout << "Test for copy ctor with same allocator types: " << std::endl;
    auto anotherList = m_customAllocList;

    // Test for copy ctor with different allocator types
    std::cout << "Test for copy ctor with different allocator types: " << std::endl;
    myList<hard, logging_allocator<hard, 10>> anotherList2 = listDefault;

    // Test for move ctor with same allocator types
    std::cout << "Test for move ctor with same allocator types: " << std::endl;
    auto anotherList3 = std::move(m_customAllocList);

    // Test for move ctor with different allocator types
    std::cout << "Test for move ctor with different allocator types: " << std::endl;
    myList<hard, logging_allocator<hard, 10>> { std::move(listDefault) };

    return 0;
}

