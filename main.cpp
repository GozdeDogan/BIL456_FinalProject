
#include"WaveFunction.h"

using namespace std;

int main(int argc, char *argv[])
{
  
    WaveFunction* a=new WaveFunction(128,13);
      
    vector<vector<float> > mfccs1 = a->getMFCCs("goodbye.wav");

    cout << "row:" << mfccs1.size() << "    col:" << mfccs1[0].size() << endl;
    
    for (int i = 0; i < mfccs1.size(); i++) { 
        for (int j = 0; j < mfccs1[i].size(); j++) 
            cout << mfccs1[i][j] << " "; 
        cout << endl; 
    }
    
    return 0;
}
