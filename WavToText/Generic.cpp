/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Generic.cpp
 * Author: GOZDEDOGAN
 * 
 * Created on January 20, 2020, 2:59 AM
 */

#include "Generic.h"

int k_ev = 2;
ofstream fout;

Generic::Generic() {
     nameM1 = "to";
     nameM2 = "play";
     nameM3 = "please";
     nameM4 = "black";
     nameM5 = "red";
     nameM6 = "computer"; 
}

Generic::~Generic() {
}

void Generic::preprocessing_operations()
{
    fout.open("searchedMatrix.txt", ios::out);
    
    fout << "M1 >" << endl;
    preprocessing_operations_helper1();
    //sleep(10);
    fout << "\nM2 >" << endl;
    preprocessing_operations_helper2();
    //sleep(10);
    fout << "\nM3 >" << endl;
    preprocessing_operations_helper3();
    //sleep(10);
    fout << "\nM4 >" << endl;
    preprocessing_operations_helper4();
    //sleep(10);
    fout << "\nM5 >" << endl;
    preprocessing_operations_helper5(); 
    //sleep(10);
    
    fout.close();
}


void Generic::preprocessing_operations_helper1()
{
    //////DECLARATIONS//////
    Matrix input_wav; //input wav matrix 
    Matrix center;
    Matrix mean_i;
    Matrix std_i;
    Matrix covariance;
    Matrix eigen_vectors;
    Matrix eigen_values;


    //searchedM1
    input_wav.readAudioWav("inputs_audio/to.wav", "wav"); 
    
    /*for (int i = 0; i < input_wav.numRows(); i++) { 
        for (int j = 0; j < input_wav.numCols(); j++){ 
            cout << input_wav.get(i, j); 
            cout << " ";
        }
        cout << endl; 
    }*/
    
    mean_i = Matrix(Matrix(input_wav).meanVec());
    std_i = Matrix(Matrix(input_wav).stddevVec());
    
    fout << "(size of Audio: " << input_wav.numRows() << " X " << input_wav.numCols() << ")" << endl;
    //////CENTER MATRIX/////
    center = new Matrix(input_wav); //creates a copy of input matrix to use for the centered matrix
    centerMatrixGeneric(input_wav, &center); //centers the 'center' matrix
    
    //////COVARIANCE MATRIX/////
    covariance = Matrix(Matrix(center).cov()); //Computes the covariance matrix

    /////COMPUTE EIGENVALUES AND EIGENVECTORS OF M//////
    eigen_vectors = new Matrix(covariance); //Copies the covariance matrix into eigen_vectors

    eigen_values = Matrix(eigen_vectors.eigenSystem()); //Creates the eigenvalues and eigen_vectors


    //cout << "(size of EigenValues: " << eigen_values.numRows() << " X " << eigen_values.numCols() << ")" << endl;
    ////NARROW THE EIGEN SYSTEM TO ONLY KEEP K LARGEST/////
    eigen_values.narrow(k_ev);
    eigen_vectors.shorten(k_ev);
    
   /* cout << "(size of EigenVectors: " << eigen_vectors.numRows() << " X " << eigen_vectors.numCols() << ")" << endl;
    cout << "eigen_vectors >>"  << endl;
    for (int i = 0; i<eigen_vectors.numRows(); i++)
    {
        for (int j = 0; j<eigen_vectors.numCols(); j++)
            cout << eigen_vectors.get(i,j) << " ";
        cout << endl;
    }*/
    
    //////TRANSLATE THE NORMALIZED DATA//////
    Matrix center_copy = new Matrix(center);
    Matrix eigenVec_copy = new Matrix(eigen_vectors);
    
    eigenVec_copy.transposeSelf();

    searchedM1 = Matrix(center_copy.dot(eigenVec_copy));

    /*cout << "(M1 - size of Encoded: " << searchedM1.numRows() << " X " << searchedM1.numCols() << ")" << endl;
    for (int i = 0; i<searchedM1.numRows(); i++)
    {
        for (int j = 0; j<searchedM1.numCols(); j++)
            cout << searchedM1.get(i,j) << " ";
        cout << endl;
    }*/
    
    fout << "(M1 - size of Encoded: " << searchedM1.numRows() << " X " << searchedM1.numCols() << ")" << endl;
    for (int i = 0; i<searchedM1.numRows(); i++)
    {
        for (int j = 0; j<searchedM1.numCols(); j++)
            fout << searchedM1.get(i,j) << " ";
        fout << endl;
    }
}

