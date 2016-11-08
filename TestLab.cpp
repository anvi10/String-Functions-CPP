#include <iostream>
#include <cstdlib> // atoi
#include <string.h>
#include <stdio.h>
#include <vector>
using namespace std;

// This is the structure used to hold test cases, along with their associated point numbers
typedef struct  {
  // Number of points in test case
  int points;
  // The test to run
  bool (*test)();
} TestCase;


// TEST is a nice way to display errors,similar to assert. We run it as follows
// TEST(something==somethingelse,"This is what we are testing");
#define S(x) #x
#define STRINGIFY(x) S(x)
#define TEST(a,b) if (!(a)) {\
    cout << __FILE__ << ":" << STRINGIFY(__LINE__) << " (" << #a << ") TEST FAILED:\n\t" << b << endl;\
    return false;\
}


#include "MyString.h"


// ----------------------------------------------
// Tests for the constructor

bool constructor_test1() {
  cout << "Testing MyString::MyString(char*)" << endl;

  MyString s;
  TEST(strlen(s.cStr())==0,"Making sure that string length is 0 (and it exists)");
  return true;
}

// This is copy of test1 - it makes sure that the default initializer copies its string
bool constructor_test2() {
  cout << "Testing MyString::MyString(char*)" << endl;

  const char *s1 = "Ramsay Bolton";
  MyString ms1(s1);
  TEST(ms1.cStr()!=s1,"ensuring that pointer is different")
  TEST(!strcmp(ms1.cStr(),s1 ),"Making sure string value is copied");

  return true;
}

// This is copy of test1 - it makes sure that the default initializer copies its string
bool constructor_test3() {
  cout << "Testing MyString::MyString(char*)" << endl;

  const char *s1 = "";
  MyString ms1(s1);
  TEST(ms1.cStr()!=s1,"ensuring that empty string pointer is different");
  TEST(!strcmp(ms1.cStr(),s1 ),"Making sure string value is copied");

  return true;
}

bool constructor_test4() {
  cout << "Testing MyString::MyString(MyString&)" << endl;

  MyString ms1("Hello World!");
  MyString ms2(ms1);
  TEST(ms1.cStr()!=ms2.cStr(),"ensuring that string pointer is different");
  TEST(!strcmp(ms2.cStr(),"Hello World!"),"Making sure string value is copied");
  return true;
}

bool constructor_test5() {
  cout << "Testing MyString::MyString(MyString&)" << endl;

  MyString ms1("");
  MyString ms2(ms1);
  TEST(ms1.cStr()!=ms2.cStr(),"ensuring that empty string pointer is different");
  TEST(!strcmp(ms2.cStr(),""),"Making sure empty string value is copied");

  return true;
}


// ----------------------------------------------
// Operator==

bool operatoreq_test1() {
  cout << "Testing MyString::operator== and != 1" << endl;

  MyString ms1("");
  MyString ms2("");
  TEST(ms1==ms2,"Empty strings are equal");
  TEST(!(ms1!=ms2),"Empty strings are equal");

  return true;
}
bool operatoreq_test2() {
  cout << "Testing MyString::operator== and != 2" << endl;

  MyString ms1("wrgfxhhtfs t!");
  MyString ms2("wrgfxhhtfs t!");
  TEST(ms1==ms2,"String equality");
  TEST(!(ms1!=ms2),"String equality");

  MyString ms3(ms1);
  TEST(ms3==ms2,"Rebuilt string equality");
  TEST(!(ms3!=ms2),"Rebuilt string inequality");

  MyString ms4("wrgfxhhtjs t!");
  MyString ms5("wrgfxhhtfs t!");
  //                    ^
  TEST(!(ms4==ms5),"String inequality");
  TEST(ms4!=ms5,"String inequality");

  MyString ms6(ms4);
  TEST(!(ms6==ms5),"Rebuilt string inequality");
  TEST(ms6!=ms5,"Rebuilt string inequality");

  return true;
}
bool operatoreq_test3() {
  cout << "Testing MyString::operator== and != 3" << endl;

  MyString ms1("wrgfxhhtj");
  MyString ms2("wrgfxhhtjs t!");

  TEST(!(ms1==ms2),"Different size string inequality");
  TEST(ms1!=ms2,"Different size string inequality");

  MyString ms3(ms1);
  TEST(!(ms3==ms2),"Rebuilt string different size inequality");
  TEST(ms3!=ms2,"Rebuilt string different size inequality");

  MyString ms4("wrgfxhhtjs t!");
  MyString ms5("wrgfxhhtj");

  TEST(!(ms4==ms5),"Different size string inequality 2");
  TEST(ms4!=ms5,"Different size string inequality 2");

  MyString ms6(ms4);
  TEST(!(ms6==ms5),"Rebuilt string different size inequality 2");
  TEST(ms6!=ms5,"Rebuilt string different size inequality 2");

  return true;
}


