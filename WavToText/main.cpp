/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: GOZDEDOGAN
 *
 * Created on January 20, 2020, 12:49 AM
 */


#include <iostream>
#include <fstream>
#include"WaveFunction.h"
#include "matrix.h"
#include "Generic.h"

using namespace std;

void centerMatrix(Matrix, Matrix*); //Centers the Matrix
void uncenterMatrix(Matrix*, Matrix, Matrix); //Uncenters the Matrix

string filename = "FindWordList.txt";
Generic generic;

void searchingWordsInMatrix(Matrix matrix, int rowSize, int colSize);
bool searchingWordsInMatrixHelper(Matrix matrix, int rowSize, int colSize, Matrix searchedMatrix, int searchedRow, int searchedCol, string searchedName, ofstream& fout);
bool findMatrixInMatrix(Matrix matrix, int rowSize, int colSize, Matrix searchedMatrix, int searchedRow, int searchedCol, int startRow, int startCol);


int main(int argc, char *argv[])
{
    generic.preprocessing_operations();
    
    //////DECLARATIONS//////
    Matrix input_wav; //input wav matrix 
    Matrix center;
    Matrix mean_i;
    Matrix std_i;
    Matrix covariance;
    Matrix eigen_vectors;
    Matrix eigen_values;
    Matrix translated_data;
    Matrix recovered_data;

    double difference;

    int k_ev = 2; // k_evaluation: bir k degerine gore islem yapiliyor ya o k degeri
    
    ofstream fout;
    fout.open("wavFileInformation.txt", ios::out);
    
    //fout << "MAIN" << endl;
    input_wav.readAudioWav("test_audio/test1.wav", "wav"); 
   // input_wav.readAudioWav("sample.wav", "wav"); 
    
    fout << "test1.wav >>" << endl;
    for (int i = 0; i < input_wav.numRows(); i++) { 
        for (int j = 0; j < input_wav.numCols(); j++){ 
            fout << input_wav.get(i, j); 
            fout << " ";
        }
        fout << endl; 
    }
    
    mean_i = Matrix(Matrix(input_wav).meanVec());
    std_i = Matrix(Matrix(input_wav).stddevVec());
    
    fout << "(size of Audio: " << input_wav.numRows() << " X " << input_wav.numCols() << ")" << endl;
    //////CENTER MATRIX/////
    center = new Matrix(input_wav); //creates a copy of input matrix to use for the centered matrix
    centerMatrix(input_wav, &center); //centers the 'center' matrix
    
    //////COVARIANCE MATRIX/////
    covariance = Matrix(Matrix(center).cov()); //Computes the covariance matrix

    /////COMPUTE EIGENVALUES AND EIGENVECTORS OF M//////
    eigen_vectors = new Matrix(covariance); //Copies the covariance matrix into eigen_vectors

    eigen_values = Matrix(eigen_vectors.eigenSystem()); //Creates the eigenvalues and eigen_vectors


    fout << "(size of EigenValues: " << eigen_values.numRows() << " X " << eigen_values.numCols() << ")" << endl;
    ////NARROW THE EIGEN SYSTEM TO ONLY KEEP K LARGEST/////
    eigen_values.narrow(k_ev);
    eigen_vectors.shorten(k_ev);
    
    fout << "(size of EigenVectors: " << eigen_vectors.numRows() << " X " << eigen_vectors.numCols() << ")" << endl;
    fout << "eigen_vectors >>"  << endl;
    for (int i = 0; i<eigen_vectors.numRows(); i++)
    {
        for (int j = 0; j<eigen_vectors.numCols(); j++)
            fout << eigen_vectors.get(i,j) << " ";
        fout << endl;
    }
    
    //////TRANSLATE THE NORMALIZED DATA//////
    Matrix center_copy = new Matrix(center);
    Matrix eigenVec_copy = new Matrix(eigen_vectors);
    
    eigenVec_copy.transposeSelf();

    translated_data = Matrix(center_copy.dot(eigenVec_copy));

    fout << "(size of Encoded: " << translated_data.numRows() << " X " << translated_data.numCols() << ")" << endl;
    for (int i = 0; i<translated_data.numRows(); i++)
    {
        for (int j = 0; j<translated_data.numCols(); j++)
            fout << translated_data.get(i,j) << " ";
        fout << endl;
    }
    
    searchingWordsInMatrix(translated_data, translated_data.numRows(), translated_data.numCols());
    
    return 0;
}

