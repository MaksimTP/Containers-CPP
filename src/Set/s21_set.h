#ifndef S21_SET_H
#define S21_SET_H

#include <vector>

#include "../s21_container.h"

namespace s21 {
template <class T>
class set {
 public:
  using const_iterator = typename list<T>::const_iterator;
  using const_reference = const T &;
  using iterator = typename list<T>::iterator;
  using key_type = T;
  using reference = T &;
  using size_type = size_t;
  using value_type = T;

  set();
  set(std::initializer_list<value_type> const &items);
  set(const set &s);
  set(set &&s);
  ~set();

  set &operator=(set &s);
  set &operator=(set &&s);

  iterator begin();
  iterator end();

  bool empty();
  size_type size();
  size_type max_size();

  void clear();
  std::pair<iterator, bool> insert(const value_type &value);
  void erase(iterator pos);
  void erase(const T &value);
  void swap(set &other);
  void merge(set &other);

  iterator find(const key_type &key);
  bool contains(const key_type &key);

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args);

 private:
  list<T> data;
};

template <class T>
set<T>::set() : data() {}

template <class T>
set<T>::set(std::initializer_list<value_type> const &items) : data(items) {
  data.sort();
}

template <class T>
set<T>::set(const set &s) : data(s.data) {
  data.sort();
}

template <class T>
set<T>::set(set &&s) : data(std::move(s.data)) {
  data.sort();
}

template <class T>
set<T>::~set() {}

template <class T>
set<T> &set<T>::operator=(set<T> &&s) {
  if (this != &s) {
    data.swap(s);
  }
  return *this;
}

template <class T>
set<T> &set<T>::operator=(set<T> &s) {
  data.clear();
  for (const auto &item : s) {
    data.push_back(item);
  }
  return *this;
}

template <class T>
typename set<T>::iterator set<T>::begin() {
  return data.begin();
}

template <class T>
typename set<T>::iterator set<T>::end() {
  return data.end();
}

template <class T>
bool set<T>::empty() {
  return data.empty();
}

template <class T>
typename set<T>::size_type set<T>::size() {
  return data.size();
}

template <class T>
typename set<T>::size_type set<T>::max_size() {
  return data.max_size();
}

template <class T>
void set<T>::clear() {
  data.clear();
}

template <class T>
std::pair<typename set<T>::iterator, bool> set<T>::insert(
    const value_type &value) {
  auto it = find(value);
  if (it != end()) {
    return std::make_pair(it, false);
  }
  data.push_back(value);
  data.sort();
  return std::make_pair(--end(), true);
}

template <class T>
void set<T>::erase(iterator pos) {
  data.erase(pos);
}

template <class T>
void set<T>::erase(const T &value) {
  auto it = find(value);
  if (it != data.end()) {
    data.erase(it);
  }
}

template <class T>
void set<T>::swap(set &other) {
  data.swap(other.data);
}

template <class T>
void set<T>::merge(set &other) {
  data.merge(other.data);
}

template <class T>
typename set<T>::iterator set<T>::find(const key_type &key) {
  for (auto it = begin(); it != end(); ++it) {
    if (*it == key) {
      return it;
    }
  }
  return end();
}

template <class T>
bool set<T>::contains(const key_type &key) {
  return find(key) != data.end();
}

template <class T>
template <typename... Args>
std::vector<std::pair<typename set<T>::iterator, bool>> set<T>::insert_many(
    Args &&...args) {
  std::vector<std::pair<typename set<T>::iterator, bool>> results;
  (results.push_back(insert(std::forward<Args>(args))), ...);
  return results;
}

}  // namespace s21

#endif