#pragma once

#include <algorithm>
#include <cassert>
#include <exception>
#include <iostream>
#include <iterator>
#include <limits>
#include <memory>

template <typename T>
class Iterator {
 public:
  typedef typename std::iterator_traits<Iterator<T>> traits;
  typedef typename traits::difference_type difference_type;
  typedef typename traits::value_type value_type;
  typedef typename traits::pointer pointer;
  typedef typename traits::reference reference;
  typedef typename traits::iterator_category iterator_category;

  explicit Iterator(pointer ptr = nullptr) : ptr_(ptr) {}
  Iterator(const Iterator &other) : ptr_(other.ptr_) {}

  Iterator &operator=(const Iterator &right) { ptr_ = right.ptr_; }
  Iterator &operator++() {
    ++ptr_;
    return *this;
  }
  Iterator &operator--() {
    --ptr_;
    return *this;
  }
  const Iterator operator++(int) {
    Iterator _Tmp = *this;
    ++*this;
    return (_Tmp);
  }
  const Iterator operator--(int) {
    Iterator _Tmp = *this;
    --*this;
    return (_Tmp);
  }
  Iterator &operator+=(difference_type off) {
    ptr_ += off;
    return (*this);
  }

  Iterator &operator-=(difference_type off) {
    ptr_ -= off;
    return (*this);
  }

  difference_type operator-(const Iterator &right) const {
    return (ptr_ - right.ptr_);
  }
  Iterator operator+(difference_type off) const {
    Iterator _Tmp = *this;
    return (_Tmp += off);
  }
  Iterator operator-(difference_type off) const {
    Iterator _Tmp = *this;
    return (_Tmp -= off);
  }

  reference operator*() const { return (*ptr_); }
  pointer operator->() const { return (ptr_); }

  reference operator[](difference_type off) const { return (*(*this + off)); }

  bool operator==(const Iterator &right) const { return (ptr_ == right.ptr_); }
  bool operator!=(const Iterator &right) const { return (ptr_ != right.ptr_); }
  bool operator>(const Iterator &right) const { return (ptr_ > right.ptr_); }
  bool operator<(const Iterator &right) const { return (ptr_ < right.ptr_); }
  bool operator>=(const Iterator &right) const { return (ptr_ >= right.ptr_); }
  bool operator<=(const Iterator &right) const { return (ptr_ <= right.ptr_); }

 private:
  pointer ptr_;
};

template <class T, class A = std::allocator<T>>
class Vector {
 public:
  typedef A allocator_type;
  typedef typename A::value_type value_type;
  typedef typename A::reference reference;
  typedef typename A::const_reference const_reference;
  typedef typename A::size_type size_type;
  typedef typename A::difference_type difference_type;
  typedef typename A::pointer pointer;
  typedef typename A::const_pointer const_pointer;
  typedef typename Iterator<T> iterator;
  typedef typename Iterator<T> const_iterator;
  typedef std::reverse_iterator<iterator> reverse_iterator;
  typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

  // Сonstructors

  Vector() : size_(0), real_size_(min_size), alloc_(allocator_type()) {
    data_ = alloc_.allocate(real_size_);
  }

  Vector(size_type a_size)
      : size(0), real_size_(a_size), alloc_(allocator_type()) {
    data_ = alloc_.allocate(real_size_);
  }

  Vector(size_type a_size, const_reference a_value,
         const allocator_type &alloc = allocator_type())
      : alloc_(alloc) {
    resize(a_size);
    for (size_type i = 0; i < size_; ++i) {
      push_back(a_value);
    }
  }

  Vector(std::initializer_list<value_type> il,
         const allocator_type &alloc = allocator_type())
      : alloc_(alloc) {
    resize(il.size());
    std::copy(il.begin(), il.end(), begin());
  }

  Vector(const Vector &other, const allocator_type &alloc) : alloc_(alloc) {
    resize(other.size());
    std::copy(other.begin(), other.end(), begin());
  }

  template <class InputIterator>
  Vector(InputIterator a_first, InputIterator a_last,
         const allocator_type &alloc = allocator_type()): alloc_(alloc) {
    resize(a_last - a_first);
    std::copy(a_first, a_last, begin());
  }

  Vector &operator=(const Vector &other) {
    resize(other.size());
    std::copy(other.begin(), other.end(), begin());
  }

  ~Vector() { alloc_.deallocate(data_, real_size_); }

  // Iterators

  iterator begin() { return iterator(data_); }

  const_iterator begin() const { return const_iterator(data_); }

  iterator end() { return iterator(data_[size_]); }

  const_iterator end() const { return const_iterator(data_[size_]); }

  reverse_iterator rbegin() { return reverse_iterator(data_[size_]); }

  const_reverse_iterator rbegin() const {
    return const_reverse_iterator(data_[size_]);
  };

  reverse_iterator rend() { return reverse_iterator(data_); }

  const_reverse_iterator rend() const { return const_reverse_iterator(data_); }

  // Capacity

  size_type size() const { return size_; }

  size_type capacity() const { return real_size_; }

  bool empty() const { return size_ == 0; }

  void reserve(size_type a_size) {
    if (a_size > real_size_) {
      realloc();
    }
  }

  void resize(size_type a_size) {
    if (a_size > real_size_) {
      realloc();
    }

    size_ = a_size;
  }
  // Element access

  reference front() { return data_[0]; }

  const_reference front() const { return data_[0]; }

  reference back() { return data_[size_ - 1]; }

  const_reference back() const { return data_[size_ - 1]; }

  reference at(size_type a_index) {
    assert(a_index > size_ - 1);
    return data_[a_index];
  }

  const_reference at(size_type a_index) const {
    assert(!(a_index > size_ - 1));
    return data_[a_index];
  }

  reference operator[](size_type a_index) { return at(a_index); }

  const_reference operator[](size_type a_index) const { return at(a_index); }

  // Modifiers

  iterator insert(iterator a_position, const T &a_value) {
    resize(size_ + 1);
    std::copy(a_position, end() - 1, a_position + 1);
    *a_position = a_value;
  }

  template <class... Args>
  iterator emplace(iterator a_position, Args &&... args) {
    insert(a_position, T(args...));
  }

  template <class... Args>
  iterator emplace_back(Args &&... args) {
    push_back(T(args...));
  }

  void push_back(const T &a_value) {
    resize(++size_);
    back() = a_value;
  }

  iterator erase(iterator a_first, iterator a_last) {
    for (auto it = a_first; it < a_last; ++it) {
      it->~T();
    }
    std::copy(a_last, end(), a_first);
    resize(size_ - 1);
  }

  iterator erase(iterator a_position) {
    a_position->~T();
    std::copy(a_position + 1, end(), a_position);
    resize(size_ - 1);
  }

  void clear() {
    for (size_type i = 0; i < size_; ++i) {
      data_[i].~T();
    }
    size_ = 0;
  }

  void pop_back() {
    back().~T();
    size_ -= 1;
  }

 private:
  void realloc() {
    size_type new_size = size_ * K_reserve;
    pointer new_data = alloc_.allocate(new_size);
    for (size_type i = 0; i < real_size_; ++i) {
      std::swap(data_[i], new_data[i]);
    }
    alloc_.deallocate(data_, real_size_);
    real_size_ = new_size;
    data_ = new_data;
  }
  const float K_reserve = 2;
  const size_type min_size = 1;
  size_type size_;
  size_type real_size_;
  allocator_type alloc_;
  pointer data_;
};
