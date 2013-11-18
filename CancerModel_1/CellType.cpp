//
//  CellType.cpp
//  CancerModel_1
//
//  Created by Yuantong Ding on 11/18/13.
//  Copyright (c) 2013 Yuantong Ding. All rights reserved.
//

#include "CellType.h"
//#include <iostream>

Type::Type (int name_)
{
    name = name_;
    oxygen_consumption = 0;
    glucose_consumption = 0;
    toxic_secretion = 0;
    growthFactor_secretion = 0;
    mutation_rate = 0;
    migration_rate = 0;
    proliferation_time = 0;
    death_rate = 0;
    death_oxygen = 0;
    death_glucose = 0;
    death_toxic = 0;
    quiescence_glucose = 0;
    quiescence_oxygen = 0;
    
}

void Type::set_oxygenConsumption (double rate)
{
    oxygen_consumption = rate;
}
void Type::set_glucoseConsumption (double rate)
{
    glucose_consumption = rate;
}
void Type::set_growthFactorSecretion (double rate)
{
    growthFactor_secretion = rate;
}
void Type::set_toxicSecretion (double rate)
{
    toxic_secretion = rate;
}
void Type::set_proliferationTime (double time)
{
    proliferation_time = time;
}
void Type::set_deathRate (double rate)
{
    death_rate = rate;
}
void Type::set_mutationRate (double rate)
{
    mutation_rate = rate;
}
void Type::set_migrationRate (double rate)
{
    migration_rate = rate;
}
void Type::set_deathOxygen (double threshold)
{
    death_oxygen = threshold;
}
void Type::set_quiescenceOxygen (double threshold)
{
    quiescence_oxygen = threshold;
}
void Type::set_deathGlucose (double threshold)
{
    death_glucose = threshold;
}
void Type::set_quiescence_glucose (double threshold)
{
    quiescence_glucose = threshold;
}
void Type::set_deathToxic (double threshold)
{
    death_toxic = threshold;
}

void Type::show()
{
    std::cout <<"Type name: "<<name<<"\n";
    std::cout <<"Cell oxygen consumption: "<<oxygen_consumption<<"\n";
    std::cout <<"Cell glucose consumption: "<<glucose_consumption<<"\n";
    std::cout <<"Cell growthFactor secretion: "<<growthFactor_secretion<<"\n";
    std::cout <<"Cell toxic secretion: "<<toxic_secretion<<"\n";
    std::cout <<"Cell proliferation time: "<<proliferation_time<<"\n";
    std::cout <<"Cell death rate: "<<death_rate<<"\n";
    std::cout <<"Cell migration rate: "<<migration_rate<<"\n";
    std::cout <<"Cell mutation rate: "<<mutation_rate<<"\n";
    std::cout <<"Cell death oxygen level: "<<death_oxygen<<"\n";
    std::cout <<"Cell death glucose level: "<<death_glucose<<"\n";
    std::cout <<"Cell death toxic level: "<<death_toxic<<"\n";
    std::cout <<"Cell quiescence oxygen level: "<<quiescence_oxygen<<"\n";
    std::cout <<"Cell quiescence glucose level: "<<quiescence_glucose<<"\n";
}


CellType::CellType (int n_type)
{
    type_number = n_type;
    for (int i=0; i<n_type; i++) {
        all_types.push_back(Type(i));
    }
}

Type& CellType::operator[] (const int nIndex)
{
    return all_types[nIndex];
}

void CellType::show()
{
    for (int i=0 ;i < type_number;  i++) {
        all_types[i].show();
        std::cout <<"\n";
    }
}