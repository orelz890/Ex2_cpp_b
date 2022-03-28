// ============================== MY TEST ===================================

// How to run: g++ -o a.out Notebook.cpp TestRunner.cpp doctest.h Notebook.hpp

#include "doctest.h"
#include "Notebook.hpp"
#include <algorithm>

const int ONE = 1;
const int THREE = 3;
const int FOR = 1;
const int FIVE = 5;
const int SIX = 6;
const int TEN = 10;
const int NINE = 9;
const int TWELVE = 12;
const int THIRTEEN = 13;
const int FORTEEN = 14;
const int FIFTEEN = 15;
const int EIGHTEEN = 18;
const int TWENTY = 20;
const int FIFTEE = 50;
const int MAX_VAL = 255;

using namespace ariel;
using ariel::Direction;
using ariel::Notebook;
using namespace std;

// In all Notebook functons(except show) that we will test, the first 4 input values are: 
// (page: int, row: int, col: int, direction: Direction).



Notebook n;
int page0 = 0;

TEST_CASE("Good writing/reading/erasing"){

    n.write(page0,ZERO,ZERO,Direction::Horizontal,"Hey");
    CHECK (n.read(page0, ZERO, ZERO, Direction::Horizontal, 3) == "Hey");
    n.write(page0,FORTEEN,ZERO,Direction::Horizontal,"second test");
    CHECK (n.read(page0, FORTEEN, ZERO, Direction::Horizontal, 11) == "second test");
    for (size_t row = 0; row < THIRTEEN; row++){
        for (size_t col = 0; col < LINE_LEN; col++){
            if (row == ZERO && col > THREE){
                CHECK(n.read(page0,row,col,Direction::Horizontal ,ONE) == "_");
            }else if(row != 0){
                CHECK(n.read(page0,row,col,Direction::Horizontal ,ONE) == "_");
            }
        }
    }
    n.write(page0,ZERO,TEN,Direction::Vertical,"vertical test");
    CHECK (n.read(page0, ZERO, TEN, Direction::Vertical, THIRTEEN) == "vertical test");

    // Checking that the notebook was filled by under score (_) in the empty cels created between the writed data
    CHECK(n.read(page0,ZERO,FOR,Direction::Horizontal ,FIVE) == "_____");
    for (size_t row = 1; row < THIRTEEN; row++){
        for (size_t col = 0; col < LINE_LEN; col++){
            if (col == ZERO){
                CHECK(n.read(page0,row,ZERO,Direction::Horizontal ,NINE) == "_________");
                col += TEN;
            }else if (row < TWELVE){
                CHECK(n.read(page0,row,col,Direction::Horizontal ,ONE) == "_");
            }        
        }
    }
    // Checking erase horizontal & vertical
    n.erase(ZERO,ZERO,ZERO,Direction::Horizontal,THREE);
    CHECK (n.read(ZERO, ZERO, ZERO, Direction::Horizontal, THREE) == "~~~");
    n.erase(ZERO,ZERO,TEN,Direction::Vertical, THIRTEEN);
    CHECK (n.read(ZERO,ZERO,TEN,Direction::Vertical,THIRTEEN) == "~~~~~~~~~~~~~");

    // Erasing not writing cel (just like writing ~)
    n.erase(ONE,ZERO,ZERO,Direction::Horizontal,ONE);
    CHECK (n.read(ONE,ZERO,ZERO,Direction::Horizontal,ONE) == "~");

}


Notebook n2;

