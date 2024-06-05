#include <gtest/gtest.h>

#include <set>

#include "../s21_containerplus.h"

TEST(OPERATOR, case1) {
  s21::multiset<int> Mymultiset1{1, 2, 3};
  s21::multiset<int> Mymultiset2{4, 5, 6};
  std::multiset<int> multiset1{1, 2, 3};
  std::multiset<int> multiset2{4, 5, 6};
  Mymultiset1 = Mymultiset2;
  multiset1 = multiset2;
  EXPECT_EQ(*Mymultiset1.begin(), *multiset1.begin());
  EXPECT_EQ(*Mymultiset2.begin(), *multiset2.begin());
}

TEST(BEGIN, case1) {
  s21::multiset<int> Mymultiset{5, 4, 6};
  EXPECT_EQ(*Mymultiset.begin(), 4);
}

TEST(BEGIN, case2) {
  s21::multiset<int> Mymultiset{4, 5, 6};
  EXPECT_EQ(*Mymultiset.begin(), 4);
}

TEST(BEGIN, case3) {
  s21::multiset<char> Mymultiset{'a', 'b', 'c'};
  EXPECT_EQ(*Mymultiset.begin(), 'a');
}

TEST(BEGIN, case4) {
  s21::multiset<char> Mymultiset{'c', 'b', 'a'};
  EXPECT_EQ(*Mymultiset.begin(), 'a');
}

TEST(BEGIN, case5) {
  s21::multiset<double> Mymultiset{1.2, 1.4111111, 1.1};
  EXPECT_EQ(*Mymultiset.begin(), 1.1);
}

TEST(EMPTY, case1) {
  s21::multiset<int> Mymultiset{1, 2, 3};
  std::multiset<int> multiset{1, 2, 3};
  EXPECT_EQ(Mymultiset.empty(), multiset.empty());
}

TEST(EMPTY, case2) {
  s21::multiset<int> Mymultiset{};
  std::multiset<int> multiset{};
  EXPECT_EQ(Mymultiset.empty(), multiset.empty());
}

TEST(EMPTY, case3) {
  s21::multiset<int> Mymultiset{0};
  std::multiset<int> multiset{0};
  EXPECT_EQ(Mymultiset.empty(), multiset.empty());
}

TEST(SIZE, case1) {
  s21::multiset<int> Mymultiset{1, 2, 3, 4};
  std::multiset<int> multiset{1, 2, 3, 4};
  EXPECT_EQ(Mymultiset.size(), multiset.size());
}

TEST(SIZE, case2) {
  s21::multiset<int> Mymultiset{};
  std::multiset<int> multiset{};
  EXPECT_EQ(Mymultiset.size(), multiset.size());
}

TEST(SIZE, case3) {
  s21::multiset<int> Mymultiset{-1};
  std::multiset<int> multiset{-1};
  EXPECT_EQ(Mymultiset.size(), multiset.size());
}

TEST(SIZE, case4) {
  s21::multiset<int> Mymultiset{1, 2, 3};
  std::multiset<int> multiset{-1, -2, -3, -4};
  EXPECT_NE(Mymultiset.size(), multiset.size());
}

TEST(CLEAR, case1) {
  s21::multiset<int> Mymultiset{1, 2, 3};
  EXPECT_EQ(Mymultiset.empty(), 0);
}

TEST(CLEAR, case2) {
  s21::multiset<int> Mymultiset;
  EXPECT_EQ(Mymultiset.empty(), 1);
}

TEST(INSERT, case1) {
  s21::multiset<int> Mymultiset{1};
  EXPECT_TRUE(*Mymultiset.insert(1));
  EXPECT_TRUE(Mymultiset.contains(1));

  EXPECT_FALSE(Mymultiset.contains(1123));
  EXPECT_TRUE(*Mymultiset.insert(1123));
  EXPECT_TRUE(Mymultiset.contains(1123));
}

