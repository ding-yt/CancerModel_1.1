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
#include "CellType.h"
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <time.h>
#include <stdlib.h>
#include "string.h"
#include "ParFile.h"

int main(int argc, const char * argv[])
{
    //read from model setting file
    std::string setting_file, output;
    std::map<std::string, double> parameters;
    ParFile p;
    std::cout<<"random max is "<<RAND_MAX<<"\n";
    for (int i=1; i<argc; i++) {
        if (i+1 != argc) {
            if (strcmp(argv[i], "-i") == 0){
                setting_file = argv[i + 1];
            }else if (strcmp(argv[i], "-o") == 0){
                output = argv[i+1];
            }
        }
        
    }
    
    parameters = p.get_parameters(setting_file);
    p.show();
    
   // Initialize condition
    int space = (int)parameters["lattices"];
    double time_max = parameters["time_max"];

    double mean_begin_oxygen_distribution = parameters["mean_begin_oxygen_distribution"];
    double mean_end_oxygen_distribution = parameters["mean_end_oxygen_distribution"];
    double variance_begin_oxygen_distribution = parameters["variance_begin_oxygen_distribution"];
    double variance_end_oxygen_distribution = parameters["variance_end_oxygen_distribution"];
    double coefficient = parameters["coefficient"];
    std::vector<int> distribution_range;
    distribution_range.push_back((int)-parameters["distribution_range"]/2);
    distribution_range.push_back((int)parameters["distribution_range"]/2);
    int normal_cell_initial = (int)parameters["type_0_initial_number"];
    int type1_cell_initial = (int)parameters["type_1_initial_number"];
    int migration_type = (int)parameters["migration_type"];
    double self_migrate = parameters["self_migrate"];
    int sample_size = (int)parameters["sample_size"];
    double sample_time_interval = parameters["sample_time_interval"];
    int cell_type_number = parameters["cell_types"];
    double time = 0;
    std::vector<double> migration_time;
    std::vector<int> prolifetation_times;
    int calculate_this_generation = 0;
    
    CellType celltypes(cell_type_number);
    
    for (int i=0; i<cell_type_number; i++) {
        std::string prefix = "type_";
        std::ostringstream s;
        s << i;
        std::string o2_consumption = prefix + s.str() + "_oxygen_consumption";
        std::string g_consumption = prefix + s.str() + "_glucose_consumption";
        std::string gf_secretion = prefix + s.str() + "_growthFactor_secretion";
        std::string t_secretion = prefix + s.str() + "_toxic_secretion";
        std::string proliferation = prefix + s.str() + "_proliferation_time";
        std::string mutation = prefix + s.str() + "_mutation_rate";
        std::string migration = prefix + s.str() + "_migration_rate";
        std::string death = prefix + s.str() + "_death_rate";
        std::string death_o2 = prefix + s.str() + "_death_oxygen";
        std::string death_g = prefix + s.str() + "_death_glucose";
        std::string death_t = prefix + s.str() + "_death_toxic";
        std::string q_o = prefix + s.str() + "_quiescence_oxygen";
        std::string q_g = prefix + s.str() + "_quiescence_glucose";
        celltypes[i].set_oxygenConsumption(parameters[o2_consumption]);
        celltypes[i].set_glucoseConsumption(parameters[g_consumption]);
        celltypes[i].set_growthFactorSecretion(parameters[gf_secretion]);
        celltypes[i].set_toxicSecretion(parameters[t_secretion]);
        celltypes[i].set_proliferationTime(parameters[proliferation]);
        celltypes[i].set_mutationRate(parameters[mutation]);
        celltypes[i].set_migrationRate(parameters[migration]);
        celltypes[i].set_deathRate(parameters[death]);
        celltypes[i].set_deathOxygen(parameters[death_o2]);
        celltypes[i].set_deathGlucose(parameters[death_g]);
        celltypes[i].set_deathToxic(parameters[death_t]);
        celltypes[i].set_quiescenceOxygen(parameters[q_o]);
        celltypes[i].set_quiescence_glucose(parameters[q_g]);
        prolifetation_times.push_back((int)celltypes[i].get_proliferation_time());
    }
    
    
    celltypes.show();
    
    Cell::set_celltype(celltypes);
    
    clock_t start_time = clock();
    
    Environment bcg(space); // initialize all lattices with location, default cell NULL, others 0
    
    std::vector<Cell> secondary_tumor;
    
    std::vector<Cell> all_cell;  // initialize cells, place x normal cells and y type1 cancer cell at random lattices
    
    for (int i=0; i<normal_cell_initial; i++) {
        int type = 0;
        int location = rand()%space;
        int name = (int)all_cell.size();
        
        while (! bcg[location].is_Empty()) {
            location = rand()%space;
        }
        Cell temp(name,type,location);
        temp.set_birthTime(0);
        temp.set_parent(-1);
        bcg[location].set_cell(name);
        all_cell.push_back(temp);
    }
    
    if (type1_cell_initial == 1) {
        int type = 1;
        int location = rand()%space;
        int name = (int)all_cell.size();
        
        while (! bcg[location].is_Empty()) {
            location = rand()%space;
        }
        Cell temp(name,type,location);
        temp.set_birthTime(0);
        temp.set_parent(-2);
        bcg[location].set_cell(name);
        all_cell.push_back(temp);
    }else{
        for (int j=0; j<type1_cell_initial; j++) {
            int type = 1;
            int location = (int)(space/2);
            int name = (int)all_cell.size();
        
            while (! bcg[location].is_Empty()) {
                location = (int)(space/2) + 1;
            }
            Cell temp(name,type,location);
            temp.set_birthTime(0);
            temp.set_parent(-2);
            bcg[location].set_cell(name);
            all_cell.push_back(temp);
        }
    }
    

    for (time = 1; time < time_max; time += 1) {
        std::cout <<"time is: " << time<<"\n";
        bcg.update_all_oxygen(all_cell);
        
        //################################################
//        for (int i=0; i<space; i++) {
//            std::cout <<bcg[i].get_oxygen()<<"\t";
//        }
//        std::cout << "\n";
        //################################################
        calculate_this_generation = 0;
        
        for (int i = 0; i < prolifetation_times.size(); i++) {
            if ((int)time%prolifetation_times[i] == 0) {
                calculate_this_generation = 1;
            }
        }
        
        if (calculate_this_generation == 1) {
            std::cout << "cell number is:"<<all_cell.size()<<"\n";
            int cell_number_this_generation = (int)all_cell.size();
            for (int i=0; i<cell_number_this_generation; i++) {
                if ((int)time % (int)all_cell[i].get_proliferation_time()==0 and all_cell[i].get_stage() != "death" and all_cell[i].get_stage() != "self_migrate") {
                    double temp_location;
                    double location_transfer;
                    double mean;
                    double variance;
                    double oxygen_diffusion;
                    
                    temp_location = all_cell[i].get_location();
                    location_transfer = distribution_range[0] + (distribution_range[1]-distribution_range[0])/(double)space*temp_location;
                    
                    mean = mean_begin_oxygen_distribution + time * (mean_end_oxygen_distribution - mean_begin_oxygen_distribution)/time_max;
                    
                    variance = variance_begin_oxygen_distribution + time * (variance_end_oxygen_distribution - variance_begin_oxygen_distribution)/time_max;
                    
                    oxygen_diffusion = coefficient*1/sqrt(variance*2*M_PI)*exp(-pow(location_transfer-mean,2)/(2*variance));
//                    std::cout << "\n" << "The lattic 56 has oxygen diffusion of "<< oxygen_diffusion;
//                    std::cout << "\n" << (distribution_range[1]-distribution_range[0])/(double)space*temp_location;
//                    std::cout << "\n" << temp_location<<" "<<"cell type "<<all_cell[i].get_type()<<" "<<location_transfer<<" "<<mean<<" "<<variance<<" "<< bcg[temp_location].get_oxygen();
                   
                    CellFate fate(1);
                    fate.decide_fate(all_cell[i],bcg[temp_location],oxygen_diffusion);
                    //      std::cout << "\n" << all_cell[i].get_stage()<<"\n";
//                     std::cout << "Cell "<< i << " at location " << all_cell[i].get_location()<< " has oxygen "<<oxygen_diffusion << ", death theshold is " << all_cell[i].get_death_oxygen() << ", fate is "<<all_cell[i].get_stage();
                    
                    
                    if (all_cell[i].get_stage() == "death") {
                        all_cell[i].set_deathTime(time);
                        bcg[all_cell[i].get_location()].remove_cell();
                    }
                    if (all_cell[i].get_stage()=="proliferation") {
                        std::vector<int> neighbour = all_cell[i].find_neighbor(space);
                        if (!(bcg[neighbour[0]].is_Empty() or bcg[neighbour[1]].is_Empty())) {
                            //              std::cout<<"No neighbour space!\n";
                            if (all_cell[i].get_type() == migration_type) {
//                                //                  std::cout<<"attemp to migrate!\n";
//                                std::vector<int> empty_space = bcg.empty_lattic();
//                                if (empty_space.size()==0) {
//                                    std::cout << "space full!\n";
//                                    time = time_max;
//                                }else{
//                                    Cell temp = fate.migration(all_cell[i], bcg);
//                                    if (temp.get_location() != all_cell[i].get_location()) {
//                                        temp.set_name((int)all_cell.size());
//                                        all_cell.push_back(temp);
//                                        bcg[temp.get_location()].set_cell(temp.get_name());
//                                        //                      all_cell[(int)all_cell.size()-1].show_parameters();
//                                    }
//                                }
                                if (fate.migrate(all_cell[i])) {
// self migrate
                                    double self_m = (double)rand()/RAND_MAX;
                                    std::cout << self_m<<"\n";
                                    if (self_m < self_migrate) {
                                        Cell temp = all_cell[i];
                                        temp.set_birthTime(time);
                                        all_cell[i].set_stage("self_migrate");
                                        temp.set_stage("self_migrate");
                                        secondary_tumor.push_back(temp);
                                        migration_time.push_back(time);
                                        bcg[all_cell[i].get_location()].remove_cell();
                                    }else{
                                        Cell temp = all_cell[i];
                                        temp.set_birthTime(time);
                                        temp.set_stage("migrate");
                                        all_cell[i].set_stage("migrate");
                                        secondary_tumor.push_back(temp);
                                        migration_time.push_back(time);
                                    }
                                }
                            }else{
                                all_cell[i].set_stage("quiescence");
                            }
                        }else{
 //                           std::cout<<"neighbour space found!\n";
                            int celltype_temp = all_cell[i].get_type();
                            int location_temp = all_cell[i].get_location();
                            
                            if (all_cell[i].get_type() == migration_type && fate.migrate(all_cell[i])) {
                                
                                double self_m = (double)rand()/RAND_MAX;
                                if (self_m < self_migrate) {
                                    Cell temp = all_cell[i];
                                    temp.set_birthTime(time);
                                    all_cell[i].set_stage("self_migrate");
                                    temp.set_stage("self_migrate");
                                    secondary_tumor.push_back(temp);
                                    migration_time.push_back(time);
                                    bcg[all_cell[i].get_location()].remove_cell();
                                }else{

                                    Cell temp = all_cell[i];
                                    temp.set_birthTime(time);
                                    temp.set_stage("migrate");
                                    all_cell[i].set_stage("migrate");
                                    secondary_tumor.push_back(temp);
                                    migration_time.push_back(time);
                                }
                            }else{
                                if (fate.mutate(all_cell[i])) {
                                    celltype_temp ++;
                                }
                                while (! bcg[location_temp].is_Empty()) {
                                    location_temp = all_cell[i].random_neighbor(space);
                                }
                                Cell temp((int)all_cell.size(),celltype_temp,location_temp);
                                temp.set_birthTime(time);
                                temp.set_parent(all_cell[i].get_name());
                            //                temp.show_parameters();
                                all_cell.push_back(temp);
                                bcg[temp.get_location()].set_cell(temp.get_name());
                            }
                            
                        }
                    }

                }
                
            }

        }
        if ((int)time % (int)sample_time_interval == 0) {
            std::string filename = output;
            std::ostringstream s;
            s << time;
            std::string new_filename = filename + s.str();
            
            std::cout <<"output file: "<<new_filename<<"\n";
            
            std::ofstream file_cell;
            file_cell.open(new_filename);
            file_cell << "Cells at time "<<time<<"\n";
            file_cell << "name"<<"\t"<<"type"<<"\t"<<"location"<<"\t"<<"stage"<<"\t"<<"parent"<<"\t"<<"birthTime"<<"\t"<<"deathTime"<<"\n";
            
            
            for (int i=0; i<all_cell.size(); i++) {
                file_cell << all_cell[i].get_name()<<"\t"<< all_cell[i].get_type()<<"\t"<<all_cell[i].get_location()<<"\t"<<all_cell[i].get_stage()<<"\t"<<all_cell[i].get_parent()<<"\t"<<all_cell[i].get_birthTime()<<"\t"<<all_cell[i].get_deathTime()<<"\n";
            }
            

            file_cell <<"\n\nSecondary tumor cell:\n";
            if (secondary_tumor.size() == 0) {
                std::cout << "No migration!\n\n";
                file_cell << "No migration!\n\n";
            }else{
                for (int i=0; i<secondary_tumor.size(); i++) {
                    file_cell << secondary_tumor[i].get_name()<<"\t"<< secondary_tumor[i].get_type()<<"\t"<<    secondary_tumor[i].get_location()<<"\t"<<secondary_tumor[i].get_stage()<<"\t"<<secondary_tumor[i].get_parent()<<"\t"<<secondary_tumor[i].get_birthTime()<<"\t"<<secondary_tumor[i].get_deathTime()<<"   \n";
                }
            }
            
            if (migration_time.size() != 0) {
                file_cell <<"\n\nMigration_begin: "<<migration_time[0]<<"\n";
                file_cell <<"total_migration_cell: "<<secondary_tumor.size()<<"\n";
            }
            
            file_cell << "\n\nSample size: "<<sample_size<<"\n";
            std::vector<int> occupied_lattices_location = bcg.occupied_lattic();
            
            if (occupied_lattices_location.size() < sample_size) {
                file_cell << "not enough cell\n";
            }else{
                for (int i=0; i<sample_size; i++) {
                
                    int sample = rand()% (int)occupied_lattices_location.size();

                    int cell_sample_name = bcg[occupied_lattices_location[sample]].get_cell();
                    file_cell << all_cell[cell_sample_name].get_name()<<"\t";
                    int parent = all_cell[cell_sample_name].get_parent();
                    file_cell<< parent <<"\t";
                    while (parent >=0 ) {
                        parent = all_cell[parent].get_parent();
                        file_cell << parent <<"\t";
                    }
                    file_cell << "\n";
                }
            }
            
            clock_t temp_time = clock();
            file_cell << "\nRunning time: " << (temp_time-start_time)/CLOCKS_PER_SEC/60 <<"min\n";

            file_cell.close();
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
    
    std::cout <<"\n\nSecondary tumor cell:\n";
    if (secondary_tumor.size() == 0) {
        std::cout << "No migration!\n\n";
    }else{
    for (int i=0; i<secondary_tumor.size(); i++) {
        std::cout << secondary_tumor[i].get_name()<<"\t"<< secondary_tumor[i].get_type()<<"\t"<<secondary_tumor[i].get_location()<<"\t"<<secondary_tumor[i].get_stage()<<"\t"<<secondary_tumor[i].get_parent()<<"\t"<<secondary_tumor[i].get_birthTime()<<"\t"<<secondary_tumor[i].get_deathTime()<<"\n";
    }
    }
    
    if (migration_time.size() != 0) {
        std::cout <<"\n\nMigration_begin: "<<migration_time[0]<<"\n";
        std::cout <<"total_migration_cell: "<<secondary_tumor.size()<<"\n";
    }
    
    std::cout << "\n\nSample size: "<<sample_size<<"\n";
    std::vector<int> occupied_lattices_location = bcg.occupied_lattic();
    
    for (int i=0; i<sample_size; i++) {
        int sample = rand()%(int)occupied_lattices_location.size();
        int cell_sample_name = bcg[occupied_lattices_location[sample]].get_cell();
        std::cout << all_cell[cell_sample_name].get_name()<<"\t";
        int parent = all_cell[cell_sample_name].get_parent();
        std::cout << parent <<"\t";
        while (parent >= 0) {
            parent = all_cell[parent].get_parent();
            std::cout << parent <<"\t";
        }
        std::cout << "\n";
    }
    

    std::ofstream file_cell;
    file_cell.open(output);
    file_cell << "Cells:\n";
    file_cell << "name"<<"\t"<<"type"<<"\t"<<"location"<<"\t"<<"stage"<<"\t"<<"parent"<<"\t"<<"birthTime"<<"\t"<<"deathTime"<<"\n";
    
    for (int i=0; i<all_cell.size(); i++) {
        file_cell << all_cell[i].get_name()<<"\t"<< all_cell[i].get_type()<<"\t"<<all_cell[i].get_location()<<"\t"<<all_cell[i].get_stage()<<"\t"<<all_cell[i].get_parent()<<"\t"<<all_cell[i].get_birthTime()<<"\t"<<all_cell[i].get_deathTime()<<"\n";
    }
    
    file_cell <<"\n\nSecondary tumor cell:\n";
    if (secondary_tumor.size() == 0) {
        file_cell << "No migration!\n\n";
    }else{
    for (int i=0; i<secondary_tumor.size(); i++) {
        file_cell << secondary_tumor[i].get_name()<<"\t"<< secondary_tumor[i].get_type()<<"\t"<<secondary_tumor[i].get_location()<<"\t"<<secondary_tumor[i].get_stage()<<"\t"<<secondary_tumor[i].get_parent()<<"\t"<<secondary_tumor[i].get_birthTime()<<"\t"<<secondary_tumor[i].get_deathTime()<<"\n";
    }
    }
    
    if (migration_time.size() != 0) {
        file_cell <<"\n\nMigration_begin: "<<migration_time[0]<<"\n";
        file_cell <<"total_migration_cell: "<<secondary_tumor.size()<<"\n";
    }
    
    std::cout << "\n\nSample size: "<<sample_size<<"\n";
    
    for (int i=0; i<sample_size; i++) {
        int sample = rand()%(int)occupied_lattices_location.size();
        int cell_sample_name = bcg[occupied_lattices_location[sample]].get_cell();
        file_cell << all_cell[cell_sample_name].get_name()<<"\t";
        int parent = all_cell[cell_sample_name].get_parent();
        file_cell << parent <<"\t";
        while (parent >= 0) {
            parent = all_cell[parent].get_parent();
            file_cell << parent <<"\t";
        }
        file_cell << "\n";
    }
    
    file_cell << "\n";
    file_cell << "normal cell:" <<count_normal_cell<<"\n";
    file_cell << "type1:" <<count_type1<<"\n";
    file_cell << "type2:" <<count_type2<<"\n";
    file_cell << "type3:" <<count_type3<<"\n";
    
    
    
    clock_t end_time = clock();
    std::cout << "Running time: " << (end_time-start_time)/CLOCKS_PER_SEC/60 <<"min\n";
    
    file_cell << "Running time: " << (end_time-start_time)/CLOCKS_PER_SEC/60 <<"min\n";
    file_cell.close();

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
