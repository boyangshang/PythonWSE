//
//  myWSE.h
//  
//
//  Created by Boyang Shang on 2020/9/25.
//  This file uses the Weighted Sample Elinmination method proposed by Cem Yuksel to select samples from a data base.
//

#ifndef myWSE_h
#define myWSE_h

#include "cyVector.h"
#include "cySampleElim.h"

//The following function uses the default weighted sample elimination method in cySampleElim.h. The default weight function will be used.
//**data: the data set is stored as pointer to pointers
//N: the size of the data set
//*sample: the selected sample will be copied to a contiguous memory
//n: sample size

template<typename PointType, typename DataType, int Dimension, typename SIZE_TYPE = size_t>
void myWeightedSampleElimination(DataType **data, SIZE_TYPE N, DataType *sample, SIZE_TYPE n){
    
    //convert input data to an array of class Vec
    PointType inputPoints[N];
    
    for (int i =0; i<N; ++i) {
        inputPoints[i] = PointType(data[i]);
    }
    
    //output points
    PointType outputPoints[n];
    for (int i=0; i<n; ++i) {
        outputPoints[i] = PointType(0.0);
        //outputPoints[i] = PointType(data[i]);
    }
    
    cy::WeightedSampleElimination<PointType,DataType,Dimension,SIZE_TYPE> WSE;
    
    PointType BoundsMin,BoundsMax;
    
    DataType mybmin[Dimension];
    DataType mybmax[Dimension];
    
    for (int i =0; i<N; ++i) {
        if (i==0) {
            for (int j =0; j<Dimension; ++j) {
                mybmin[j] = data[i][j];
                mybmax[j] = data[i][j];
            }
        }else{
            for (int j =0; j<Dimension; ++j) {
                if (data[i][j]<mybmin[j]) {
                    mybmin[j] = data[i][j];
                }
                
                if (data[i][j] > mybmax[j]) {
                    mybmax[j] = data[i][j];
                }
            }
        }
    }
    
    BoundsMin = PointType(mybmin);
    BoundsMax = PointType(mybmax);
    
    WSE.SetBoundsMin(BoundsMin);
    WSE.SetBoundsMax(BoundsMax);
    
    //we will have the sample points ordered sequentially
    bool Progressive = true;
    //we will be using the automatically computed d_max
    DataType d_max = -1.0;
    
    WSE.Eliminate(inputPoints,N,outputPoints,n,Progressive,d_max,Dimension);
    
    //save the outputPoints in contiguous memory
    
    for (int i = 0; i<n; ++i) {
        for (int j=0; j<Dimension; ++j) {
            sample[i*Dimension+j] = outputPoints[i][j];
        }
    }
    
    
    
    
}

//typedef myWeightedSampleElimination<cyVec2d,double,2,int>; myWSE_2D;
//typedef myWeightedSampleElimination<cy::Vec<double,10>,double,10,int>;  myWSE_10D;


#endif /* myWSE_h */
