//
// Created by Caleb Moore on 2/11/21.
//
#include "catch.hpp"
#include "DSString.h"
#include "DSVector.h"
#include "DSList.h"
#include "DSStack.h"

using namespace std;

TEST_CASE("String class", "[DSString]"){
    //test assignment through multiple forms of construction
    SECTION("Equals Check") {
        //checks different forms of construction
        DSString one = "Testing";
        DSString two("secondary");
        DSString four;
        four = "Testing";

        REQUIRE_FALSE(one == two);
        REQUIRE(one == "Testing");
        REQUIRE(four == one);
    }
    SECTION("DSString to DSString Assignment Check"){
        DSString one = "Good";
        DSString two = one;

        REQUIRE(one == two);
    }
    //test + operator overload
    SECTION("+ Check"){
        DSString first = "good";
        DSString second = "morning";

        REQUIRE(first + second == "goodmorning");
        REQUIRE(first + "good" == "goodgood");
    }
    //test substring
    SECTION("Substring Check"){
        DSString whole = "Racecar";

        REQUIRE(whole.substring(0, 4) == "Race");
    }
    //test comparison operators
    SECTION("Comparison Check"){
        DSString one = "first";
        DSString two = "second";
        DSString three = "123";
        DSString four = "234";

        REQUIRE(one < two);
        REQUIRE_FALSE(one > two);
        REQUIRE(three < four);
        REQUIRE(four > three);
        REQUIRE(three < one);
        REQUIRE(four < two);

    }
    //test the index-using char selector
    SECTION("[] Check"){
        DSString test = "index Testing";

        REQUIRE(test[0] == 'i');
        REQUIRE(test[5] == ' ');
        REQUIRE_FALSE(test[6] == 't');
        REQUIRE(test[6] == 'T');
        REQUIRE_THROWS_AS(test[23], out_of_range);
    }
    //test the get length function
    SECTION("Length Check"){
        DSString testing_four = "four";
        DSString testing_seven = "buffalo";

        REQUIRE(testing_four.getLength() == 4);
        REQUIRE(testing_seven.getLength() == 7);
        REQUIRE_FALSE(testing_seven.getLength() == 0);
    }
    //test delete function
    SECTION("Delete Check"){
        DSString testing = "test";

        REQUIRE(testing == "test");
    }
    SECTION("Digit Recognition and Transformation Check"){
        DSString test = "1A";
        REQUIRE(test.is_digit(0));
        REQUIRE_FALSE(test.is_digit(1));

        int i = 0;
        DSString t = "2";
        i = t.to_digit();
        REQUIRE(i == 2);
        REQUIRE((i + 2) == 4);
    }
    SECTION("To Lower Case Check"){
        DSString test = "CASE";
        DSString test2 = "Case";
        DSString test3 = "Case!";
        test.lower();
        test2.lower();
        test3.lower();

        REQUIRE(test == "case");
        REQUIRE(test2 == "case");
        REQUIRE(test3 == "case!");
    }
}


