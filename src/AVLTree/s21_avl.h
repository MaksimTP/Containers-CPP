#ifndef S21_AVL_H
#define S21_AVL_H

#include <iostream>

template <class Key, class Value>
class s21_AVLTree {
 protected:
  struct Node;

 public:
  class Iterator;
  class ConstIterator;

  using key_type = Key;
  using value_type = Value;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = Iterator;
  using const_iterator = ConstIterator;
  using size_type = size_t;

  class Iterator {
   public:
    Iterator();
    Iterator(Node* node, Node* past_node = nullptr);
    iterator& operator++();
    iterator operator++(int);
    iterator& operator--();
    iterator operator--(int);
    reference operator*();
    bool operator==(const iterator& it);
    friend class s21_AVLTree<Key, Value>;
    bool operator!=(const iterator& it);

   protected:
    Node* iter_node_;
    Node* iter_past_node_;
    Node* MoveForward(Node* node);
    Node* MoveBack(Node* node);
  };

  class ConstIterator : public Iterator {
   public:
    ConstIterator() : Iterator(){};
    const_reference operator*() const { return Iterator::operator*(); }
  };

  s21_AVLTree();
  s21_AVLTree(const s21_AVLTree& other);
  s21_AVLTree(s21_AVLTree&& other) noexcept;
  ~s21_AVLTree();
  s21_AVLTree& operator=(s21_AVLTree&& other) noexcept;
  s21_AVLTree& operator=(const s21_AVLTree& other);
  iterator begin();
  iterator end();
  bool empty();
  size_type size();
  size_type max_size();
  void clear();
  std::pair<iterator, bool> insert(const Key& key);
  void erase(iterator pos);
  void swap(s21_AVLTree& other);
  void merge(s21_AVLTree& other);
  bool contains(const Key& key);

 protected:
  iterator Find(const Key& key);
  struct Node {
    Node(Key key, value_type value);
    Node(Key key, value_type value, Node* parent);
    Key key_;
    value_type value_;
    Node* left_ = nullptr;
    Node* right_ = nullptr;
    Node* parent_ = nullptr;
    int height_ = 0;
    friend class s21_AVLTree<Key, Value>;
    ;
  };

  Node* root_;

  void FreeNode(Node* node);
  Node* CopyTree(Node* node, Node* parent);
  void SwapValue(Node* a, Node* b);
  void RightRotate(Node* node);
  void LeftRotate(Node* node);
  void Balance(Node* node);
  int GetBalance(Node* node);
  int GetHeight(Node* node);
  void SetHeight(Node* node);
  static Node* GetMin(Node* node);
  static Node* GetMax(Node* node);
  bool RecursiveInsert(Node* node, const Key& key, Value value);
  Node* RecursiveDelete(Node* node, Key key);
  size_t RecursiveSize(Node* node);
  Node* RecursiveFind(Node* node, const Key& key);
};

#include <sys/types.h>

#include <limits>

template <class Key, class Value>
s21_AVLTree<Key, Value>::s21_AVLTree() : root_(nullptr) {}

template <class Key, class Value>
s21_AVLTree<Key, Value>::s21_AVLTree(const s21_AVLTree &other)
    : root_(CopyTree(other.root_, nullptr)) {}

template <class Key, class Value>
s21_AVLTree<Key, Value>::s21_AVLTree(s21_AVLTree &&other) noexcept {
  std::swap(root_, other.root_);
}

template <class Key, class Value>
s21_AVLTree<Key, Value>::~s21_AVLTree() {
  clear();
}

template <class Key, class Value>
s21_AVLTree<Key, Value> &s21_AVLTree<Key, Value>::operator=(
    s21_AVLTree &&other) noexcept {
  if (this != &other) {
    std::swap(root_, other.root_);
  }
  return *this;
}

template <class Key, class Value>
s21_AVLTree<Key, Value> &s21_AVLTree<Key, Value>::operator=(
    const s21_AVLTree &other) {
  if (this != &other) {
    s21_AVLTree temp(other);
    FreeNode(root_);
    *this = std::move(temp);
  }
  return *this;
}

template <class Key, class Value>
typename s21_AVLTree<Key, Value>::Iterator s21_AVLTree<Key, Value>::begin() {
  return s21_AVLTree::Iterator(GetMin(root_));
}

