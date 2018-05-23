#include <catch.hpp>
#include <sstream>

#include "matrix.hpp"
TEST_CASE("creating rb tree") {
  RBT<int> tree;
  REQUIRE(tree.root() == nullptr);
}

TEST_CASE("elements can be inserted in rb tree", "[insert]""){
 RBT<int> tree;
 tree.insert( 10 );
 tree.insert( 85 );
          tree.insert( 15 );
          tree.insert( 70 );
          tree.insert( 20 );
          tree.insert( 60 );
          tree.insert( 30 );
          tree.insert( 50 );
          tree.insert( 65 );
          tree.insert( 80 );
          tree.insert( 90 );
          tree.insert( 40 );
          tree.insert( 5 );
          tree.insert( 55 );
          
         std::string out{
      "---------90R\n"
"------85B\n"
"---------80R\n"
"---70Bn"
"---------65B\n"
"------60R\n"
"------------55R\n"
"---------50B\n"
"------------40R\n"
"30B\n"
"------20B\n"
"---15B\n"
"------10B\n"
"---------5R\n"}; 
          std::ostringstream stream;
          tree.print(stream, 0, tree.root());
          REQUIRE(stream.str() == out);
}
          
TEST_CASE("elements can be removde from rb tree", "[remove]"){
 RBT<int> tree;
  tree.insert( 10 );
  tree.remove( 10 );
  REQUIRE(tree.root() == nullptr);
  tree.insert( 2 );
	tree.insert( 1 );
	tree.insert( 3 );
	tree.insert( 4 );
	tree.insert( 5 );
  tree.remove( 2 );
  std::string out{
      "------5B\n"
      "---4R\n"
      "------3B\n"
      "2B\n"
      "---1B\n"};
	  std::ostringstream stream;
          tree.print(stream, 0, tree.root());
          REQUIRE(stream.str() == out);
}
TEST_CASE("elements can be removed from rb tree ", "[remove, bug]"){
RBT<int> tree;
tree.insert( 1 );
			tree.insert( 2 );
			tree.insert( 6 );
			tree.insert( 8 );
			tree.insert( 9 );
			tree.insert( 7 );
			tree.insert( 4 );
			tree.insert( 4 );
			tree.insert( 2 );
			tree.insert( 4 );
			tree.insert( 4 );
			tree.remove( 4 );
			tree.remove( 4 );
			tree.remove( 4 );
			tree.remove( 4 );
			tree.remove( 8 );
	  std::string out{
      "---9B\n"
      "------7B\n"
      "6B\n"
      "------2B\n"
      "---2B\n"
      "------1B\n"};
		  std::ostringstream stream;
	 std::ostringstream stream2;
                  tree.print(stream, 0, tree.root());
	          REQUIRE(stream.str() == out);
	 std::string out2{
	 "---7B\n"
         "6B\n"
	 "------2B\n"
	 "---2R\n"
	 "------1B\n"
	 }; 
	tree.remove( 9 );
	tree.print(stream2, 0, tree.root());
	REQUIRE(stream2.str() == out2);
}
