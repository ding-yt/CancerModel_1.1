//
//  Cell.cpp
//  CancerModel_1
//
//  Created by Yuantong Ding on 11/7/13.
//  Copyright (c) 2013 Yuantong Ding. All rights reserved.
//

#include "Cell.h"
#include <vector>
#include <ctime>

CellType Cell::celltypes = CellType(1);

void Cell::set_celltype(CellType all_types){
    celltypes = all_types;
}

Cell::Cell (int n, int t, int l)
{
    name = n;
    type = t;
    location.push_back(l);
    stage = "alive";
    parent = -1;
//    switch (type) {
//        case 0:
//            oxygen_consumption = 0.00002;
//            glucose_consumption = 0;
//            growthFactor_secretion = 0;
//            toxic_secretion = 0;
//            proliferation_time = 8;
//            death_rate = 0;
//            mutation_rate = 0;
//            migration_rate = 0;
//            break;
//        case 1:
//            oxygen_consumption = 0.00002;
//            glucose_consumption = 0;
//            growthFactor_secretion = 0;
//            toxic_secretion = 0;
//            proliferation_time = 6;
//            death_rate = 0;
//            mutation_rate = 0.1;
//            migration_rate = 0;
//            break;
//        case 2:
//            oxygen_consumption = 0.000025;
//            glucose_consumption = 0;
//            growthFactor_secretion = 0;
//            toxic_secretion = 0;
//            proliferation_time = 5;
//            death_rate = 0;
//            mutation_rate = 0.2;
//            migration_rate = 0;
//            break;
//        case 3:
//            oxygen_consumption = 0.00003;
//            glucose_consumption = 0;
//            growthFactor_secretion = 0;
//            toxic_secretion = 0;
//            proliferation_time = 4;
//            death_rate = 0;
//            mutation_rate = 0;
//            migration_rate = 0.2;
//            break;
//        default:
//            break;
//    }
}


Cell::Cell (int n, int t, std::vector<int> l)
{
    name = n;
    type = t;

    location = l;

    stage = "alive";
    parent = -1;
}

void Cell::set_name (int n)
{
    name = n;
}

void Cell::set_type (int t)
{
    type = t;
}

void Cell::set_location (int l)
{
    location[0] = l;
}

void Cell::set_location (std::vector<int> l)
{
    location = l;
}

void Cell::set_stage (std::string s)
{
    stage = s;
}

void Cell::set_parent (int p)
{
    parent = p;
}


std::vector<int> Cell::find_neighbor( int max )
{
    std::vector<int> neighbor_location;
    if (location[0] == 0)
    {
        neighbor_location.push_back(1);
    }
    else if (location[0] == max)
    {
        neighbor_location.push_back(location[0]-1);
    }
    else
    {
        neighbor_location.push_back(location[0]-1);
        neighbor_location.push_back(location[0]+1);
    }
    return neighbor_location;
}

// ################# need neighbor finder function for 2D and 3D here #################

int Cell::random_neighbor(int max)
{
    std::vector<int> neighbor = Cell::find_neighbor(max);
    if (neighbor.size() == 1) {
        return neighbor[0];
    }else{
        srand((unsigned)time(0));
        int r = rand() % 10;
        if (r < 5) {
            return neighbor[0];
        }else{
            return neighbor[1];
        }
    }
}

void Cell::show()
{
    std::cout <<"Cell name: "<<name<<"\n";
    std::cout <<"Cell type: "<<type<<"\n";
    if (location.size() == 1) {
         std::cout <<"Cell location: "<<location[0]<<"\n";
    }else{
        for (int i = 0; i < location.size()-1; i++) {
            std::cout <<"Cell location: "<<location[i]<<",";
        }
        std::cout <<location[location.size()-1]<<"\n";
    }
    std::cout <<"Cell parent: "<<parent<<"\n";
//    std::cout <<"Cell oxygen consumption: "<<oxygen_consumption<<"\n";
//    std::cout <<"Cell glucose consumption: "<<glucose_consumption<<"\n";
//    std::cout <<"Cell growthFactor secretion: "<<growthFactor_secretion<<"\n";
//    std::cout <<"Cell toxic secretion: "<<toxic_secretion<<"\n";
//    std::cout <<"Cell proliferation time: "<<proliferation_time<<"\n";
//    std::cout <<"Cell death rate: "<<death_rate<<"\n";
//    std::cout <<"Cell migration rate: "<<migration_rate<<"\n";
//    std::cout <<"Cell mutation rate: "<<mutation_rate<<"\n";
    
}