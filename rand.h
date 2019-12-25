/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   rand.h
 * Author: GOZDEDOGAN
 *
 * Created on December 10, 2019, 8:37 PM
 */

#ifndef RAND_H
#define RAND_H

///////////////////////////////////////////////////
//
// This header file is for use with rand.cpp, randf.cpp, or randmt.cpp
// Each file provides a different random number generator engine and
// this header can be used for any of them.
//    rand.cpp - old fashion random number generator based on numerical recipies
//    randf.cpp - super fast random number generator good for most purposes
//    randmt.cpp - hard core Mersenne Twister random number generator
// NOTE: Compile by using rand.h and picking EXACTLY ONE of the cpp files.
// 
//
// WARNING: INIT REQUIRED before use!!!
//
// IMPORTANT: If running on MICROSOFT WINDOWS then define the symbol WINDOWS
// For example, uncomment the next line
// #define WINDOWS


// WARNING: the following includes may vary by OS, since these
// libraries may be in different places on different machines.
////////////////////////////////////////////////////////////////

//#include <sys/time.h>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#ifndef WINDOWS
#include <unistd.h>
#endif
#include <cmath>

// init
void     initRand();                       // WARNING: init required before use!!!
void     initRand(unsigned long long int a, unsigned long long int b);  // init with 2 seeds

// simple calls
unsigned long long int randULL();          // 64 bits random number
double   randUnit();                       // random [0,1)
double   randPMUnit();                     // random [-1,1)
int      randMod(int m);                   // random int in [0,m-1]
void     randMod2(int m, int &a, int &b);  // two random numbers [0,m-1] that are not equal
int      randMask(unsigned long long int mask);  // random in bit mask
bool     choose(double prob);              // true with probability prob
unsigned long long randCoinToss();         // 50:50 true or false
bool     choose8(int eigth);               // fast choose based on prob in 1/8 increments
bool     chooseMask(unsigned long long int mask, int prob); 
double   randNorm(double stddev);          // normal distribution with (mean=0)
double   randCauchy();                     // Cauchy distribution (mean=0, scale=1)
double   randCauchy(double mean, double scale);

#endif /* RAND_H */

