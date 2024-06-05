#include <gtest/gtest.h>

#include <set>

#include "../s21_container.h"

TEST(OPERATOR, Set1) {
  s21::set<int> MySet1{1, 2, 3};
  s21::set<int> MySet2{4, 5, 6};
  std::set<int> Set1{1, 2, 3};
  std::set<int> Set2{4, 5, 6};
  MySet1 = MySet2;
  Set1 = Set2;
  EXPECT_EQ(*MySet1.begin(), *Set1.begin());
  EXPECT_EQ(*MySet2.begin(), *Set2.begin());
}

TEST(BEGIN, Set2) {
  s21::set<int> MySet{5, 4, 6};
  EXPECT_EQ(*MySet.begin(), 4);
}

TEST(BEGIN, Set3) {
  s21::set<int> MySet{4, 5, 6};
  EXPECT_EQ(*MySet.begin(), 4);
}

TEST(BEGIN, Set4) {
  s21::set<char> MySet{'a', 'b', 'c'};
  EXPECT_EQ(*MySet.begin(), 'a');
}

TEST(BEGIN, Set5) {
  s21::set<char> MySet{'c', 'b', 'a'};
  EXPECT_EQ(*MySet.begin(), 'a');
}

TEST(BEGIN, Set6) {
  s21::set<double> MySet{1.2, 1.4111111, 1.1};
  EXPECT_EQ(*MySet.begin(), 1.1);
}

TEST(EMPTY, Set7) {
  s21::set<int> MySet{1, 2, 3};
  std::set<int> Set{1, 2, 3};
  EXPECT_EQ(MySet.empty(), Set.empty());
}

TEST(EMPTY, Set8) {
  s21::set<int> MySet{};
  std::set<int> Set{};
  EXPECT_EQ(MySet.empty(), Set.empty());
}

TEST(EMPTY, Set9) {
  s21::set<int> MySet{0};
  std::set<int> Set{0};
  EXPECT_EQ(MySet.empty(), Set.empty());
}

TEST(SIZE, Set10) {
  s21::set<int> MySet{1, 2, 3, 4};
  std::set<int> Set{1, 2, 3, 4};
  EXPECT_EQ(MySet.size(), Set.size());
}

TEST(SIZE, Set11) {
  s21::set<int> MySet{};
  std::set<int> Set{};
  EXPECT_EQ(MySet.size(), Set.size());
}

TEST(SIZE, Set12) {
  s21::set<int> MySet{-1};
  std::set<int> Set{-1};
  EXPECT_EQ(MySet.size(), Set.size());
}

TEST(CLEAR, Set13) {
  s21::set<int> MySet{1, 2, 3};
  EXPECT_EQ(MySet.empty(), 0);
}

TEST(CLEAR, Set14) {
  s21::set<int> MySet;
  EXPECT_EQ(MySet.empty(), 1);
}

TEST(INSERT, Set15) {
  s21::set<int> s21_set{1};

  std::pair<s21::set<int>::iterator, bool> insert1 = s21_set.insert(9);
  EXPECT_EQ(*insert1.first, 9);
  EXPECT_EQ(insert1.second, true);

  std::pair<s21::set<int>::iterator, bool> insert2 = s21_set.insert(9);
  std::pair<s21::set<int>::iterator, bool> insert3 = s21_set.insert(9);
  EXPECT_EQ(insert2.second, 0);
  EXPECT_EQ(insert3.second, false);

  std::pair<s21::set<int>::iterator, bool> insert4 = s21_set.insert(23);
  EXPECT_EQ(*insert4.first, 23);
  EXPECT_EQ(insert4.second, true);

  std::pair<s21::set<int>::iterator, bool> insert5 = s21_set.insert(98);
  EXPECT_EQ(*insert5.first, 98);
  EXPECT_EQ(insert5.second, true);
}