//testing the DSVector functionality
TEST_CASE("Vector Class", "[DSVector]"){
    SECTION("Construction and Copy Check") {
        DSVector<int> int_test;

        //make sure an empty DSVector was created
        REQUIRE(int_test.get_size() == 0);
        REQUIRE(int_test.get_capacity() == 10);

        for(int i = 0; i < 4; i++){
            int_test.push_back(i);
        }

        DSVector<int> copy;
        copy = int_test;

        for(int i = 0; i < 4; i++){
            REQUIRE(copy[i] == int_test[i]);
            REQUIRE(copy.get_size() == 4);
            REQUIRE(copy.get_capacity() == 10);
        }
    }
    SECTION("Push Back Check"){
        //make sure adding an element works correctly
        DSVector<int> int_test;

        int_test.push_back(3);
        REQUIRE(int_test.get_size() == 1);
        REQUIRE(int_test.get_capacity() == 10);

        //make sure the capacity grows when the size is getting too big
        for(int i = 0; i < 10; i++){
            int_test.push_back(1);
        }

        //make sure vector is expanded correctly
        REQUIRE(int_test.get_size() == 11);
        REQUIRE(int_test.get_capacity() == 20);
        //double check for the correct exponential growth of the vector
        for(int i = 0; i < 10; i++){
            int_test.push_back(1);
        }
        //check the growth
        REQUIRE(int_test.get_size() == 21);
        REQUIRE(int_test.get_capacity() == 40);
    }
    SECTION("Locator Check"){
        DSVector<int> int_test;
        for(int i = 0; i < 13; i++){
            int_test.push_back(i);
        }

        //check the location finding works for all of the added elements
        for(int i = 0; i < 13; i++){
            REQUIRE(int_test[i] == i);
        }
        //and for the out of bounds an error is thrown
        REQUIRE_THROWS_AS(int_test[13], out_of_range);
    }
    SECTION("Insert Check"){
        DSVector<int> int_test;
        for(int i = 0; i < 11; i++){
            int_test.push_back(i);
        }

        int t = 18;
        int_test.insert(t, 1);

        //make sure everything is created and moved back correctly
        REQUIRE(int_test[0] == 18);
        REQUIRE(int_test[1] == 0);
        REQUIRE(int_test[11] == 10);

        //double check insert not at front
        int m = 14;
        int_test.insert(m, 7);

        REQUIRE(int_test[6] == 14);
        REQUIRE(int_test[5] == 4);
        REQUIRE(int_test[12] == 10);
    }
    SECTION("Get Functions Check"){
        DSVector<int> int_test;
        for(int i = 0; i < 5; i++){
            int_test.push_back(i);
        }
        REQUIRE(int_test.get_size() == 5);
        REQUIRE(int_test.get_capacity() == 10);
        REQUIRE(int_test.get_back() == 4);
        REQUIRE(int_test.get_front() == 0);
    }
    SECTION("Assignment Check"){
        DSVector<int> int_test;
        for(int i = 0; i < 7; i++){
            int_test.push_back(i);
        }
        DSVector<int> int_test_copy;
        int_test_copy = int_test;

        REQUIRE(int_test_copy.get_size() == 7);
        REQUIRE(int_test_copy.get_capacity() == 10);
        for(int i = 0; i < 7; i++){
            REQUIRE(int_test_copy[i] == i);
        }
    }
    SECTION("Erase Check"){
        DSVector<int> int_test;
        for(int i = 0; i < 5; i++){
            int_test.push_back(i);
        }
        int l = 2;
        int_test.erase_at(l);
        REQUIRE(int_test.get_front() == 0);
        REQUIRE(int_test.get_back() == 4);
        REQUIRE(int_test[2] == 3);
        REQUIRE(int_test.get_size() == 4);
        REQUIRE(int_test.get_capacity() == 10);
    }
    //testing all the new iterator functions
    SECTION("Iterator functions check"){
        DSVector<int> test;

        for(int i = 0; i < 7; i++){
            test.push_back(i);
        }

        REQUIRE(test.get_it() == test[0]);
        test.move_it_next();
        test.move_it_next();

        REQUIRE(test.get_it() == test[2]);
        REQUIRE(test.getItIndex() == 2);

        test.reset_it();
        REQUIRE(test.getItIndex() == 0);
        REQUIRE(test.get_it() == test[0]);
    }
    SECTION("Pop Back Check"){
        DSVector<int> int_test;
        for(int i = 0; i < 4; i++){
            int_test.push_back(i);
        }

        int_test.pop_back();
        REQUIRE(int_test.get_size() == 3);
        REQUIRE(int_test.get_capacity() == 10);
        REQUIRE(int_test.get_back() == 2);
    }
    SECTION("Sort Check"){
        DSVector<int> int_test;
        int_test.push_back(3);
        int_test.push_back(1);
        int_test.push_back(2);

        int_test.sort();

        REQUIRE(int_test[0] == 1);
        REQUIRE(int_test[1] == 2);
        REQUIRE(int_test[2] == 3);
    }
    SECTION("Elim Dupes Check"){
        DSVector<int> int_test;
        int_test.push_back(1);
        int_test.push_back(2);
        int_test.push_back(3);
        int_test.push_back(1);
        int_test.push_back(2);
        int_test.push_back(3);

        int_test.elim_dupes();

        REQUIRE(int_test[0] == 1);
        REQUIRE(int_test[1] == 2);
        REQUIRE(int_test[2] == 3);
    }
    SECTION("Assignment Check"){
        DSVector<int> int_test;
        for(int i = 0; i < 4; i++){
            int_test.push_back(i);
        }
        DSVector<int> checking;
        checking = int_test;

        for(int i = 0; i < 4; i++){
            REQUIRE(checking[i] == i);
        }
    }
}

