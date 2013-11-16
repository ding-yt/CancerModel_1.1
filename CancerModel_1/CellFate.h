//
//  CellFate.h
//  CancerModel_1
//
//  Created by Yuantong Ding on 11/8/13.
//  Copyright (c) 2013 Yuantong Ding. All rights reserved.
//

#ifndef __CancerModel_1__CellFate__
#define __CancerModel_1__CellFate__

#include <iostream>
#include <string>
#include "Lattic.h"
#include "Cell.h"
#include "Environment.h"

class CellFate
{
//    Lattic::Lattic lattics;
//    Cell::Cell cells;

    
//    int generation;
//    int current_generation;
//    int space;
    double death_threshold_oxygen = 0.10;
    double quiescence_threshold_oxygen = 0.12;
//    double mean_begin_oxygen_distribution = 0;
//    double mean_end_oxygen_distribution = 0;
//    double variance_begin_oxygen_distribution = 0.2;
//    double variance_end_oxygen_distribution = 5;

    
public:
    CellFate (int i) {;} ;
//    CellFate (Cell::Cell c, Lattic::Lattic l);
    void decide_fate(Cell& c, Lattic& l, double oxygen_diffusion);
    Cell migration(Cell& c, Environment& e);
    bool mutate(Cell&c);
    
    
};

#endif /* defined(__CancerModel_1__CellFate__) */
