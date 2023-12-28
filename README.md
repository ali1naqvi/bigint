# Bigint Class Documentation

## Overview
The `bigint` class is a C++ implementation designed to hold quite large numbers. It either accepts numbers that are small enough to fit into a int64_t type or numbers larger (they would have to be defined as a string.)

## Features
- Arbitrary-length integer handling.
- Basic arithmetic operations (addition, subtraction, multiplication).
- Comparison operations (equal, not equal, less than, greater than, etc.).
- Handling of both positive and negative large integers.
- values can be taken in as a string or as an int.

## Usage
The class provides multiple constructors:  
    bigint(): Initializes a bigint with a value of 0.  
    bigint(const string&): Initializes a bigint from a string.  
    bigint(const int64_t&): Initializes a bigint from an int64_t value.  
To use these constructors:  
    bigint a; // Default constructor  
    bigint b("-1092992939929329323"); // From string  
    bigint c(132838283); // From int64_t  
With this, you can then add, subtract, multiply, or compare like you would do with any variable.  

## Examples  
bigint add1("123456");  
bigint add2("654321");  
add1 + add1 = 777777;  

bigint sub1("123456");  
bigint sub2("654321");  
sub1 - sub2 = -530865;  

## Future Work  
Due to time constraints, I could not implement 'int64_t' numbers interacting with bigint variables properly. Although it was not resuired, I still wish to complete this task.  

### Include the Header  
To use the `bigint` class, include its header file in your C++ project:  
```cpp  
#include "bigint.h"  
