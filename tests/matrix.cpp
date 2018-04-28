#include <catch.hpp>
#include <sstream>

#include "matrix.hpp"

TEST_CASE("create"){
scoped_ptr<int> sp1;
REQUIRE(sp1.get() == nullptr);
}
TEST_CASE("get"){
scoped_ptr<int> sp1(new int(2));
scoped_ptr<int> sp2(new int(3));
int ptr1 = sp1.get();
int ptr2 = sp2.get(); 
REQUIRE(*ptr1 == 2);
REQUIRE(*ptr2 == 3);
}
TEST_CASE("swap"){
scoped_ptr<int> sp1(new int(2));
scoped_ptr<int> sp2(new int(3));
sp1.swap(sp2);
REQUIRE(*sp1 == 3);
REQUIRE(*sp2 == 2);
}
TEST_CASE("reset"){
scoped_ptr<int> sp1(new int(2));
REQUIRE(*sp1 == 2);
sp1.reset(new int(6));
REQUIRE(*sp1 == 6);
}
TEST_CASE("ptr->"){
scoped_ptr<Mypair> sp1(new Mypair(4,5));
REQUIRE(sp1->first == 4);
REQUIRE(sp2->second == 5);
}
