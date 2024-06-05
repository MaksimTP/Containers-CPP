#ifndef S21_MULTISET_H
#define S21_MULTISET_H

#include "../s21_container.h"

namespace s21 {

template <class T>
class multiset {
 public:
  using const_iterator = typename list<T>::const_iterator;
  using const_reference = const T&;
  using iterator = typename list<T>::iterator;
  using key_type = T;
  using reference = T&;
  using size_type = size_t;
  using value_type = T;

  multiset();
  multiset(std::initializer_list<value_type> const& items);
  multiset(const multiset& ms);
  multiset(multiset&& ms);
  ~multiset();

  multiset& operator=(multiset& ms);
  multiset& operator=(multiset&& ms);

  iterator begin();
  iterator end();

  bool empty();
  size_type size();
  size_type max_size();

  void clear();
  iterator insert(const value_type& value);
  void erase(iterator pos);
  void erase(const T& value);
  void swap(multiset& other);
  void merge(multiset& other);

  size_type count(const key_type& key);
  iterator find(const key_type& key);
  bool contains(const key_type& key);
  std::pair<iterator, iterator> equal_range(const key_type& key);
  iterator lower_bound(const key_type& key);
  iterator upper_bound(const key_type& key);

  template <typename... Args>
  std::vector<std::pair<typename multiset<T>::iterator, bool>> insert_many(
      Args&&... args);

 private:
  list<T> data;
};

template <class T>
multiset<T>::multiset() : data() {}

template <class T>
multiset<T>::multiset(std::initializer_list<value_type> const& items)
    : data(items) {
  data.sort();
}

template <class T>
multiset<T>::multiset(const multiset& ms) : data(ms.data) {
  data.sort();
}

template <class T>
multiset<T>::multiset(multiset&& ms) : data(std::move(ms.data)) {
  data.sort();
}

template <class T>
multiset<T>::~multiset() {}

template <class T>
multiset<T>& multiset<T>::operator=(multiset<T>&& ms) {
  if (this != &ms) {
    data.swap(ms);
  }
  return *this;
}

template <class T>
multiset<T>& multiset<T>::operator=(multiset<T>& ms) {
  data.clear();
  for (const auto& item : ms) {
    data.push_back(item);
  }
  return *this;
}

template <class T>
typename multiset<T>::iterator multiset<T>::begin() {
  return data.begin();
}

template <class T>
typename multiset<T>::iterator multiset<T>::end() {
  return data.end();
}

template <class T>
bool multiset<T>::empty() {
  return data.empty();
}

template <class T>
typename multiset<T>::size_type multiset<T>::size() {
  return data.size();
}

template <class T>
typename multiset<T>::size_type multiset<T>::max_size() {
  return data.max_size();
}

template <class T>
void multiset<T>::clear() {
  data.clear();
}

template <class T>
typename multiset<T>::iterator multiset<T>::insert(const value_type& value) {
  auto it = data.begin();
  while (it != data.end() && *it <= value) {
    ++it;
  }

  return data.insert(it, value);
}

template <class T>
void multiset<T>::erase(iterator pos) {
  data.erase(pos);
}

template <class T>
void multiset<T>::erase(const T& value) {
  auto it = find(value);
  if (it != data.end()) {
    data.erase(it);
  }
}

template <class T>
void multiset<T>::swap(multiset& other) {
  data.swap(other.data);
}

template <class T>
void multiset<T>::merge(multiset& other) {
  data.merge(other.data);
}

template <class T>
typename multiset<T>::size_type multiset<T>::count(const key_type& key) {
  size_type count = 0;
  for (const auto& elem : data) {
    if (elem == key) ++count;
  }
  return count;
}

template <class T>
typename multiset<T>::iterator multiset<T>::find(const key_type& key) {
  for (auto it = begin(); it != end(); ++it) {
    if (*it == key) {
      return it;
    }
  }
  return end();
}

template <class T>
bool multiset<T>::contains(const key_type& key) {
  return find(key) != data.end();
}

template <class T>
std::pair<typename multiset<T>::iterator, typename multiset<T>::iterator>
multiset<T>::equal_range(const key_type& key) {
  auto lower = lower_bound(key);
  auto upper = lower;

  while (upper != end() && !(*upper > key)) {
    ++upper;
  }
  return std::make_pair(lower, upper);
}

template <typename T>
typename multiset<T>::iterator multiset<T>::lower_bound(const key_type& key) {
  auto it = begin();
  while (it != end() && *it < key) {
    ++it;
  }
  return it;
}

template <class T>
typename multiset<T>::iterator multiset<T>::upper_bound(const key_type& key) {
  auto it = begin();
  while (it != end() && *it <= key) {
    ++it;
  }
  return it;
}

template <class T>
template <typename... Args>
std::vector<std::pair<typename multiset<T>::iterator, bool>>
multiset<T>::insert_many(Args&&... args) {
  std::vector<std::pair<typename multiset<T>::iterator, bool>> results;
  ((results.push_back(std::make_pair(insert(std::forward<Args>(args)), true))),
   ...);
  return results;
}

}  // namespace s21

#endif