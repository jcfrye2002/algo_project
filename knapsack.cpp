#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int knapsack_variant(int n, int W, int l, vector<int> &weights, vector<int> &values)
{
    vector<vector<vector<int>>> OPT(n + 1, vector<vector<int>>(W + 1, vector<int>(l + 1, 0)));

    for (int i = 1; i <= n; ++i)
    {
        for (int w = 0; w <= W; ++w)
        {
            for (int k = 0; k <= l; ++k)
            {
                // Base cases
                if (i < k || w == 0 || k == 0)
                {
                    OPT[i][w][k] = 0;
                }
                else if (weights[i - 1] == w && k == 1)
                {
                    OPT[i][w][k] = max(OPT[i - 1][w][k], values[i - 1]);
                }
                else if (weights[i - 1] <= w && k > 1)
                {
                    OPT[i][w][k] = max(OPT[i - 1][w][k], values[i - 1] + OPT[i - 1][w - weights[i - 1]][k - 1]);
                }
                else
                {
                    OPT[i][w][k] = OPT[i - 1][w][k];
                }
            }
        }
    }

    // Check if a solution exists
    if (OPT[n][W][l] == 0)
    {
        cout << "No solution exists." << endl;
        return 0;
    }

    // Traceback to find the selected items
    int i = n, w = W, k = l;
    vector<int> selected_items;

    while (i > 0 && w > 0 && k > 0)
    {
        if (weights[i - 1] == w && k == 1)
        {
            selected_items.push_back(i);
            break;
        }
        else if (OPT[i][w][k] != OPT[i - 1][w][k])
        {
            selected_items.push_back(i);
            w -= weights[i - 1];
            k--;
        }
        i--;
    }

    // Output the selected items and their values and weights
    cout << "Selected items:" << endl;
    for (int i = selected_items.size() - 1; i >= 0; --i)
    {
        int item_index = selected_items[i] - 1;
        cout << "Item " << selected_items[i] << ": Value = " << values[item_index]
             << ", Weight = " << weights[item_index] << endl;
    }

    // Output the maximum value of the subset
    cout << "Maximum value of a subset: " << OPT[n][W][l] << endl;

    return OPT[n][W][l];
}

int main()
{
    while (true)
    {
        int n, W, l;
        cout << "Enter the number of items (enter 0 to exit): ";
        cin >> n;

        if (n == 0)
        {
            break; // Exit the program if the user enters 0
        }

        vector<int> weights(n), values(n);

        cout << "Enter the weights of items: ";
        for (int i = 0; i < n; ++i)
        {
            cin >> weights[i];
        }

        cout << "Enter the values of items: ";
        for (int i = 0; i < n; ++i)
        {
            cin >> values[i];
        }

        cout << "Enter the total weight (W): ";
        cin >> W;

        cout << "Enter the number of items in the subset (l): ";
        cin >> l;

        knapsack_variant(n, W, l, weights, values);
    }

    return 0;
}