TEST_CASE("Bad input") {
    
    n2.write(ZERO,ZERO,ONE,Direction::Vertical,"OrelZamler");
    n2.erase(ZERO,ZERO,FIVE,Direction::Horizontal,SIX);
    for (size_t i = 0; i < MAX_VAL; i++){
        char c = i;
        string s;
        s += c;

        // col do not exist: try erase/write/read
        if (i>LINE_LEN){
            CHECK_THROWS(n2.write(ZERO,ZERO,i-FIFTEEN,Direction::Horizontal,"char cel dont exist!"));
            // Reading one illigal char
            CHECK_THROWS(n2.read(ZERO,ZERO,i,Direction::Horizontal,ONE));
            // reading string that some of its chars cels dont exist!
            CHECK_THROWS(n2.read(ZERO,ZERO,i-EIGHTEEN,Direction::Horizontal,TWENTY));
            // Erasing one illigal char
            CHECK_THROWS(n2.erase(ZERO,ZERO,i,Direction::Horizontal,ONE));
            // Erasing string that some of its chars cel dont exists!
            CHECK_THROWS(n2.erase(ZERO,ZERO,i-EIGHTEEN,Direction::Horizontal,TWENTY));
        }
        
        // Char is printable. Check writing overiding:
        if (i >= MIN_CHAR && i <= MAX_CHAR){
            string const &over_riding_one_char = s;
            string const &over_riding_the_entire_word = "Word";
            string const &over_riding_a_word_and_more = "Word" + s;
            string const &over_riding_erased_data = "Z";
            string const &over_riding_erased_data_and_more = "OrelZ";
            string const &over_riding_erased_and_written_data = "OrelZamler";

            CHECK_THROWS(n2.write(ZERO,ZERO,ONE,Direction::Horizontal,over_riding_one_char));
            CHECK_THROWS(n2.write(ZERO,ZERO,ONE,Direction::Horizontal,over_riding_the_entire_word));
            CHECK_THROWS(n2.write(ZERO,ZERO,ZERO,Direction::Horizontal,over_riding_a_word_and_more));
            CHECK_THROWS(n2.write(ZERO,ZERO,FIVE,Direction::Vertical,over_riding_erased_data));            
            CHECK_THROWS(n2.write(ZERO,ZERO,FIVE,Direction::Vertical,over_riding_erased_data_and_more));
            CHECK_THROWS(n2.write(ZERO,ZERO,ZERO,Direction::Horizontal,over_riding_erased_and_written_data));
        }
        // Char is not printabe!
        else{
            CHECK_THROWS(n2.write(ZERO, i%TEN, i%LINE_LEN, Direction::Horizontal, s));
            CHECK_THROWS(n2.write(ZERO, i%TEN, i%LINE_LEN, Direction::Horizontal, "legal string" + s));
        }
    }
    
    // Negetive input
    for (int i = -FIFTEE; i < ZERO; i++){
        CHECK_THROWS(n2.write(i,ZERO,ZERO,Direction::Horizontal,"not legal"));
        CHECK_THROWS(n2.write(ZERO,i,ZERO,Direction::Horizontal,"not legal"));
        CHECK_THROWS(n2.write(ZERO,ZERO,i,Direction::Horizontal,"not legal"));

        CHECK_THROWS(n2.read(i,ZERO,ZERO,Direction::Horizontal,ONE));
        CHECK_THROWS(n2.read(ZERO,i,ZERO,Direction::Horizontal,ONE));
        CHECK_THROWS(n2.read(ZERO,ZERO,i,Direction::Horizontal,ONE));
        CHECK_THROWS(n2.read(ZERO,ZERO,i,Direction::Horizontal,i));

        CHECK_THROWS(n2.erase(i,ZERO,ZERO,Direction::Horizontal,ONE));
        CHECK_THROWS(n2.erase(ZERO,i,ZERO,Direction::Horizontal,ONE));
        CHECK_THROWS(n2.erase(ZERO,ZERO,i,Direction::Horizontal,ONE));
        CHECK_THROWS(n2.erase(ZERO,ZERO,ZERO,Direction::Horizontal,i));

    }
    
}


// ============================== TEST3 ===================================


// /**
//  * @file Test.cpp
//  * @author Ofri Tavor
//  * @brief Test cases for the assignment
//  * @date 2022-03
//  */

// #include "Direction.hpp"
// using ariel::Direction;
// #include "Notebook.hpp"
// #include "doctest.h"
// #include <string>
// #define EMPTY_CHAR '_'
// #define REMOVED_CHAR '~'
// #define INVALID_LONG_STRING "GFDGDFGJDFGJKFDHGFDUGFDJKGFDLGJFDAAIGLHFDAGUJADFJSDABFDSFOSDJGUJFDHGFDGJFSD;LAGISFDOGFDIGHFDGJDFGFDA"