// ----------------------------------------------
// Operator>

bool operatorgt_test1() {
  cout << "Testing MyString::operator <= and > 1" << endl;

  MyString ms1("");
  MyString ms2("");
  TEST(ms1<=ms2,"Empty strings are equal");
  TEST(!(ms1>ms2),"Empty strings are equal");

  MyString ms3("Hello World!");
  MyString ms4("Hello World!");
  TEST(ms3<=ms4,"Equal strings are equal");
  TEST(!(ms3>ms4),"Equal strings are equal");

  return true;
}

bool operatorgt_test2() {
  cout << "Testing MyString::operator <= and > 2" << endl;

  MyString ms1("Rawr I am Hungry!");
  MyString ms2("Rawr I am Hungry!!");
  TEST(ms1<=ms2,"Longer/shorter strings 1");
  TEST(!(ms1>ms2),"Longer/shorter strings 1");

  MyString ms3("Rawr I am Hungry!!");
  MyString ms4("Rawr I am Hungry!");
  TEST(!(ms3<=ms4),"Longer/shorter strings 2");
  TEST(ms3>ms4,"Longer/shorter strings 2");

  return true;
}

bool operatorgt_test3() {
  cout << "Testing MyString::operator <= and > 3" << endl;

  MyString ms1("bollywood");
  MyString ms2("hollywood");
  TEST(ms1<=ms2,"Alphabetical 1");
  TEST(!(ms1>ms2),"Alphabetical 1");
  TEST(!(ms2<=ms1),"Alphabetical 1");
  TEST(ms2>ms1,"Alphabetical 1");

  MyString ms3("aaab");
  MyString ms4("aaaa");
  TEST(!(ms3<=ms4),"Alphabetical 2");
  TEST(ms3>ms4,"Alphabetical 2");
  TEST(ms4<=ms3,"Alphabetical 2");
  TEST(!(ms4>ms3),"Alphabetical 2");

  return true;
}


bool operatorset_test1() {
  cout << "Testing MyString::operator =" << endl;

  MyString ms1;
  MyString ms2("Hello World!!");
  MyString ms3("Another!");

  ms1 = ms2;
  ms3 = ms2;

  TEST(ms1.cStr()!=ms2.cStr(),"Making sure copy happens on set");
  TEST(!strcmp(ms1.cStr(),ms2.cStr()),"Making sure copy was correct");

  TEST(ms3.cStr()!=ms2.cStr(),"Making sure copy happens on set");
  TEST(!strcmp(ms3.cStr(),ms2.cStr()),"Making sure copy was correct");

  return true;
}


bool operatorindex_test1() {
  cout << "Testing MyString::operator []" << endl;

  const char* teststring = "Hello There!";
  MyString ms1(teststring);

  for (int i=0;i<12;i++) {
    TEST(ms1[i]==teststring[i],"Ensuring string indexing works");
  }

  // We didn't specify how to respond beyond the bounds, so we don't do anything

  return true;
}

