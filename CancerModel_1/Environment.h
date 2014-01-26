//
//  Environment.h
//  CancerModel_1
//
//  Created by Yuantong Ding on 11/14/13.
//  Copyright (c) 2013 Yuantong Ding. All rights reserved.
//

#ifndef __CancerModel_1__Environment__
#define __CancerModel_1__Environment__

#include <iostream>
#include "Lattic.h"
#include <vector>
#include "Cell.h"
#include "PDE_2D.h"

class Environment
{
    std::vector<Lattic> env;
    std::vector<std::vector<Lattic>> _env_2D;
    int space = 0;
    std::vector<std::vector<double>> _oxygen;
//    std::vector<std::vector<double>> _indicater;
    int _dimension[3] = {0,0,0};
    
//    double cell_oxygen_consumption = 0.01;
//    double mean_begin_oxygen_distribution = 0;
//    double mean_end_oxygen_distribution = 0;
//    double variance_begin_oxygen_distribution = 0.2;
//    double variance_end_oxygen_distribution = 5;
    
//    double cell_glucose_consumption = 0.01;
//    double cell_growthFactor_secretion = 0.01;
//    double cell_toxic_secretion = 0.01;
    
public:
    Environment(int s);
    void set_space (int s);
    Lattic& operator[] (const int nIndex);
    void update_all_oxygen (std::vector<Cell> all_cells);
    
    int get_space() const { return space; };
    std::vector<int> empty_lattic();
    
//############### 2D ####################//
    Environment(int x, int y);
    Lattic& operator() (const int x,const int y);
    void initialO2(double o2);
    std::vector<std::vector<double>>* getO2();
    void updataOxygen(double timeStep,std::vector<std::vector<double>>* indicater);
};

#endif /* defined(__CancerModel_1__Environment__) */
