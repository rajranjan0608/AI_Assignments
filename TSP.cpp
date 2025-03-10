#include <iostream>
#include <queue> 

using namespace std;
#define MAX 100

<<<<<<< HEAD
struct state {
	int F, v[MAX], uv[MAX];
=======
//States consisting of Cost Function, cost and vector of Visited and Un-Visited Nodes
struct state {
	int F, g;
	vector<int> v, uv;
>>>>>>> c2e7a2453b62587ca3d49f040060542a1a1a2e0b
};

struct CompareHeight {
    bool operator()(state const& s1, state const& s2)
    {
<<<<<<< HEAD
        return s1.F < s2.F;
    }
};

int main() {

	int n;
	cout << "Enter no. of nodes: "; cin >> n;

	int arr[n][n] = {0};

	for(int i = 1; i <= n; i++) {
		cout << "Distance of Node " << i << " to the following nodes: " << "\n";
		for(int j = 1; j <= n; j++) {
			if(j != i) {
				cout << j << ": ";
				cin >> arr[i][j];
				cout << "\n";
=======
        return s2.F < s1.F;
    }
};

//MST as the Heuristic Function
int MST(int V) {

	return 0;
}

int main() {

	int n;
	// cout << "Enter no. of nodes: ";
	cin >> n;

	int arr[n+1][n+1];

	for(int i = 0; i <= n; i++) {
		for(int j = 0; j <= n; j++) {
			arr[i][j] = 0;
		}
	}

	for(int i = 1; i <= n; i++) {
		
		/*
		5
		10 1 2 10
		1 5 2
		5 5
		1
		*/
		for(int j = i+1; j <= n; j++) {
			if(j == i+1) {
				// cout << "Distance of Node " << i << " to the following nodes: " << "\n";
			}
			if(arr[i][j] == 0) {
				int cost;
				// cout << j << ": ";
				cin >> cost;
				arr[i][j] = arr[j][i] = cost;
				// cout << "\n";
>>>>>>> c2e7a2453b62587ca3d49f040060542a1a1a2e0b
			}
		}
	}

<<<<<<< HEAD
	priority_queue<state, vector<state>, CompareHeight> Q;

	state s0;
	s0.F = 0;

	for(int i = 1; i <= n; i++) {
		s0.uv[i] = i;
	}

	s0.
=======
	//Declare the Priority Queue of State
	priority_queue<state, vector<state>, CompareHeight> Q, testQ;

	//Declare and initialze 1st State
	state s0;
	s0.F = 0;
	s0.g = 0;

	//Put the 1st node to Visted and Rest to Un-Visited
	s0.v.push_back(1);
	for(int i = 2; i <= n; i++) {
		s0.uv.push_back(i);
	}

	//Push the 1st State to Queue
	Q.push(s0);

	int flag = 0;
	state bestSol;

	while(!Q.empty()) {

		state parState = Q.top();	Q.pop();

		int H = MST(parState.v.size()); //Incomplete

		//If there are no nodes to Visit
		if(parState.uv.size() == 0) {

			//Add the cost for returning to 1st node to the total cost
			parState.g += arr[1][parState.v[parState.v.size()-1]+1];

			//If the solution is already calculated assign the parState to bestSol
			if(flag == 0) {
				bestSol = parState;
				flag = 1;
			}else if(parState.g < bestSol.g) {
				bestSol = parState;
			}
		}

		//Create Child's by putting every node from Un-Visted to Visited one by one
		for(int i = 0; i < parState.uv.size(); i++) {

			//Creating Child same as Parent
			state child = parState;

			//Erase 1 node from Child's Unvisited and put it to Child's Visited
			child.v.push_back(parState.uv[i]);
			child.uv.erase(child.uv.begin()+i);
			
			//cout << "Par Cost: " << parState.g << " Cost: " << arr[parState.v[parState.v.size()-1]][parState.uv[i]] << "\n";
			
			//Calculate Child's G value
			child.g = parState.g + arr[parState.v[parState.v.size()-1]+1][parState.uv[i]+1];
			
			//cout << "Parent State: " << parState.uv[i] << " & Child State: " << child.uv[i] << "\n";
			
			//Calculate Child's Cost function (F)
			child.F = child.g + H;

			//child.F = child.g + 
			
			//cout << "(G, F, H): " << child.g << " " << child.F << " " << H << "\n";
			
			//Push the Child to Priority Queue
			Q.push(child);
		}
	}

	for(int i = 0; i < bestSol.v.size(); i++) {

		cout << bestSol.v[i] << " -> ";

	}

	cout << "1\nCost: " << bestSol.g << "\n";
>>>>>>> c2e7a2453b62587ca3d49f040060542a1a1a2e0b

	return 0;
}
