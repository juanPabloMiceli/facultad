#include "gtest/gtest.h"
#include "../src/Templates.cpp"
#include <string>

using namespace std;

TEST(Base, cuadrado) {
  EXPECT_EQ(cuadrado(1.2), 1.2*1.2);
  EXPECT_EQ(cuadrado(10), 100);
  EXPECT_EQ(cuadrado(1), 1);
}

TEST(Base, contiene) {
    vector<int> v = {1,23,5, 35};
  EXPECT_TRUE(contiene(string("Hola todos"), 't'));
  EXPECT_TRUE(contiene(string("Hola todos"), 'H'));
  EXPECT_TRUE(contiene(string("Hola todos"), ' '));
  EXPECT_TRUE(contiene(v, 3));
  EXPECT_FALSE(contiene(string("Hola todos"), 'h'));
}
