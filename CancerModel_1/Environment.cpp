//
//  Environment.cpp
//  CancerModel_1
//
//  Created by Yuantong Ding on 11/14/13.
//  Copyright (c) 2013 Yuantong Ding. All rights reserved.
//

#include "Environment.h"
Environment::Environment(int s)
{
    space = s;
    int i;
    for (i = 0; i < space; i++) {
        env.push_back(Lattic(i));
    }
    
}

Lattic& Environment::operator[] (const int nIndex)
{
    return env[nIndex];
}

void Environment::set_space (int s)
{
    space = s;
}

void Environment::update_all_oxygen(std::vector<Cell> all_cells)
{
    for (int i=0; i<space; i++) {
        if (!env[i].is_Empty()) {
            int temp_cell = env[i].get_cell();
            env[i].set_oxygen(env[i].get_oxygen() - all_cells[temp_cell].get_oxygen_consumption());
        }      
    }
}

std::vector<int> Environment::empty_lattic()
{
    std::vector<int> empty_lattics;
    for (int i=0; i< space; i++) {
        if (env[i].is_Empty()) {
            empty_lattics.push_back(env[i].get_location());
        }
    }
    return empty_lattics;
}

//void Environment::initialize_enviroment()
//{
//    int i;
//    for (i = 0; i < space; i++) {
//        env.push_back(Lattic(i));
//    }
//}