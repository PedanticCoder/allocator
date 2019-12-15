#ifndef MYLIST_H
#define MYLIST_H

#include <iostream>

template<typename T>
struct Node
{
    Node *next;
    T data;
    template<typename ...Args>
    Node(Args &&...args) : next(nullptr), data(std::forward<Args>(args)...) {}
};

template<typename T>
struct iterator
{
    using value_type = T;
    using pointer = const T*;
    using reference = const T&;
    using iterator_category = std::forward_iterator_tag;
    using self = iterator<T>;

    Node<T>* the_node;

    iterator()
        :the_node(nullptr) {}

    iterator(Node<T> *the_node_)
        :the_node(the_node_) {}

    reference operator*() const
    {
        return the_node->data;
    }

    pointer operator->() const {
        return &(the_node->data);
    }

    self& operator++()
    {
        if(the_node==nullptr) {
            return *this;
        }
        else {
            the_node = the_node->next;
        }
        return *this;
    }

    bool operator==(const iterator& it) const
    {
        return (the_node==it.the_node);
    }

    bool operator!=(const iterator& it) const
    {
        return !(it==*this);
    }
};

template<typename T, typename Allocator_ = std::allocator<T>>
class myList
{
public:

    myList()
        :head(nullptr), alloc() {
        std::cout << "myList ctor" << std::endl;
    }

    // copy ctor with same allocator types
    myList(const myList& other)
        :head(nullptr), alloc()
    {
        std::cout << "myList copy ctor with same alloc types" << std::endl;
        copyListHelper(other);
    }

    // copy ctor with different allocator types
    template<typename otherAlloc>
    myList(const myList<T, otherAlloc>& other)
        :head(nullptr), alloc()
    {
        std::cout << "myList copy ctor with different alloc types" << std::endl;
        copyListHelper(other);
    }

    template<typename otherAlloc>
    void copyListHelper(const myList<T, otherAlloc>& other)
    {
        Node<T>* currentNode =  other.cbegin().the_node;
        while (currentNode != nullptr)
        {
          this->push_back(currentNode->data);
          currentNode = currentNode->next;
        }
    }

    // move ctor with same allocator types
    myList(myList&& other)
        :head(other.head), alloc(other.alloc) {
        std::cout << "myList move ctor with same alloc types" << std::endl;
        other.head = nullptr;
    }

    // move ctor with different allocator types
    template<typename otherAlloc>
    myList(myList<T, otherAlloc>&& other)
        :head(nullptr), alloc() {
        std::cout << "myList move ctor with different alloc types" << std::endl;
        if(other.cbegin().the_node != nullptr)
        {
            this->head = alloc.allocate(1);
            alloc.construct(head, std::move(*other.cbegin().the_node));
            auto pDst = head;
            auto pOther = other.cbegin().the_node;
            while(pOther->next != nullptr)
            {
                pDst->next = alloc.allocate(1);
                pDst = pDst->next;
                pOther = pOther->next;
                alloc.construct(pDst, std::move(*pOther));
            }
        }
    }

    ~myList()
    {
        std::cout << "myList dtor" << std::endl;
        auto current = head;
        while (current != nullptr) {
            auto pRemove = current;
            current = current->next;
            alloc.destroy(pRemove);
            alloc.deallocate(pRemove, 1);
        }
    }



    template<typename... Args>
    void push_back(Args&&...args)
    {
        Node<T>* new_node = alloc.allocate(1);
        alloc.construct(new_node, std::forward<Args>(args)...);

        if(head==nullptr)
        {
            head = new_node;
        }
        else
        {
            Node<T>* current = this->head;

            while (current->next!=nullptr)
            {
                current = current->next;
            }
            current->next = new_node;
        }
    }

    template<typename... Args>
    void emplaceBack(Args&&...args)
    {
        Node<T> *new_node = alloc.allocate(1);
        alloc.construct(&new_node->data, std::forward<Args>(args)...);

        if(head==nullptr)
        {
            head = new_node;
        }
        else
        {
            Node<T>* current = this->head;

            while (current->next!=nullptr)
            {
                current = current->next;
            }
            current->next = new_node;
        }
    }

    void pop_front()
    {
        Node<T> *temp = head;
        head = head->next;
        delete temp;
    }

    T& operator[](const size_t index)
    {
        size_t counter = 0;
        Node<T> *current = this->head;
        while(current!=nullptr)
        {
            if(counter==index)
            {
                return current->data;
            }
            current = current->next;
            counter++;
        }
        throw "invalid pointer";
    }

    iterator<T> cbegin() const noexcept {
        return iterator<T>(head);
    }

    iterator<T> cend() noexcept {
        return iterator<T>();
    }
private:
    Node<T> *head = nullptr;
    using Allocator = typename Allocator_::template rebind<Node<T>>::other;
    Allocator alloc;
};

#endif // MYLIST_H

