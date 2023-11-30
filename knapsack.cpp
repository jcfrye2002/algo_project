#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <limits>

using namespace std;

void knapsack_variant(int n, int W, int l, vector<int> &weights, vector<int> &values)
{

    vector<vector<vector<int>>> OPT(n, vector<vector<int>>(W, vector<int>(l, 0))); //matrix to store subsets

    //populate matrix
    for (int i = 0; i < n; ++i) //number of items
    {
        for (int w = 0; w < W; ++w) //weight
        {
            for (int k = 0; k < l; ++k) //subset size
            {

                if (i < k)
                {
                    OPT[i][w][k] = -numeric_limits<int>::infinity(); //if item count is < subset size, no solution, negative infinity
                }
                else if (w > 0 && k == 0)
                {
                    OPT[i][w][k] = -numeric_limits<int>::infinity(); //if weight is positive and subset size is 0, negative infinity
                }
                else if (w == 0 && k > 0)
                {
                    OPT[i][w][k] = -numeric_limits<int>::infinity(); //if weight is 0 and subset size is positive
                }
                else if (w == 0 && k == 0)
                {
                    OPT[i][w][k] = 0; //if both weight and subset size is 0
                }
                else if (weights[i - 1] > w)
                {
                    OPT[i][w][k] = OPT[i - 1][w][k]; //if weight of item is greater than total weight, look at i - 1th item
                }
                else
                {

                    OPT[i][w][k] = max(OPT[i - 1][w][k], values[i - 1] + OPT[i - 1][w - weights[i - 1]][k - 1]); //take maximum of two cases
                    //Case 1: item not taken, look at i - 1 items, same weight w, k subset
                    //Case 2: item taken (add its value), look at i - 1 items, subtract weight of item i from total weight, reduce subset size by 1
                }
            }
        }
    }

    //traceback function
    int i = n - 1, w = W - 1, k = l - 1;
    bool solution = false;
    while (i > 0 && w > 0 && k > 0) //while item count,weight,subset is positive
    {
        if (OPT[i][w][k] != OPT[i - 1][w][k]) //checks whether optimal value for current state OPT[i][w][k] is different from optimal value for the 
            //state obtained by excluding OPT[i - 1][w][k]. If different,implies item i is part of the optimal solution.
        {
            solution = true; //solution has been found
            cout << "Item " << i + 1 << ": Weight = " << weights[i] << ", Value = " << values[i] << endl; //prints item properties
            w -= weights[i]; //decreases weight by weight of the current item
            --k; //decrease subset size availibility
        }
        --i;
    }
    if (!solution)
    {
        cout << "No solution exists!" << endl; //solution doesn't exist
    }
}

int main()
{
    while (true) //keeps checking for input
    {
        //input for number of items
        cout << "Enter the number of items (or type 'exit' to quit): ";
        string input;
        cin >> input;

        if (input == "exit") //exit from running program
        {
            break;
        }

        int n = stoi(input);

        cout << "Enter the total weight (W): "; //input for weight of subset
        int W;
        cin >> W;

        cout << "Enter the subset size (l): "; //input for subset size
        int l;
        cin >> l;

        vector<int> weights(n), values(n); //declare vectors to store attriubtes of items

        cout << "Enter weights of items:" << endl; //user input for item weights
        for (int i = 0; i < n; ++i)
        {
            cin >> weights[i];
        }

        cout << "Enter values of items:" << endl; //user input for item values
        for (int i = 0; i < n; ++i)
        {
            cin >> values[i];
        }

        knapsack_variant(n, W, l, weights, values); //run knapsack_variant function with user input
    }

    return 0;
}
