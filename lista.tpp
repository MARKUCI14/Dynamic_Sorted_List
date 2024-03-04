#include "lista.h"

template<typename type>
lista<type>::lista()
{
    head = nullptr;
    size = 0;
    order = 1;
}

template<typename type>
lista<type>::lista(const size_t &n)
{
    head = nullptr;
    size = 0;
    order = 1;
    resize(n);
}

template<typename type>
lista<type>::lista(const size_t &n, type *values)
{
    head = nullptr;
    order = 1;
    size = n;
    for (size_t i=0;i<n;i++)
    {
        insert(values[i]);
    }
}

template<typename type>
lista<type>::lista(const lista<type> &other)
{
    Node<type>* current = other.head;
    order = other.order;
    size = other.size;
    while (current != nullptr)
    {
        insert(current -> data);
        current = current -> next;
    }
}

template<typename type>
lista<type>::~lista()
{
    while (head != nullptr)
    {
        Node<type>* temp = head;
        head = head -> next;
        delete temp;
    }
}

template<typename type>
void lista<type>::resize(const size_t new_size)
{
    if (new_size < 0)
    {
        std::cout<<"Invalid size!";
        return;
    }
    if (new_size == size) {
            return;
    }
    else if (new_size < size) {
        for (size_t i = 0; i < size - new_size; i++) {
            pop_back();
        }
    }
    else {
        for (size_t i = 0; i < new_size - size + 1; i++) {
            insert(type());
        }
    }
    size = new_size;
}
template<typename type>
void lista<type>::insert(const type &value)
{
    if (full())
    {
        std::cout<<"List is full!"<<'\n';
        return;
    }
    if (order == 1)
    {
        Node<type>* newNode = new Node<type>(value);
        if (head == nullptr)
        {
            head = newNode;
            size++;
            return;
        }
        
        if (value < head->data)
        {
            newNode -> next = head;
            head = newNode;
            size++;
            return;
        }
        
        Node<type>* current = head;
        while (current -> next != nullptr && current -> next -> data < value)
        {
            current = current -> next;
        }
        
        newNode -> next = current -> next;
        current -> next = newNode;
    }
    else{
        Node<type>* newNode = new Node<type>(value);
        if (head == nullptr)
        {
            head = newNode;
            size++;
            return;
        }
        
        if (value > head->data)
        {
            newNode -> next = head;
            head = newNode;
            size++;
            return;
        }
        
        Node<type>* current = head;
        while (current -> next != nullptr && current -> next -> data > value)
        {
            current = current -> next;
        }
        
        newNode -> next = current -> next;
        current -> next = newNode;
    }
}

template<typename type>
void lista<type>::assign(const size_t &n, type *data){
    for (size_t i=0; i < n; i++)
    {
        insert(data[i]);
    }
}

template<typename type>
void lista<type>::remove_value(const type value)
{
    Node<type>* current = head;
    Node<type>* previous = nullptr;
    bool removed = false;
    
    
    while (current != nullptr && removed==false)
    {
        if (current -> data == value)
        {
            if (previous == nullptr)
            {
                head = current -> next;
            }
            else
            {
                previous -> next = current -> next;
            }
            delete current;
            size--;
            return;
        }
        previous = current;
        current = current -> next;
    }
}
template<typename type>
void lista<type>::remove_all_value(const type value){
    Node<type>* current = head;
    Node<type>* previous = nullptr;
    
    while (current != nullptr)
    {
        if (current -> data == value)
        {
            if (previous != nullptr){
                previous -> next = current -> next;
                delete current;
                current = previous->next;
            }
            else{
                head = current -> next;
                delete current;
                current = head;
            }
            size--;
        }
        else{
            previous = current;
            current = current -> next;
        }
        
    }
}

template<typename type>
void lista<type>::remove(const size_t index)
{
    if (index<0 || index>size)
    {
        std::cout<<"Not a valid index!";
        return;
    }
    
    Node<type>* current = head;
    Node<type>* previous = nullptr;
    size_t i = 0;
    
    while (current != nullptr && i<index)
    {
        previous = current;
        current = current -> next;
        i++;
    }
    
    if (previous == nullptr)
    {
        head = current -> next;
    }
    else
    {
        previous -> next = current -> next;
    }
    
    delete current;
    size--;
}

template<typename type>
bool lista<type>::empty(){
    return head == nullptr;
}

template<typename type>
bool lista<type>::full(){
    return size==INT_MAX;
}

template <typename type>
size_t lista<type>::find(const type value){
    size_t index = 0;
    Node<type>* current = head;
    
    while (current != nullptr)
    {
        if (current -> data == value)
        {
            return index;
        }
        current = current -> next;
        index++;
    }
    
    std::cout<<"Not found!"<<'\n';
    return -1;
}

template<typename type>
size_t lista<type>::binary_search(const type &value){
    size_t left = 0;
    size_t right = size - 1;
    while (left <= right)
    {
        size_t mid = (left + right)/2;
        type val = get(mid);
        if (val == value)
        {
            return mid;
        }
        else{
            if (order == 1)
            {
                if (val < value)
                {
                    left = mid+1;
                }
                else{
                    right = mid - 1;
                }
            }
            else
            {
                if (val > value)
                {
                    left = mid+1;
                }
                else{
                    right = mid - 1;
                }
            }
        }
    }
    return -1;
}

template <typename type>
bool lista<type>::contain(const type &value){
    Node<type>* current = head;
    
    while (current != nullptr)
    {
        if (current -> data == value)
        {
            return true;
        }
        current = current -> next;
    }
    return false;
}