// /**
//  * This test case will check how the function deals with bad input.
//  * The inputs might be invalid by themselves, like negative index of a row for example,
//  * and they can also be valid inputs that together make the whole input invalid, like a word that
//  * starts in the middle of the row and end after its end.
//  */
// TEST_CASE("Bad inputs")
// {
//     ariel::Notebook notebook;
//     SUBCASE("Invalid Numbers")
//     {
//         SUBCASE("negative numeric inputs")
//         {
//             SUBCASE("Negative page index")
//             {
//                 CHECK_THROWS(notebook.show(-1));
//                 CHECK_THROWS(notebook.write(-1, 1, 1, Direction::Horizontal, "rrrr"));
//                 CHECK_THROWS(notebook.write(-1, 1, 1, Direction::Vertical, "rrrr"));
//                 CHECK_THROWS(notebook.erase(-1, 1, 1, Direction::Vertical, 3));
//                 CHECK_THROWS(notebook.erase(-1, 1, 1, Direction::Horizontal, 3));
//                 CHECK_THROWS(notebook.read(-1, 1, 1, Direction::Horizontal, 5));
//                 CHECK_THROWS(notebook.read(-1, 1, 1, Direction::Vertical, 5));
//             }
//             SUBCASE("Negative row index")
//             {
//                 CHECK_THROWS(notebook.write(1, -1, 1, Direction::Horizontal, "aaa"));
//                 CHECK_THROWS(notebook.write(1, -1, 1, Direction::Vertical, "aaa"));
//                 CHECK_THROWS(notebook.erase(1, -1, 1, Direction::Vertical, 3));
//                 CHECK_THROWS(notebook.erase(1, -1, 1, Direction::Horizontal, 3));
//                 CHECK_THROWS(notebook.read(1, -1, 1, Direction::Horizontal, 5));
//                 CHECK_THROWS(notebook.read(1, -1, 1, Direction::Vertical, 5));
//             }
//             SUBCASE("Negative column index")
//             {
//                 CHECK_THROWS(notebook.write(1, 1, -1, Direction::Horizontal, "rrrr"));
//                 CHECK_THROWS(notebook.write(1, 1, -1, Direction::Vertical, "rrrr"));
//                 CHECK_THROWS(notebook.erase(1, 1, -1, Direction::Vertical, 3));
//                 CHECK_THROWS(notebook.erase(1, 1, -1, Direction::Horizontal, 3));
//                 CHECK_THROWS(notebook.read(1, 1, -1, Direction::Horizontal, 5));
//                 CHECK_THROWS(notebook.read(1, 1, -1, Direction::Vertical, 5));
//             }
//             SUBCASE("Negative Length")
//             {
//                 CHECK_THROWS(notebook.read(1, 1, 1, Direction::Vertical, -5));
//                 CHECK_THROWS(notebook.read(1, 1, 1, Direction::Horizontal, -5));
//                 CHECK_THROWS(notebook.erase(1, 1, 1, Direction::Vertical, -5));
//                 CHECK_THROWS(notebook.erase(1, 1, 1, Direction::Horizontal, -5));
//             }
//         }
//         /**
//          * This sub case check the case that the column index is positive and within the given bounds.
//          */
//         SUBCASE("Invalid positive column check")
//         {
//             SUBCASE("Invalid column, everything else is valid")
//             {
//                 CHECK_THROWS(notebook.write(1, 1, 150, Direction::Horizontal, "rrrr"));
//                 CHECK_THROWS(notebook.write(1, 1, 150, Direction::Vertical, "rrrr"));
//                 CHECK_THROWS(notebook.erase(1, 1, 150, Direction::Vertical, 3));
//                 CHECK_THROWS(notebook.erase(1, 1, 101, Direction::Horizontal, 3));
//                 CHECK_THROWS(notebook.read(1, 1, 101, Direction::Horizontal, 5));
//                 CHECK_THROWS(notebook.read(1, 1, 101, Direction::Vertical, 5));
//             }
//         }
//         /**
//          * This sub case will check if the function throw an exception in case that the column
//          * and the length together will reach out of the given bounds.
//          */
//         SUBCASE("Bounds test-> the output should be out of bounds")
//         {
//             SUBCASE("Valid position and length: full row case")
//             {
//                 CHECK_NOTHROW(notebook.read(1, 1, 0, Direction::Vertical, 101));
//                 CHECK_THROWS(notebook.read(1, 1, 0, Direction::Horizontal, 101));
//                 CHECK_NOTHROW(notebook.erase(1, 1, 0, Direction::Vertical, 101));
//                 CHECK_THROWS(notebook.erase(1, 1, 0, Direction::Horizontal, 101));
//                 CHECK_THROWS(notebook.write(1,1,0,Direction::Horizontal, INVALID_LONG_STRING));
//             }
//             SUBCASE("Valid column, valid length, but it will be out of bounds")
//             {
//                 CHECK_THROWS(notebook.write(1, 1, 98, Direction::Horizontal, "rrrr"));
//                 CHECK_THROWS(notebook.erase(1, 1, 98, Direction::Horizontal, 3));
//                 CHECK_THROWS(notebook.read(1, 1, 98, Direction::Horizontal, 5));
//             }
//         }
//     }
//     SUBCASE("Invalid Characters -> ~"){
//         ariel::Notebook notebook;
//         CHECK_THROWS(notebook.write(1,1,0,Direction::Horizontal, "~~~~~"));
//         CHECK_THROWS(notebook.write(1,1,0,Direction::Vertical, "~~~~~"));
//         SUBCASE("Overwriting using ~ is not allowd")
//         ariel::Notebook notebook;
//         notebook.write(1,1,0,Direction::Horizontal, "hello world");
//         CHECK_THROWS(notebook.write(1,1,0,Direction::Vertical, "~~~~~~~~~~~"));
//         CHECK_NOTHROW(notebook.erase(1,1,0,Direction::Horizontal,11));
//     }
// }

