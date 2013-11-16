//
//  CellFate.cpp
//  CancerModel_1
//
//  Created by Yuantong Ding on 11/8/13.
//  Copyright (c) 2013 Yuantong Ding. All rights reserved.
//

#include "CellFate.h"
#include "Lattic.h"
#include "Cell.h"
#include <string>
#include <math.h> 
#include <ctime>

//CellFate::CellFate (Cell::Cell c, Lattic::Lattic l)
//{
//    cells = c;
//    lattics = l;
////    generation = g;
////    current_generation = cg;
////    space = s;
//}

void CellFate::decide_fate(Cell& c, Lattic& l, double oxygen_diffusion)
{
//    Cell cells = c;
//    Lattic lattics = l;
    std::string stage;
    stage = c.get_stage();
//    double location_transfer = -5 + 10/space*lattics.get_location();
//    double mean = mean_begin_oxygen_distribution + current_generation*(mean_end_oxygen_distribution - mean_begin_oxygen_distribution)/generation;
//    double variance = variance_begin_oxygen_distribution + current_generation * (variance_end_oxygen_distribution - variance_begin_oxygen_distribution)/generation;
//    double oxygen_distribution = 1/sqrt(variance*2*3.14)*exp(-(location_transfer-mean)/(2*variance));
    double oxygen = l.get_oxygen() + oxygen_diffusion;
    
    if (stage != "death") {
        if (oxygen <= death_threshold_oxygen) {
            c.set_stage("death");
//            std::cout << "\n cell dead\n";
            l.remove_cell();
        }else if (oxygen <= quiescence_threshold_oxygen){
            c.set_stage("quiescence");
        }else{
            c.set_stage("proliferation");
        }
    }
    
}

Cell CellFate::migration(Cell& c, Environment& e)
{
    srand((unsigned)time(0));
    int r = rand() % 100;
//    std::cout <<"rand "<<r<<"\n";
    double rate = c.get_migration_rate();
    int daughter_location = c.get_location();
    Cell daughter = c;
    
    if ((double)r/100 <= rate) {
        std::vector<int> empty_space = e.empty_lattic();
        int index = rand()%empty_space.size();
        if (index != 0 ) {
            daughter_location = empty_space[index];
            std::cout << "migrate!\n";
            daughter.set_location(daughter_location);
            daughter.set_parent(c.get_name());
        }        
    }
    
    return daughter;
}

bool CellFate::mutate(Cell &c)
{
    srand((unsigned)time(0));
    int r = rand() % 100;
    double rate = (double)r/100;
//    std::cout <<"rand "<<rate<<"\n";
    if (rate < c.get_mutation_rate()) {
        return true;
    }else{
        return false;
    }
}