template<typename type>
void lista<type>::replace(type old_value, type new_value){
    Node<type>* current = head;
    
    while (current != nullptr)
    {
        if (current -> data == old_value)
        {
            remove(old_value);
        }
        current = current -> next;
    }
    insert(new_value);
}

template<typename type>
type lista<type>::get(const size_t index){
    if (index<0 || index>size)
    {
        std::cout<<"Not a valid index!";
        return NULL;
    }
    
    Node<type>* current = head;
    for(size_t i = 0; i<index; i++)
    {
        current = current -> next;
    }
    return current->data;
}

template<typename type>
void lista<type>::print(){
    
    Node<type>* current = head;
    while (current != nullptr)
    {
        std::cout<<current -> data<<' ';
        current = current -> next;
    }
    std::cout<<'\n';
}

template<typename type>
type lista<type>::back(){
    if (empty())
    {
        std::cout<<"The list is empty!";
    }
    
    Node<type>* current = head;
    while (current -> next != nullptr)
    {
        current = current -> next;
    }
    return current -> data;
}

template<typename type>
type lista<type>::front(){
    if (empty())
    {
        std::cout<<"The list is empty!";
    }
    
    return head->data;
}

template<typename type>
void lista<type>::pop_back(){
    if (empty())
    {
        std::cout<<"The list is empty!";
        return;
    }
    if (head -> next == nullptr)
    {
        delete head;
        head = nullptr;
        return;
    }
    
    Node<type>* current = head;
    while (current -> next -> next != nullptr)
    {
        current = current -> next;
    }
    delete current -> next;
    size--;
    current -> next = nullptr;
}

template<typename type>
void lista<type>::pop_front(){
    if (empty())
    {
        std::cout<<"The list is empty!";
        return;
    }
    Node<type>* temp = head;
    head = head->next;
    size--;
    delete temp;
}

template<typename type>
Node<type>* lista<type>::begin(){
    return head;
}

template<typename type>
Node<type>* lista<type>::end(){
    return nullptr;
}

template<typename type>
size_t lista<type>::getSize(){
    return size;
}

template<typename type>
bool lista<type>::getOrder(){
    return order;
}

template<typename type>
void lista<type>::merge(lista<type> &other){
    Node<type>* current1 = head;
    Node<type>* current2 = other.head;
    Node<type>* previous = nullptr;
    
    if (current2 == nullptr) {
        return;
    }
        
    while (current1 != nullptr && current2 != nullptr) {
        if (current1 -> data < current2 -> data) {
            previous = current1;
            current1 = current1->next;
        }
        else
        {
            Node<type>* temp = current2;
            current2 = current2->next;
            
            if (previous == nullptr) {
                head = temp;
            }
            else {
                previous -> next = temp;
            }
            temp -> next = current1;
            previous = temp;
        }
    }
    if (current1 == nullptr)
    {
        if (previous == nullptr) {
            head = current2;
        }
        else {
            previous -> next = current2;
        }
    }
        
    other.head = nullptr; // clear the other list
}

template<typename type>
void lista<type>::unique(){
    Node<type>* current = head;
    while (current != nullptr && current -> next != nullptr)
    {
        if (current -> data == current -> next -> data)
        {
            Node<type>* temp = current -> next;
            current -> next = current -> next -> next;
            delete temp;
        }
        else{
            current =  current -> next;
        }
    }
}

template<typename type>
void lista<type>::clear(){
    Node<type>* current = head;
    while (current != nullptr)
    {
        Node<type>* temp = current;
        current = current -> next;
        delete temp;
    }
    head = nullptr;
}

template<typename type>
void lista<type>::reverse(){
    if (head==nullptr || head->next==nullptr)
    {
        return;
    }
    
    Node<type>* previous = nullptr;
    Node<type>* current = head;
    
    while (current != nullptr)
    {
        Node<type>* temp = current -> next;
        current -> next = previous;
        previous = current;
        current = temp;
    }
    head = previous;
    
    if (order == 1) order=0;
    else order = 1;
}

template<typename type>
unsigned int lista<type>::count(const type &value){
    Node<type>* current = head;
    unsigned int cnt = 0;
    while (current != nullptr)
    {
        if (current -> data == value)
        {
            cnt++;
        }
        current = current -> next;
    }
    return cnt;
}


template<typename type>
lista<type> lista<type>::getSubList(const size_t start_index, const size_t end_index){
    lista<type> sub_list;
    
    if (start_index > end_index || start_index < 0 || end_index > (size-1))
    {
        std::cout<<"Invalid index";
        return sub_list;
    }
    
    sub_list.size = end_index - start_index + 1;
    sub_list.order = order;
    
    Node<type>* current = head;
    size_t i = 0;
    
    while (current != nullptr && i<=end_index)
    {
        if (i >= start_index)
        {
            sub_list.insert(current->data);
        }
        current = current -> next;
        i++;
    }
    
    return sub_list;
}

template<typename type>
bool lista<type>::operator== (const lista<type> &other)
{
    Node<type>* current1 = head;
    Node<type>* current2 = other.head;
    
    if (size != other.size)
    {
        return false;
    }
    
    while (current1 != nullptr && current2 != nullptr)
    {
        if (current1 -> data != current2 -> data)
            return false;
        current1 = current1 -> next;
        current2 = current2 -> next;
    }
    
    return true;
}

template<typename type>
bool lista<type>::operator!= (const lista<type> &other)
{
    return !operator==(other);
}

template<typename type>
type lista<type>::operator[](const size_t index)
{
    if (index<0 || index>size)
    {
        std::cout<<"Not a valid index!";
        return NULL;
    }
    Node<type>* current = head;
    for(size_t i = 0; i<index; i++)
    {
        current = current -> next;
    }
    return current -> data;
    
}