void Generic::preprocessing_operations_helper2()
{
    //////DECLARATIONS//////
    Matrix input_wav; //input wav matrix 
    Matrix center;
    Matrix mean_i;
    Matrix std_i;
    Matrix covariance;
    Matrix eigen_vectors;
    Matrix eigen_values;

    
    //searchedM2
    input_wav.readAudioWav("inputs_audio/play.wav", "wav"); 
    
   /* for (int i = 0; i < input_wav.numRows(); i++) { 
        for (int j = 0; j < input_wav.numCols(); j++){ 
            cout << input_wav.get(i, j); 
            cout << " ";
        }
        cout << endl; 
    }*/
    
    mean_i = Matrix(Matrix(input_wav).meanVec());
    std_i = Matrix(Matrix(input_wav).stddevVec());
    
    fout << "(size of Audio: " << input_wav.numRows() << " X " << input_wav.numCols() << ")" << endl;
    //////CENTER MATRIX/////
    center = new Matrix(input_wav); //creates a copy of input matrix to use for the centered matrix
    centerMatrixGeneric(input_wav, &center); //centers the 'center' matrix
    
    //////COVARIANCE MATRIX/////
    covariance = Matrix(Matrix(center).cov()); //Computes the covariance matrix

    /////COMPUTE EIGENVALUES AND EIGENVECTORS OF M//////
    eigen_vectors = new Matrix(covariance); //Copies the covariance matrix into eigen_vectors

    eigen_values = Matrix(eigen_vectors.eigenSystem()); //Creates the eigenvalues and eigen_vectors


   // cout << "(size of EigenValues: " << eigen_values.numRows() << " X " << eigen_values.numCols() << ")" << endl;
    ////NARROW THE EIGEN SYSTEM TO ONLY KEEP K LARGEST/////
    eigen_values.narrow(k_ev);
    eigen_vectors.shorten(k_ev);
    
   /* cout << "(size of EigenVectors: " << eigen_vectors.numRows() << " X " << eigen_vectors.numCols() << ")" << endl;
    cout << "eigen_vectors >>"  << endl;
    for (int i = 0; i<eigen_vectors.numRows(); i++)
    {
        for (int j = 0; j<eigen_vectors.numCols(); j++)
            cout << eigen_vectors.get(i,j) << " ";
        cout << endl;
    }*/
    
    //////TRANSLATE THE NORMALIZED DATA//////
    Matrix center_copy = new Matrix(center);
    Matrix eigenVec_copy = new Matrix(eigen_vectors);
    
    eigenVec_copy.transposeSelf();

    searchedM2 = Matrix(center_copy.dot(eigenVec_copy));

    /*cout << "(M2 - size of Encoded: " << searchedM2.numRows() << " X " << searchedM2.numCols() << ")" << endl;
    for (int i = 0; i<searchedM2.numRows(); i++)
    {
        for (int j = 0; j<searchedM2.numCols(); j++)
            cout << searchedM2.get(i,j) << " ";
        cout << endl;
    }*/
    
    fout << "(M2 - size of Encoded: " << searchedM2.numRows() << " X " << searchedM2.numCols() << ")" << endl;
    for (int i = 0; i<searchedM2.numRows(); i++)
    {
        for (int j = 0; j<searchedM2.numCols(); j++)
            fout << searchedM2.get(i,j) << " ";
        fout << endl;
    }
}

