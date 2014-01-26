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
    _dimension[0] = s;
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


/*  2D
*
*/

Environment::Environment(int x, int y){
    for (int i=0; i<x; i++) {
        for (int j=0; j<y; j++) {
            _env_2D[i].push_back(Lattic());
            _oxygen[i].push_back(0.3);
            _indicater[i].push_back(0);
        }
    }
    _dimension[0] = x;
    _dimension[1] = y;
}

Lattic& Environment::operator() (const int x,const int y){
    return _env_2D[x][y];
}

void Environment::initialO2(double o2){
    for (int i=0; i<_oxygen.size(); i++) {
        for (int j=0; j<_oxygen[i].size(); j++) {
            _oxygen[i][j] = o2;
        }
    }
}

std::vector<std::vector<double>>* Environment::getO2(){
    return &_oxygen;
}

void Environment::updataOxygen(double timeStep, std::vector<std::vector<double>>* indicater){
//    for (int i=0; i<_indicater.size(); i++) {
//        for (int j=0; j<_indicater[i].size(); j++) {
//            if (!_env_2D[i][j].is_Empty()) {
//                _indicater[i][j] = _env_2D[i][j].get_cell()
//            }
//        }
//    }
    PDE_2D pde;
    pde.setDimensionStep(_dimension[0], _dimension[1]);
    pde.pdeSolve(timeStep, &_oxygen, indicater);
    
}
