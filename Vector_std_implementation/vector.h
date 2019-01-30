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

  explicit Iterator(pointer ptr = nullptr);
  Iterator(const Iterator &other);

  Iterator &operator=(const Iterator &);
  Iterator &operator++();
  Iterator &operator--();
  const Iterator operator++(int);
  const Iterator operator--(int);
  Iterator &operator+=(difference_type);
  Iterator &operator-=(difference_type);

  difference_type operator-(const Iterator &) const;
  Iterator operator+(difference_type) const;
  Iterator operator-(difference_type) const;

  reference operator*() const;
  pointer operator->() const;
  reference operator[](difference_type) const;

  bool operator==(const Iterator &) const;
  bool operator!=(const Iterator &) const;
  bool operator>(const Iterator &) const;
  bool operator<(const Iterator &) const;
  bool operator>=(const Iterator &) const;
  bool operator<=(const Iterator &) const;
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
  typedef typename const Iterator<T> const_iterator;
  typedef std::reverse_iterator<iterator> reverse_iterator;
  typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

  // Сonstructors

  Vector()
      : size_(0),
        real_size_(min_size),
        alloc_(allocator_type()) {
    data_ = alloc_.allocate(real_size_);
  }

  Vector(size_type a_size)
      : size(0), real_size_(a_size), alloc_(allocator_type()) {
    data_ = alloc_.allocate(real_size_);
  }

  Vector(size_type a_size, const_reference a_value,
         const allocator_type &alloc = allocator_type());

  Vector(std::initializer_list<value_type> il,
         const allocator_type &alloc = allocator_type());

  Vector(const Vector &other, const allocator_type &alloc);

  template <class InputIterator>
  Vector(InputIterator a_first, InputIterator a_last,
         const allocator_type &alloc = allocator_type());

  Vector &operator=(const Vector &other);

  ~Vector() { alloc_.deallocate(data_, real_size_); }

  // Iterators

  iterator begin();

  const_iterator begin() const;

  iterator end();

  const_iterator end() const;

  reverse_iterator rbegin();

  const_reverse_iterator rbegin() const;

  reverse_iterator rend();

  const_reverse_iterator rend() const;

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

  const_reference at(size_type a_index) const { return at(a_index); }

  reference operator[](size_type a_index) { return at(a_index); }

  const_reference operator[](size_type a_index) const { return at(a_index); }

  // Modifiers

  iterator insert(iterator a_position, const T &a_value);

  template <class... Args>
  iterator emplace(iterator a_position, Args &&... args);

  template <class... Args>
  iterator emplace_back(Args &&... args);

  void push_back(const T &a_value) { 
	  resize(++size_);
      back() = a_value;
  }

  iterator erase(iterator a_first, iterator a_last);

  iterator erase(iterator a_position);

  void clear();

  void pop_back();

 private:
  void realloc() {
    size_type new_size = real_size_ * K_reserve;
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
