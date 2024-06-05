#ifndef S21_LIST_H
#define S21_LIST_H

#include <cstdlib>
#include <iostream>
#include <limits>

namespace s21 {
template <class T>
class list {
 public:
  class ListIterator;
  class ListConstIterator;

  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using iterator = ListIterator;
  using const_iterator = ListConstIterator;
  using size_type = size_t;

  list();
  list(size_type n);
  list(std::initializer_list<value_type> const& items);
  list(const list& l);
  list(list&& l);

  ~list();

  list& operator=(list&& l);
  list& operator=(list& l);

  const_reference front();
  const_reference back();

  iterator begin();
  iterator end();
  const_iterator begin() const;
  const_iterator end() const;

  bool empty();
  size_type size();
  size_type max_size();

  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void push_front(const_reference value);
  void pop_front();
  void swap(list& other);
  void merge(list& other);
  void splice(iterator pos, list& other);
  void reverse();
  void unique();
  void sort();

  template <typename... Args>
  iterator insert_many(iterator pos, Args&&... args);

  template <typename... Args>
  void insert_many_back(Args&&... args);

  template <typename... Args>
  void insert_many_front(Args&&... args);

 private:
  struct Node {
    T data;
    Node* next;
    Node* prev;

    Node(T data) : data(data), prev(nullptr), next(nullptr) {}
    Node(Node* prev, Node* next, T data) : data(data), prev(prev), next(next) {}
  };

  Node* head_;
  Node* tail_;
  size_t size_;
};

template <class T>
list<T>::list() : head_(nullptr), tail_(nullptr), size_(0) {}

template <class T>
list<T>::list(size_type n) : head_(nullptr), tail_(nullptr), size_(0) {
  for (size_type i = 0; i < n; ++i) {
    push_back(T());
  }
  size_ = n;
}

template <class T>
list<T>::list(std::initializer_list<value_type> const& items)
    : head_(nullptr), tail_(nullptr), size_(0) {
  for (auto item : items) {
    push_back(item);
  }
}

template <class T>
list<T>::list(const list& l) : head_(nullptr), tail_(nullptr), size_(0) {
  for (auto it = l.begin(); it != l.end(); ++it) {
    push_back(*it);
  }
}

template <class T>
list<T>::list(list&& l) : head_(nullptr), tail_(nullptr), size_(0) {
  swap(l);
}

template <class T>
list<T>& list<T>::operator=(list<T>&& l) {
  if (this != &l) {
    swap(l);
    l.clear();
  }
  return *this;
}

template <class T>
list<T>& list<T>::operator=(list<T>& l) {
  clear();
  for (const auto& item : l) {
    push_back(item);
  }
  return *this;
}

template <class T>
list<T>::~list() {
  clear();
}

template <class T>
class list<T>::ListIterator {
  friend class ListConstIterator;

 public:
  ListIterator(Node* node, Node* head, Node* tail)
      : current_(node), head_(head), tail_(tail){};

  ListIterator operator++() {
    if (current_ != nullptr) {
      current_ = current_->next;
    } else {
      current_ = head_;
    }
    return *this;
  }

  ListIterator operator++(int) {
    if (current_ != nullptr) {
      current_ = current_->next;
    } else {
      current_ = head_;
    }
    return *this;
  }

  ListIterator operator--() {
    if (current_ != nullptr) {
      current_ = current_->prev;
    } else {
      current_ = tail_;
    }
    return *this;
  }

  ListIterator operator--(int) {
    if (current_ != nullptr) {
      current_ = current_->prev;
    } else {
      current_ = tail_;
    }
    return *this;
  }

  reference operator*() { return current_->data; }

  bool operator==(const ListIterator& other) const {
    return current_ == other.current_;
  }

  bool operator!=(const ListIterator& other) const {
    return current_ != other.current_;
  }

  Node* operator&() { return current_; }

 private:
  Node* current_;
  Node* head_;
  Node* tail_;
};

template <class T>
class list<T>::ListConstIterator {
  friend class ListIterator;

 public:
  ListConstIterator(Node* node, Node* head, Node* tail)
      : current_(node), head_(head), tail_(tail){};

  explicit ListConstIterator(const typename list<T>::ListIterator& other)
      : current_(other.current_), head_(other.head_), tail_(other.tail_) {}

  ListConstIterator& operator=(const typename list<T>::ListIterator& other) {
    current_ = other.current_;
    return *this;
  }

  ListConstIterator operator++() {
    if (current_ != nullptr) {
      current_ = current_->next;
    } else {
      current_ = head_;
    }
    return *this;
  }

  ListConstIterator operator++(int) {
    if (current_ != nullptr) {
      current_ = current_->next;
    } else {
      current_ = head_;
    }
    return *this;
  }

  ListConstIterator operator--() {
    if (current_ != nullptr) {
      current_ = current_->prev;
    } else {
      current_ = tail_;
    }
    return *this;
  }

  ListConstIterator operator--(int) {
    if (current_ != nullptr) {
      current_ = current_->prev;
    } else {
      current_ = tail_;
    }
    return *this;
  }

  const_reference operator*() const { return current_->data; }

  bool operator==(const ListConstIterator& other) const {
    return current_ == other.current_;
  }

  bool operator!=(const ListConstIterator& other) const {
    return current_ != other.current_;
  }

  const Node* operator&() { return current_; }

