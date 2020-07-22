//
//  lib.h
//  Bilinear_Interpolation
//
//  Created by  Maulik Patel on 22/07/2020.
//  Copyright © 2020 Maulik Patel. All rights reserved.
//

#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <algorithm>

typedef  std::vector<uint16_t>      array1d_u16 ;
typedef  std::vector<array1d_u16>   array2d_u16;


template <typename T>
int linearInterpolation( const T start, const T end, const size_t numPoints, std::vector<T> &buffer )
{
    if( numPoints <= 0 )
        return 1;
    
    buffer.resize(numPoints);           // resize buffer for required size
    buffer.at(0) = start;               // populate given start point
    buffer.at(numPoints-1) = end;       // populate given end point
    double rate = ((double) (end - start)) / (numPoints-1); // calculate the even space between two consecutive points
    for( size_t i{1} ; i< numPoints-1; i++ )
        buffer.at(i) = (T) (start+ i*rate );

    return 0;
}



bool approximatelyEqualAbsRel(double a, double b, double absEpsilon, double relEpsilon)
{
    // Check if the numbers are really close -- needed when comparing numbers near zero.
    double diff{ std::abs(a - b) };
    if (diff <= absEpsilon)
        return true;
 
    // Otherwise fall back to Knuth's algorithm
    return (diff <= (std::max(std::abs(a), std::abs(b)) * relEpsilon));
}
