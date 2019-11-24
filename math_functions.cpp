#include "math_functions.h"
#include <vector>
#include <numeric>

int fibonacciGen(size_t idx, size_t size)
{
    std::vector<int> m_vect;
    m_vect.reserve(size);

    for(size_t i = 0; i < size; ++i) {
        m_vect.push_back(1);
    }

    std::adjacent_difference(m_vect.begin(), m_vect.end() - 1, m_vect.begin() + 1, std::plus<int>());

    return m_vect.at(idx);
}

int factorialGen(int idx)
{
    return (idx == 1 || idx == 0) ? 1 : factorialGen(idx - 1) * idx;
}

