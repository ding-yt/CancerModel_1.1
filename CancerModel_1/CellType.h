//
//  CellType.h
//  CancerModel_1
//
//  Created by Yuantong Ding on 11/18/13.
//  Copyright (c) 2013 Yuantong Ding. All rights reserved.
//

#ifndef __CancerModel_1__CellType__
#define __CancerModel_1__CellType__

#include <iostream>
#include <vector>

class Trait
{
protected:
    int name;
    double oxygen_consumption;
    double glucose_consumption;
    double growthFactor_secretion;
    double toxic_secretion;
    double proliferation_time;
    double death_rate;
    double mutation_rate;
    double migration_rate;
    double death_oxygen;
    double quiescence_oxygen;
    double death_glucose;
    double quiescence_glucose;
    double death_toxic;
    
};

class Type : public Trait
{
public:
    Type();
    Type (int name_);
    void set_oxygenConsumption (double rate);
    void set_glucoseConsumption (double rate);
    void set_growthFactorSecretion (double rate);
    void set_toxicSecretion (double rate);
    void set_proliferationTime (double time);
    void set_deathRate (double rate);
    void set_mutationRate (double rate);
    void set_migrationRate (double rate);
    void set_deathOxygen (double threshold);
    void set_quiescenceOxygen (double threshold);
    void set_deathGlucose (double threshold);
    void set_quiescence_glucose (double threshold);
    void set_deathToxic (double threshold);
    
    int get_name() const { return name; }
    double get_oxygen_consumption() const { return oxygen_consumption; }
    double get_glucose_consumption() const { return glucose_consumption; }
    double get_growthFactor_secretion() const { return growthFactor_secretion; }
    double get_toxic_secretion() const { return toxic_secretion; }
    double get_proliferation_time() const { return proliferation_time; }
    double get_death_rate() const { return death_rate; }
    double get_mutation_rate() const { return mutation_rate; }
    double get_migration_rate() const { return migration_rate; }
    double get_deathOxygen () const { return death_oxygen; }
    double get_deathGlucose () const { return death_glucose; }
    double get_deathToxic () const { return death_toxic; }
    double get_quiescenceOxygen () const { return quiescence_oxygen; }
    double get_quiescenceGlucose () const { return quiescence_glucose; }
    
    void show();
    
};


class CellType
{
    std::vector<Type> all_types;
    int type_number;
    
public:
    CellType (int n_type);
    Type& operator[] (const int nIndex);
    void show();
    
};


#endif /* defined(__CancerModel_1__CellType__) */
