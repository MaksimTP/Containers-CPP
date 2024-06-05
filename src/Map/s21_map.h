#ifndef S21_MAP_H
#define S21_MAP_H

#include <vector>

#include "../AVLTree/s21_avl.h"

namespace s21 {
template <typename Key, typename T>
class map : public s21_AVLTree<Key, T> {
 public:
  class MapIterator;
  class ConstMapIterator;

  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = MapIterator;
  using const_iterator = ConstMapIterator;
  using size_type = size_t;

  map() : s21_AVLTree<Key, T>(){};
  map(std::initializer_list<value_type> const &items);
  map(const map &other) : s21_AVLTree<Key, T>(other){};
  map(map &&other) noexcept : s21_AVLTree<Key, T>(std::move(other)){};
  map &operator=(map &&other) noexcept;
  map &operator=(const map &other);
  ~map() = default;

  iterator begin();
  iterator end();
  const_iterator cbegin() const;
  const_iterator cend() const;
  void merge(map &other);

  class MapIterator : public s21_AVLTree<Key, T>::Iterator {
   public:
    friend class map;
    MapIterator() : s21_AVLTree<Key, T>::Iterator(){};
    MapIterator(typename s21_AVLTree<Key, T>::Node *node,
                typename s21_AVLTree<Key, T>::Node *past_node = nullptr)
        : s21_AVLTree<Key, T>::Iterator(node, past_node = nullptr){};
    value_type &operator*();

   protected:
    T &return_value();
  };

  class ConstMapIterator : public MapIterator {
   public:
    friend class map;
    ConstMapIterator() : MapIterator(){};
    ConstMapIterator(typename s21_AVLTree<Key, T>::Node *node,
                     typename s21_AVLTree<Key, T>::Node *past_node = nullptr)
        : MapIterator(node, past_node = nullptr){};
    const_reference operator*() const { return MapIterator::operator*(); };
  };

  T &at(const Key &key);
  T &operator[](const Key &key);
  std::pair<iterator, bool> insert(const value_type &value);
  std::pair<iterator, bool> insert(const Key &key, const T &obj);
  std::pair<iterator, bool> insert_or_assign(const Key &key, const T &obj);
  template <class... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args);
  void erase(iterator pos);

 private:
  iterator find(const Key &key);
};

template <typename Key, typename T>
map<Key, T>::map(const std::initializer_list<value_type> &items) {
  for (auto i = items.begin(); i != items.end(); ++i) {
    insert(*i);
  }
}

template <typename Key, typename T>
map<Key, T> &map<Key, T>::operator=(map &&other) noexcept {
  if (this != &other) {
    s21_AVLTree<Key, T>::operator=(std::move(other));
  }
  return *this;
}

template <typename Key, typename T>
map<Key, T> &map<Key, T>::operator=(const map &other) {
  if (this != &other) {
    s21_AVLTree<Key, T>::operator=(other);
  }
  return *this;
}

template <typename Key, typename T>
std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert(
    const value_type &value) {
  return insert(value.first, value.second);
}

template <typename Key, typename T>
std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert(
    const Key &key, const T &obj) {
  std::pair<iterator, bool> return_value;
  if (s21_AVLTree<Key, T>::root_ == nullptr) {
    s21_AVLTree<Key, T>::root_ =
        new typename s21_AVLTree<Key, T>::Node(key, obj);
    return_value.first = iterator(s21_AVLTree<Key, T>::root_);
    return_value.second = true;
  } else {
    bool check_insert = s21_AVLTree<Key, T>::RecursiveInsert(
        s21_AVLTree<Key, T>::root_, key, obj);
    return_value.first = find(key);
    return_value.second = check_insert;
  }
  return return_value;
}

template <typename Key, typename T>
typename map<Key, T>::value_type &map<Key, T>::MapIterator::operator*() {
  if (s21_AVLTree<Key, T>::Iterator::iter_node_ == nullptr) {
    static value_type fake_value{};
    return fake_value;
  }
  std::pair<const key_type, mapped_type> pr =
      std::make_pair(s21_AVLTree<Key, T>::Iterator::iter_node_->key_,
                     s21_AVLTree<Key, T>::Iterator::iter_node_->value_);
  std::pair<const key_type, mapped_type> &ref = pr;
  return ref;
}