bool length_test1() {
  cout << "Testing MyString::length" << endl;

  const char* teststring = "Hello There! 4efekmaeko43\t\r";
  TEST(MyString(teststring).length()==(int)strlen(teststring),"Making sure test string lengths match");
  TEST(MyString("").length()==0,"Making sure empty string is length 0");

  return true;
}

bool substring_test1() {
  cout << "Testing MyString::substring basics" << endl;

  const char* teststring = "Hi there!";
  MyString ms1(teststring);

  const char* ms1loc = ms1.cStr();

  MyString ss = ms1.substring(1,4);

  TEST(ms1.cStr()==ms1loc,"Making sure string location doesn't change on substring");
  TEST(ss.cStr()!=ms1loc+1,"Making sure that memory was actually copied");
  TEST(!strcmp(ms1.cStr(),teststring),"Making sure original wasn't modified");
  TEST(!strcmp(ss.cStr(),"i th"),"Making sure correct substring chosen");

  return true;
}

bool substring_test2() {
  cout << "Testing MyString::substring size bounds" << endl;

  const char* teststring = "Hi there!";
  MyString ms1(teststring);

  TEST(!strcmp(ms1.substring(1,342345).cStr(),"i there!"),"Making sure correct substring chosen");
  TEST(!strcmp(ms1.substring(1,0).cStr(),""),"Making sure size 0 substring works");
  TEST(!strcmp(ms1.substring(9,2).cStr(),""),"What if we put index right at the end of the string?");

  return true;
}

bool substring_test3() {
  cout << "Testing MyString::substring index out of bounds" << endl;

  const char* teststring = "OCRAP I MIGHT SEGFAULT";
  MyString ms1(teststring);

  try {
    TEST(!strcmp(ms1.substring(300000,2).cStr(),""),"Indexing at wrong location is a no-no");
  } catch (...) {
    // If the student throws an exception, all is well
    cout << "Exception caught for an out of bound index. Good job!" << endl;
  }

  return true;
}



bool remove_test1() {
  cout << "Testing MyString::remove" << endl;

  MyString ms1("Johnny's string removal services.");

  const char* sloc = ms1.cStr();

  ms1.remove(4,2);

  TEST(!strcmp(ms1.cStr(),"John's string removal services."),"Making sure basic remove works");

  // Let's check if they were clever about it...
  if (ms1.cStr()==sloc) {
    cout << "Looks like you didn't reallocate memory to remove from a string. Very nice thinking.\nIn some cases, you might want to reallocate anyways if the new string is much shorter." << endl;
  }

  return true;
}

bool remove_test2() {
  cout << "Testing MyString::remove length bounds" << endl;

  const char* teststring = "Johnny's string removal services.";
  MyString ms1(teststring);

  const char* sloc = ms1.cStr();

  ms1.remove(4,0);
  TEST(!strcmp(ms1.cStr(),teststring),"Making sure removing 0 doesn't do anything.");

  // No need to reallocate if nothing removed
  if (ms1.cStr()!=sloc) {
    cout << "WARNING: When removing 0, you have no need to create a new string!" << endl;
  }

  ms1.remove(4,324343);

  TEST(!strcmp(ms1.cStr(),"John"),"Checking for correct remove of out of bounds string");

  return true;
}

bool remove_test3() {
  cout << "Testing MyString::remove index bounds" << endl;

  const char* teststring = "OCRAP I MIGHT SEGFAULT";
  MyString ms1(teststring);

  try {
    ms1.remove(300000,2);
    TEST(!strcmp(ms1.cStr(),teststring),"Indexing at wrong location is a no-no");
  } catch (...) {
    // If the student throws an exception, all is well
    cout << "Exception caught for an out of bound index. Good job!" << endl;
  }

  return true;

}

