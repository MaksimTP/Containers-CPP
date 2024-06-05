#ifndef S21_VECTOR_H
#define S21_VECTOR_H

#include "../s21_container.h"

namespace s21 {
template <class T>
class vector {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using iterator = T*;
  using const_iterator = const T*;
  using size_type = size_t;

  vector() : data_(nullptr), size_(0), capacity_(0){};
  vector(size_type n) : data_(new T[n]), size_(n), capacity_(n){};
  vector(std::initializer_list<value_type> const& items);
  vector(const vector& v);
  vector(vector&& v);

  ~vector(){};

  vector& operator=(vector&& v);

  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference front() { return *data_; };
  const_reference back() { return data_[size_ - 1]; };
  T* data() { return data_; };

  iterator begin() { return data_; };
  iterator end() { return data_ + size_; };

  bool empty() { return data_ == nullptr; };
  size_type size() { return size_; };
  size_type max_size();
  void reserve(size_type size);
  size_type capacity() { return capacity_; };
  void shrink_to_fit();

  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void swap(vector& other);

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args&&... args);
  template <typename... Args>
  void insert_many_back(Args&&... args);

 private:
  T* data_;
  size_type size_;
  size_type capacity_;
};

template <typename T>
vector<T>::vector(std::initializer_list<value_type> const& items)
    : vector(items.size()) {
  for (size_type i = 0; i < size_; ++i) {
    data_[i] = *(items.begin() + i);
  }
}

template <typename T>
vector<T>::vector(const vector<T>& v) : vector(v.size_) {
  for (size_type i = 0; i < size_; ++i) {
    data_[i] = v.data_[i];
  }
}

template <typename T>
vector<T>::vector(vector<T>&& v) {
  size_ = v.size_;
  v.size_ = 0;
  capacity_ = v.capacity_;
  v.capacity_ = 0;
  data_ = v.data_;
  v.data_ = nullptr;
}

template <typename T>
vector<T>& vector<T>::operator=(vector<T>&& v) {
  if (this != &v) {
    this->swap(v);
  }
  return *this;
}

template <typename T>
typename vector<T>::reference vector<T>::at(size_type pos) {
  if (pos >= size_ || size_ == 0) {
    throw std::out_of_range("Index out range");
  }
  return data_[pos];
}

template <typename T>
typename vector<T>::reference vector<T>::operator[](size_type pos) {
  return *(data_ + pos);
}

template <typename T>
void vector<T>::reserve(size_type size) {
  if (size > max_size() - size_) {
    throw std::length_error("Can't allocate memory of this size");
  }
  if (size >= size_) {
    vector<value_type> tmp(size);
    for (size_type i = 0; i < size_; ++i) {
      tmp.data_[i] = data_[i];
    }
    tmp.size_ = size_;
    *this = std::move(tmp);
  }
}

template <typename T>
void vector<T>::shrink_to_fit() {
  if (size_ != capacity_) {
    vector<value_type> tmp(size_);
    for (size_type i = 0; i < size_; ++i) {
      tmp.data_[i] = data_[i];
    }
    *this = std::move(tmp);
  }
}

template <typename T>
void vector<T>::clear() {
  delete[] data_;
  data_ = nullptr;
  size_ = 0;
}

template <typename T>
typename vector<T>::iterator vector<T>::insert(iterator pos,
                                               const_reference value) {
  vector<value_type> tmp(size_ + 1);
  size_type j = 0, position = pos - this->begin();
  for (size_type i = 0; i < tmp.size_; ++i) {
    if (i == position) {
      tmp.data_[i] = value;
    } else {
      tmp.data_[i] = data_[j++];
    }
  }
  *this = std::move(tmp);
  return data_ + position;
}

template <typename T>
void vector<T>::erase(iterator pos) {
  vector<value_type> tmp(size_ - 1);
  size_type j = 0, position = pos - this->begin();
  for (size_type i = 0; i < size_; ++i) {
    if (i != position) {
      tmp.data_[j++] = data_[i];
    }
  }
  *this = std::move(tmp);
}

template <typename T>
typename vector<T>::size_type vector<T>::max_size() {
  return std::numeric_limits<std::size_t>::max() / sizeof(value_type);
}

template <typename T>
void vector<T>::push_back(const_reference value) {
  if (capacity_ > size_) {
    data_[size_] = value;
    size_ += 1;
  } else {
    vector<value_type> tmp(size_ + 1);
    for (size_type i = 0; i < size_; ++i) {
      tmp.data_[i] = data_[i];
    }
    tmp[size_] = value;
    *this = std::move(tmp);
  }
}

template <typename T>
void vector<T>::pop_back() {
  size_ -= 1;
}

template <typename T>
void vector<T>::swap(vector& other) {
  value_type* tmp_arr = data_;
  size_type tmp_size = size_;
  size_type tmp_capacity = capacity_;
  data_ = other.data_;
  size_ = other.size_;
  capacity_ = other.capacity_;
  other.data_ = tmp_arr;
  other.size_ = tmp_size;
  other.capacity_ = tmp_capacity;
}

template <typename T>
template <typename... Args>
typename vector<T>::iterator vector<T>::insert_many(const_iterator pos,
                                                    Args&&... args) {
  vector<value_type> temp{args...};
  iterator cur_pos = begin() + (pos - begin());
  for (size_t i = 0; i < temp.size(); ++i) {
    cur_pos = insert(cur_pos, temp[i]);
    ++cur_pos;
  }
  return cur_pos;
}

template <typename T>
template <typename... Args>
void vector<T>::insert_many_back(Args&&... args) {
  insert_many(end(), args...);
}

}  // namespace s21

#endif