// /**
//  * This test case will check how the functions will deal with problematic scenarios.
//  */

// TEST_CASE("Problematic scenarios")
// {
//     SUBCASE("Write in inavailable columns")
//     {
//         ariel::Notebook notebook;
//         notebook.write(1, 1, 10, Direction::Horizontal, "hello world");
//         CHECK_THROWS(notebook.write(1, 1, 10, Direction::Horizontal, "hello hello"));
//         CHECK_THROWS(notebook.write(1, 1, 10, Direction::Vertical, "hello hello"));
//         CHECK_THROWS(notebook.write(1, 1, 16, Direction::Horizontal, "hello"));
//         CHECK_THROWS(notebook.write(1, 1, 16, Direction::Vertical, "hello"));
//         CHECK_THROWS(notebook.write(1, 1, 8, Direction::Horizontal, "bye"));
//         CHECK_THROWS(notebook.write(1, 1, 20, Direction::Horizontal, "bye"));
//     }
//     SUBCASE("Write on a removed column")
//     {
//         ariel::Notebook notebook;
//         notebook.write(1, 1, 10, Direction::Horizontal, "hello world");
//         notebook.erase(1, 1, 10, Direction::Horizontal, 11);
//         CHECK_THROWS(notebook.write(1, 1, 10, Direction::Horizontal, "hello hello"));
//         CHECK_THROWS(notebook.write(1, 1, 10, Direction::Vertical, "hello hello"));
//         CHECK_THROWS(notebook.write(1, 1, 16, Direction::Horizontal, "hello"));
//         CHECK_THROWS(notebook.write(1, 1, 16, Direction::Vertical, "hello"));
//         CHECK_THROWS(notebook.write(1, 1, 8, Direction::Horizontal, "bye"));
//         CHECK_THROWS(notebook.write(1, 1, 20, Direction::Horizontal, "bye"));
//     }
//     SUBCASE("Overwriting an 'empty' character - '_' is allowed"){
//         ariel::Notebook notebook;
//             notebook.write(1, 6, 0, Direction::Horizontal, "hello_hello");
//             CHECK_NOTHROW(notebook.write(1,6,5,Direction::Horizontal, "^"));
//             notebook.write(1, 7, 0, Direction::Horizontal, "hello_world");
//             CHECK_NOTHROW(notebook.write(1,7,5,Direction::Vertical,"ABCD"));
//     }
//     SUBCASE("Erase an erased column throw an Unnecessary exception")
//     {
//         ariel::Notebook notebook;
//         notebook.write(1, 1, 10, Direction::Horizontal, "hello world");
//         notebook.erase(1, 1, 10, Direction::Horizontal, 11);
//         CHECK_NOTHROW(notebook.erase(1, 1, 10, Direction::Horizontal, 11));
//         CHECK_NOTHROW(notebook.erase(1, 1, 16, Direction::Horizontal, 5));
//         CHECK_NOTHROW(notebook.erase(1, 1, 8, Direction::Horizontal, 3));
//         CHECK_NOTHROW(notebook.erase(1, 1, 20, Direction::Horizontal, 3));
//     }

