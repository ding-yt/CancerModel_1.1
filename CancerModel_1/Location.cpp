//
//  Location.cpp
//  CancerModel_1
//
//  Created by Yuantong Ding on 1/23/14.
//  Copyright (c) 2014 Yuantong Ding. All rights reserved.
//

#include "Location.h"
Location::Location(int i){
    _coordinate[0] = i;
    _coordinate[1] = -1;
    _coordinate[2] = -1;
    _dimension = 1;
};

Location::Location(int i, int j){
    _coordinate[0] = i;
    _coordinate[1] = j;
    _coordinate[2] = -1;
    _dimension = 2;
}

Location::Location(int x, int y,int z){
    _coordinate[0] = x;
    _coordinate[1] = y;
    _coordinate[2] = z;
    _dimension = 3;
}

void Location::setLocation(int i){
    _coordinate[0] = i;
};

void Location::setLocation(int i, int j){
    _coordinate[0] = i;
    _coordinate[1] = j;
}

void Location::setLocation(int x, int y,int z){
    _coordinate[0] = x;
    _coordinate[1] = y;
    _coordinate[2] = z;
}

std::vector<Location> Location::findNeighbour(){
    std::vector<Location> temp;
    switch (_dimension) {
        case 1:            
            temp.push_back(Location(_coordinate[0]-1));
            temp.push_back(Location(_coordinate[0]+1));            
            return temp;
            break;
        case 2:
            for (int x=-1; x<=1; x++) {
                for (int y=-1; y<=1; y++) {
                    temp.push_back(Location(_coordinate[0]+x,_coordinate[1]+y));
                }
            }
            return temp;
            break;
        default:
            break;
    }
}

