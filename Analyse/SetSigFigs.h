// C++ program to round-off a number to given no. of 
// significant digits 
//#include <bits/stdc++.h> 
/*#include <iostream>
//#include <boost/math/special_functions/round.hpp>
//#include <math.h>
#include <cmath>
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

double SetSigFigs(double d, int digits)
{   
    if(d == 0)
        return 0;

    //decimal scale = (decimal)Math.Pow(10, Math.Floor(Math.Log10(Math.Abs(d))) + 1);
    double scale = pow(10, floor(log10(abs(d))) + 1);
    // C++ 11 has a function just called "round"
    return scale * boost::math::round(d / scale, digits);
}*/