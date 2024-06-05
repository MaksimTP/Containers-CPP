#ifndef S21_STACK_H
#define S21_STACK_H

#include <initializer_list>
#include <iostream>

namespace s21 {
template <class T>
class Stack {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;

  Stack();
  Stack(std::initializer_list<value_type> const& items);
  Stack(const Stack& s);
  Stack(Stack&& s);

  const_reference top();

  bool empty();
  size_type size();

  void push(const_reference value);
  void pop();
  void swap(Stack& other);

  Stack<T>& operator=(Stack&& s);
  ~Stack();

 private:
  struct Node {
    T value;
    Node* next = nullptr;
    Node* prev = nullptr;
  };

  Node* head;
  Node* tail;
  size_t stack_size;

  void Free();
};

template <typename T>
s21::Stack<T>::Stack() : head(nullptr), tail(nullptr), stack_size(0) {}

template <typename T>
s21::Stack<T>::Stack(std::initializer_list<value_type> const& items)
    : stack_size(0) {
  for (auto it = items.begin(); it != items.end(); it++) {
    push(*it);
  }
}

template <typename T>
s21::Stack<T>::Stack(const Stack& s) : stack_size(0) {
  size_t i = 0;
  for (Node* node = s.tail; i < s.stack_size; i++, node = node->prev) {
    push(node->value);
  }
}

template <typename T>
s21::Stack<T>::Stack(Stack&& s) : stack_size(0) {
  std::swap(stack_size, s.stack_size);
  std::swap(head, s.head);
  std::swap(tail, s.tail);
}

template <typename T>
typename s21::Stack<T>::const_reference s21::Stack<T>::top() {
  return head->value;
}

template <typename T>
bool s21::Stack<T>::empty() {
  return size() == 0;
}

template <typename T>
typename s21::Stack<T>::size_type s21::Stack<T>::size() {
  return stack_size;
}

template <typename T>
void s21::Stack<T>::push(s21::Stack<T>::const_reference value) {
  Node* new_node = new Node;
  new_node->value = value;

  if (empty()) {
    tail = new_node;
    head = new_node;
  } else {
    new_node->next = head;
    head->prev = new_node;
    head = new_node;
  }

  stack_size++;
}

template <typename T>
void s21::Stack<T>::pop() {
  if (empty()) {
    return;
  }

  if (size() == 1) {
    delete head;
    head = nullptr;
    tail = nullptr;
  } else {
    Node* temp_head = head;
    head = head->next;
    head->prev = nullptr;
    delete temp_head;
  }

  stack_size--;
}

template <typename T>
void s21::Stack<T>::swap(Stack& other) {
  Stack temp(*this);
  *this = std::move(other);
  other.Free();
  size_t i = 0;
  for (Node* node = temp.tail; i < temp.stack_size; i++, node = node->prev) {
    other.push(node->value);
  }
}

template <typename T>
s21::Stack<T>& s21::Stack<T>::operator=(Stack&& s) {
  std::swap(stack_size, s.stack_size);
  std::swap(head, s.head);
  std::swap(tail, s.tail);

  return *this;
}

template <typename T>
void s21::Stack<T>::Free() {
  while (!empty()) {
    pop();
  }
}

template <typename T>
s21::Stack<T>::~Stack() {
  Free();
}

};  // namespace s21

#endif