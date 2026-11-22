
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

int main()
{
    int n, capacity;

    cout << "========================================\n";
    cout << "       0/1 KNAPSACK PROBLEM             \n";
    cout << "       DYNAMIC PROGRAMMING              \n";
    cout << "========================================\n";

    // Input number of items
    cout << "\nEnter number of items: ";
    cin >> n;

    if (cin.fail() || n <= 0)
    {
        cout << "Invalid number of items!\n";
        return 1;
    }

    vector<int> weight(n);
    vector<int> profit(n);

    // Input weights
    cout << "\nEnter weights of items:\n";

    for (int i = 0; i < n; i++)
    {
        cout << "Weight of item " << i + 1 << ": ";
        cin >> weight[i];

        if (cin.fail() || weight[i] <= 0)
        {
            cout << "Invalid weight!\n";
            return 1;
        }
    }

    // Input profits
    cout << "\nEnter profits of items:\n";

    for (int i = 0; i < n; i++)
    {
        cout << "Profit of item " << i + 1 << ": ";
        cin >> profit[i];

        if (cin.fail() || profit[i] < 0)
        {
            cout << "Invalid profit!\n";
            return 1;
        }
    }

    // Input capacity
    cout << "\nEnter knapsack capacity: ";
    cin >> capacity;

    if (cin.fail() || capacity < 0)
    {
        cout << "Invalid capacity!\n";
        return 1;
    }

    // Display item details
    cout << "\n========================================\n";
    cout << "              ITEM DETAILS              \n";
    cout << "========================================\n";

    cout << left << setw(12) << "Item"
         << setw(12) << "Weight"
         << "Profit\n";

    cout << "----------------------------------------\n";

    for (int i = 0; i < n; i++)
    {
        cout << left << setw(12) << i + 1
             << setw(12) << weight[i]
             << profit[i] << endl;
    }

    // Create DP table
    vector<vector<int>> dp(
        n + 1, vector<int>(capacity + 1, 0)
    );

    // Dynamic Programming
    for (int i = 1; i <= n; i++)
    {
        for (int w = 0; w <= capacity; w++)
        {
            if (weight[i - 1] <= w)
            {
                int includeItem =
                    profit[i - 1] +
                    dp[i - 1][w - weight[i - 1]];

                int excludeItem = dp[i - 1][w];

                dp[i][w] = max(includeItem, excludeItem);
            }
            else
            {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    // Display DP Table
    cout << "\n========================================\n";
    cout << "             DP TABLE                  \n";
    cout << "========================================\n";

    cout << left << setw(8) << "Item";

    for (int w = 0; w <= capacity; w++)
        cout << setw(5) << w;

    cout << endl;

    for (int i = 0; i <= n; i++)
    {
        cout << left << setw(8) << i;

        for (int w = 0; w <= capacity; w++)
        {
            cout << setw(5) << dp[i][w];
        }

        cout << endl;
    }

    // Find selected items
    vector<int> selected(n, 0);

    int w = capacity;

    for (int i = n; i >= 1; i--)
    {
        if (dp[i][w] != dp[i - 1][w])
        {
            selected[i - 1] = 1;
            w -= weight[i - 1];
        }
    }

    // Display selected items
    cout << "\n========================================\n";
    cout << "             FINAL SOLUTION             \n";
    cout << "========================================\n";

    cout << left << setw(10) << "Item"
         << setw(12) << "Weight"
         << setw(12) << "Profit"
         << "Status\n";

    cout << "----------------------------------------\n";

    int totalWeight = 0;
    int totalProfit = 0;

    for (int i = 0; i < n; i++)
    {
        cout << left << setw(10) << i + 1
             << setw(12) << weight[i]
             << setw(12) << profit[i];

        if (selected[i] == 1)
        {
            cout << "Selected\n";

            totalWeight += weight[i];
            totalProfit += profit[i];
        }
        else
        {
            cout << "Not Selected\n";
        }
    }

    // Final results
    cout << "\n========================================\n";
    cout << "              RESULT                   \n";
    cout << "========================================\n";

    cout << "Knapsack Capacity : " << capacity << endl;
    cout << "Total Weight      : " << totalWeight << endl;
    cout << "Remaining Capacity: "
         << capacity - totalWeight << endl;

    cout << "Maximum Profit    : " << totalProfit << endl;

    cout << "\nSelected Item Numbers: ";

    bool found = false;

    for (int i = 0; i < n; i++)
    {
        if (selected[i] == 1)
        {
            cout << i + 1 << " ";
            found = true;
        }
    }

    if (!found)
        cout << "None";

    cout << "\n\nTime Complexity  : O(n * W)";
    cout << "\nSpace Complexity : O(n * W)";

    cout << "\n\n========================================\n";
    cout << "             PROGRAM ENDED             \n";
    cout << "========================================\n";

    return 0;
}
