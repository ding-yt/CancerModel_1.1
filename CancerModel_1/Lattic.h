//
//  Lattic.h
//  CancerModel_1
//
//  Created by Yuantong Ding on 11/7/13.
//  Copyright (c) 2013 Yuantong Ding. All rights reserved.
//

#ifndef __CancerModel_1__Lattic__
#define __CancerModel_1__Lattic__

#include <iostream>

class Lattic
{
    int location;
    int cell;
    double oxygen = 0;
    double glucose = 0;
    double growthFactor = 0;
    double toxic = 0;
    bool isEmpty = true;
//    int space;
    
public:
//    Lattic (int x, int y, int z);
//    Lattic (int x, int y);
    Lattic ();
    Lattic (int x);
    void set_location (int x);
    void set_cell (int c);
    void set_oxygen (double o);
    void set_glucose (double g);
    void set_growthFactor (double gf);
    void set_toxic (double t);
//    void set_space (int sp) { space = sp; };
//    void set_isEmpty (bool iE);
    
    int get_location() const { return location; }
    int get_cell() const { return cell; }
    double get_oxygen() const { return oxygen; }
    double get_glucose() const { return glucose; }
    double get_growthFactor() const { return growthFactor; }
    double get_toxic() const { return toxic; }
    bool is_Empty() const { return isEmpty; }
    
    void remove_cell();
};

#endif /* defined(__CancerModel_1__Lattic__) */



