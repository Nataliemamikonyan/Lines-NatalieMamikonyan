#ifndef MY_QUEUE_H
#define MY_QUEUE_H
#include <iostream>
#include <iomanip>
#include <cassert>
#include <string>
#include <cmath>

using namespace std;

#include "node.h"
#include "linkedlistfunctionsTemplated.h"

template <typename T>
class Queue
{
public:
    class Iterator{
    public:
        friend class Queue;                               //give access to list to access _ptr

        Iterator(){_ptr = NULL;}                    //default ctor
        Iterator(node<T>* p):_ptr(p){                   //Point Iterator to where p is pointing to
        }

        T& operator *()                        //dereference operator
        {
            assert(_ptr);
            return _ptr->_item;
        }
        T* operator ->()                       //member access operator
        {
            assert(_ptr);
            return &_ptr->_item;
        } 

        bool is_null()                                 //true if _ptr is NULL
        {
            return (!_ptr);
        }

        friend bool operator !=(const Iterator& left, const Iterator& right) //true if left != right
        {
            return left._ptr != right._ptr;
        }

        friend bool operator ==(const Iterator& left, const Iterator& right) //true if left == right
        {
            return left._ptr == right._ptr;
    
        }

        Iterator& operator++()                         //member operator: ++it; or ++it = new_value
        {
            assert(_ptr);
            _ptr = _ptr->_next;
            return *this;
        }

        friend Iterator operator++(Iterator& it, int unused)         //friend operator: it++
        {
            assert(it._ptr);
            Iterator temp = it;
            it._ptr = it._ptr->_next;
            return temp;
        }

    private:
        node<T>* _ptr;                          //pointer being encapsulated
    };

    Queue();

    Queue(const Queue<T>& copyMe);
    ~Queue();
    Queue& operator=(const Queue<T>& RHS);

    bool empty() { return _front == nullptr; }
    T front();
    T back();

    void push(T item);
    T pop();

    Iterator begin() const;            //Iterator to the head node
    Iterator end() const;              //Iterator to NULL
    void print_pointers();
    int size() const { return _size; }
    template<typename TT>
    friend ostream& operator << (ostream& outs, const Queue<TT>& printMe);
private:
    node<T>* _front;
    node<T>* _rear;
    int _size;
};

template <typename T>
Queue<T>::Queue(): _front(nullptr), _rear(nullptr), _size(0){}

template <typename T>
Queue<T>::Queue(const Queue<T>& copyMe)
{
    _size = copyMe._size;
    _front = nullptr;
    _rear = _copy_list<T>(_front, copyMe._front);
}

template <typename T>
Queue<T>::~Queue()
{
     _clear_list<T>(_front);
    _front = nullptr;
    _rear = nullptr;
    _size = 0;
}

template <typename T>
Queue<T>& Queue<T>::operator=(const Queue<T>& RHS)
{
    if (&RHS == this)
    {
        return *this;
    }
    _clear_list<T>(_front);
    _size = RHS._size;
    _front = nullptr;
    _rear = _copy_list<T>(_front, RHS._front);

    return *this;
}

template <typename T>
T Queue<T>::front()
{
    return _front->_item;
}

template <typename T>
T Queue<T>::back()
{
    return _rear->_item;
}

template <typename T>
void Queue<T>::push(T item)
{
    _rear = _insert_after<T>(_front, _rear, item);
    _size++;
}

template <typename T>
T Queue<T>::pop()
{
    assert(_front && "tried to pop from an empty queue");
    _size --;
    T item = _delete_head<T>(_front);
    if(_size == 1)
    {        
        _rear = _front;
    } 
    else if(_size == 0)
    {
        _rear = nullptr;
        _front = nullptr;
    }
    return item;
}

template <class T>
typename Queue<T>::Iterator Queue<T>::begin() const
{
    return Iterator(_front);
}

template <class T>
typename Queue<T>::Iterator Queue<T>::end() const
{
    node<T>* end_of_list = nullptr;
    return Iterator(end_of_list);
} 

template <class T>
void Queue<T>::print_pointers()
{
    _print_list<T>(_front);
}

template<typename TT>
ostream& operator << (ostream& outs, const Queue<TT>& printMe)
{
    outs << "Queue:Head->";
    _print_list<TT>(printMe._front);
    outs<<"   ["<<printMe._size<<"]";
    return outs;
}

#endif