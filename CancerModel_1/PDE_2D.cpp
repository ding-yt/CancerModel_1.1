//
//  PDE_2D.cpp
//  CancerModel_1
//
//  Created by Yuantong Ding on 1/26/14.
//  Copyright (c) 2014 Yuantong Ding. All rights reserved.
//

#include "PDE_2D.h"

void PDE_2D::pdeSolve(int timeStep, std::vector<std::vector<double>> *initial, std::vector<std::vector<double>> *indicater){
    grids = initial;
    
//    for (int i=0; i<_xStep; i++) {
//        for (int j=0; j<_yStep; j++) {
//            grids[i].push_back(0);
//        }
//    }
//    
//    for (int i=0; i<_xStep; i++) {
//        for (int j=0; j<_yStep; j++) {
//            indicater[i].push_back(0);
//        }
//    }
    
    for (int i=0; i<_yStep; i++) {
        (*grids)[_xMin][i] = bc_txMiny;
    }
        
    //    std::cout<<grids.size()<<" "<<grids[100].size()<<"\n";
    double dy = (_yMax-_yMin)/(_yStep-1);
    double dx = (_xMax-_xMin)/(_xStep-1);
    double dt;
    if (dx<dy) {
        dt = dx*dx/_kappa/4;
    }else{
        dt = dy*dy/_kappa/4;
    }
    double ax = _kappa*dt/dx/dx;
    double ay = _kappa*dt/dy/dy;
    
    //    std::cout<<"dt is "<<dt<<"\t ax is "<<ax<<"\t ay is "<<ay<<"\n";
    
    for (double t=1; t<_NtimeStep; t++) {
        
        std::vector<std::vector<double>> newGrids(_xStep);
        for (int i=0; i<_xStep; i++) {
            newGrids[i].resize(_yStep);
        }
        
        for (int i=1; i<_xStep-1; i++) {
            for (int j=1; j<_yStep-1; j++) {
                newGrids[i][j] = (*grids)[i][j] + ax*((*grids)[i][j+1]-2*(*grids)[i][j]+(*grids)[i][j-1])+ay*((*grids)[i+1][j]-2*(*grids)[i][j]+(*grids)[i-1][j])-uptake*(*indicater)[i][j];
                //               std::cout <<newGrids[i][j]<<"\n";
            }
        }
        //       std::cout <<newGrids[1][1]<<"\n";
        
        
        for (int i=_yMin; i<_yStep; i++) {
            newGrids[_xStep-1][i] = bc_txMaxy;
        }
        for (int i=_xMin; i<_xStep; i++) {
            newGrids[i][_yMin] = bc_txyMin;
        }
        for (int i=_yMin; i<_yStep; i++) {
            newGrids[i][_yStep-1] = bc_txyMax;
        }
        for (int i=_yMin; i<_yStep; i++) {
            newGrids[_xMin][i] = bc_txMiny;
        }
        
        //        std::cout << "time is " << t<<"\n";
        //        for (int i=0; i<5; i++) {
        //            for (int j=0; j<5; j++) {
        //                std::cout << newGrids[i][j] <<"\t";
        //            }
        //            std::cout << "\n";
        //        }
        
        for (int i=0; i<_xStep; i++) {
            for (int j=0; j<_yStep; j++) {
                (*grids)[i][j] = newGrids[i][j];
            }
        }
        
        if ((int)t%100 == 0) {
            std::cout << "time is " << t<<"\n";
            for (int i=0; i<5; i++) {
                for (int j=0; j<5; j++) {
                    std::cout << (*grids)[i][j] <<"\t";
                }
                std::cout << "\n";
            }
            
        }
        
    }
//    return grids;
}