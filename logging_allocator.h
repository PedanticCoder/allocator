#ifndef LOGGING_ALLOCATOR_H
#define LOGGING_ALLOCATOR_H

#include<iostream>

template<typename T, size_t N>
struct logging_allocator {

    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;

    template<typename U>
    struct rebind {
        using other = logging_allocator<U, N>;
    };

    logging_allocator() = default;

    ~logging_allocator() {}

    T *allocate(std::size_t n) const {
            std::cout << __PRETTY_FUNCTION__ << "[n = " << n << "]" << std::endl;
            if(bufCounter + n > N)
                throw std::bad_alloc();
            if(!bufPtr)
                bufPtr = reinterpret_cast<pointer>(malloc(N * sizeof(T)));
            if(!bufPtr)
                throw std::bad_alloc();
            pointer ptr = bufPtr + bufCounter;
            bufCounter+=n;
            return ptr;
    }

    void deallocate(T *p, std::size_t n) const {
            std::cout << __PRETTY_FUNCTION__ << "[n = " << n << "]" << std::endl;
            if(!p) return;
            bufCounter-=n;
            if(bufCounter!=0) return;
            std::free(bufPtr);
            bufPtr = nullptr;
    }

    template<typename U, typename ...Args>
    void construct(U *p, Args &&...args) const {
            std::cout << __PRETTY_FUNCTION__ << std::endl;
            new(p) U(std::forward<Args>(args)...);
    }

    void destroy(T *p) const {
            std::cout << __PRETTY_FUNCTION__ << std::endl;
            p->~T();
    }

private:
    mutable size_t bufCounter = 0;
    mutable pointer bufPtr = nullptr;
};


#endif // LOGGING_ALLOCATOR_H

