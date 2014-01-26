//
//  Location.h
//  CancerModel_1
//
//  Created by Yuantong Ding on 1/23/14.
//  Copyright (c) 2014 Yuantong Ding. All rights reserved.
//

#ifndef __CancerModel_1__Location__
#define __CancerModel_1__Location__

#include <iostream>
#include <vector>

#endif /* defined(__CancerModel_1__Location__) */

class Location{
    int _coordinate[3];
    int _dimension;
    
public:
    Location();
    Location(int x);
    Location(int x, int y);
    Location(int x, int y,int z);
    void setLocation(int x);
    void setLocation(int x, int y);
    void setLocation(int x, int y,int z);
    
    std::vector<Location> findNeighbour();
    Location randomNeighbour();
    
    
};