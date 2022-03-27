#include "doctest.h"
#include "Notebook.hpp"
#include <string>
#include <algorithm>

const int ZERO = 0;
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
