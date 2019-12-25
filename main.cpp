
#include <iostream>
#include <fstream>
#include"WaveFunction.h"
#include "mat.h"

using namespace std;

void centerMatrix(Matrix, Matrix*); //Centers the Matrix
void uncenterMatrix(Matrix*, Matrix, Matrix); //Uncenters the Matrix

int main(int argc, char *argv[])
{
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

   
   
    input_wav.readAudioWav("goodbye.wav", "wav"); 
    /*for (int i = 0; i < input_wav.numRows(); i++) { 
        for (int j = 0; j < input_wav.numCols(); j++){ 
            cout << input_wav.get(i, j); 
            cout << " ";
        }
        cout << endl; 
    }*/
    
    mean_i = Matrix(Matrix(input_wav).meanVec());
    std_i = Matrix(Matrix(input_wav).stddevVec());
    
    cout << "(size of Audio: " << input_wav.numRows() << " X " << input_wav.numCols() << ")" << endl;
    //////CENTER MATRIX/////
    center = new Matrix(input_wav); //creates a copy of input matrix to use for the centered matrix
    centerMatrix(input_wav, &center); //centers the 'center' matrix
    
    //////COVARIANCE MATRIX/////
    covariance = Matrix(Matrix(center).cov()); //Computes the covariance matrix

    /////COMPUTE EIGENVALUES AND EIGENVECTORS OF M//////
    eigen_vectors = new Matrix(covariance); //Copies the covariance matrix into eigen_vectors

    eigen_values = Matrix(eigen_vectors.eigenSystem()); //Creates the eigenvalues and eigen_vectors


    cout << "(size of EigenValues: " << eigen_values.numRows() << " X " << eigen_values.numCols() << ")" << endl;
    ////NARROW THE EIGEN SYSTEM TO ONLY KEEP K LARGEST/////
    eigen_values.narrow(k_ev);
    eigen_vectors.shorten(k_ev);
    
    cout << "(size of EigenVectors: " << eigen_vectors.numRows() << " X " << eigen_vectors.numCols() << ")" << endl;
    cout << "eigen_vectors >>"  << endl;
    for (int i = 0; i<eigen_vectors.numRows(); i++)
    {
        for (int j = 0; j<eigen_vectors.numCols(); j++)
            cout << eigen_vectors.get(i,j) << " ";
        cout << endl;
    }
    

    //////TRANSLATE THE NORMALIZED DATA//////
    Matrix center_copy = new Matrix(center);
    Matrix eigenVec_copy = new Matrix(eigen_vectors);
    
    eigenVec_copy.transposeSelf();

    translated_data = Matrix(center_copy.dot(eigenVec_copy));

    cout << "(size of Encoded: " << translated_data.numRows() << " X " << translated_data.numCols() << ")" << endl;
    for (int i = 0; i<translated_data.numRows(); i++)
    {
        for (int j = 0; j<translated_data.numCols(); j++)
            cout << translated_data.get(i,j) << " ";
        cout << endl;
    }
    
    
    //////RECOVER DATA FROM COMPRESSED IMAGE/////
   /* recovered_data = Matrix(translated_data.dot(eigen_vectors));
    
    uncenterMatrix(&recovered_data, mean_i, std_i);*/

    
   /* cout << "recovered data >>" << endl;
    for (int i=0; i<recovered_data.numRows(); i++){
        for (int j=0; j<recovered_data.numCols(); j++)
        {
            cout << recovered_data.get(i, j) << " ";
        }
        cout << endl;
    }*/
    
    ///////RECOVERED DATA ANALYSIS//////
   /* difference = (input_wav.dist2(recovered_data))/(input_wav.numRows() * input_wav.numCols());

    cout << "DIST: " << difference << endl;*/
    
    ////SAVE NEW PPM FILE///// //// Save new wav file ////
    /*recovered_data.writeImagePpm("z-after.ppm", "output");*/
    ////////////////////////////////////////////////////////
    
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
