//
//  PDE_2D.h
//  CancerModel_1
//
//  Created by Yuantong Ding on 1/26/14.
//  Copyright (c) 2014 Yuantong Ding. All rights reserved.
//

#ifndef __CancerModel_1__PDE_2D__
#define __CancerModel_1__PDE_2D__

#include <iostream>
#include <vector>


class PDE_2D{
    int _xStep = 200;//
    int _yStep = 200;//
    double _xMax = 0.2;//
    double _yMax = 0.2;//
    double _xMin = 0;//
    double _yMin = 0;//
    double _NtimeStep = 1000;
    double bc_txMaxy = 0;
    double bc_txyMin = 0;
    double bc_txyMax = 0;
    double bc_txMiny = 0.8;
    double _kappa = 0.0000006;
    double uptake = 1;
    std::vector<std::vector<double>> *grids;
    std::vector<std::vector<double>> *indicater;
    
public:
//    PDE_2D();
//    void setDimensionStep(double x, double y){ _xStep = x; _yStep = y; };
    void setDimensionStep(double x, double y){ _xStep = x; _yStep = y; };
    void setDimensionMin(double x,double y){ _xMin = x; _yMin = y; };
    void setDimensionMax(double x,double y){ _xMax = x; _yMax = y; };
    void setKappa(double k){ _kappa = k;};
    void setNtimeStep(double n){ _NtimeStep = n; };
//    std::vector<std::vector<double>>& pdeSolve(int timeStep, std::vector<std::vector<double>> *initial, std::vector<std::vector<double>> *indicater);
     void pdeSolve(int timeStep, std::vector<std::vector<double>> *initial, std::vector<std::vector<double>> *indicater);
   
    
  
};
#endif /* defined(__CancerModel_1__PDE_2D__) */