void Generic::preprocessing_operations_helper3()
{
    //////DECLARATIONS//////
    Matrix input_wav; //input wav matrix 
    Matrix center;
    Matrix mean_i;
    Matrix std_i;
    Matrix covariance;
    Matrix eigen_vectors;
    Matrix eigen_values;

    //searchedM3
    input_wav.readAudioWav("inputs_audio/please.wav", "wav"); 
    
    /*for (int i = 0; i < input_wav.numRows(); i++) { 
        for (int j = 0; j < input_wav.numCols(); j++){ 
            cout << input_wav.get(i, j); 
            cout << " ";
        }
        cout << endl; 
    }*/
    
    mean_i = Matrix(Matrix(input_wav).meanVec());
    std_i = Matrix(Matrix(input_wav).stddevVec());
    
    fout << "(size of Audio: " << input_wav.numRows() << " X " << input_wav.numCols() << ")" << endl;
    //////CENTER MATRIX/////
    center = new Matrix(input_wav); //creates a copy of input matrix to use for the centered matrix
    centerMatrixGeneric(input_wav, &center); //centers the 'center' matrix
    
    //////COVARIANCE MATRIX/////
    covariance = Matrix(Matrix(center).cov()); //Computes the covariance matrix

    /////COMPUTE EIGENVALUES AND EIGENVECTORS OF M//////
    eigen_vectors = new Matrix(covariance); //Copies the covariance matrix into eigen_vectors

    eigen_values = Matrix(eigen_vectors.eigenSystem()); //Creates the eigenvalues and eigen_vectors


   // cout << "(size of EigenValues: " << eigen_values.numRows() << " X " << eigen_values.numCols() << ")" << endl;
    ////NARROW THE EIGEN SYSTEM TO ONLY KEEP K LARGEST/////
    eigen_values.narrow(k_ev);
    eigen_vectors.shorten(k_ev);
    
   /* cout << "(size of EigenVectors: " << eigen_vectors.numRows() << " X " << eigen_vectors.numCols() << ")" << endl;
    cout << "eigen_vectors >>"  << endl;
    for (int i = 0; i<eigen_vectors.numRows(); i++)
    {
        for (int j = 0; j<eigen_vectors.numCols(); j++)
            cout << eigen_vectors.get(i,j) << " ";
        cout << endl;
    }*/
    
    //////TRANSLATE THE NORMALIZED DATA//////
    Matrix center_copy = new Matrix(center);
    Matrix eigenVec_copy = new Matrix(eigen_vectors);
    
    eigenVec_copy.transposeSelf();

    searchedM3 = Matrix(center_copy.dot(eigenVec_copy));

    /*cout << "(M3- size of Encoded: " << searchedM3.numRows() << " X " << searchedM3.numCols() << ")" << endl;
    for (int i = 0; i<searchedM3.numRows(); i++)
    {
        for (int j = 0; j<searchedM3.numCols(); j++)
            cout << searchedM3.get(i,j) << " ";
        cout << endl;
    }*/
    
    fout << "(M3- size of Encoded: " << searchedM3.numRows() << " X " << searchedM3.numCols() << ")" << endl;
    for (int i = 0; i<searchedM3.numRows(); i++)
    {
        for (int j = 0; j<searchedM3.numCols(); j++)
            fout << searchedM3.get(i,j) << " ";
        fout << endl;
    }
}

void Generic::preprocessing_operations_helper4()
{
    //////DECLARATIONS//////
    Matrix input_wav; //input wav matrix 
    Matrix center;
    Matrix mean_i;
    Matrix std_i;
    Matrix covariance;
    Matrix eigen_vectors;
    Matrix eigen_values;

     //searchedM4
    input_wav.readAudioWav("inputs_audio/black.wav", "wav"); 
    
   /* for (int i = 0; i < input_wav.numRows(); i++) { 
        for (int j = 0; j < input_wav.numCols(); j++){ 
            cout << input_wav.get(i, j); 
            cout << " ";
        }
        cout << endl; 
    }*/
    
    mean_i = Matrix(Matrix(input_wav).meanVec());
    std_i = Matrix(Matrix(input_wav).stddevVec());
    
    fout << "(size of Audio: " << input_wav.numRows() << " X " << input_wav.numCols() << ")" << endl;
    //////CENTER MATRIX/////
    center = new Matrix(input_wav); //creates a copy of input matrix to use for the centered matrix
    centerMatrixGeneric(input_wav, &center); //centers the 'center' matrix
    
    //////COVARIANCE MATRIX/////
    covariance = Matrix(Matrix(center).cov()); //Computes the covariance matrix

    /////COMPUTE EIGENVALUES AND EIGENVECTORS OF M//////
    eigen_vectors = new Matrix(covariance); //Copies the covariance matrix into eigen_vectors

    eigen_values = Matrix(eigen_vectors.eigenSystem()); //Creates the eigenvalues and eigen_vectors


   // cout << "(size of EigenValues: " << eigen_values.numRows() << " X " << eigen_values.numCols() << ")" << endl;
    ////NARROW THE EIGEN SYSTEM TO ONLY KEEP K LARGEST/////
    eigen_values.narrow(k_ev);
    eigen_vectors.shorten(k_ev);
    
   /* cout << "(size of EigenVectors: " << eigen_vectors.numRows() << " X " << eigen_vectors.numCols() << ")" << endl;
    cout << "eigen_vectors >>"  << endl;
    for (int i = 0; i<eigen_vectors.numRows(); i++)
    {
        for (int j = 0; j<eigen_vectors.numCols(); j++)
            cout << eigen_vectors.get(i,j) << " ";
        cout << endl;
    }*/
    
    //////TRANSLATE THE NORMALIZED DATA//////
    Matrix center_copy = new Matrix(center);
    Matrix eigenVec_copy = new Matrix(eigen_vectors);
    
    eigenVec_copy.transposeSelf();

    searchedM4 = Matrix(center_copy.dot(eigenVec_copy));

   /* cout << "(M4 - size of Encoded: " << searchedM4.numRows() << " X " << searchedM4.numCols() << ")" << endl;
    for (int i = 0; i<searchedM4.numRows(); i++)
    {
        for (int j = 0; j<searchedM4.numCols(); j++)
            cout << searchedM4.get(i,j) << " ";
        cout << endl;
    }*/
    
    fout << "(M4 - size of Encoded: " << searchedM4.numRows() << " X " << searchedM4.numCols() << ")" << endl;
    for (int i = 0; i<searchedM4.numRows(); i++)
    {
        for (int j = 0; j<searchedM4.numCols(); j++)
            fout << searchedM4.get(i,j) << " ";
        fout << endl;
    }
}

