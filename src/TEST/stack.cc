#include <gtest/gtest.h>

#include "../s21_container.h"

TEST(ctors, default_ctor) {
  s21::Stack<int> s;
  EXPECT_EQ(s.size(), 0);
}

TEST(ctors, initializer_list) {
  s21::Stack<int> s = {1, 2, 3, 4, 5};
  int arr[] = {5, 4, 3, 2, 1};
  EXPECT_EQ(s.size(), 5);
  for (size_t i = 0; i != s.size() && !s.empty(); i++) {
    EXPECT_EQ(arr[i], s.top());
    s.pop();
  }
}

TEST(ctors, copy_ctor) {
  s21::Stack<double> s = {1.5, 3.0, 4.5};
  s21::Stack<double> x(s);
  EXPECT_EQ(s.size(), x.size());
  for (size_t i = 0; i != s.size() && !s.empty(); i++) {
    EXPECT_DOUBLE_EQ(s.top(), x.top());
    s.pop();
    x.pop();
  }

  EXPECT_EQ(s.size(), x.size());
}

TEST(ctors, move_ctor) {
  s21::Stack<int> s1 = {1, 2, 3, 4};
  s21::Stack<int> s2(std::move(s1));

  EXPECT_EQ(s1.size(), 0);
  EXPECT_EQ(s2.size(), 4);

  int arr[] = {4, 3, 2, 1};

  for (size_t i = 0; i < s2.size(); i++) {
    EXPECT_DOUBLE_EQ(arr[i], s2.top());
    s2.pop();
  }
}

TEST(methods, top) {
  s21::Stack<int> s1 = {1, 2, 3};
  EXPECT_EQ(3, s1.top());

  s21::Stack<double> s2 = {1.5, 3.0, 4.5};
  EXPECT_DOUBLE_EQ(4.5, s2.top());
}

TEST(methods, empty) {
  s21::Stack<int> s1 = {1, 2, 3};
  EXPECT_FALSE(s1.empty());

  s21::Stack<double> s2;
  EXPECT_TRUE(s2.empty());
}

TEST(methods, size) {
  s21::Stack<std::string> s1 = {"Hello", ",", "my", "man"};
  EXPECT_EQ(s1.size(), 4);
}

TEST(methods, push) {
  s21::Stack<int> s;
  s.push(3);
  EXPECT_EQ(s.top(), 3);
  EXPECT_EQ(s.size(), 1);
  EXPECT_FALSE(s.empty());
}

TEST(methods, pop) {
  s21::Stack<int> s = {3, 2};
  s.pop();
  EXPECT_EQ(s.size(), 1);
  EXPECT_EQ(s.top(), 3);
  s.pop();
  EXPECT_TRUE(s.empty());
}

TEST(methods, swap) {
  s21::Stack<int> s1 = {1, 2, 3, 4};
  s21::Stack<int> s2 = {4, 3, 3, 2};

  s1.swap(s2);

  int expected_s2[] = {4, 3, 2, 1};
  int expected_s1[] = {2, 3, 3, 4};

  for (size_t i = 0; i != s1.size(); i++) {
    EXPECT_EQ(s1.top(), expected_s1[i]);
    s1.pop();
  }

  for (size_t i = 0; i != s2.size(); i++) {
    EXPECT_EQ(s2.top(), expected_s2[i]);
    s2.pop();
  }
}

TEST(overloads, move_assignment) {
  s21::Stack<int> s1 = {1, 2, 3, 4};
  s21::Stack<int> s2;

  s2 = std::move(s1);
  EXPECT_EQ(s1.size(), 0);

  int arr[] = {4, 3, 2, 1};

  for (size_t i = 0; i != s2.size(); i++) {
    EXPECT_EQ(arr[i], s2.top());
    s2.pop();
  }
}
