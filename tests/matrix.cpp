#include <catch.hpp>
#include <sstream>

#include "matrix.hpp"


TEST_CASE("create"){
RBT<int> tree;
REQUIRE(tree.root() == nullptr);
}
TEST_CASE("insert"){
RBT<int> tree;
tree.insert(1);
tree.insert(2);
tree.insert(3);
tree.insert(4);
tree.insert(5);
tree.insert(6);
tree.insert(7);
tree.insert(8);
tree.insert(9);
tree.insert(10);
std::string out{
 "------------10R\n"
 "---------9B\n"
 "------8R\n"
 "---------7B\n"
 "---6B\n"
 "------5B\n"
 "4B\n"
 "------3B\n"
 "---2B\n"
 "------1B\n"
};
std::ostringstream stream;
tree.print(stream, 0, tree.root());
REQUIRE(stream.str() == out);
}
     
   
   
 
  
  
  
     