template <class Key, class Value>
typename s21_AVLTree<Key, Value>::Iterator s21_AVLTree<Key, Value>::end() {
  if (root_ == nullptr) return begin();

  Node *last_node = GetMax(root_);
  Iterator test(nullptr, last_node);
  return test;
}

template <class Key, class Value>
bool s21_AVLTree<Key, Value>::empty() {
  return root_ == nullptr;
}

template <class Key, class Value>
size_t s21_AVLTree<Key, Value>::size() {
  return RecursiveSize(root_);
}

template <class Key, class Value>
size_t s21_AVLTree<Key, Value>::max_size() {
  return std::numeric_limits<size_type>::max() /
         sizeof(typename s21_AVLTree<Key, Value>::Node);
}

template <class Key, class Value>
void s21_AVLTree<Key, Value>::clear() {
  if (root_ != nullptr) FreeNode(root_);
  root_ = nullptr;
}

template <class Key, class Value>
std::pair<typename s21_AVLTree<Key, Value>::Iterator, bool>
s21_AVLTree<Key, Value>::insert(const Key &key) {
  std::pair<Iterator, bool> return_value;
  if (root_ == nullptr) {
    root_ = new Node(key, key);
    return_value.first = Iterator(root_);
    return_value.second = true;
  } else {
    bool check_insert = RecursiveInsert(root_, key, key);
    return_value.first = Find(key);
    return_value.second = check_insert;
  }

  return return_value;
}

template <class Key, class Value>
void s21_AVLTree<Key, Value>::erase(iterator pos) {
  if (root_ == nullptr || pos.iter_node_ == nullptr) return;
  root_ = RecursiveDelete(root_, *pos);
}

template <class Key, class Value>
void s21_AVLTree<Key, Value>::swap(s21_AVLTree &other) {
  std::swap(root_, other.root_);
}

template <class Key, class Value>
void s21_AVLTree<Key, Value>::merge(s21_AVLTree &other) {
  s21_AVLTree const_tree(other);
  Iterator const_it = const_tree.begin();

  for (; const_it != const_tree.end(); ++const_it) {
    std::pair<Iterator, bool> pr = insert(*const_it);
    if (pr.second) other.erase(pr.first);
  }
}

template <class Key, class Value>
typename s21_AVLTree<Key, Value>::iterator s21_AVLTree<Key, Value>::Find(
    const Key &key) {
  Node *exact_node = RecursiveFind(root_, key);
  return Iterator(exact_node);
}

template <class Key, class Value>
bool s21_AVLTree<Key, Value>::contains(const Key &key) {
  Node *contain_node = RecursiveFind(root_, key);
  return !(contain_node == nullptr);
}

template <class Key, class Value>
typename s21_AVLTree<Key, Value>::Node *
s21_AVLTree<Key, Value>::Iterator::MoveForward(s21_AVLTree::Node *node) {
  if (node->right_ != nullptr) {
    return GetMin(node->right_);
  }

  Node *parent = node->parent_;

  while (parent != nullptr && node == parent->right_) {
    node = parent;
    parent = parent->parent_;
  }

  return parent;
}

template <class Key, class Value>
typename s21_AVLTree<Key, Value>::Node *
s21_AVLTree<Key, Value>::Iterator::MoveBack(s21_AVLTree::Node *node) {
  if (node->left_ != nullptr) {
    return GetMax(node->left_);
  }

  Node *parent = node->parent_;

  while (parent != nullptr && node == parent->left_) {
    node = parent;
    parent = node->parent_;
  }

  return parent;
}

template <class Key, class Value>
s21_AVLTree<Key, Value>::Iterator::Iterator()
    : iter_node_(nullptr), iter_past_node_(nullptr) {}

template <class Key, class Value>
s21_AVLTree<Key, Value>::Iterator::Iterator(s21_AVLTree::Node *node,
                                            s21_AVLTree::Node *past_node)
    : iter_node_(node), iter_past_node_(past_node) {}

template <class Key, class Value>
typename s21_AVLTree<Key, Value>::iterator &
s21_AVLTree<Key, Value>::Iterator::operator++() {
  Node *tmp;

  if (iter_node_ != nullptr) {
    tmp = GetMax(iter_node_);
  }

  iter_node_ = MoveForward(iter_node_);

  if (iter_node_ == nullptr) {
    iter_past_node_ = tmp;
  }

  return *this;
}

template <class Key, class Value>
typename s21_AVLTree<Key, Value>::iterator
s21_AVLTree<Key, Value>::Iterator::operator++(int) {
  Iterator temp = *this;
  operator++();
  return temp;
}