//testing the linked list
TEST_CASE("DSList class", "[DSList]"){
    SECTION("constructor check"){
        DSList<int> test;

        REQUIRE(test.empty());
        REQUIRE_THROWS_AS(test.get_front(), out_of_range);
        REQUIRE_THROWS_AS(test.get_back(), out_of_range);
        REQUIRE(test.get_size() == 0);
    }
    SECTION("add and all get checks"){
        DSList<int> test;

        test.add(2);
        test.add(3);

        REQUIRE(test.get_size() == 2);
        REQUIRE(test.get_back() == 3);
        REQUIRE(test.get_front() == 2);
    }
    SECTION("empty and clear check"){
        DSList<int> test;

        for(int i = 0; i < 5; i++){
            test.add(i);
        }
        REQUIRE(test.get_size() == 5);
        REQUIRE(!test.empty());

        test.clear();

        REQUIRE(test.get_size() == 0);
        REQUIRE(test.empty());
    }
    SECTION("copy constructor check"){
        DSList<int> test;
        test.add(4);
        test.add(3);
        test.add(7);

        DSList<int> test2(test);
        REQUIRE(test2.get_size() == 3);
        REQUIRE(test2.get_front() == 4);
        REQUIRE(test2.get_back() == 7);

        test.clear();
        test.add(9);

        REQUIRE(test2.get_size() == 3);
        REQUIRE(test2.get_front() == 4);
        REQUIRE(test2.get_back() == 7);
    }
    SECTION("assignment check"){
        DSList<int> test;
        test.add(4);
        test.add(3);
        test.add(7);

        DSList<int> test2 = test;
        REQUIRE(test2.get_size() == 3);
        REQUIRE(test2.get_front() == 4);
        REQUIRE(test2.get_back() == 7);

        test.clear();
        test.add(9);

        REQUIRE(test2.get_size() == 3);
        REQUIRE(test2.get_front() == 4);
        REQUIRE(test2.get_back() == 7);
    }
    SECTION("add front check"){
        DSList<int> test;

        test.add_front(3);
        test.add_front(4);

        REQUIRE(test.get_back() == 3);
        REQUIRE(test.get_front() == 4);
    }
    SECTION("delete at check"){
        DSList<int> test;

        test.add(3);
        test.add(4);
        test.add(5);
        test.add(6);

        test.delete_at(1); //delete in middle somewhere

        REQUIRE(test.get_front() == 3);
        REQUIRE(test.get_back() == 6);
        REQUIRE(test.get_size() == 3);

        test.delete_at(0); //try delete front

        REQUIRE(test.get_size() == 2);
        REQUIRE(test.get_front() == 5);
        REQUIRE(test.get_back() == 6);

        test.add(9);
        test.add(1);

        test.delete_at(3); //try delete back

        REQUIRE(test.get_size() == 3);
        REQUIRE(test.get_front() == 5);
        REQUIRE(test.get_back() == 9);
    }
}
TEST_CASE("DSStack", "[DSStack]"){
    SECTION("Construction/copy check"){
        DSStack<int> test;

        REQUIRE(test.is_empty());
        for(int i = 0; i < 5; i++){
            test.push(i);
        }
        REQUIRE(test.top() == 4);
        DSStack<int> test2(test);
        REQUIRE(test2.top() == 4);

        test.pop();
        REQUIRE(test2.top() == 4);
    }
    SECTION("Assignment check"){
        DSStack<int> test;

        REQUIRE(test.is_empty());
        for(int i = 0; i < 5; i++){
            test.push(i);
        }
        REQUIRE(test.top() == 4);
        DSStack<int> test2 = test;
        REQUIRE(test2.top() == 4);

        test.pop();
        REQUIRE(test2.top() == 4);
    }
    SECTION("Push check"){
        DSStack<int> test;
        for(int i = 0; i < 6; i++){
            test.push(i);
            REQUIRE(test.top() == i);
        }
    }
    SECTION("Top and Pop check"){
        DSStack<int> test;
        for(int i = 0; i < 10; i++){
            test.push(i);
            REQUIRE(test.top() == i);

            test.pop();
            REQUIRE(test.is_empty());
        }
    }
    SECTION("Empty check"){
        DSStack<int> test;
        for(int i = 0; i < 10; i++){
            REQUIRE(test.is_empty());
            test.push(i);
            REQUIRE_FALSE(test.is_empty());
            test.pop();
            REQUIRE(test.is_empty());
        }
    }
}