/*
*Centers the center matrix using Z-Score method
*/
void centerMatrix(Matrix input, Matrix *center){
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
void uncenterMatrix(Matrix *recovered, Matrix mean, Matrix std){
    Matrix recov_copy = new Matrix(recovered);

    for(int r = 0; r < recovered->numRows(); r++){
        for(int c = 0; c < recovered->numCols(); c++){
            double redo;
            redo = ((recov_copy.get(r,c) * std.get(0,c)) + mean.get(0,c));
            recovered->set(r,c, redo);
        }
    }
}


void searchingWordsInMatrix(Matrix matrix, int rowSize, int colSize)
{       
    ofstream fout;
    fout.open(filename, ios::out/* | ios::app*/);
    if (!fout.is_open()) {
        cerr << "Unable to open file " << filename << endl;
        exit(1);   // call system to stop
    }   
    
    searchingWordsInMatrixHelper(matrix, rowSize, colSize, generic.searchedM1, generic.searchedM1.numRows(), generic.searchedM1.numCols(), generic.nameM1, fout);    
    searchingWordsInMatrixHelper(matrix, rowSize, colSize, generic.searchedM2, generic.searchedM2.numRows(), generic.searchedM2.numCols(), generic.nameM2, fout);
    searchingWordsInMatrixHelper(matrix, rowSize, colSize, generic.searchedM3, generic.searchedM3.numRows(), generic.searchedM3.numCols(), generic.nameM3, fout);
    searchingWordsInMatrixHelper(matrix, rowSize, colSize, generic.searchedM4, generic.searchedM4.numRows(), generic.searchedM4.numCols(), generic.nameM4, fout);
    searchingWordsInMatrixHelper(matrix, rowSize, colSize, generic.searchedM5, generic.searchedM5.numRows(), generic.searchedM5.numCols(), generic.nameM5, fout);
        
    fout.close();
}

bool searchingWordsInMatrixHelper(Matrix matrix, int rowSize, int colSize, Matrix searchedMatrix, int searchedRow, int searchedCol, string searchedName, ofstream& fout)
{          
    for(int i = 0; i < rowSize; i++)
    {
        for(int j = 0; j < colSize; j++)
        {
            if(matrix.get(i, j) == searchedMatrix.get(0, 0))
            {
                if(findMatrixInMatrix(matrix, rowSize, colSize, searchedMatrix, searchedRow, searchedCol, i, j))
                {
                    cout << "FIND: ";
                    cout << searchedName << endl;
                    fout << searchedName << endl;
                    return true;
                }
            }
        }
    }
    return false;
}

bool findMatrixInMatrix(Matrix matrix, int rowSize, int colSize, Matrix searchedMatrix, int searchedRow, int searchedCol, int startRow, int startCol)
{
    int check = 0;
    
    for(int i = startRow, searched_i = 0; (i < startRow + searchedRow) && (searched_i < searchedRow); i++, searched_i++)
    {
        for(int j = startCol, searched_j = 0; (j < startCol + searchedCol) && (searched_j < searchedCol); j++, searched_j++)
        {
            if(matrix.get(i, j) == searchedMatrix.get(searched_i, searched_j))
            {
               /* cout << "EQUAL!" << endl;
                cout << "matrix[i][j]: " << matrix.get(i, j) << " \t i:" << i << "\tj:" << j <<endl;
                cout << "searchedMatrix[searched_i][searched_j]: " << searchedMatrix.get(searched_i, searched_j) << "\tsearched_i:"; 
                cout << searched_i << "\tsearched_j:" << searched_i << endl;*/
                
                check = 1;
            }
            else
                return false;
        }
    }
    return true;
}
