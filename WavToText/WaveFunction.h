/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   WaveFunction.h
 * Author: GOZDEDOGAN
 *
 * Created on January 20, 2020, 12:52 AM
 */

#ifndef WAVEFUNCTION_H
#define WAVEFUNCTION_H

#include"WaveStructure.h"

class WaveFunction{
private:
    int CharCmp(const char *first,const char *second,unsigned short len);
    void InitHamming();

    void InitFilt(float *FiltCoe1, float *FiltCoe2, int *Num);

    void HammingWindow(short* buf,float* data);

    void ComputeFFT(float *buffer,vector<complex<float> >& vecList);

    void FFT(const unsigned long & ulN, vector<complex<float> >& vecList);


    void Filt(float *spdata, float *FiltCoe1, float *FiltCoe2, int *Num, float *En,vector<complex<float> >& vecList);


    void MFCC(float *En);


    float ComputeDTW(float *cep1, float *cep2, int num1, int num2);
    float Distance(float * ps1,float * ps2,int k1,int k2);

    void AdjustSize();

private:
    vector<float> xishu;
    double *Hamming;
    vector<vector<float> > SourceMFCCs;
    int MFCC_P;
    int MFCC_Pf;
    int FrmLen;
    int FFTLen;

public:
    
    vector<vector<float> > getMFCCs(string filename);
    vector<vector<float> > addFirstOrderDifference(vector<vector<float> > mfccs);
    vector<vector<float> > addOrderDifference(vector<vector<float> > mfccs);
    

    float ComputeDTW(vector<vector<float> > cep1,vector<vector<float> > cep2);
    WaveFunction(int frm_len, int mfcc_num);
    ~WaveFunction();
};

#endif /* WAVEFUNCTION_H */

