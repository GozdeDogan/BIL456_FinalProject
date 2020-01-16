/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: GOZDEDOGAN
 *
 * Created on January 8, 2020, 10:59 PM
 */

//Worst case O(n)
//ilk gectigi yeri buluyor!

// C++ program to find location of a str in 
// an array of strings which is sorted and 
// has empty strings between strings. 
#include <bits/stdc++.h> 
#include <fstream>
using namespace std; 

// Function to print the sorted array of string 
void printArrayString(string str[], int n);
// Main function to find string location 
int searchStr(string arr[], string str, int size);
int searching(string searchArr[], string searchElmArr[], string foundArr[], int sizeSearchArr, int sizeSearchElmArr);
int readFile(string str[], string filename);
void reads(string arr[], int &sizeArr, string str[], int &sizeStr);



// Driver Code 
int main() 
{ 
    // Input arr of Strings. 
    string arr[] = {"for", "ide", "gel", "mal", "geeks", "ide", "say", "practice", "it" , "yes", "quiz", "no", "or"}; 
    int sizeArr = 13;
    
    // input Search String arr
    string str[] = {"say", "her", "ide", "quiz"}; 
    int sizeStr = 4;
    
    //reads(arr, sizeArr, str, sizeStr);
    
    printArrayString(arr, sizeArr);
    printArrayString(str, sizeStr);
    
    string foundArr[] = {};
    
    int sizeFoundArr = searching(arr, str, foundArr, sizeArr, sizeStr);
    printArrayString(foundArr, sizeFoundArr);
    
    return 0; 
} 

// Function to print the sorted array of string 
void printArrayString(string str[], int n) 
{ 
    cout << "{";
    for (int i=0; i<n; i++){ 
        cout << str[i];
        if(i != n-1)
            cout << ", ";
    }
    cout << "}" << endl;
}


// Main function to find string location 
int searchStr(string arr[], string str, int size) 
{ 
    for(int i = 0; i < size; i++)
    {
        //cout << "arr[i]: " << arr[i] << "\tstr:" << str << endl;
        if(arr[i] == str){
            //cout << "searchStr, i: " << i << endl;
            return i;
        }
    } 
} 

int searching(string searchArr[], string searchElmArr[], string foundArr[], int sizeSearchArr, int sizeSearchElmArr)
{
    int index = 0;
  
    //cout << "size searchElmArr: " << sizeSearchElmArr << endl;
    
    for(int i = 0; i<sizeSearchElmArr; i++)
    {
        //cout << "i: " << i  << "\tSearchElmArr: " << searchElmArr[i] << endl;
        int index2 = searchStr(searchArr, searchElmArr[i], sizeSearchArr);
        //cout << "index2: " << index2 << endl;
        if (index2 > -1 && index2 < sizeSearchArr)
        {
            //cout << "elm: " << searchElmArr[i] << "\tindex: " << index2 << endl;
           // cout << "index: " << index << endl;
            //cout << "foundArr[index]: " << foundArr[index] << "\tsearchArr[index2]: " << searchArr[index2] << endl;
            foundArr[index] = searchArr[index2];
            //cout << "foundArr[index]: " << foundArr[index] << "\tsearchArr[index2]: " << searchArr[index2] << endl;
            index++;
        }
    }   
    
    //cout << "size foundArr: " << index << endl;
    //printArrayString(foundArr, index);
    return index;
}

int readFile(string str[], string filename)
{
    int sizeStr = 0;
    ifstream inFile; 
    inFile.open(filename);
    
    if (!inFile.is_open()) {
        cerr << "Unable to open file datafile.txt";
        exit(1);   // call system to stop
    }
    
    char* sTemp;
    do {
        inFile >> sTemp;
        //cout << sTemp << endl;
        str[sizeStr] = sTemp;
        sizeStr++;
    }while (!inFile.eof());
    //sizeStr--;
    //cout << "sizeStr:" << sizeStr << endl;
    inFile.close();
    
    return sizeStr;
}

void reads(string arr[], int &sizeArr, string str[], int &sizeStr)
{
    sizeArr = readFile(arr, "InputFile.txt");
    sizeStr = readFile(str, "WordList.txt");
}