bool operatorplus_test1() {
  cout << "Testing MyString::operator + 1" << endl;

  const char* ms1s = "Oh Hello ";
  const char* ms2s = "World!";
  MyString ms1(ms1s);
  MyString ms2(ms2s);
  TEST(!strcmp((ms1+ms2).cStr(),"Oh Hello World!"),"Making sure adding strings works fine...");
  TEST(!strcmp(ms1.cStr(),ms1s),"Making sure string 1 isn't changed after add");
  TEST(!strcmp(ms2.cStr(),ms2s),"Making sure string 2 isn't changed after add");

  return true;
}

bool operatorplus_test2() {
  cout << "Testing MyString::operator + 2" << endl;
  const char* teststring = "Foo Bar Baz\nW00t";
  MyString ms1(teststring);

  MyString ms2;

  TEST(!strcmp((ms1+ms2).cStr(),teststring),"Making sure adding an empty string works fine");
  TEST(!strcmp((ms2+ms1).cStr(),teststring),"Making sure adding an empty string works fine");

  return true;
}


bool words_test1() {
  cout << "Testing words (basic)" << endl;

  vector<MyString> v = words(MyString("This is a basic test of words"));

  TEST(v.size()==7,"'This is a basic test of words' should have vector length 7");
  TEST(!strcmp(v[0].cStr(),"This"),"Wrong word!");
  TEST(!strcmp(v[1].cStr(),"is"),"Wrong word!");
  TEST(!strcmp(v[2].cStr(),"a"),"Wrong word!");
  TEST(!strcmp(v[3].cStr(),"basic"),"Wrong word!");
  TEST(!strcmp(v[4].cStr(),"test"),"Wrong word!");
  TEST(!strcmp(v[5].cStr(),"of"),"Wrong word!");
  TEST(!strcmp(v[6].cStr(),"words"),"Wrong word!");

  return true;
}

bool words_test2() {
  cout << "Testing words (cutoffs)" << endl;

  const char* teststring = "Th1s is a not-basic\ntest of words.";

  cout << "Using test string: \"" << teststring << "\"" << endl;

  vector<MyString> v = words(MyString(teststring));
  TEST(v.size()==9,"vector should have vector length 9");
  TEST(!strcmp(v[0].cStr(),"Th"),"Wrong word!");
  TEST(!strcmp(v[1].cStr(),"s"),"Wrong word!");
  TEST(!strcmp(v[2].cStr(),"is"),"Wrong word!");
  TEST(!strcmp(v[3].cStr(),"a"),"Wrong word!");
  TEST(!strcmp(v[4].cStr(),"not"),"Wrong word!");
  TEST(!strcmp(v[5].cStr(),"basic"),"Wrong word!");
  TEST(!strcmp(v[6].cStr(),"test"),"Wrong word!");
  TEST(!strcmp(v[7].cStr(),"of"),"Wrong word!");
  TEST(!strcmp(v[8].cStr(),"words"),"Wrong word!");

  return true;
}

bool words_test3() {
  cout << "Testing words (advanced)" << endl;

  const char* teststring = "wg  456 $ .! \n\r w.@$# lol...hi";

  cout << "Using test string: \"" << teststring << "\"" << endl;

  vector<MyString> v = words(MyString(teststring));
  TEST(v.size()==4,"vector should have 4 words");
  TEST(!strcmp(v[0].cStr(),"wg"),"Wrong word!");
  TEST(!strcmp(v[1].cStr(),"w"),"Wrong word!");
  TEST(!strcmp(v[2].cStr(),"lol"),"Wrong word!");
  TEST(!strcmp(v[3].cStr(),"hi"),"Wrong word!");

  return true;
}