template <class Key, class Value>
typename s21_AVLTree<Key, Value>::iterator &
s21_AVLTree<Key, Value>::Iterator::operator--() {
  if (iter_node_ == nullptr && iter_past_node_ != nullptr) {
    *this = iter_past_node_;
    return *this;
  }

  iter_node_ = MoveBack(iter_node_);

  return *this;
}

template <class Key, class Value>
typename s21_AVLTree<Key, Value>::iterator
s21_AVLTree<Key, Value>::Iterator::operator--(int) {
  Iterator temp = *this;
  operator--();
  return temp;
}

template <class Key, class Value>
Value &s21_AVLTree<Key, Value>::Iterator::operator*() {
  if (iter_node_ == nullptr) {
    static Value fake_value{};
    return fake_value;
  }
  return iter_node_->key_;
}

template <class Key, class Value>
bool s21_AVLTree<Key, Value>::Iterator::operator==(
    const s21_AVLTree::iterator &it) {
  return iter_node_ == it.iter_node_;
}

template <class Key, class Value>
bool s21_AVLTree<Key, Value>::Iterator::operator!=(
    const s21_AVLTree::iterator &it) {
  return !operator==(it);
}

template <class Key, class Value>
s21_AVLTree<Key, Value>::Node::Node(Key key, value_type value)
    : key_(key), value_(value) {}

template <class Key, class Value>
s21_AVLTree<Key, Value>::Node::Node(Key key, value_type value, Node *node)
    : key_(key), value_(value), parent_(node) {}

template <class Key, class Value>
typename s21_AVLTree<Key, Value>::Node *s21_AVLTree<Key, Value>::CopyTree(
    s21_AVLTree::Node *node, s21_AVLTree::Node *parent) {
  if (node == nullptr) return nullptr;

  Node *new_node = new Node(node->key_, node->value_, parent);
  new_node->left_ = CopyTree(node->left_, new_node);
  new_node->right_ = CopyTree(node->right_, new_node);
  return new_node;
}

template <class Key, class Value>
void s21_AVLTree<Key, Value>::FreeNode(Node *node) {
  if (node == nullptr) return;
  FreeNode(node->left_);
  FreeNode(node->right_);
  delete node;
}

template <class Key, class Value>
int s21_AVLTree<Key, Value>::GetHeight(s21_AVLTree::Node *node) {
  return node == nullptr ? -1 : node->height_;
}

template <class Key, class Value>
int s21_AVLTree<Key, Value>::GetBalance(s21_AVLTree::Node *node) {
  return node == nullptr ? 0 : GetHeight(node->right_) - GetHeight(node->left_);
}

template <class Key, class Value>
void s21_AVLTree<Key, Value>::SetHeight(s21_AVLTree::Node *node) {
  node->height_ = std::max(GetHeight(node->left_), GetHeight(node->right_) + 1);
}

template <class Key, class Value>
void s21_AVLTree<Key, Value>::SwapValue(s21_AVLTree::Node *a,
                                        s21_AVLTree::Node *b) {
  std::swap(a->key_, b->key_);
  std::swap(a->value_, b->value_);
}

template <typename Key, typename Value>
void s21_AVLTree<Key, Value>::RightRotate(s21_AVLTree::Node *node) {
  Node *new_left = node->left_->left_;
  Node *new_right_right = node->right_;
  Node *new_right_left = node->left_->right_;

  SwapValue(node, node->left_);
  node->right_ = node->left_;

  node->left_ = new_left;
  if (node->left_) {
    node->left_->parent_ = node;
  }

  node->right_->left_ = new_right_left;
  if (node->right_->left_) {
    node->right_->left_->parent_ = node->right_;
  }

  node->right_->right_ = new_right_right;
  if (node->right_->right_) {
    node->right_->right_->parent_ = node->right_;
  }

  SetHeight(node->right_);
  SetHeight(node);
}

template <typename Key, typename Value>
void s21_AVLTree<Key, Value>::LeftRotate(s21_AVLTree::Node *node) {
  Node *new_right = node->right_->right_;
  Node *new_left_left = node->left_;
  Node *new_left_right = node->right_->left_;

  SwapValue(node, node->right_);
  node->left_ = node->right_;

  node->right_ = new_right;
  if (node->right_) {
    node->right_->parent_ = node;
  }

  node->left_->right_ = new_left_right;
  if (node->left_->right_) {
    node->left_->right_->parent_ = node->left_;
  }

  node->left_->left_ = new_left_left;
  if (node->left_->left_) {
    node->left_->left_->parent_ = node->left_;
  }

  SetHeight(node->left_);
  SetHeight(node);
}