//     /**
//      * This sub case check if the function can deal with "infinite" number of pages which contains "infinite"
//      * number of rows. The function should not throw an exception.
//      */
    
//     SUBCASE("Dealing with rows or pages that does not exist->they should be since there are infinite rows and pages, even if they are not defined.")
//     {
//         ariel::Notebook notebook;
//         CHECK_NOTHROW(notebook.erase(1, 1, 10, Direction::Horizontal, 23));
//         CHECK_NOTHROW(notebook.erase(1, 2, 16, Direction::Horizontal, 12));
//         CHECK_NOTHROW(notebook.erase(1, 3, 8, Direction::Horizontal, 30));
//         CHECK_NOTHROW(notebook.write(1, 5, 25, Direction::Horizontal, "hello hello"));
//         CHECK_NOTHROW(notebook.read(2, 1, 20, Direction::Horizontal, 30));
//         CHECK_NOTHROW(notebook.read(1, 1, 25, Direction::Vertical, 30));
//         CHECK_NOTHROW(notebook.show(3));
//     }
// }



// ============================== TEST1 ===================================


// /**
//  *
//  * AUTHORS: Aviad Gilboa
//  * 
//  * Date: 03-2022
// **/ 
// // How to run: g++ -o a.out Notebook.cpp TestRunner.cpp doctest.h Notebook.hpp
// #include "doctest.h"
// #include "Notebook.hpp"
// using namespace ariel;
// #include <string>
// #include <algorithm>

// /* Test cases for write function */

// TEST_CASE("length of the line is between 0-99"){
    
//     for ( int i=100; i<200;i++){
//         Notebook note;
//         try
//         {
//             note.write(1,i-100,0,Direction::Vertical,"Look at me");
//             note.write(1,i-100,2,Direction::Horizontal,"I'm Mr. meeseeks");
//         }
//         catch(const std::exception& e)
//         {
//             CHECK_EQ(true,false);
//         }
        
//         CHECK_THROWS(note.write(1,i-100,i,Direction::Vertical,"o"));
//         CHECK_THROWS(note.write(1,i-100,2,Direction::Vertical,"o"));
//         CHECK_THROWS(note.write(1,i-100,98,Direction::Horizontal,"abc"));
//     }
// }
// TEST_CASE("case: special chars"){
//     Notebook note;
//     note.write(1,0,0,Direction::Horizontal,"n____n");
//     try{note.write(1,0,1,Direction::Horizontal,"abcd");}
//     catch(std::exception &){
//         CHECK_EQ(true,false);
//     }
//     CHECK_THROWS(note.write(1,1,1,Direction::Horizontal,"\n"));
// }
// TEST_CASE("Case: writing twice on the same position"){
//     Notebook note;
//      for (int i=0; i<96;i++){
//         note.write(1,i,i,Direction::Horizontal,"abcd");
//      }
//      for (int i=1; i<96;i++){
//          CHECK_THROWS(note.write(1,i-1,i,Direction::Vertical,"ab"));
//          CHECK_THROWS(note.write(1,i-1,i,Direction::Vertical,"ab"));
//      }
// }

