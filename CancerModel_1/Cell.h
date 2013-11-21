//
//  Cell.h
//  CancerModel_1
//
//  Created by Yuantong Ding on 11/7/13.
//  Copyright (c) 2013 Yuantong Ding. All rights reserved.
//

#ifndef __CancerModel_1__Cell__
#define __CancerModel_1__Cell__

#include <iostream>
#include <string>
#include <vector>
#include "CellType.h"

class Cell
{
    int name;
    int type;
    std::vector<int> location;
    int parent ; //default = -1
    std::string stage; // default = "alive"
    static CellType celltypes;
//    double oxygen_consumption;
//    double glucose_consumption;
//    double growthFactor_secretion;
//    double toxic_secretion;
//    double proliferation_time;
//    double death_rate;
//    double mutation_rate;
//    double migration_rate;
//    double death_oxygen;
//    double quiescence_oxygen;
//    double death_glucose;
//    double quiescence_glucose;
//    double death_toxic;
//    int space;
    
public:
    Cell ();
    Cell (int name, int type, int location);
    Cell (int name, int type, std::vector<int> location);
    void set_name (int n);
    void set_type (int t);
    void set_location (int l);
    void set_location (std::vector<int> l);
    void set_stage (std::string s);
    void set_parent (int p);
    void show();
    static void set_celltype(CellType all_types);
//    void set_space (int sp) { space = sp; };
    
    int get_name() const { return name; }
    int get_type() const { return type; }
    int get_location() const { return location[0];}
    std::vector<int> get_locationMD() const { return  location; } // multiple demesion 
    int get_parent() const { return parent;}
    std::string get_stage() const { return stage; }
    double get_oxygen_consumption() const { return celltypes[type].get_oxygen_consumption(); }
    double get_glucose_consumption() const { return celltypes[type].get_glucose_consumption(); }
    double get_growthFactor_secretion() const { return celltypes[type].get_growthFactor_secretion(); }
    double get_toxic_secretion() const { return celltypes[type].get_toxic_secretion(); }
    double get_proliferation_time() const { return celltypes[type].get_proliferation_time(); }
    double get_death_rate() const { return celltypes[type].get_death_rate(); }
    double get_mutation_rate() const { return celltypes[type].get_mutation_rate(); }
    double get_migration_rate() const { return celltypes[type].get_migration_rate(); }
    double get_quiescence_oxygen() const { return celltypes[type].get_quiescenceOxygen(); }
    double get_quiescence_glucose() const { return celltypes[type].get_quiescenceGlucose(); }
    double get_death_oxygen() const { return celltypes[type].get_deathOxygen(); }
    double get_death_glucose() const { return celltypes[type].get_deathGlucose(); }
    double get_death_toxic() const { return celltypes[type].get_deathToxic(); }
    
    std::vector<int> find_neighbor( int max);
    int random_neighbor( int max );
    
};


#endif /* defined(__CancerModel_1__Cell__) */
