#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//n = number of items, W = total weight capacity, l = subset size
vector<int> KnapsackVariant(int n, int W, int l, const vector<int>& weights, const vector<int>& values) {
    vector<vector<vector<int>>> OPT(n + 1, vector<vector<int>>(W + 1, vector<int>(l + 1, 0))); //create vector to store subproblem solutions

    // fill matrix using bottom-up dynamic programming
    for (int i = 1; i <= n; ++i) { //iterates over the number of items
        for (int w = 1; w <= W; ++w) { //iterates over weight capacity
            for (int k = 1; k <= l; ++k) {//iterates over subset size
                if (weights[i - 1] > w || k > i) {
                    OPT[i][w][k] = OPT[i - 1][w][k];//if weight of the current item greater than current total weight (w) OR if subset size (k)
                    // is greater than the current item index (i), then it sets OPT[i][w][k] to the value obtained without including the current item (OPT[i - 1][w][k]).
                } else {
                    OPT[i][w][k] = max(OPT[i - 1][w][k], values[i - 1] + OPT[i - 1][w - weights[i - 1]][k - 1]); //If conditions are not met current item can be included in the subset.                
                }
            }
        }
    }

    //if a solution doesn't exist
    if (OPT[n][W][l] == 0) {
        cout << "No subset exists with the given constraints." << endl;
        return {};
    }

    // Traceback function
    vector<int> subset; //creates vector to return subset
    int i = n, w = W, k = l; //initlize variables to values at end of dynamic programming process
    while (i > 0 && w > 0 && k > 0) { //while items > 0, weight capacity is positive, remaining subset size is positive
        if (OPT[i][w][k] != OPT[i - 1][w][k]) { //checks if current item is in optimal soution, if not equal current item was included
            subset.push_back(i);
            w -= weights[i - 1];
            k--;
        }
        i--;
    }

    return subset;
}

int main() {
    int n, W, l;

    // input item number, weight, and subset size
    cout << "Enter the number of items: ";
    cin >> n;
    cout << "Enter the total weight: ";
    cin >> W;
    cout << "Enter the subset size: ";
    cin >> l;

    // input weights and values
    vector<int> weights(n), values(n);
    cout << "Enter weights of the items: ";
    for (int i = 0; i < n; ++i) {
        cin >> weights[i];
    }
    cout << "Enter values of the items: ";
    for (int i = 0; i < n; ++i) {
        cin >> values[i];
    }

    vector<int> optimalSubset = KnapsackVariant(n, W, l, weights, values); //call function solution

    //print solution
    if (!optimalSubset.empty()) {
        cout << "Optimal Subset: ";
        for (int i = optimalSubset.size() - 1; i >= 0; --i) {
            cout << optimalSubset[i] << " ";
        }
        cout << endl;
    }

    return 0;
}