void Generic::preprocessing_operations_helper5()
{
    //////DECLARATIONS//////
    Matrix input_wav; //input wav matrix 
    Matrix center;
    Matrix mean_i;
    Matrix std_i;
    Matrix covariance;
    Matrix eigen_vectors;
    Matrix eigen_values;

    
    //searchedM5
    input_wav.readAudioWav("inputs_audio/red.wav", "wav"); 
    
  /*  for (int i = 0; i < input_wav.numRows(); i++) { 
        for (int j = 0; j < input_wav.numCols(); j++){ 
            cout << input_wav.get(i, j); 
            cout << " ";
        }
        cout << endl; 
    }*/
    
    mean_i = Matrix(Matrix(input_wav).meanVec());
    std_i = Matrix(Matrix(input_wav).stddevVec());
    
    fout << "(size of Audio: " << input_wav.numRows() << " X " << input_wav.numCols() << ")" << endl;
    //////CENTER MATRIX/////
    center = new Matrix(input_wav); //creates a copy of input matrix to use for the centered matrix
    centerMatrixGeneric(input_wav, &center); //centers the 'center' matrix
    
    //////COVARIANCE MATRIX/////
    covariance = Matrix(Matrix(center).cov()); //Computes the covariance matrix

    /////COMPUTE EIGENVALUES AND EIGENVECTORS OF M//////
    eigen_vectors = new Matrix(covariance); //Copies the covariance matrix into eigen_vectors

    eigen_values = Matrix(eigen_vectors.eigenSystem()); //Creates the eigenvalues and eigen_vectors


   // cout << "(size of EigenValues: " << eigen_values.numRows() << " X " << eigen_values.numCols() << ")" << endl;
    ////NARROW THE EIGEN SYSTEM TO ONLY KEEP K LARGEST/////
    eigen_values.narrow(k_ev);
    eigen_vectors.shorten(k_ev);
    
   /* cout << "(size of EigenVectors: " << eigen_vectors.numRows() << " X " << eigen_vectors.numCols() << ")" << endl;
    cout << "eigen_vectors >>"  << endl;
    for (int i = 0; i<eigen_vectors.numRows(); i++)
    {
        for (int j = 0; j<eigen_vectors.numCols(); j++)
            cout << eigen_vectors.get(i,j) << " ";
        cout << endl;
    }*/
    
    //////TRANSLATE THE NORMALIZED DATA//////
    Matrix center_copy = new Matrix(center);
    Matrix eigenVec_copy = new Matrix(eigen_vectors);
    
    eigenVec_copy.transposeSelf();

    searchedM5 = Matrix(center_copy.dot(eigenVec_copy));

   /* cout << "(M5 - size of Encoded: " << searchedM5.numRows() << " X " << searchedM5.numCols() << ")" << endl;
    for (int i = 0; i<searchedM5.numRows(); i++)
    {
        for (int j = 0; j<searchedM5.numCols(); j++)
            cout << searchedM5.get(i,j) << " ";
        cout << endl;
    }*/
    
    fout << "(M5 - size of Encoded: " << searchedM5.numRows() << " X " << searchedM5.numCols() << ")" << endl;
    for (int i = 0; i<searchedM5.numRows(); i++)
    {
        for (int j = 0; j<searchedM5.numCols(); j++)
            fout << searchedM5.get(i,j) << " ";
        fout << endl;
    }
    
}

