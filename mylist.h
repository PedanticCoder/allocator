#ifndef MYLIST_H
#define MYLIST_H

#include <iostream>

template<typename T, typename Allocator=std::allocator<T>>
class myList
{
    Allocator alloc;

public:
    class Node
    {
    public:
        Node *next;
        T data;
        Node(T data = T(), Node *next = nullptr)
        {
            this->data = data;
            this->next = next;
        }
    };
    size_t size;
    Node *head;

public:
    friend class iterator;

    myList()
    {
        size = 0;
        head = nullptr;
    }

    ~myList()
    {
        clear();
    }

    void push_back(T data)
    {
        if(head==nullptr)
        {
            head = new Node(data);
        }
        else
        {
            Node* current = this->head;

            while (current->next!=nullptr)
            {
                current = current->next;
            }
            current->next = new Node(data);
        }
        size++;
    }

    void pop_front()
    {
        Node *temp = head;
        head = head->next;
        delete temp;
        size--;
    }

    void clear()
    {
        while(size)
        {
            pop_front();
        }
    }

    size_t getSize() { return size; }

    T& operator[](const size_t index)
    {
        size_t counter = 0;
        Node *current = this->head;
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

    class iterator
    {
    public:
        iterator()
            :the_node(nullptr) {}

        iterator(Node *the_node_)
            :the_node(the_node_) {}

        iterator(const iterator& it)
            :the_node(it.the_node) {}

        iterator& operator=(const iterator& it)
        {
            the_node = it.the_node;
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

        iterator& operator++()
        {
            if(the_node==nullptr)
                throw "empty iterator";
            else if(the_node->next==nullptr)
                throw "invalid iterator";
            else
                return *this;
        }

        T& operator*() const
        {
            if(the_node==nullptr)
                throw "dereference an empty iterator";
            return the_node->data;
        }

    private:
        myList::Node* the_node;
    };
};




#endif // MYLIST_H