bool roman_test1() {
  cout << "Testing roman (basic)" << endl;

  TEST(roman(MyString("I"))==1,"Checking roman basics");
  TEST(roman(MyString("V"))==5,"Checking roman basics");
  TEST(roman(MyString("X"))==10,"Checking roman basics");
  TEST(roman(MyString("L"))==50,"Checking roman basics");
  TEST(roman(MyString("C"))==100,"Checking roman basics");

  return true;
}

bool roman_test2() {
  cout << "Testing roman (additive)" << endl;

  TEST(roman(MyString("II"))==2,"Checking roman additive");
  TEST(roman(MyString("VI"))==6,"Checking roman additive");
  TEST(roman(MyString("VII"))==7,"Checking roman additive");
  TEST(roman(MyString("XI"))==11,"Checking roman additive");
  TEST(roman(MyString("XVI"))==16,"Checking roman additive");
  TEST(roman(MyString("LX"))==60,"Checking roman additive");
  TEST(roman(MyString("LXXI"))==71,"Checking roman additive");
  TEST(roman(MyString("CXI"))==111,"Checking roman additive");
  TEST(roman(MyString("CCVII"))==207,"Checking roman additive");

  return true;
}

bool roman_test3() {
  cout << "Testing roman (subtraction)" << endl;

  TEST(roman(MyString("IV"))==4,"Checking roman subtraction");
  TEST(roman(MyString("XIV"))==14,"Checking roman subtraction");
  TEST(roman(MyString("XIV"))==14,"Checking roman subtraction");
  TEST(roman(MyString("XIX"))==19,"Checking roman subtraction");
  TEST(roman(MyString("IXX"))==19,"Checking roman subtraction");


  return true;
}

bool roman_test4() {
  cout << "Testing roman (unusual)" << endl;
  
  TEST(roman(MyString("IIV"))==3,"Checking roman subtraction");
  TEST(roman(MyString("XIIX"))==18,"Checking roman subtraction");
    TEST(roman(MyString("IIXX"))==18,"Checking roman subtraction");

  // To those sensitive snowflakes: This is a yo-momma joke (look it up). Please don't fire me.
  unsigned int your_mom = 30;
  TEST(roman(MyString("XXL"))==your_mom,"checking if XXL == 30");
  
  TEST(roman(MyString("IIIIV"))==1,"Subtraction should work however far you need it to go");
  TEST(roman(MyString("IIIII"))==5,"These are weird notations that are nevertheless sometimes used");
  TEST(roman(MyString("IIVII"))==5,"Can you symmetry?");

  return true;
}

// ----------------------------------------------


// The total number of points in the whole assignment
#define TOTALPOINTS 100

// The total number of tests
#define TESTNUMBER 29

// Each test case is put in here, along with its point value
const TestCase testcases[TESTNUMBER] = {
  {5,constructor_test1},{5,constructor_test2},{3,constructor_test3},{5,constructor_test4},{2,constructor_test5},
  {2,operatoreq_test1},{4,operatoreq_test2},{4,operatoreq_test3},
  {3,operatorgt_test1},{4,operatorgt_test2},{3,operatorgt_test3},
  {5,operatorset_test1},
  {5,operatorindex_test1},
  {5,length_test1},
  {2,substring_test1},{2,substring_test2},{1,substring_test3},
  {2,remove_test1},{2,remove_test2},{1,remove_test3},
  {3,operatorplus_test1},{2,operatorplus_test2},
  {2,words_test1},{2,words_test2},{1,words_test3},
  {2,roman_test1},{3,roman_test2},{3,roman_test3},{2,roman_test4},
};


int main(int argc, char** argv) {
    // NOTE: This grading file was modified to not include the framework used to grade. It just includes a way to run the test cases.
    // Therefore, your code might behave a little differently, since memory and time limits are not imposed. Our grading system's output is
    // considered the source of truth.
    for (int i=0;i<TESTNUMBER;i++) {
        if (testcases[i].test()) {
            cout << "Test Passed!" << endl;
        } else {
            cout << "Test Failed!" << endl;
        }
    }
    return 0;
}