 private:
  const Node* current_;
  Node* head_;
  Node* tail_;
};

template <class T>
typename list<T>::const_reference list<T>::front() {
  return head_->data;
}

template <class T>
typename list<T>::const_reference list<T>::back() {
  return tail_->data;
}

template <class T>
typename list<T>::iterator list<T>::begin() {
  return iterator(head_, head_, tail_);
}

template <class T>
typename list<T>::iterator list<T>::end() {
  return iterator(nullptr, head_, tail_);
}

template <class T>
typename list<T>::const_iterator list<T>::begin() const {
  return const_iterator(head_, head_, tail_);
}

template <class T>
typename list<T>::const_iterator list<T>::end() const {
  return const_iterator(nullptr, head_, tail_);
}

template <class T>
bool list<T>::empty() {
  return size_ == 0;
}

template <class T>
typename list<T>::size_type list<T>::size() {
  return size_;
}

template <class T>
typename list<T>::size_type list<T>::max_size() {
  return std::numeric_limits<size_type>::max() / sizeof(Node);
}

template <typename T>
void list<T>::push_back(const_reference value) {
  Node* ptr = new Node(value);
  ptr->prev = tail_;
  if (tail_ != nullptr) {
    tail_->next = ptr;
  }
  if (head_ == nullptr) {
    head_ = ptr;
  }
  ++size_;
  tail_ = ptr;
}

template <typename T>
void list<T>::push_front(const_reference value) {
  Node* ptr = new Node(value);
  ptr->next = head_;
  if (head_ != nullptr) {
    head_->prev = ptr;
  }
  if (head_ == nullptr) {
    head_ = ptr;
  }
  ++size_;
  head_ = ptr;
}

template <typename T>
void list<T>::pop_front() {
  if (head_ == nullptr) return;

  Node* ptr = head_->next;
  if (ptr != nullptr)
    ptr->prev = nullptr;
  else
    tail_ = nullptr;
  delete head_;
  head_ = ptr;
  --size_;
}

template <typename T>
void list<T>::pop_back() {
  if (tail_ == nullptr) return;

  Node* ptr = tail_->prev;
  if (ptr != nullptr)
    ptr->next = nullptr;
  else
    head_ = nullptr;
  delete tail_;
  tail_ = ptr;
  --size_;
}

template <typename T>
void list<T>::clear() {
  while (head_ != nullptr) pop_front();

  head_ = nullptr;
  tail_ = nullptr;
  size_ = 0;
}

template <typename T>
typename list<T>::iterator list<T>::insert(iterator pos,
                                           const_reference value) {
  if (pos == begin()) {
    push_front(value);
    return begin();
  } else if (pos == end()) {
    push_back(value);
    return iterator(tail_, head_, tail_);
  } else {
    Node* current = &pos;
    Node* old_element = current;
    Node* new_element = new Node(value);
    new_element->next = old_element;
    new_element->prev = old_element->prev;
    if (old_element->prev != nullptr) {
      old_element->prev->next = new_element;
    }
    old_element->prev = new_element;
    size_++;
    return iterator(new_element, head_, tail_);
  }
}

template <typename T>
void list<T>::erase(iterator pos) {
  if (pos == end()) return;
  if (&pos == tail_)
    pop_back();
  else if (pos == begin()) {
    pop_front();
  } else {
    Node* current = &pos;
    current->prev->next = current->next;
    current->next->prev = current->prev;
    delete current;
    size_--;
  }
}

template <typename T>
void list<T>::swap(list& other) {
  using std::swap;
  swap(this->head_, other.head_);
  swap(this->tail_, other.tail_);
  swap(this->size_, other.size_);
}

template <typename T>
void list<T>::reverse() {
  if (size_ < 2) return;
  Node* current = head_;
  Node* prev = nullptr;
  while (current != nullptr) {
    Node* next = current->next;
    current->next = prev;
    current->prev = next;
    prev = current;
    current = next;
  }
  std::swap(head_, tail_);
}

template <typename T>
void list<T>::unique() {
  if (size_ < 2) return;
  iterator current = begin();
  while (current != end()) {
    iterator next = current;
    ++next;
    while (next != end() && *current == *next) {
      erase(next);
      next = current;
      ++next;
    }
    ++current;
  }
}

template <typename T>
void list<T>::sort() {
  for (iterator current = begin(); current != end(); ++current) {
    iterator pos = current;
    ++pos;
    while (pos != end()) {
      if (*current > *pos) std::swap(*pos, *current);
      ++pos;
    }
  }
}

template <typename T>
void list<T>::merge(list& other) {
  if (other.empty()) return;
  if (empty()) {
    *this = std::move(other);
    return;
  }
  iterator current = begin();
  iterator o_current = other.begin();
  while (current != end() && o_current != other.end()) {
    if (*o_current < *current) {
      insert(current, *o_current);
      ++o_current;
    } else
      ++current;
  }
  while (o_current != other.end()) {
    insert(current, *o_current);
    ++o_current;
  }
  other.clear();
}

template <typename T>
void list<T>::splice(iterator pos, list& other) {
  for (iterator current = other.begin(); current != other.end(); ++current)
    insert(pos, *current);
  other.clear();
}

template <typename T>
template <typename... Args>
typename list<T>::iterator list<T>::insert_many(iterator pos, Args&&... args) {
  for (const auto& arg : std::initializer_list<int>{args...}) {
    insert(pos, arg);
  }
  for (const auto& arg : std::initializer_list<int>{args...}) {
    --pos;
  }
  return pos;
}

template <typename T>
template <typename... Args>
void list<T>::insert_many_back(Args&&... args) {
  for (const auto& arg : std::initializer_list<int>{args...}) {
    push_back(arg);
  }
}

template <typename T>
template <typename... Args>
void list<T>::insert_many_front(Args&&... args) {
  for (const auto& arg : std::initializer_list<int>{args...}) {
    push_front(arg);
  }
}

}  // namespace s21

#endif