void Generic::preprocessing_operations_helper6()
{
    //////DECLARATIONS//////
    Matrix input_wav; //input wav matrix 
    Matrix center;
    Matrix mean_i;
    Matrix std_i;
    Matrix covariance;
    Matrix eigen_vectors;
    Matrix eigen_values;

    //searchedM6
    input_wav.readAudioWav("inputs_audio/computer.wav", "wav"); 
    
    /*for (int i = 0; i < input_wav.numRows(); i++) { 
        for (int j = 0; j < input_wav.numCols(); j++){ 
            cout << input_wav.get(i, j); 
            cout << " ";
        }
        cout << endl; 
    }*/
    
    mean_i = Matrix(Matrix(input_wav).meanVec());
    std_i = Matrix(Matrix(input_wav).stddevVec());
    
    fout << "(size of Audio: " << input_wav.numRows() << " X " << input_wav.numCols() << ")" << endl;
    //////CENTER MATRIX/////
    center = new Matrix(input_wav); //creates a copy of input matrix to use for the centered matrix
    centerMatrixGeneric(input_wav, &center); //centers the 'center' matrix
    
    //////COVARIANCE MATRIX/////
    covariance = Matrix(Matrix(center).cov()); //Computes the covariance matrix

    /////COMPUTE EIGENVALUES AND EIGENVECTORS OF M//////
    eigen_vectors = new Matrix(covariance); //Copies the covariance matrix into eigen_vectors

    eigen_values = Matrix(eigen_vectors.eigenSystem()); //Creates the eigenvalues and eigen_vectors


   // cout << "(size of EigenValues: " << eigen_values.numRows() << " X " << eigen_values.numCols() << ")" << endl;
    ////NARROW THE EIGEN SYSTEM TO ONLY KEEP K LARGEST/////
    eigen_values.narrow(k_ev);
    eigen_vectors.shorten(k_ev);
    
  /*  cout << "(size of EigenVectors: " << eigen_vectors.numRows() << " X " << eigen_vectors.numCols() << ")" << endl;
    cout << "eigen_vectors >>"  << endl;
    for (int i = 0; i<eigen_vectors.numRows(); i++)
    {
        for (int j = 0; j<eigen_vectors.numCols(); j++)
            cout << eigen_vectors.get(i,j) << " ";
        cout << endl;
    }*/
    
    //////TRANSLATE THE NORMALIZED DATA//////
    Matrix center_copy = new Matrix(center);
    Matrix eigenVec_copy = new Matrix(eigen_vectors);
    
    eigenVec_copy.transposeSelf();

    searchedM6 = Matrix(center_copy.dot(eigenVec_copy));

    /*cout << "(M6 - size of Encoded: " << searchedM6.numRows() << " X " << searchedM6.numCols() << ")" << endl;
    for (int i = 0; i<searchedM6.numRows(); i++)
    {
        for (int j = 0; j<searchedM6.numCols(); j++)
            cout << searchedM6.get(i,j) << " ";
        cout << endl;
    }*/
    
    fout << "(M6 - size of Encoded: " << searchedM6.numRows() << " X " << searchedM6.numCols() << ")" << endl;
    for (int i = 0; i<searchedM6.numRows(); i++)
    {
        for (int j = 0; j<searchedM6.numCols(); j++)
            fout << searchedM6.get(i,j) << " ";
        fout << endl;
    }
}


/*
*Centers the center matrix using Z-Score method
*/
void Generic::centerMatrixGeneric(Matrix input, Matrix *center){
    Matrix mean;
    Matrix std;

    mean = Matrix(Matrix(input).meanVec());
    std = Matrix(Matrix(input).stddevVec());

    for(int r = 0; r < center->numRows(); r++){
        for(int c = 0; c < center->numCols(); c++){
            double zscore;
            zscore = ((input.get(r,c) - mean.get(0,c))/std.get(0,c));
            center->set(r,c, zscore);
        }
    }
}

/*
*Uncenters the centered matrix using the previous inputs Mean and std
*/
void Generic::uncenterMatrixGeneric(Matrix *recovered, Matrix mean, Matrix std){
    Matrix recov_copy = new Matrix(recovered);

    for(int r = 0; r < recovered->numRows(); r++){
        for(int c = 0; c < recovered->numCols(); c++){
            double redo;
            redo = ((recov_copy.get(r,c) * std.get(0,c)) + mean.get(0,c));
            recovered->set(r,c, redo);
        }
    }
}

