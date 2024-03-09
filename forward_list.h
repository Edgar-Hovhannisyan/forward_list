#ifndef FORWARD_LIST_H
#define FORWARD_LIST_H
#include <cstddef>
#include <iostream>
#include <initializer_list>
#include <iterator>
template <typename T>
class forward_list 
{
public:
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = value_type&;
    using const_reference = const value_type&;
public:
    forward_list();
    forward_list(size_type count, const_reference value);
    forward_list(size_type count);
    forward_list(const forward_list& other);
    forward_list(forward_list&& other) noexcept;
    forward_list(const std::initializer_list<value_type>& init);
    template <typename InputIt>
    forward_list(InputIt begin, InputIt end);

    ~forward_list();
    void push_front(const_reference value);
    void pop_front();
    forward_list& operator=(const forward_list& other);
    forward_list& operator=(forward_list&& other) noexcept;
    forward_list& operator=(const std::initializer_list<value_type>& init);
    reference front();
    const_reference front() const;
    bool empty() const;
    size_type max_size() const;
    void assign(size_type count, const_reference value);
    template <class InputIt>
    void assign_range(InputIt begin, InputIt end);
    void assign(const std::initializer_list<value_type>& init);
    void clear() noexcept;
    void print() const;

private:
    struct Node 
    {
        T m_data;
        Node* m_next;
        Node(const T& data, Node* next);
    };
    Node* m_head;

public:
    class iterator : public std::iterator<std::forward_iterator_tag, T>
    {
    public:
        iterator(Node* m_data);
        reference operator*();
        Node* operator->();
        iterator& operator++();
        iterator operator++(int);
        ~iterator();
        bool operator ==(const iterator& other);
        bool operator !=(const iterator& other);

    private:
        Node* m_data;
    };

public:
    iterator begin();
    iterator end();
    iterator before_begin();
    iterator before_end();




};
#include "forward_list.tpp"
#endif //FORWARD_LIST_H