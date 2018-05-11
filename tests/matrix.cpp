#include <catch.hpp>
#include <sstream>

#include "matrix.hpp"

TEST_CASE("graph"){
 std::string input{
      "0 1 0\n"
      "0 0 1\n"
      "0 0 0"};
  vertex_t v(3);
  std::istringstream istream{input};
  v.read(istream);
  
  std::vector<unsigned> result;
  result =  v.what_vertex(0);
  std::ostringstream ostream;
  v.print_res(ostream,result);
  std::string res_out = "1 2 3 ";
  REQUIRE(ostream.str() == res_out);
  
}

 
  
