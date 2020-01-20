/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   rand.h
 * Author: GOZDEDOGAN
 *
 * Created on January 20, 2020, 12:56 AM
 */

#ifndef RAND_H
#define RAND_H

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

