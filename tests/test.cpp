// Copyright 2018 Your Name <your_email>

#include <gtest/gtest.h>

#include <header.hpp>

TEST(SHARED_PTR, init) {
  SharedPtr<int> ptr;
  //EXPECT_FALSE(ptr);
  SharedPtr<int> p(new int(5));
  EXPECT_EQ(p.use_count(), 1);
  EXPECT_EQ(*p, 5);
  //EXPECT_TRUE(p);
  SharedPtr<int> p1(p);
  EXPECT_EQ(p.use_count(), p1.use_count());
  EXPECT_EQ(p.use_count(), 2);
  EXPECT_EQ(*p1, 5);
  //EXPECT_TRUE(p1);
}

TEST(SHARED_PTR, assign) {
  SharedPtr<int> p(new int(8));
  SharedPtr<int> p1(new int(2));
  p = p1;
  EXPECT_EQ(p.use_count(), p1.use_count());
  EXPECT_EQ(p.use_count(), 2);
  EXPECT_EQ(*p1, *p);
  EXPECT_TRUE(p1);
}

/*TEST(SHARED_PTR, test_of_reset) {
  SharedPtr<int> p(new int(3));
  SharedPtr<int> p1(p);
  EXPECT_EQ(p.use_count(), 2);
  p.reset();
  EXPECT_FALSE(p);
  EXPECT_EQ(p1.use_count(), 1);
  p1.reset(new int(10));
  EXPECT_EQ(p1.use_count(), 1);
  EXPECT_EQ(*p1, 10);
}

TEST(SHARED_PTR, test_of_swap) {
  SharedPtr<int> p(new int(3));
  SharedPtr<int> p1(new int(10));
  p1.Swap(p);
  EXPECT_EQ(p1.use_count(), 1);
  EXPECT_EQ(p.use_count(), 1);
  EXPECT_EQ(*p1, 3);
  EXPECT_EQ(*p, 10);
}*/
