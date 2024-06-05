#ifndef S21_ARRAY_H
#define S21_ARRAY_H
#include "../s21_container.h"

namespace s21 {
template <typename T, size_t N>
struct array {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  array() : size_(N){};
  array(std::initializer_list<value_type> const &items);
  array(const array &a);
  array(array &&a) : array(a){};
  ~array(){};

  array &operator=(array &&a);

  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference front() { return *data_; };
  const_reference back() { return data_[size_ - 1]; };
  iterator data();

  iterator begin() { return data_; };
  iterator end() { return data_ + size(); };

  bool empty() { return N == 0; };
  size_type size() { return size_; };
  size_type max_size() { return size(); };

  void swap(array &a);
  void fill(const_reference value);

 private:
  size_type size_ = N;
  value_type data_[N];
};

template <typename T, size_t N>
array<T, N>::array(std::initializer_list<value_type> const &items) : array() {
  for (size_type i = 0; i < items.size(); ++i) {
    data_[i] = *(items.begin() + i);
  }
}

template <typename T, size_t N>
array<T, N>::array(const array &a) {
  for (size_type i = 0; i < size_; ++i) {
    data_[i] = a.data_[i];
  }
}

template <class T, size_t N>
array<T, N> &array<T, N>::operator=(array &&a) {
  if (this != &a) {
    for (size_type i = 0; i < a.size(); ++i) {
      data_[i] = std::move(a.data_[i]);
    }
  }
  return *this;
}

template <class T, size_t N>
typename s21::array<T, N>::reference s21::array<T, N>::at(size_type pos) {
  if (pos >= N) {
    throw std::out_of_range("Index out of range");
  }
  return data_[pos];
}

template <class T, size_t N>
typename s21::array<T, N>::reference s21::array<T, N>::operator[](
    size_type pos) {
  return data_[pos];
}

template <class T, size_t N>
typename s21::array<T, N>::iterator s21::array<T, N>::data() {
  return data_;
}

template <typename T, size_t N>
void array<T, N>::swap(array &other) {
  value_type tmp;
  for (size_type i = 0; i < size_; ++i) {
    tmp = other.data_[i];
    other.data_[i] = data_[i];
    data_[i] = tmp;
  }
}

template <class T, size_t N>
void array<T, N>::fill(const_reference value) {
  for (size_type i = 0; i < N; ++i) {
    data_[i] = value;
  }
}
}  // namespace s21

#endif
