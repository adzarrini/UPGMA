#include<iostream>
#include<fstream>
#include<random>

using namespace std;

void createInputFile(string filename, int n, int max, int seed); 

int main(int argc, char* argv[]) {
    if (argc != 5) {
        cerr << "Arguments must be presented in the following way." << endl;
        cerr << "./gen-dm <filename> <number> <max> <seed>" << endl;
        exit(1);
    }

    string filename = argv[1];
    int n = atoi(argv[2]);
    int max = atoi(argv[3]);
    int seed = atoi(argv[4]);
    
    createInputFile(filename, n, max, seed);   
}

void createInputFile(string filename, int n, int max, int seed) {
    ofstream fout (filename);
    if (!fout) {
        cerr << "Error creating output file" << endl;
        exit(1);
    }
	
	fout << n << endl;

    srand(seed);
    for (int i = 0; i < n; i++) {
        for(int j = 0; j < i; j++) {
            fout << double(rand()) / RAND_MAX * max << endl; 
        }
    }

    fout.close();
}

