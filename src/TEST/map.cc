#include <gtest/gtest.h>

#include <map>

#include "../s21_container.h"

TEST(map, DefCtorMap) {
  s21::map<int, char> s21_map;
  std::map<int, char> orig_map;
  EXPECT_EQ(s21_map.empty(), orig_map.empty());
}

TEST(map, CtorInitListMap) {
  s21::map<int, char> s21_map = {{1, 'x'}, {2, 'b'}, {3, 'b'}, {4, 'y'}};
  std::map<int, char> orig_map = {{1, 'x'}, {2, 'b'}, {3, 'b'}, {4, 'y'}};

  EXPECT_EQ(s21_map.size(), orig_map.size());
  auto s21_it = s21_map.begin();
  auto orig_it = orig_map.begin();

  for (; s21_it != s21_map.end(); ++s21_it, ++orig_it) {
    EXPECT_TRUE((*s21_it).first == (*orig_it).first);
    EXPECT_TRUE((*s21_it).second == (*orig_it).second);
  }
}

TEST(map, CtorInitList2Map) {
  s21::map<int, char> s21_map = {};
  std::map<int, char> orig_map = {};

  EXPECT_EQ(s21_map.size(), orig_map.size());
  auto s21_it = s21_map.begin();
  auto orig_it = orig_map.begin();

  for (; s21_it != s21_map.end(); ++s21_it, ++orig_it) {
    EXPECT_TRUE((*s21_it).first == (*orig_it).first);
    EXPECT_TRUE((*s21_it).second == (*orig_it).second);
  }
}

TEST(map, CtorCopyMap) {
  s21::map<int, int> s21_map = {{1, 2}, {3, 4}, {5, 6}};
  std::map<int, int> orig_map = {{1, 2}, {3, 4}, {5, 6}};
  s21::map<int, int> s21_map_cpy = s21_map;
  std::map<int, int> orig_map_cpy = orig_map;

  EXPECT_EQ(s21_map_cpy.size(), orig_map_cpy.size());
  auto s21_it = s21_map_cpy.begin();
  auto orig_it = orig_map_cpy.begin();

  for (; s21_it != s21_map_cpy.end(); ++s21_it, ++orig_it) {
    EXPECT_TRUE((*s21_it).first == (*orig_it).first);
    EXPECT_TRUE((*s21_it).second == (*orig_it).second);
  }
}

TEST(map, MapOperator) {
  s21::map<char, std::string> s21_map = {
      {'a', "Alina"}, {'b', "Boris"}, {'c', "Chuck"}};
  std::map<char, std::string> orig_map = {
      {'a', "Alina"}, {'b', "Boris"}, {'c', "Chuck"}};

  s21_map['a'] = "Vasya";
  orig_map['b'] = "Borka";

  EXPECT_FALSE(s21_map['a'] == orig_map['a']);
  EXPECT_FALSE(s21_map['b'] == orig_map['b']);
  EXPECT_TRUE(s21_map['c'] == orig_map['c']);
}

TEST(map, MapAtOperatorException) {
  s21::map<char, std::string> s21_map = {{'a', "Alina"}, {'b', "Boris"}};
  EXPECT_THROW(s21_map.at('g') = "Alisa", std::out_of_range);
}

TEST(map, MapCapacity) {
  s21::map<int, int> s21_map;
  std::map<int, int> orig_map;
  s21_map.clear();
  orig_map.clear();

  EXPECT_EQ(s21_map.empty(), orig_map.empty());
  s21_map.insert(std::make_pair(1, 1));
  orig_map.insert(std::make_pair(1, 1));

  EXPECT_EQ(s21_map.empty(), orig_map.empty());
  s21_map.clear();
  orig_map.clear();

  EXPECT_EQ(s21_map.empty(), orig_map.empty());
}

TEST(map, MapInsert) {
  s21::map<char, std::string> s21_map;
  std::map<char, std::string> orig_map;
  EXPECT_TRUE(s21_map.empty() == orig_map.empty());
  s21_map.insert('z', "wow");
  EXPECT_FALSE(s21_map.empty() == orig_map.empty());
  EXPECT_EQ(s21_map.size(), 1);
}

TEST(map, MapInsert1) {
  s21::map<int, char> s21_map;
  std::map<int, char> orig_map;

  s21_map.insert(std::make_pair(1, 'a'));
  s21_map.insert(std::make_pair(2, 'a'));
  s21_map.insert(std::make_pair(3, 'a'));

  orig_map.insert(std::make_pair(1, 'a'));
  orig_map.insert(std::make_pair(2, 'a'));
  orig_map.insert(std::make_pair(3, 'a'));

  auto s21_it = s21_map.begin();
  auto orig_it = orig_map.begin();

  for (; s21_it != s21_map.end(); ++s21_it, ++orig_it) {
    EXPECT_TRUE((*s21_it).first == (*orig_it).first);
    EXPECT_TRUE((*s21_it).second == (*orig_it).second);
  }

  auto pr1 = s21_map.insert(std::make_pair(1, 'a'));
  auto pr2 = orig_map.insert(std::make_pair(1, 'a'));
  EXPECT_TRUE(pr1.second == pr2.second);
}

TEST(map, MapInsert3) {
  s21::map<int, char> s21_map;
  std::map<int, char> orig_map;

  s21_map.insert(1, 'a');
  s21_map.insert(2, 'a');
  s21_map.insert(3, 'a');

  orig_map.insert(std::make_pair(1, 'a'));
  orig_map.insert(std::make_pair(2, 'a'));
  orig_map.insert(std::make_pair(3, 'a'));

  auto s21_it = s21_map.begin();
  auto orig_it = orig_map.begin();

  for (; s21_it != s21_map.end(); ++s21_it, ++orig_it) {
    EXPECT_TRUE((*s21_it).first == (*orig_it).first);
    EXPECT_TRUE((*s21_it).second == (*orig_it).second);
  }

  auto pr1 = s21_map.insert_or_assign(1, 'b');
  auto i = orig_map.begin();
  EXPECT_TRUE((*pr1.first).first == (*i).first);
  EXPECT_FALSE((*pr1.first).second == (*i).second);
}

TEST(map, MapErase) {
  s21::map<int, char> s21_map = {{1, 'x'}, {2, 'b'}, {3, 'b'}, {4, 'y'}};
  std::map<int, char> orig_map = {{1, 'x'}, {2, 'b'}, {3, 'b'}, {4, 'y'}};

  EXPECT_EQ(s21_map.size(), orig_map.size());
  s21_map.erase(s21_map.begin());
  orig_map.erase(orig_map.begin());
  EXPECT_EQ(s21_map.size(), orig_map.size());

  auto s21_it = s21_map.begin();
  auto orig_it = orig_map.begin();
  for (; s21_it != s21_map.end(); ++s21_it, ++orig_it) {
    EXPECT_TRUE((*s21_it).first == (*orig_it).first);
    EXPECT_TRUE((*s21_it).second == (*orig_it).second);
  }
}

TEST(map, SwapMap) {
  s21::map<int, int> s21_map = {{1, 1}};
  s21::map<int, int> s21_swap_map = {{3, 3}, {4, 4}};

  s21_map.swap(s21_swap_map);

  EXPECT_EQ(s21_map.size(), 2);
  EXPECT_EQ(s21_swap_map.size(), 1);

  auto x = (*(s21_map.begin())).first;
  auto y = (*(s21_swap_map.begin())).first;

  EXPECT_EQ(x, 3);
  EXPECT_EQ(y, 1);
}
