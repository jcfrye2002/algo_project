#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <limits>

using namespace std;

void knapsack_variant(int n, int W, int l, vector<int> &weights, vector<int> &values)
{

    vector<vector<vector<int>>> OPT(n, vector<vector<int>>(W, vector<int>(l, 0)));

    for (int i = 0; i < n; ++i)
    {
        for (int w = 0; w < W; ++w)
        {
            for (int k = 0; k < l; ++k)
            {

                if (i < k)
                {
                    OPT[i][w][k] = -numeric_limits<int>::infinity();
                }
                else if (w > 0 && k == 0)
                {
                    OPT[i][w][k] = -numeric_limits<int>::infinity();
                }
                else if (w == 0 && k > 0)
                {
                    OPT[i][w][k] = -numeric_limits<int>::infinity();
                }
                else if (w == 0 && k == 0)
                {
                    OPT[i][w][k] = 0;
                }
                else if (weights[i - 1] > w)
                {
                    OPT[i][w][k] = OPT[i - 1][w][k];
                }
                else
                {

                    OPT[i][w][k] = max(OPT[i - 1][w][k], values[i - 1] + OPT[i - 1][w - weights[i - 1]][k - 1]); // maybe wrong
                }
            }
        }
    }

    int i = n - 1, w = W - 1, k = l - 1;
    bool solution = false;
    while (i > 0 && w > 0 && k > 0)
    {
        if (OPT[i][w][k] != OPT[i - 1][w][k])
        {
            solution = true;
            cout << "Item " << i + 1 << ": Weight = " << weights[i] << ", Value = " << values[i] << endl;
            w -= weights[i];
            --k;
        }
        --i;
    }
    if (!solution)
    {
        cout << "No solution exists!" << endl;
    }
}

int main()
{
    while (true)
    {
        cout << "Enter the number of items (or type 'exit' to quit): ";
        string input;
        cin >> input;

        if (input == "exit")
        {
            break;
        }

        int n = stoi(input);

        cout << "Enter the total weight (W): ";
        int W;
        cin >> W;

        cout << "Enter the subset size (l): ";
        int l;
        cin >> l;

        vector<int> weights(n), values(n);

        cout << "Enter weights of items:" << endl;
        for (int i = 0; i < n; ++i)
        {
            cin >> weights[i];
        }

        cout << "Enter values of items:" << endl;
        for (int i = 0; i < n; ++i)
        {
            cin >> values[i];
        }

        knapsack_variant(n, W, l, weights, values);
    }

    return 0;
}