// TEST_CASE("case: there is infinate rows"){
//     Notebook note;
//     std::string s;
//     for (int i=1; i<10000;i++){s+="a";}
//      int k=0;
//     for(;k<100;k++){
//         try{
//             note.write(0,0,k,Direction::Vertical,s);}
//         catch(std::exception&){
//             CHECK_EQ(true,false);
//         }
//     }   
// }

// TEST_CASE("case: there is infinate pages"){
//     Notebook note;
//     for(int i=0; i<10000;i++){
//         try{
//             note.write(i,0,0,Direction::Horizontal,"%#!#");}
//         catch(std::exception&){
//             CHECK_EQ(true, false);
//         }
//     }
// }

// /*Test cases for earse function  */
// TEST_CASE("case: earse outside the line"){
//     Notebook note;
//     CHECK_THROWS(note.erase(0,4,98,Direction::Horizontal,3));
//     CHECK_THROWS(note.erase(1,2,102,Direction::Vertical, 50));
//     CHECK_THROWS(note.erase(1,2,100,Direction::Vertical, 5));
// }

// TEST_CASE("case: replace the current char to '~' "){
//     Notebook note;
//     note.write(1,2,55,Direction::Horizontal,"hello world");
//     note.erase(1,2,60,Direction::Horizontal,6);
//     CHECK_EQ(note.read(1,2,55,Direction::Horizontal,11),"hello~~~~~~");
//     note.erase(1,2,53,Direction::Horizontal,2);
//     CHECK_EQ(note.read(1,2,50,Direction::Horizontal,16),"___~~hello~~~~~~"); 
// }
// TEST_CASE("can't write again after earse"){
//     Notebook note;
//     try{
//         note.write(1,2,55,Direction::Horizontal,"morty and jessica forever");
//         note.erase(1,2,66,Direction::Horizontal,7);}
//     catch(std::exception){
//         CHECK_EQ(true,false);
//     }
//     CHECK_THROWS(note.write(1,0,55,Direction::Vertical,"this is not gonna work"));
//         note.write(0,30,40,Direction::Horizontal,"my name is bird person");
//     note.erase(0,30,51,Direction::Horizontal,11);
//     note.write(0,30,62,Direction::Horizontal,"Phoenixperson");
//     CHECK_EQ(note.read(0,30,40,Direction::Horizontal,35),"my name is ~~~~~~~~~~~Phoenixperson");
//     CHECK_EQ(note.read(0,30,38,Direction::Horizontal,39),"__my name is ~~~~~~~~~~~Phoenixperson__");
// }

// /* Test cases for read function */
// TEST_CASE("case: the empty cube represent by '_' "){
//     Notebook note;
//     std::string st;
//     st = note.read(0,0,0,Direction::Horizontal,100);
//     bool flag;
//     for(unsigned long i=0; i<100;i++){
//         flag = st[i]=='_';
//         CHECK_FALSE(!flag);}
//     note.write(0,1,40,Direction::Vertical,"my name is bird person");
//     note.erase(0,1,51,Direction::Vertical,11);
//     note.write(0,1,62,Direction::Vertical,"Phoenixperson");
//     st = note.read(0,1,0,Direction::Vertical,100);
//     for(unsigned long i=0; i<40;i++){
//         flag =st[i]=='_';
//         CHECK_FALSE(!flag);}
//     for(unsigned long i=76;i<100;i++){
//         flag = st[i]=='_';
//         CHECK_FALSE(!flag);}
// }

// TEST_CASE("case: want to read above the limits of the line"){
//     Notebook note;
//     CHECK_THROWS(note.read(0,1,100,Direction::Vertical,5));
//     CHECK_THROWS(note.read(1,1,98,Direction::Horizontal,5));
// }

