#include <cstddef>
#include <initializer_list>
#include <limits>
template <typename T>
forward_list<T>::forward_list() :
    m_head{nullptr}
{}

template <typename T>
forward_list<T>::forward_list(size_type count, const_reference value)
{
    for(int i = 0; i < count; ++i)
    {
        this->push_front(value);
    }
}

template <typename T>
forward_list<T>::forward_list(size_type count)
{
    for(int i = 0; i < count; ++i)
    {
        this->push_front(T());
    }
}

template <typename T>
forward_list<T>::forward_list(const forward_list& other) 
{
    Node* current = other.m_head;
    while (current)
    {
        this->push_front(current->m_data);
        current = current->m_next;
    }
    
}

template <typename T>
forward_list<T>::forward_list(forward_list&& other) noexcept : m_head(other.m_head)
{
    other.m_head = nullptr;
}

template <typename T>
forward_list<T>::forward_list(const std::initializer_list<value_type>& init)
{
    for(auto it = init.end() - 1; it >= init.begin(); --it)
    {
        this->push_front(*it);
    }
}

template <typename T>
template <typename InputIt>
forward_list<T>::forward_list(InputIt first, InputIt last) : m_head(nullptr)
{
    m_head = new Node(*first, nullptr);
    Node* current = m_head;
    while (++first!= last)
    {
        current->m_next = new Node(*first, nullptr);
        current = current->m_next;
    }

}


template <typename T>
forward_list<T>::~forward_list()
{
    while(m_head)
    {
        this->pop_front();
    }
    m_head = nullptr;
}
template <typename T>
void forward_list<T>::push_front(const_reference value)
{
    Node* newNode = new Node(value, m_head);
    m_head = newNode;
}
template<typename T>
void forward_list<T>::pop_front()
{
    Node* deleteNode = m_head;
    m_head = m_head->m_next;
    delete deleteNode;
}
template<typename T>
forward_list<T>& forward_list<T>::operator=(const forward_list<value_type>& other)
{
    if(this != &other)
    {
      this->~forward_list();
      this->m_head = new Node(other.m_head->m_data, nullptr);
      Node* current = this->m_head;
      Node* otherCurrent = other.m_head->m_next;
      while(otherCurrent)
      {
        current->m_next = new Node(otherCurrent->m_data, nullptr);
        current = current->m_next;
        otherCurrent = otherCurrent->m_next;
      }
       
    }
    return *this;
}

template <typename T>
forward_list<T>& forward_list<T>::operator=(forward_list<value_type>&& other) noexcept
{
    if(this != &other)
    {
        this->m_head = other.m_head;
        other.m_head = nullptr;
    }
    return *this;
}

template <typename T>
forward_list<T>& forward_list<T>::operator=(const std::initializer_list<value_type>& init)
{
    if(m_head)
    {
        this->~forward_list();
        
    }
    auto begin = std::begin(init);
    auto end = std::end(init);
    this->m_head = new Node(*begin, nullptr);
    Node* current = m_head;
    while (++begin != end)
    {
    current->m_next = new Node(*begin, nullptr);
    current = current->m_next;
    }
    return *this;
}

template <typename T>
typename forward_list<T>::reference forward_list<T>::front()
{
    return *m_head;
}

template <typename T>
typename forward_list<T>::const_reference forward_list<T>::front() const 
{
    return *m_head;
}

template <typename T>
bool forward_list<T>::empty() const
{
    return this->m_head == nullptr;
}

template <typename T>
typename forward_list<T>::size_type forward_list<T>::max_size() const 
{
    return std::numeric_limits<size_type>::max();
}

template <typename T>
void forward_list<T>::assign(size_type count, const_reference value)
{
    if(m_head)
    {
        this->~forward_list();
    }
    for(int i = 0 ; i < count ; i++)
    {
        this->push_front(value);
    }
}

template <typename T>
template <class InputIter>
void forward_list<T>::assign_range(InputIter begin, InputIter end)
{
    if (m_head)
    {
        this->~forward_list();
    }
    
    if (begin != end) {
        this->m_head = new Node{*begin, nullptr};
        Node* current = m_head;
        while (++begin != end)
        {
            current->m_next = new Node{*begin, nullptr};
            current = current->m_next;
        }
    }
}


template <typename T>
void forward_list<T>::assign(const std::initializer_list<value_type>& init)
{
    if(m_head)
    {
        this->~forward_list();
    }
    auto begin = std::begin(init);
    auto end = std::end(init);
    m_head = new Node(*begin, nullptr);
    Node* current = m_head;
    while(++begin != end)
    {
        current->m_next = new Node(*begin, nullptr);
        current = current->m_next;
    }
}


template <typename T>
void forward_list<T>::clear() noexcept
{
    while(m_head)
    {
        this->pop_front();
    }
}

template <typename T>
void forward_list<T>::print() const 
{
    Node* current = m_head;
    while(current)
    {
        std::cout << current->m_data << " -> ";
        current = current->m_next;
    }
    std::cout << std::endl;
}

//Non_const Forward_Iterator
template <typename T>
forward_list<T>::iterator::iterator(typename forward_list<value_type>::Node* data) : 
    m_data(data) 
{}


template <typename T>
typename forward_list<T>::reference forward_list<T>::iterator::operator*() 
{
    return m_data->m_data;
}

template <typename T>
typename forward_list<T>::Node* forward_list<T>::iterator::operator->()
{
    return &(m_data->m_data);
}

template <typename T>
typename forward_list<T>::iterator& forward_list<T>::iterator::operator++()
{
    m_data = m_data->m_next;
    return *this;
}

template <typename T>
typename forward_list<T>::iterator forward_list<T>::iterator::operator++(int)
{
    iterator tmp = *this; // Create a copy of the current iterator
    ++(*this); // Increment the iterator
    return tmp; // Return the copy
}

template <typename T>
forward_list<T>::iterator::~iterator()
{
    delete m_data;
}

template <typename T>
bool forward_list<T>::iterator::operator==(const iterator& other)
{
    return m_data == other.m_data;
}

template <typename T>
bool forward_list<T>::iterator::operator!=(const iterator& other)
{
    return m_data != other.m_data;
}

template <typename T>
typename forward_list<T>::iterator forward_list<T>::begin()
{
    return iterator(m_head);
}

template <typename T>
typename forward_list<T>::iterator forward_list<T>::end()
{
    return iterator(nullptr);
}

template <typename T>
typename forward_list<T>::iterator forward_list<T>::before_begin()
{
    return iterator(nullptr);
}

template<typename T>
typename forward_list<T>::iterator forward_list<T>::before_end()
{
    Node* current = m_head;
    while (current->m_next)
    {
        current = current->m_next;
    }

    return iterator(current);    
}


template <typename T>
forward_list<T>::Node::Node(const T& data, Node* next) :
    m_data{data},
    m_next{next}
{}