TEST(INSERT, case2) {
  s21::multiset<double> Mymultiset{1.1};
  EXPECT_TRUE(*Mymultiset.insert(1.1));
  EXPECT_TRUE(Mymultiset.contains(1.1));
  EXPECT_FALSE(Mymultiset.contains(1.0000001));
  EXPECT_TRUE(*Mymultiset.insert(1.0000001));
  EXPECT_TRUE(Mymultiset.contains(1.0000001));
  EXPECT_FALSE(Mymultiset.contains(821.23));
  EXPECT_TRUE(*Mymultiset.insert(821.23));
  EXPECT_TRUE(Mymultiset.contains(821.23));
  EXPECT_FALSE(Mymultiset.contains(111.267123));
  EXPECT_TRUE(*Mymultiset.insert(111.267123));
  EXPECT_TRUE(Mymultiset.contains(111.267123));
  EXPECT_TRUE(*Mymultiset.insert(111.267123));
  EXPECT_TRUE(Mymultiset.contains(111.267123));
}

TEST(INSERT, case3) {
  s21::multiset<char> Mymultiset{'H'};
  EXPECT_TRUE(*Mymultiset.insert('O'));
  EXPECT_TRUE(Mymultiset.contains('O'));
  EXPECT_TRUE(*Mymultiset.insert('L'));
  EXPECT_TRUE(Mymultiset.contains('L'));
  EXPECT_TRUE(*Mymultiset.insert('A'));
  EXPECT_TRUE(Mymultiset.contains('A'));
  EXPECT_TRUE(*Mymultiset.insert('H'));
  EXPECT_TRUE(Mymultiset.contains('H'));
  EXPECT_TRUE(*Mymultiset.insert('I'));
  EXPECT_TRUE(Mymultiset.contains('I'));
}

TEST(INSERT, case4) {
  s21::multiset<std::string> Mymultiset{"Hello"};
  EXPECT_EQ(*Mymultiset.insert("World"), "World");
  EXPECT_TRUE(Mymultiset.contains("World"));
  EXPECT_EQ(*Mymultiset.insert("!"), "!");
  EXPECT_TRUE(Mymultiset.contains("!"));
}

TEST(ERASE, case1) {
  s21::multiset<int> Mymultiset{1, 2, 3};
  int value1 = 4;
  int value2 = 5;
  int value3 = 6;
  Mymultiset.insert(value1);
  Mymultiset.insert(value2);
  Mymultiset.insert(value3);
  if (auto iter = Mymultiset.find(5); iter != Mymultiset.end())
    Mymultiset.erase(iter);
  EXPECT_TRUE(Mymultiset.contains(value1));
  EXPECT_FALSE(Mymultiset.contains(value2));
  EXPECT_TRUE(Mymultiset.contains(value3));
}

TEST(ERASE, case2) {
  s21::multiset<int> Mymultiset{1, 2, 3};
  Mymultiset.erase(3);
  EXPECT_FALSE(Mymultiset.contains(3));
}

TEST(ERASE, case3) {
  s21::multiset<int> Mymultiset{1, 2, 3};
  Mymultiset.erase(5);
  EXPECT_TRUE(Mymultiset.contains(1));
  EXPECT_TRUE(Mymultiset.contains(2));
  EXPECT_TRUE(Mymultiset.contains(3));
}

TEST(ERASE, case4) {
  s21::multiset<char> Mymultiset{'a', 'b', 'c'};
  Mymultiset.erase('c');
  EXPECT_TRUE(Mymultiset.contains('a'));
  EXPECT_TRUE(Mymultiset.contains('b'));
  EXPECT_FALSE(Mymultiset.contains('c'));
}

TEST(SWAP, case1) {
  s21::multiset<int> Mymultiset1{1, 2, 3};
  s21::multiset<int> Mymultiset2{4, 5, 6};
  Mymultiset1.swap(Mymultiset2);
  EXPECT_TRUE(Mymultiset1.contains(4));
  EXPECT_TRUE(Mymultiset1.contains(5));
  EXPECT_TRUE(Mymultiset1.contains(6));
  EXPECT_TRUE(Mymultiset2.contains(1));
  EXPECT_TRUE(Mymultiset2.contains(2));
  EXPECT_TRUE(Mymultiset2.contains(3));
}

TEST(SWAP, case2) {
  s21::multiset<char> Mymultiset1{'a', 'b', 'c'};
  s21::multiset<char> Mymultiset2{'d', 'f', 'e'};
  Mymultiset1.swap(Mymultiset2);
  EXPECT_TRUE(Mymultiset1.contains('d'));
  EXPECT_TRUE(Mymultiset1.contains('f'));
  EXPECT_TRUE(Mymultiset1.contains('e'));
  EXPECT_TRUE(Mymultiset2.contains('a'));
  EXPECT_TRUE(Mymultiset2.contains('b'));
  EXPECT_TRUE(Mymultiset2.contains('c'));
}