template <typename Key, typename Value>
void s21_AVLTree<Key, Value>::Balance(
    Node *node) {  // правила балансировки чтобы понять какой вид поворота нужен
  int balance = GetBalance(node);
  if (balance == -2) {
    if (GetBalance(node->left_) == 1) LeftRotate(node->left_);
    RightRotate(node);
  } else if (balance == 2) {
    if (GetBalance(node->right_) == -1) RightRotate(node->right_);
    LeftRotate(node);
  }
}

// MIN AND MAX IN TREE

template <typename Key, typename Value>
typename s21_AVLTree<Key, Value>::Node *s21_AVLTree<Key, Value>::GetMin(
    s21_AVLTree::Node *node) {
  if (node == nullptr) return nullptr;
  if (node->left_ == nullptr) return node;
  return GetMin(node->left_);
}

template <typename Key, typename Value>
typename s21_AVLTree<Key, Value>::Node *s21_AVLTree<Key, Value>::GetMax(
    s21_AVLTree::Node *node) {
  if (node == nullptr) return nullptr;
  if (node->right_ == nullptr) return node;
  return GetMax(node->right_);
}

// RECURSIVE SUPPORT FUNCTIONS

template <typename Key, typename Value>
size_t s21_AVLTree<Key, Value>::RecursiveSize(s21_AVLTree::Node *node) {
  if (node == nullptr) return 0;
  size_t left_size = RecursiveSize(node->left_);
  size_t right_size = RecursiveSize(node->right_);
  return 1 + left_size + right_size;
}

template <typename Key, typename Value>
bool s21_AVLTree<Key, Value>::RecursiveInsert(
    s21_AVLTree::Node *node, const Key &key,
    Value value) {  // Рекурсивная вставка в дерево с добавленной логикой
                    // понимания произошла ли вставка на самом деле, возвращает
                    // также указатель на ноду
  bool check_insert = false;
  if (key < node->key_) {
    if (node->left_ == nullptr) {
      node->left_ = new Node(key, value, node);
      check_insert = true;
    } else {
      check_insert = RecursiveInsert(node->left_, key, value);
    }
  } else if (key > node->key_) {
    if (node->right_ == nullptr) {
      node->right_ = new Node(key, value, node);
      check_insert = true;
    } else {
      check_insert = RecursiveInsert(node->right_, key, value);
    }
  } else if (key == node->key_) {
    return check_insert;  // инсерт не произошел потому что такой ключ был в
                          // дереве
  }
  SetHeight(node);
  Balance(node);
  return check_insert;
}

template <typename Key, typename Value>
typename s21_AVLTree<Key, Value>::Node *
s21_AVLTree<Key, Value>::RecursiveDelete(s21_AVLTree::Node *node, Key key) {
  if (node == nullptr) return nullptr;
  if (key < node->key_) {
    node->left_ = RecursiveDelete(node->left_, key);
  } else if (key > node->key_) {
    node->right_ = RecursiveDelete(node->right_, key);
  } else {
    if (node->left_ == nullptr || node->right_ == nullptr) {
      Node *node_right = node->right_;
      Node *node_left = node->left_;
      Node *node_parent = node->parent_;
      delete node;
      if (node_left == nullptr) {
        node = node_right;
      } else {
        node = node_left;
      }
      if (node != nullptr) node->parent_ = node_parent;
    } else {
      Node *min_in_right = GetMin(node->right_);
      node->key_ = min_in_right->key_;
      node->value_ = min_in_right->value_;
      node->right_ = RecursiveDelete(node->right_, min_in_right->key_);
    }
  }
  if (node != nullptr) {
    SetHeight(node);
    Balance(node);
  }
  return node;
}

template <typename Key, typename Value>
typename s21_AVLTree<Key, Value>::Node *s21_AVLTree<Key, Value>::RecursiveFind(
    s21_AVLTree::Node *node, const Key &key) {
  if (node == nullptr || node->key_ == key) return node;
  if (key > node->key_) {
    return RecursiveFind(node->right_, key);
  } else {
    return RecursiveFind(node->left_, key);
  }
}

#endif  // S21_AVL_H