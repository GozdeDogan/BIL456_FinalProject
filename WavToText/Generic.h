/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Generic.h
 * Author: GOZDEDOGAN
 *
 * Created on January 20, 2020, 2:59 AM
 */

#ifndef GENERIC_H
#define GENERIC_H

#include <iostream>
#include <fstream>
#include"WaveFunction.h"
#include "matrix.h"

using namespace std;

class Generic {
public:
    Generic();
    virtual ~Generic();
    void preprocessing_operations();
     
    Matrix searchedM1;
    Matrix searchedM2; 
    Matrix searchedM3;
    Matrix searchedM4;
    Matrix searchedM5;
    Matrix searchedM6;
    //string nameM1 = "to", nameM2 = "play", nameM3 = "please", nameM4 = "black", nameM5 = "red", nameM6 = "computer"; 
    string nameM1;
    string nameM2;
    string nameM3;
    string nameM4;
    string nameM5;
    string nameM6;
    
private:
    void preprocessing_operations_helper1();
    void preprocessing_operations_helper2();
    void preprocessing_operations_helper3();
    void preprocessing_operations_helper4();
    void preprocessing_operations_helper5();
    void preprocessing_operations_helper6();
    void centerMatrixGeneric(Matrix, Matrix*); //Centers the Matrix
    void uncenterMatrixGeneric(Matrix*, Matrix, Matrix); //Uncenters the Matrix
};

#endif /* GENERIC_H */

