// C++ program to round-off a number to given no. of 
// significant digits 
//#include <bits/stdc++.h> 
#include <iostream>
using namespace std; 
  
// Function to round - off the number 
double RoundOff(double N, double n) 
{ 
    int h; 
    double l, a, b, c, d, e, i, j, m, f, g; 
    b = N; 
    c = floor(N); 
  
    // Counting the no. of digits to the left of decimal point 
    // in the given no. 
    for (i = 0; b >= 1; ++i) 
        b = b / 10; 
  
    d = n - i; 
    b = N; 
    b = b * pow(10, d); 
    e = b + 0.5; 
    if ((float)e == (float)ceil(b)) { 
        f = (ceil(b)); 
        h = f - 2; 
        if (h % 2 != 0) { 
            e = e - 1; 
        } 
    } 
    j = floor(e); 
    m = pow(10, d); 
    j = j / m; 
    
    return j; 
} 