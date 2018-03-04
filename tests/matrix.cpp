#include <catch.hpp>
#include <sstream>

#include "matrix.hpp"

TEST_CASE("creating matrix")
{
    matrix_t matrix;
    REQUIRE( matrix.rows() == 0 );
    REQUIRE( matrix.collumns() == 0 );
}

TEST_CASE("reading matrix")
{
    std::string input{
        "3, 3\n"
        "1 1 1\n"
        "2 2 2\n"
        "3 3 3" };
    matrix_t matrix;
    std::istringstream istream{ input };
    
    REQUIRE( matrix.read( istream ) );
    REQUIRE( matrix.rows() == 3 );
    REQUIRE( matrix.collumns() == 3 );
    
    std::ostringstream ostream;
    matrix.write( ostream );
    
    REQUIRE( input == ostream.str() );
}

TEST_CASE("Matrix Add")
{
    std::string input1{
        "3, 3\n"
        "1 1 1\n"
        "1 1 1\n"
        "1 1 1" };
     std::string input2{
        "3, 3\n"
        "2 2 2\n"
        "2 2 2\n"
        "2 2 2" };
     std::string output{
        "3, 3\n"
        "3 3 3\n"
        "3 3 3\n"
        "3 3 3" };
    matrix_t matrix1 , matrix2 ,result;
    
    std::istringstream istream1{ input1 };
    std::istringstream istream2{ input2 };
    
    matrix1.read( istream1 ) ;
    matrix2.read( istream2 ) ;
    
    result= matrix1 + matrix2 ;
        
    std::ostringstream ostream;
    result.write( ostream );
    
    REQUIRE( output == ostream.str() );
}

TEST_CASE("Matrix Sub")
{
    std::string input1{
        "3, 3\n"
        "1 1 1\n"
        "1 1 1\n"
        "1 1 1" };
     std::string input2{
        "3, 3\n"
        "5 5 5\n"
        "5 5 5\n"
        "5 5 5" };
     std::string output{
        "3, 3\n"
        "4 4 4\n"
        "4 4 4\n"
        "4 4 4" };
    matrix_t matrix1 , matrix2 ,result;
    
    std::istringstream istream1{ input1 };
    std::istringstream istream2{ input2 };
    
    matrix1.read( istream1 ) ;
    matrix2.read( istream2 ) ;
  
    result= matrix2 - matrix1 ;
    
    std::ostringstream ostream;
    result.write( ostream );
    
    REQUIRE( output == ostream.str() );
}

TEST_CASE("Matrix Mul")
{
    std::string input1{
        "3, 3\n"
        "1 1 1\n"
        "1 1 1\n"
        "1 1 1" };
     std::string input2{
        "3, 3\n"
        "2 2 2\n"
        "2 2 2\n"
        "2 2 2" };
     std::string output{
        "3, 3\n"
        "6 6 6\n"
        "6 6 6\n"
        "6 6 6" };
    matrix_t matrix1 , matrix2 ,result;
    
    std::istringstream istream1{ input1 };
    std::istringstream istream2{ input2 };
    
    matrix1.read( istream1 ) ;
    matrix2.read( istream2 ) ;

    result = matrix1 * matrix2 ;
    
    std::ostringstream ostream;
    result.write( ostream );
    
    REQUIRE( output == ostream.str() );
}
TEST_CASE("Matrix SelfAdd")
{
    std::string input1{
        "3, 3\n"
        "1 1 1\n"
        "1 1 1\n"
        "1 1 1" };
     std::string input2{
        "3, 3\n"
        "2 2 2\n"
        "2 2 2\n"
        "2 2 2" };
     std::string output{
        "3, 3\n"
        "3 3 3\n"
        "3 3 3\n"
        "3 3 3" };
    matrix_t matrix1 , matrix2 ;
    
    std::istringstream istream1{ input1 };
    std::istringstream istream2{ input2 };
    
    matrix1.read( istream1 ) ;
    matrix2.read( istream2 ) ;

    matrix1 += matrix2 ;
    
    std::ostringstream ostream;
    matrix1.write( ostream );
    
    REQUIRE( output == ostream.str() );
}
TEST_CASE("Matrix SelfSub")
{
    std::string input1{
        "3, 3\n"
        "1 1 1\n"
        "1 1 1\n"
        "1 1 1" };
     std::string input2{
        "3, 3\n"
        "5 5 5\n"
        "5 5 5\n"
        "5 5 5" };
     std::string output{
        "3, 3\n"
        "4 4 4\n"
        "4 4 4\n"
        "4 4 4" };
    matrix_t matrix1 , matrix2;
    
    std::istringstream istream1{ input1 };
    std::istringstream istream2{ input2 };
    
    matrix1.read( istream1 ) ;
    matrix2.read( istream2 ) ;
  
    matrix2 -= matrix1;
    
    std::ostringstream ostream;
    matrix2.write( ostream );
    
    REQUIRE( output == ostream.str() );
}
TEST_CASE("Matrix SelfMul")
{
    std::string input1{
        "3, 3\n"
        "1 1 1\n"
        "1 1 1\n"
        "1 1 1" };
     std::string input2{
        "3, 3\n"
        "2 2 2\n"
        "2 2 2\n"
        "2 2 2" };
     std::string output{
        "3, 3\n"
        "6 6 6\n"
        "6 6 6\n"
        "6 6 6" };
    matrix_t matrix1 , matrix2 ;
    
    std::istringstream istream1{ input1 };
    std::istringstream istream2{ input2 };
    
    matrix1.read( istream1 ) ;
    matrix2.read( istream2 ) ;

    matrix1 *= matrix2 ;
    
    std::ostringstream ostream;
    matrix1.write( ostream );
    
    REQUIRE( output == ostream.str() );
}