TEST(INSERT, Set16) {
  s21::set<double> s21_set;

  std::pair<s21::set<double>::iterator, bool> insert1 = s21_set.insert(1.4);
  EXPECT_EQ(*insert1.first, 1.4);
  EXPECT_EQ(insert1.second, true);

  std::pair<s21::set<double>::iterator, bool> insert2 = s21_set.insert(2.77);
  EXPECT_EQ(*insert2.first, 2.77);
  EXPECT_EQ(insert2.second, true);

  std::pair<s21::set<double>::iterator, bool> insert3 = s21_set.insert(3.9);
  EXPECT_EQ(*insert3.first, 3.9);
  EXPECT_EQ(insert3.second, true);

  std::pair<s21::set<double>::iterator, bool> insert4 = s21_set.insert(2.77);
  std::pair<s21::set<double>::iterator, bool> insert5 = s21_set.insert(3.9);
  EXPECT_EQ(insert4.second, false);
  EXPECT_EQ(insert5.second, false);
}

TEST(INSERT, Set17) {
  s21::set<std::string> s21_set;

  std::pair<s21::set<std::string>::iterator, bool> insert1 =
      s21_set.insert("hello");
  EXPECT_EQ(*insert1.first, "hello");
  EXPECT_EQ(insert1.second, true);

  std::pair<s21::set<std::string>::iterator, bool> insert2 =
      s21_set.insert("hi");
  EXPECT_EQ(*insert2.first, "hi");
  EXPECT_EQ(insert2.second, true);

  std::pair<s21::set<std::string>::iterator, bool> insert3 =
      s21_set.insert("hi");
  EXPECT_EQ(insert3.second, false);

  std::pair<s21::set<std::string>::iterator, bool> insert4 =
      s21_set.insert("hola");
  EXPECT_EQ(*insert4.first, "hola");
  EXPECT_EQ(insert4.second, true);

  std::pair<s21::set<std::string>::iterator, bool> insert5 =
      s21_set.insert("hello");
  EXPECT_EQ(insert5.second, false);
}

TEST(ERASE, Set18) {
  s21::set<int> MySet{1, 2, 3};
  int value1 = 4;
  int value2 = 5;
  int value3 = 6;
  MySet.insert(value1);
  MySet.insert(value2);
  MySet.insert(value3);
  if (auto iter = MySet.find(5); iter != MySet.end()) MySet.erase(iter);
  EXPECT_TRUE(MySet.contains(value1));
  EXPECT_FALSE(MySet.contains(value2));
  EXPECT_TRUE(MySet.contains(value3));
}

TEST(ERASE, Set19) {
  s21::set<int> MySet{1, 2, 3};
  MySet.erase(3);
  EXPECT_FALSE(MySet.contains(3));
}

TEST(ERASE, Set20) {
  s21::set<int> MySet{1, 2, 3};
  MySet.erase(5);
  EXPECT_TRUE(MySet.contains(1));
  EXPECT_TRUE(MySet.contains(2));
  EXPECT_TRUE(MySet.contains(3));
}

TEST(ERASE, Set21) {
  s21::set<char> MySet{'a', 'b', 'c'};
  MySet.erase('c');
  EXPECT_TRUE(MySet.contains('a'));
  EXPECT_TRUE(MySet.contains('b'));
  EXPECT_FALSE(MySet.contains('c'));
}

TEST(SWAP, Set22) {
  s21::set<int> MySet1{1, 2, 3};
  s21::set<int> MySet2{4, 5, 6};
  MySet1.swap(MySet2);
  EXPECT_TRUE(MySet1.contains(4));
  EXPECT_TRUE(MySet1.contains(5));
  EXPECT_TRUE(MySet1.contains(6));
  EXPECT_TRUE(MySet2.contains(1));
  EXPECT_TRUE(MySet2.contains(2));
  EXPECT_TRUE(MySet2.contains(3));
}

TEST(SWAP, Set23) {
  s21::set<char> MySet1{'a', 'b', 'c'};
  s21::set<char> MySet2{'d', 'f', 'e'};
  MySet1.swap(MySet2);
  EXPECT_TRUE(MySet1.contains('d'));
  EXPECT_TRUE(MySet1.contains('f'));
  EXPECT_TRUE(MySet1.contains('e'));
  EXPECT_TRUE(MySet2.contains('a'));
  EXPECT_TRUE(MySet2.contains('b'));
  EXPECT_TRUE(MySet2.contains('c'));
}

