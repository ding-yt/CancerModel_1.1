//
//  Lattic.cpp
//  CancerModel_1
//
//  Created by Yuantong Ding on 11/7/13.
//  Copyright (c) 2013 Yuantong Ding. All rights reserved.
//

#include "Lattic.h"

//Lattic::Lattic (int x, int y, int z)
//{
//    location() = x;
//    location[1] = y;
//    location.push_back(z);
//}
//
//Lattic::Lattic (int x, int y)
//{
//    location.push_back(x);
//    location.push_back(y);
//    location.push_back(0);
//}

Lattic::Lattic (int x)
{
    location = x;
}

void Lattic::set_cell(int c)
{
    cell = c;
    isEmpty = false;
}

void Lattic::set_location (int x)
{
    location = x ;
}

void Lattic::set_oxygen (double o)
{
    oxygen = o;
}

void Lattic::set_glucose (double g)
{
    glucose = g;
}

void Lattic::set_growthFactor(double gf)
{
    growthFactor = gf;
}

void Lattic::remove_cell()
{
    cell = NULL;
    isEmpty = true;
}

//void Lattic::set_toxic(double t)
//{
//    toxic = t;
//}