template <typename Key, typename T>
T &map<Key, T>::MapIterator::return_value() {
  if (s21_AVLTree<Key, T>::Iterator::iter_node_ == nullptr) {
    static T fake_value{};
    return fake_value;
  }
  return s21_AVLTree<Key, T>::Iterator::iter_node_->value_;
}

template <typename Key, typename T>
typename map<Key, T>::iterator map<Key, T>::find(const Key &key) {
  typename s21_AVLTree<Key, T>::Node *node =
      s21_AVLTree<Key, T>::RecursiveFind(s21_AVLTree<Key, T>::root_, key);
  return iterator(node);
}

template <typename Key, typename T>
std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert_or_assign(
    const Key &key, const T &obj) {
  auto it = find(key);
  if (it != this->end()) {
    erase(it);
    auto pr = insert(key, obj);
    pr.second = false;
    return pr;
  }
  return insert(key, obj);
}

template <typename Key, typename T>
template <class... Args>
std::vector<std::pair<typename map<Key, T>::iterator, bool>>
map<Key, T>::insert_many(Args &&...args) {
  std::vector<std::pair<typename map<Key, T>::iterator, bool>> vec;
  for (const auto &arg : {args...}) {
    vec.push_back(insert(arg));
  }
  return vec;
}

template <typename Key, typename T>
T &map<Key, T>::at(const Key &key) {
  auto it = find(key);
  if (it == nullptr)
    throw std::out_of_range(
        "Container does not have an element with the specified key");
  return it.return_value();
}

template <typename Key, typename T>
T &map<Key, T>::operator[](const Key &key) {
  auto it = find(key);
  if (it == nullptr) {
    auto pr = insert(std::make_pair(key, T()));
    it = pr.first;
  }
  return it.return_value();
}

template <typename Key, typename T>
typename map<Key, T>::iterator map<Key, T>::begin() {
  return map<Key, T>::MapIterator(
      s21_AVLTree<Key, T>::GetMin(s21_AVLTree<Key, T>::root_));
}

template <typename Key, typename T>
typename map<Key, T>::iterator map<Key, T>::end() {
  if (s21_AVLTree<Key, T>::root_ == nullptr) return begin();

  typename s21_AVLTree<Key, T>::Node *last_node =
      s21_AVLTree<Key, T>::GetMax(s21_AVLTree<Key, T>::root_);
  MapIterator test(nullptr, last_node);
  return test;
}

template <typename Key, typename T>
typename map<Key, T>::const_iterator map<Key, T>::cbegin() const {
  return map<Key, T>::ConstMapIterator(
      s21_AVLTree<Key, T>::GetMin(s21_AVLTree<Key, T>::root_));
}

template <typename Key, typename T>
typename map<Key, T>::const_iterator map<Key, T>::cend() const {
  if (s21_AVLTree<Key, T>::root_ == nullptr) return cbegin();

  typename s21_AVLTree<Key, T>::Node *last_node =
      s21_AVLTree<Key, T>::GetMax(s21_AVLTree<Key, T>::root_);
  ConstMapIterator test(nullptr, last_node);
  return test;
}

template <typename Key, typename T>
void map<Key, T>::merge(map &other) {
  map const_tree(other);
  iterator const_it = const_tree.begin();
  for (; const_it != const_tree.end(); ++const_it) {
    auto key = (*const_it).first;
    auto obj = (*const_it).second;
    std::pair<iterator, bool> pr = insert(key, obj);
    if (pr.second) other.erase(pr.first);
  }
}

template <typename Key, typename T>
void map<Key, T>::erase(map::iterator pos) {
  if (s21_AVLTree<Key, T>::root_ == nullptr || pos.iter_node_ == nullptr)
    return;
  s21_AVLTree<Key, T>::root_ = s21_AVLTree<Key, T>::RecursiveDelete(
      s21_AVLTree<Key, T>::root_, (*pos).first);
}

}  // namespace s21

#endif