TEST(SWAP, case3) {
  s21::multiset<std::string> Mymultiset1{"hello", "World"};
  s21::multiset<std::string> Mymultiset2{"peer", "to", "peer"};
  Mymultiset1.swap(Mymultiset2);
  EXPECT_TRUE(Mymultiset1.contains("peer"));
  EXPECT_TRUE(Mymultiset1.contains("to"));
  EXPECT_TRUE(Mymultiset2.contains("hello"));
  EXPECT_TRUE(Mymultiset2.contains("World"));
}

TEST(MERGE, case1) {
  s21::multiset<int> Mymultiset1{1, 2, 3};
  s21::multiset<int> Mymultiset2{4, 5, 6};
  Mymultiset1.merge(Mymultiset2);
  EXPECT_TRUE(Mymultiset1.contains(1));
  EXPECT_TRUE(Mymultiset1.contains(2));
  EXPECT_TRUE(Mymultiset1.contains(3));
  EXPECT_TRUE(Mymultiset1.contains(4));
  EXPECT_TRUE(Mymultiset1.contains(5));
  EXPECT_TRUE(Mymultiset1.contains(6));
}

TEST(MERGE, case2) {
  s21::multiset<char> Mymultiset1{'a', 'b', 'c'};
  s21::multiset<char> Mymultiset2{'d', 'f', 'e'};
  Mymultiset1.merge(Mymultiset2);
  EXPECT_TRUE(Mymultiset1.contains('a'));
  EXPECT_TRUE(Mymultiset1.contains('b'));
  EXPECT_TRUE(Mymultiset1.contains('c'));
  EXPECT_TRUE(Mymultiset1.contains('d'));
  EXPECT_TRUE(Mymultiset1.contains('f'));
  EXPECT_TRUE(Mymultiset1.contains('e'));
}

TEST(MERGE, case3) {
  s21::multiset<std::string> Mymultiset1{"Hello"};
  s21::multiset<std::string> Mymultiset2{"World"};
  Mymultiset1.merge(Mymultiset2);
  EXPECT_TRUE(Mymultiset1.contains("Hello"));
  EXPECT_TRUE(Mymultiset1.contains("World"));
}

TEST(FIND, case1) {
  s21::multiset<int> Mymultiset1{123, 213, 312};
  auto iter = Mymultiset1.find(123);
  EXPECT_EQ(*iter, 123);
}

TEST(FIND, case2) {
  s21::multiset<int> Mymultiset1{123, 213, 312};
  auto iter = Mymultiset1.find(213);
  EXPECT_EQ(*iter, 213);
}

TEST(FIND, case3) {
  s21::multiset<char> Mymultiset1{'a', 'b', 'c'};
  auto iter = Mymultiset1.find('b');
  EXPECT_EQ(*iter, 'b');
}

TEST(COUNT, case1) {
  s21::multiset<int> Mymultiset{1, 1, 1, 2, 2, 2, 2, 3, 5, 5, 55};
  EXPECT_EQ(Mymultiset.count(1), 3);
  EXPECT_EQ(Mymultiset.count(2), 4);
  EXPECT_EQ(Mymultiset.count(3), 1);
  EXPECT_EQ(Mymultiset.count(55), 1);
}

TEST(COUNT, case2) {
  s21::multiset<double> Mymultiset{1.1,  1.1,  1.2, 2.45, 2.45, 2.45,
                                   2.44, 3.21, 5.5, 5.5,  55};
  EXPECT_EQ(Mymultiset.count(1.1), 2);
  EXPECT_EQ(Mymultiset.count(2.45), 3);
  EXPECT_EQ(Mymultiset.count(3.21), 1);
  EXPECT_EQ(Mymultiset.count(5.5), 2);
}

TEST(COUNT, case3) {
  s21::multiset<char> Mymultiset{'a', 'b', 'c', 'c', 'a', 'a', 'd', 'd'};
  EXPECT_EQ(Mymultiset.count('a'), 3);
  EXPECT_EQ(Mymultiset.count('b'), 1);
  EXPECT_EQ(Mymultiset.count('c'), 2);
  EXPECT_EQ(Mymultiset.count('d'), 2);
}

