#include<iostream>
#include<fstream>
#include<random>
#include<vector>

using namespace std;

#define INF 100000000

void readClusters(string filename);
void generateCluster(int n, int max, int seed);
void buildTree();
void print2dVector(vector<vector<double> >& v);
string add2Map(string a, string b);
string getString(char a); 
void printTree(); 

int n;
vector<vector<double> > C;
vector<string> tree;

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
    
    print2dVector(C);
    buildTree();
    printTree();

	return 0;
}

void readClusters(string filename) {
	ifstream fin (filename);
	if(!fin) {
		cerr << "Error opening input file!" << endl;
		exit(1);
	}

	fin >> n;

	vector<vector<double> > t(
        n,
        vector<double>(n));
    C = t;

    tree.reserve(2*n-1);

	for (int i = 0; i < n; i++) {
        tree.push_back(getString((char) ('a'+i)));
		for(int j = i + 1; j < n; j++) {
            fin >> C[i][j];
			C[j][i] = C[i][j];
		}
	}

	fin.close();
}

void generateCluster(int n, int max, int seed) {
	srand(seed);

	vector<vector<double> > t(
        n,
        vector<double>(n));
    C = t;

    
    tree.reserve(2*n-1);

	for (int i = 0; i < n; i++) {
        tree.push_back(getString((char) ('a'+i)));
        for(int j = i + 1; j < n; j++) {
			C[i][j] = double(rand()) / RAND_MAX * max;
			C[j][i] = C[i][j];
		}
	}
}

void buildTree() {
    static int cnt = 0;
    if (C.size() == 1) {
        return;
    }

    double min = INF;
    int l, r;

 	for (int i = 0; i < C.size(); i++) {
        for(int j = i + 1; j < C[i].size(); j++) {
	        if (min > C[i][j]) {
                min = C[i][j];
                l = i;
                r = j;
            }
        }
	}
    
    for (int i = 0; i < C.size(); i++) {
        if (i == l || i == r) continue;
            
        double dlr = (C[i][l] + C[i][r]) / 2;
        C[i][l] = dlr;
        C[l][i] = dlr;

        C[i].erase(C[i].begin()+r);
    }
    C[l].erase(C[l].begin()+r);
    C.erase(C.begin()+r);
   
    tree[l] = add2Map(tree[l], tree[r]);
    tree.erase(tree.begin()+r);

    buildTree();
}

void print2dVector(vector<vector<double> >& v) {
    cout << v.size() << endl;
	for (int i = 0; i < v.size(); i++) {
		for(int j = 0; j < v[i].size(); j++) {
			cout << fixed << setprecision(4) << v[i][j] << "\t";
		}
		cout << endl;
	}
    cout << endl;
}

string add2Map(string a, string b) {
    return "( " + a + " , " + b + " )"; 
}

string getString(char a) {
    string t(1,a);
    return t;
}

void printTree() {
   cout << tree[0] << endl;
}
