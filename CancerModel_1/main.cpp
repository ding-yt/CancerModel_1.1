//
//  main.cpp
//  CancerModel_1
//
//  Created by Yuantong Ding on 11/7/13.
//  Copyright (c) 2013 Yuantong Ding. All rights reserved.
//

// Initialize condition: space size, lattics, cells, time
// 

#include <iostream>
#include <vector>
#include <math.h> 
#include "Lattic.h"
#include "Cell.h"
#include "Environment.h"
#include "CellFate.h"
#include <fstream>

int main(int argc, const char * argv[])
{
   // Initialize condition
    int space = 5000;
    double time_max = 200;

    double mean_begin_oxygen_distribution = 0;
    double mean_end_oxygen_distribution = 0;
    double variance_begin_oxygen_distribution = 0.2;
    double variance_end_oxygen_distribution = 6;
    std::vector<int> distribution_range;
    distribution_range.push_back(-10);
    distribution_range.push_back(10);
    int normal_cell_initial = 20;
    int type1_cell_initial = 10;
    int migration_type = 3;
    double time = 0;
    int sample_size = 10;
    
    Environment bcg(space); // initialize all lattices with location, default cell NULL, others 0
    
    std::vector<Cell> all_cell;  // initialize cells, place x normal cells and y type1 cancer cell at random lattices
    for (int i=0; i<normal_cell_initial; i++) {
        int type = 0;
        int location = rand()%space;
        int name = (int)all_cell.size();
        
        while (! bcg[location].is_Empty()) {
            location = rand()%space;
        }
        Cell temp(name,type,location);
        bcg[location].set_cell(name);
        all_cell.push_back(temp);
    }
    
    for (int j=0; j<type1_cell_initial; j++) {
        int type = 1;
        int location = rand()%space;
        int name = (int)all_cell.size();
        
        while (! bcg[location].is_Empty()) {
            location = rand()%space;
        }
        Cell temp(name,type,location);
        bcg[location].set_cell(name);
        all_cell.push_back(temp);
    }
    

    
//    std::cout << "\n" << "environment size is " << bcg.get_space();
//    std::cout << "\n" << "The location of lattic 30 is "<<bcg[30].get_location();

    
//    Lattic a(1);
//    std::cout << "Lattic "<<a.get_location()<<" has oxygen "<<a.get_oxygen()<<"\n";
//    a.set_location(2);
//    a.set_oxygen(0.5);
//    std::cout << "Lattic "<<a.get_location()<<" has oxygen "<<a.get_oxygen()<<"\n";
    
//    Cell c(0,0,20);
//    Cell c1(1,3,56);
//    all_cell.push_back(c);
//    all_cell.push_back(c1);
//    std::vector<int> neighbor = c1.find_neighbor( space );
//    std::cout << "c1 neighbor is ";
//    for (int i=0; i<neighbor.size(); i++) {
//        std::cout << neighbor[i]<<" ";
//    }
    
    
//    bcg[56].set_cell(56);
//    bcg[55].set_cell(3);
//    bcg[57].set_cell(4);
//    bcg[55].remove_cell();
//    bcg[57].remove_cell();
//
//    bcg.update_all_oxygen(all_cell);
//    std::cout << "\n" << "The lattic 56 has oxygen of "<< bcg[56].get_oxygen();
    for (time = 1; time < time_max; time += 1) {
        std::cout <<"time is: " << time<<"\n";
        bcg.update_all_oxygen(all_cell);
        
        if ((int)time%8==0 or (int)time%6==0 or (int)time%5==0 or (int)time%4==0) {
            std::cout << "cell number is:"<<all_cell.size()<<"\n";
            int cell_number_this_generation = (int)all_cell.size();
            for (int i=0; i<cell_number_this_generation; i++) {
                if ((int)time % (int)all_cell[i].get_proliferation_time()==0 and all_cell[i].get_stage() != "death") {
                    double temp_location;
                    double location_transfer;
                    double mean;
                    double variance;
                    double oxygen_diffusion;
                    
                    temp_location = all_cell[i].get_location();
                    location_transfer = distribution_range[0] + (distribution_range[1]-distribution_range[0])/(double)space*temp_location;
                    
                    mean = mean_begin_oxygen_distribution + time * (mean_end_oxygen_distribution - mean_begin_oxygen_distribution)/time_max;
                    
                    variance = variance_begin_oxygen_distribution + time * (variance_end_oxygen_distribution - variance_begin_oxygen_distribution)/time_max;
                    
                    oxygen_diffusion = 10*1/sqrt(variance*2*M_PI)*exp(-pow(location_transfer-mean,2)/(2*variance));
//                    std::cout << "\n" << "The lattic 56 has oxygen diffusion of "<< oxygen_diffusion;
//                    std::cout << "\n" << (distribution_range[1]-distribution_range[0])/(double)space*temp_location;
//                    std::cout << "\n" << temp_location<<" "<<"cell type "<<all_cell[i].get_type()<<" "<<location_transfer<<" "<<mean<<" "<<variance<<" "<< bcg[temp_location].get_oxygen();
                    
                    CellFate fate(1);
                    fate.decide_fate(all_cell[i],bcg[temp_location],oxygen_diffusion);
                    //      std::cout << "\n" << all_cell[i].get_stage()<<"\n";
                    if (all_cell[i].get_stage() == "death") {
                        bcg[all_cell[i].get_location()].remove_cell();
                    }
                    if (all_cell[i].get_stage()=="proliferation") {
                        std::vector<int> neighbour = all_cell[i].find_neighbor(space);
                        if (!(bcg[neighbour[0]].is_Empty() or bcg[neighbour[1]].is_Empty())) {
                            //              std::cout<<"No neighbour space!\n";
                            if (all_cell[i].get_type() == migration_type) {
                                //                  std::cout<<"attemp to migrate!\n";
                                std::vector<int> empty_space = bcg.empty_lattic();
                                if (empty_space.size()==0) {
                                    std::cout << "space full!\n";
                                    time = time_max;
                                }else{
                                    Cell temp = fate.migration(all_cell[i], bcg);
                                    if (temp.get_location() != all_cell[i].get_location()) {
                                        temp.set_name((int)all_cell.size());
                                        all_cell.push_back(temp);
                                        bcg[temp.get_location()].set_cell(temp.get_name());
                                        //                      all_cell[(int)all_cell.size()-1].show_parameters();
                                    }
                                }
                            }else{
                                all_cell[i].set_stage("quiescence");
                            }
                        }else{
 //                           std::cout<<"neighbour space found!\n";
                            int celltype_temp = all_cell[i].get_type();
                            int location_temp = all_cell[i].get_location();
                            
                            if (fate.mutate(all_cell[i])) {
                                celltype_temp ++;
                            }
                            while (! bcg[location_temp].is_Empty()) {
                                location_temp = all_cell[i].random_neighbor(space);
                            }
                            Cell temp((int)all_cell.size(),celltype_temp,location_temp);
                            //                temp.show_parameters();
                            all_cell.push_back(temp);
                            bcg[temp.get_location()].set_cell(temp.get_name());
                            
                        }
                    }

                }
                
            }

        }
    }
    
    int count_normal_cell = 0;
    int count_type1 =0;
    int count_type2 =0;
    int count_type3 =0;
    for (int i=0; i<all_cell.size(); i++) {
        if (all_cell[i].get_stage() != "death") {
            switch (all_cell[i].get_type()) {
                case 0:
                    count_normal_cell++;
                    break;
                case 1:
                    count_type1++;
                    break;
                case 2:
                    count_type2++;
                    break;
                case 3:
                    count_type3++;
                    break;
                    
                default:
                    break;
            }
        }
    }
    std::cout << "normal cell:" <<count_normal_cell<<"\n";
    std::cout << "type1:" <<count_type1<<"\n";
    std::cout << "type2:" <<count_type2<<"\n";
    std::cout << "type3:" <<count_type3<<"\n";
    
    std::ofstream file_cell;
    file_cell.open("cells.txt");
    file_cell << "Cells:\n";
    for (int i=0; i<all_cell.size(); i++) {
        file_cell << all_cell[i].get_name()<<"\t"<< all_cell[i].get_type()<<"\t"<<all_cell[i].get_location()<<"\t"<<all_cell[i].get_stage()<<"\t"<<all_cell[i].get_parent()<<"\n";
    }
    file_cell.close();
    
    for (int i=0; i<sample_size; i++) {
        int sample = rand()%space;
        while ( bcg[sample].is_Empty()) {
            sample = rand()%space;
        }
        int cell_sample_name = bcg[sample].get_cell();
        std::cout << all_cell[cell_sample_name].get_name()<<"\t";
        int parent = all_cell[cell_sample_name].get_parent();
        std::cout << parent <<"\t";
        while (parent != 0) {
            parent = all_cell[parent].get_parent();
            std::cout << parent <<"\t";
        }
       std::cout << "\n";
    }

    return 0;
}

/*
 foreach cell {
 cellfate(cell, lattic, generation, space)
 cell death;
 cell quiescence
 cell proliferation
 }
 
 empty_neighbour_space{
 no:
 cell type:
 last stage -> migrate rate
 others -> Q
 yes:
 proliferate:
 mutate/double
 last stage -> neighbour/migrate
 }
 
 */
