#ifndef lista_h
#define lista_h

#include <iostream>
#include <climits>

template<typename type>
class Node{
public:
    type data;
    Node<type>* next;
    Node<type>(type value) : data(value), next(nullptr) {}
};

template<typename type>
class lista{
    Node<type>* head;
    size_t size;
    bool order;
public:
    lista();
    
    lista(const size_t &n);
    
    lista(const size_t &n, type *values);
    
    lista(const lista<type> &other);
    
    ~lista();
    
    void resize(const size_t new_size);
    
    void insert(const type &value);
    
    void assign(const size_t &n, type *data);
    
    void remove_value(const type value);
    
    void remove_all_value(const type value);
    
    void remove(const size_t index);
    
    bool empty();
    
    bool full();
    
    size_t find(const type value);
    
    size_t binary_search(const type &value);
    
    bool contain(const type &value);
    
    void replace(type old_value, type new_value);
    
    type get(const size_t index);
    
    void print();
    
    type back();
    
    type front();
    
    void pop_back();
    
    void pop_front();
    
    Node<type>* begin();
    
    Node<type>* end();
    
    size_t getSize();
    
    bool getOrder();
    
    void merge(lista<type> &other);
    
    void unique();
    
    void clear();
    
    void reverse();
    
    unsigned int count(const type &value);
    
    lista<type> getSubList(const size_t start_index, const size_t end_index);
    
    bool operator== (const lista<type> &other);
    
    bool operator!= (const lista<type> &other);
    
    type operator[](const size_t index);
};
#include "lista.tpp"

#endif