TEST(SWAP, Set24) {
  s21::set<std::string> MySet1{"hello", "World"};
  s21::set<std::string> MySet2{"peer", "to", "peer"};
  MySet1.swap(MySet2);
  EXPECT_TRUE(MySet1.contains("peer"));
  EXPECT_TRUE(MySet1.contains("to"));
  EXPECT_TRUE(MySet2.contains("hello"));
  EXPECT_TRUE(MySet2.contains("World"));
}

TEST(MERGE, Set25) {
  s21::set<int> MySet1{1, 2, 3};
  s21::set<int> MySet2{4, 5, 6};
  MySet1.merge(MySet2);
  EXPECT_TRUE(MySet1.contains(1));
  EXPECT_TRUE(MySet1.contains(2));
  EXPECT_TRUE(MySet1.contains(3));
  EXPECT_TRUE(MySet1.contains(4));
  EXPECT_TRUE(MySet1.contains(5));
  EXPECT_TRUE(MySet1.contains(6));
}

TEST(MERGE, Set26) {
  s21::set<char> MySet1{'a', 'b', 'c'};
  s21::set<char> MySet2{'d', 'f', 'e'};
  MySet1.merge(MySet2);
  EXPECT_TRUE(MySet1.contains('a'));
  EXPECT_TRUE(MySet1.contains('b'));
  EXPECT_TRUE(MySet1.contains('c'));
  EXPECT_TRUE(MySet1.contains('d'));
  EXPECT_TRUE(MySet1.contains('f'));
  EXPECT_TRUE(MySet1.contains('e'));
}

TEST(MERGE, Set27) {
  s21::set<std::string> MySet1{"Hello"};
  s21::set<std::string> MySet2{"World"};
  MySet1.merge(MySet2);
  EXPECT_TRUE(MySet1.contains("Hello"));
  EXPECT_TRUE(MySet1.contains("World"));
}

TEST(FIND, Set28) {
  s21::set<int> MySet1{123, 213, 312};
  auto iter = MySet1.find(123);
  EXPECT_EQ(*iter, 123);
}

TEST(FIND, Set29) {
  s21::set<int> MySet1{123, 213, 312};
  auto iter = MySet1.find(213);
  EXPECT_EQ(*iter, 213);
}

TEST(FIND, Set30) {
  s21::set<char> MySet1{'a', 'b', 'c'};
  auto iter = MySet1.find('b');
  EXPECT_EQ(*iter, 'b');
}

TEST(CONTAINS, Set31) {
  s21::set<int> MySet1{123, 213, 312};
  EXPECT_FALSE(MySet1.contains(1));
  EXPECT_FALSE(MySet1.contains(2));
  EXPECT_FALSE(MySet1.contains(3));
  EXPECT_TRUE(MySet1.contains(213));
}

TEST(INSERT_MANY, Set32) {
  s21::set<int> MySet1{1, 2, 3};
  MySet1.insert_many(4, 5, 6);
  EXPECT_TRUE(MySet1.contains(4));
  EXPECT_TRUE(MySet1.contains(5));
  EXPECT_TRUE(MySet1.contains(6));
}

TEST(INSERT_MANY, Set33) {
  s21::set<double> MySet1{1.1, 2.2, 3.3};
  MySet1.insert_many(1.4, 2.3, 3.34);
  EXPECT_TRUE(MySet1.contains(1.4));
  EXPECT_TRUE(MySet1.contains(2.3));
  EXPECT_TRUE(MySet1.contains(3.34));
}

TEST(INSERT_MANY, Set34) {
  s21::set<char> MySet1{'a', 'b', 'c'};
  MySet1.insert_many('d', 'e', 'f');
  EXPECT_TRUE(MySet1.contains('d'));
  EXPECT_TRUE(MySet1.contains('e'));
  EXPECT_TRUE(MySet1.contains('f'));
}

// g++ set.cc -o test -lgtest -pthread
