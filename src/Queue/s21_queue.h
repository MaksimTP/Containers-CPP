#ifndef S21_QUEUE_H
#define S21_QUEUE_H

#include "../s21_container.h"

namespace s21 {
template <class T>
class queue {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;

  queue() : list_(){};
  queue(std::initializer_list<value_type> const& items) : list_(items){};
  queue(const queue& q) : list_(q.list_){};
  queue(queue&& q) : list_(std::move(q.list_)){};

  ~queue(){};

  queue& operator=(queue&& q);

  const_reference front() { return list_.front(); };
  const_reference back() { return list_.back(); };

  bool empty() { return list_.empty(); };
  size_type size() { return list_.size(); };

  void push(const_reference value) { list_.push_back(value); };
  void pop() { list_.pop_front(); };
  void swap(queue& other) { list_.swap(other.list_); };

  template <typename... Args>
  void insert_many_back(Args&&... args) {
    list_.insert_many_back(std::forward<Args>(args)...);
  };

  void clear() { list_.clear(); }

 private:
  list<T> list_;
};

template <class T>
queue<T>& queue<T>::operator=(queue<T>&& q) {
  if (this != &q) {
    swap(q);
  }
  q.clear();
  return *this;
}
}  // namespace s21

#endif