TEST(CONTAINS, case1) {
  s21::multiset<int> Mymultiset1{123, 213, 312};
  EXPECT_FALSE(Mymultiset1.contains(1));
  EXPECT_FALSE(Mymultiset1.contains(2));
  EXPECT_FALSE(Mymultiset1.contains(3));
  EXPECT_TRUE(Mymultiset1.contains(213));
}

TEST(EQUAL_RANGE, case1) {
  s21::multiset<int> Mymultiset{1, 2, 2, 3, 3, 3, 4, 4, 4, 4};
  auto range = Mymultiset.equal_range(3);
  for (auto it = range.first; it != range.second; ++it) {
    EXPECT_EQ(*it, 3);
  }
}

TEST(EQUAL_RANGE, case2) {
  s21::multiset<int> Mymultiset{1, 2, 2, 3, 3, 3, 4, 4, 4, 4};
  auto range = Mymultiset.equal_range(4);
  for (auto it = range.first; it != range.second; ++it) {
    EXPECT_EQ(*it, 4);
  }
}

TEST(UPPER_BOUND, case1) {
  s21::multiset<int> Mymultiset{1, 2, 2, 3, 3, 3, 4, 4, 4, 4};
  auto it = Mymultiset.upper_bound(2);
  EXPECT_EQ(*it, 3);
}

TEST(UPPER_BOUND, case2) {
  s21::multiset<int> Mymultiset{1, 1, 1, 1, 4, 4, 4, 4};
  auto it = Mymultiset.upper_bound(1);
  EXPECT_EQ(*it, 4);
}

TEST(UPPER_BOUND, case3) {
  s21::multiset<char> Mymultiset{'a', 'd', 'e', 'z'};
  auto it = Mymultiset.upper_bound('a');
  EXPECT_EQ(*it, 'd');
}

TEST(UPPER_BOUND, case4) {
  s21::multiset<char> Mymultiset{'a', 'b', 'd', 'e', 'z'};
  auto it = Mymultiset.upper_bound('d');
  EXPECT_EQ(*it, 'e');
}

TEST(LOWER_BOUND, case1) {
  s21::multiset<int> Mymultiset{1, 2, 2, 3, 3, 3, 4, 4, 4, 4};
  auto it = Mymultiset.lower_bound(4);
  EXPECT_EQ(*it, 4);
}

TEST(LOWER_BOUND, case2) {
  s21::multiset<int> Mymultiset{1, 1, 1, 1, 4, 4, 4, 4};
  auto it = Mymultiset.lower_bound(4);
  EXPECT_EQ(*it, 4);
}

TEST(LOWER_BOUND, case3) {
  s21::multiset<char> Mymultiset{'a', 'd', 'e', 'z'};
  auto it = Mymultiset.lower_bound('d');
  EXPECT_EQ(*it, 'd');
}

TEST(LOWER_BOUND, case4) {
  s21::multiset<char> Mymultiset{'a', 'b', 'd', 'e', 'z'};
  auto it = Mymultiset.lower_bound('d');
  EXPECT_EQ(*it, 'd');
}

TEST(INSERT_MANY, case1) {
  s21::multiset<int> Mymultiset{1, 1, 1, 1, 4, 4, 4, 4};
  Mymultiset.insert_many(4, 8, 8, 8, 2, 4);
  EXPECT_TRUE(Mymultiset.contains(8));
  EXPECT_TRUE(Mymultiset.contains(2));
}

TEST(INSERT_MANY, case2) {
  s21::multiset<double> Mymultiset{1.1, 1.2, 1.3, 1.4, 4.5, 4.6, 4.7, 4.8};
  Mymultiset.insert_many(4.9, 8.1, 8.2, 8.3, 2.4, 4.1);
  EXPECT_TRUE(Mymultiset.contains(4.9));
  EXPECT_TRUE(Mymultiset.contains(8.1));
  EXPECT_TRUE(Mymultiset.contains(8.2));
  EXPECT_TRUE(Mymultiset.contains(8.3));
  EXPECT_TRUE(Mymultiset.contains(2.4));
  EXPECT_TRUE(Mymultiset.contains(4.1));
}

TEST(INSERT_MANY, case3) {
  s21::multiset<char> Mymultiset{'a', 'b', 'c'};
  Mymultiset.insert_many('d', 'e', 'f');
  EXPECT_TRUE(Mymultiset.contains('d'));
  EXPECT_TRUE(Mymultiset.contains('e'));
  EXPECT_TRUE(Mymultiset.contains('f'));
}
