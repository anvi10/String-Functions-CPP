
// CS251 Data Structures
// String Implementation
// IMPORTANT: Do not use any of the functions in the string C runtime library
// Example. Do not use strcpy, strcmp, etc. Implement your own

// IMPORTANT: See the MyString.h file for a description of
// what each method needs to do.

#include <stdio.h>
#include <string.h>
#include "MyString.h"
#include <iostream>
// My own implementation of strlen
using namespace std;

int
MyString::slength(const char *s) const
{
  //TODO
  int i = 0;
while (*s != '\0') {
	s++;
	i++;
}
return i;	
}

char *
MyString::mystrdup(const char * s) {
 int l = slength(s);
         char * c;
         c = new char[l];
         int i = 0;
         for (i = 0; i <l; i ++) {
                 c[i] = s[i];
         }   
         return c;
}

// Initialize _s. Allocate memory for _s and copy s into _s
void
MyString::initialize(const char * s)
{
  //TODO
int len = slength(s); //will call the funct on line 16
_s = new char[len+1];
int x = 0;
for ( x = 0; x < len; x++) {
	_s[x] = s[x];
}
_s[len] = '\0';

}

// Create a MyString from a C string
MyString::MyString(const char * s)
{
	initialize(s);
}

// Create a MyString from a copy of another string
MyString::MyString(const MyString &s)
{
  //TODO
  initialize(s._s);
}

// Create a MyString with an empty string
MyString::MyString()
{
  //TODO
  initialize("");
}

// Assignment operator. Without this operator the assignment is
// just a shallow copy that will copy the pointer _s. If the original _s
// goes away then the assigned _s will be a dangling reference.
MyString &
MyString::operator = (const MyString & other) {
  //TODO
  initialize(other._s);
}

// Obtain a substring of at most n chars starting at location i
// if i is larger than the length of the string return an empty string.
MyString
MyString::substring(int i, int p)
{
	int n = i+p;
	char * sub = new char[n-i+1];
	int j;

	for (j = i; j<n; j++) {
		sub[j-i] = _s[j];
	}

	sub[n-i] = '\0';

	return MyString(sub);
}

// Remove at most n chars starting at location i
void
MyString::remove(int j, int n)
{
	
  int l = slength(_s);
  int len = l - n;
  char * news = new char [len+1];
  news[len] = '\0';
  int k = 0;

  for (int i = 0; i<l; i++, k++) {
  	if (i==j) { 
		i+=n;
	}
	news[k] = _s[i];
  }

  delete _s;
  _s = news;
  //TODO
}

// Return true if strings "this" and s are equal
bool
MyString::operator == (const MyString & st)
{
 char * s = st._s;
 char * t = this->_s;

int i = 0;
      while(t[i] != '\0') {
              	if (t[i] != s[i]) {
	      		return false;
		}
      i++;
      }

        if( s[i] != '\0' ) {
		return false;
	}
return true;
}


// Return true if strings "this" and s are not equal
bool
MyString::operator != (const MyString &s)
{
	return !(this->_s == s._s);
}

// Return true if string "this"  is less than  or equal to s
bool
MyString::operator <= (const MyString &s)
{
  //TODO
  char * s2 = s._s;
  char *t = this->_s;
  int i = 0;

        while(s2[i] != '\0') {
		if (t[i] == '\0') 
			return true;
		if (t[i] < s2[i] ) 
			return true;
		if (t[i] > s2[i]) 
			return false;
	i++;
        }

	if (t[i] == '\0') 
		return true;

return false;
}

// Return true if string "this" is greater than s
bool
MyString::operator > (const MyString &s)
{
	return !(this->_s <= s._s);
}

// Return character at position i
char
MyString::operator [] (int i)
{
	return _s[i];
}

// Return C representation of string
const char *
MyString::cStr()
{
	return _s;
}

// Get string length of this string.
int
MyString::length() const
{
	return slength(this->_s);
}

// Destructor. Deallocate the space used by _s
MyString::~MyString()
{
 	delete _s;
}

// Concatanate two strings (non member method)
MyString operator + (const MyString  &s1o , const MyString  &s2o )
{
 char * out = new char[s1o.length() + s2o.length() + 1];
 char * s1 = s1o._s;
 char * s2 = s2o._s;
 int i = 0;
        int j = 0;
        while (s1[i] != '\0') {
                out[i] = s1[i];
		i++;
		}
	while(s2[j] != '\0') {
			
                out[i+j] = s2[j];

                j++;
        }   
	
        out [i+j] = '\0';
        return MyString(out);
}

/* Break a string into substrings of letters, e.g "A dog and a hyper-sphere"
breaks into <"A", "dog", "and", "a", "hyper", "sphere">.  The input is a string
and the output is a vector of strings. */
std::vector<MyString> words (MyString in) {
  //TODO
  vector <MyString> out ;
  int l = in.length();
  char * s = new char [l+1];
 
 for (int k = 0; k<l; k++) {
 	s[k] = in[k];
 }

 s[l] = '\0';
  int i = 0;
  int j = 0;
	while (s[i] != '\0') {

		while ((s[j] >= 'a' && s[j] <= 'z') || (s[j] >= 'A' && s[j] <= 'Z')) { 
			j++;
		}

		char t = s[j];
		s[j] = '\0';
		out.push_back(MyString(&s[i]));
		i = j+1;
		s[j] = t;
		j++;
	}
	return out;
}

/*
Convert a roman numberal into a number, e.g. "CLXIV" converts to 164.  The
input is a roman numeral expressed as a string whose characters are "I", "V",
"X", "L", and "C".  The output is a positive integer.
*/

int cases(char c) {

	if(c == 'M')
		return 1000;
	if(c == 'D')
		return 500;
	if(c == 'C')
		return 100;
	if(c == 'L')
		return 50;
	if(c == 'X')
		return 10;
	if(c == 'V')
		return 5;
	if(c == 'I')
		return 1;
}

unsigned int roman (MyString s) {
  //TODO
  int output = 0;
  char c = ' '; 
  int end = s.length() - 1;

for (int i = end; i >= 0; i--) {
int tempRom = cases(s[i]);

	if ( tempRom < output ) {
		if ( s[i] != c  ) {
			output -= tempRom;
			c = s[i];
		}
	} else {
		output += tempRom;
		c = s[i];
	}
}
  return output;
}

