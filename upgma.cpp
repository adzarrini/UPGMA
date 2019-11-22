#include<iostream>
#include<fstream>
#include<random>

using namespace std;

void readClusters(string filename);
void generateCluster(int n, int max, int seed);
void printCluster();

int n;
double **C;

int main(int argc, char* argv[]) {
	if (argc != 3 && argc != 5)
	{
		std::cerr << "Arguments must be presented in either of the following ways." << std::endl;
		std::cerr << "./upgma -f <file>" << std::endl;
		std::cerr << "./upgma -g <number> <max> <seed>" << std::endl;
		exit(1);
	}
	
	if(!strncmp(argv[1], "-f", 2) && argc == 3) {
		readClusters(argv[2]);
	}

	if(!strncmp(argv[1], "-g", 2) && argc == 5) {
		n = atoi(argv[2]);
		int max = atoi(argv[3]);
		int seed = atoi(argv[4]);
		generateCluster(n, max, seed);
	}

	printCluster();

	return 0;
}

void readClusters(string filename) {
	ifstream fin (filename);
	if(!fin) {
		cerr << "Error opening input file!" << endl;
		exit(1);
	}

	fin >> n;

	C = new double*[n];

	for (int i = 0; i < n; i++) {
		C[i] = new double[n];
		for(int j = 0; j < n; j++) {
			fin >> C[i][j];
		}
	}

	fin.close();
}

void generateCluster(int n, int max, int seed) {
	srand(seed);

	C = new double*[n];

	for (int i = 0; i < n; i++) {
		C[i] = new double[n];
		for(int j = 0; j < n; j++) {
			C[i][j] = double(rand()) / RAND_MAX * max;
		}
	}
}

void printCluster() {
	for (int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			cout << C[i][j] << "\t";
		}
		cout << endl;
	}
}