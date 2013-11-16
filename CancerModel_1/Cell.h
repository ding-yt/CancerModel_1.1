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

class Cell
{
    int name;
    int type;
    int location;
    int parent = 0;
    std::string stage = "alive";
    double oxygen_consumption = 0;
    double glucose_consumption = 0;
    double growthFactor_secretion = 0;
    double toxic_secretion = 0;
    double proliferation_time = 0;
    double death_rate = 0;
    double mutation_rate = 0;
    double migration_rate = 0;
//    int space;
    
public:
    Cell ();
    Cell (int n, int t, int l);
    void set_name (int n);
    void set_type (int t);
    void set_location (int l);
    void set_stage (std::string s);
    void set_parent (int p);
    void show_parameters();
//    void set_space (int sp) { space = sp; };
    
    int get_name() const { return name; }
    int get_type() const { return type; }
    int get_location() const { return location;}
    int get_parent() const { return parent;}
    std::string get_stage() const { return stage; }
    double get_oxygen_consumption() const { return oxygen_consumption; }
    double get_glucose_consumption() const { return glucose_consumption; }
    double get_growthFactor_secretion() const { return growthFactor_secretion; }
    double get_toxic_secretion() const { return toxic_secretion; }
    double get_proliferation_time() const { return proliferation_time; }
    double get_death_rate() const { return death_rate; }
    double get_mutation_rate() const { return mutation_rate; }
    double get_migration_rate() const { return migration_rate; }
    
    std::vector<int> find_neighbor( int max);
    int random_neighbor( int max );
    
};


#endif /* defined(__CancerModel_1__Cell__) */
