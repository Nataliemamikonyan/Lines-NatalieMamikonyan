#ifndef LINKED_LIST_FUNCTIONS_H
#define LINKED_LIST_FUNCTIONS_H
#include <iostream>
#include <iomanip>
#include <cassert>
#include <string>
#include <cmath>

using namespace std;

#include "node.h"

//Linked List General Functions:
template <typename T>
void _print_list(node<T>* head);  // done

//recursive fun! :)
template <typename T>
void _print_list_backwards(node<T> *head);

//return ptr to key or NULL
template <typename T>
node<T>* _search_list(node<T>* head, T key);  // done

template <typename T>
node<T>* _insert_head(node<T> *&head, T insert_this);  // done

//insert after ptr: insert head if marker null
template <typename T>
node<T>* _insert_after(node<T>*& head, node<T> *after_this, T insert_this);  // done

//insert before ptr: insert head if marker null
template <typename T>
node<T>* _insert_before(node<T>*& head, node<T>* before_this, T insert_this);  // done

//ptr to previous node
template <typename T>
node<T>* _previous_node(node<T>* prev_to_this);  // done

template <typename T>
T _delete_head(node<T>*&head);  // done

//delete, return item
template <typename T>
T _delete_node(node<T>*& head, node<T>* delete_this);  // done

//duplicate the list...
template <typename T>
node<T>* _copy_list(node<T>* head);  // done

//duplicate the list, return pointer to last node in dest... 
//     use this function in your queue big three 
template <typename T>
node<T> *_copy_list(node<T> *&dest, node<T> *src);  // done

//delete all the nodes
template <typename T>
void _clear_list(node<T>*& head);  // done

//_item at this position
template <typename T>
T& _at(node<T>* head, int pos);  // done

//--------------------------------------------------------------------------------

template <typename T>
void _print_list(node<T>* head)
{
    // cout << "Head->";
    node<T>* walker = head;
    while (walker)
    {
        cout << " <-" << (walker->_item).x << ", " << (walker->_item).y << "->";
        walker = walker->_next;
    }
    cout << "|||" << endl;
}

template <typename T>
node<T>* _search_list(node<T>* head, T key)
{
    node<T>* walker = head;
    // loop through the list and compare each item with the key
    while(walker)
    {
        if(walker->_item == key)
        {
            // return the node that contains the desiered item
            return walker;
        }
        walker = walker->_next;
    }
    // item was not found
    return nullptr;
}

template <typename T>
node<T>* _insert_head(node<T> *&head, T insert_this)
{
    node<T> * newNode = new node<T>(insert_this);
    newNode->_next = head;
    // checking for other nodes in the list before assigning _prev
    if (head)
    {
        head->_prev = newNode;
    }
    head = newNode;
    return head;
}

template <typename T>
node<T>* _insert_after(node<T>*& head, node<T> *after_this, T insert_this)
{
    // insert head if marker or head is null
    if (!head || !after_this)
    {
        head = _insert_head(head, insert_this);
        return head;
    }
    else
    {
        node<T> * newNode = new node<T>(insert_this);
        newNode->_next = after_this->_next;
        // checking to see if there is any nodes after the inserted node to avoid referencing null
        if(after_this->_next)
        {
            (after_this->_next)->_prev = newNode;
        }
        after_this->_next = newNode;
        newNode->_prev = after_this;
        return newNode;
    }
}

template <typename T>
node<T>* _insert_before(node<T>*& head, node<T>* before_this, T insert_this)
{
    if(!head)
    {
        head = _insert_head(head, insert_this);
        return head;
    }
    else
    {
        // instert after the previous node of the marker
        return _insert_after(head, before_this->_prev, insert_this);
    }
}

template <typename T>
node<T>* _previous_node(node<T>* prev_to_this)
{
    if(prev_to_this || prev_to_this->_prev)
    {
        return prev_to_this->_prev;
    }
    // in the case where the node is the head
    else
    {
        return nullptr;
    }
}

template <typename T>
T _delete_head(node<T>*&head)
{
    assert(head);
    T item = head->_item;
    node<T> *temp = head;
    head = head->_next;  
    delete temp;
    return item;
}

template <typename T>
T _delete_node(node<T>*& head, node<T>* delete_this)
{
    assert(head);
    T item = delete_this->_item;
    // deleting the head if the node we want to delete equals the head
    if(head == delete_this)
    {
        _delete_head<T>(head);
        return item;
    }
    else
    {
        node<T>* temp = delete_this;
        (temp->_prev)->_next =  temp->_next;
        //  checking to make sure node isn't the last in the list
        if(temp->_next)
        {
            (temp->_next)->_prev = temp->_prev;
        }
        delete temp;
        return item;
    }
}

template <typename T>
node<T>* _copy_list(node<T>* head)
{
    // simply calls the other copy list function
    node<T>* dest = nullptr;
    _copy_list<T>(dest, head);
    return dest;
}

template <typename T>
node<T> *_copy_list(node<T>* &dest, node<T> *src)
{
    // initilize two walkers for the resprective lists
    node<T>* walker = src;
    node<T>* new_walker = dest; 
    //  initlizes the new list with all the nodes from the src list
    while(walker)
    {
       new_walker = _insert_after(dest, new_walker, walker->_item);
       walker = walker->_next;
    }
    // returns the last node of the new list
    return new_walker;
}

template <typename T>
T& _at(node<T>* head, int pos)
{
    node<T>* walker = head;

    // iterates until the node in the wanted position is found
    for(int i = 1; i < pos; i++)
    {
        assert(walker && "_at(): index out of bounds.. ");
        walker = walker->_next;
    }
    // return the item in the node
    return walker->_item;
}

template <typename T>
void _clear_list(node<T>*& head)
{
    // continues to call _delete_head() while there are still nodes in the list
    while(head)
    {
       _delete_head<T>(head);
    }
}

#endif