
#include <iostream>
#include <vector>
#include <climits>
#include <iomanip>
#include <string>

using namespace std;

int main()
{
    int n;

    cout << "============================================\n";
    cout << "       MATRIX CHAIN MULTIPLICATION          \n";
    cout << "          DYNAMIC PROGRAMMING               \n";
    cout << "============================================\n";

    // Input number of matrices
    cout << "\nEnter number of matrices: ";
    cin >> n;

    if (cin.fail() || n <= 0)
    {
        cout << "Invalid number of matrices!\n";
        return 1;
    }

    // Input dimensions
    vector<int> p(n + 1);

    cout << "\nEnter " << n + 1 << " dimensions:\n";

    for (int i = 0; i <= n; i++)
    {
        cin >> p[i];

        if (cin.fail() || p[i] <= 0)
        {
            cout << "Invalid matrix dimension!\n";
            return 1;
        }
    }

    // Display matrix dimensions
    cout << "\n============================================\n";
    cout << "             MATRIX DETAILS                 \n";
    cout << "============================================\n";

    for (int i = 1; i <= n; i++)
    {
        cout << "Matrix A" << i << " : "
             << p[i - 1] << " x " << p[i] << endl;
    }

    // DP table and split table
    vector<vector<long long>> dp(
        n + 1, vector<long long>(n + 1, 0)
    );

    vector<vector<int>> split(
        n + 1, vector<int>(n + 1, 0)
    );

    // Dynamic Programming
    for (int length = 2; length <= n; length++)
    {
        for (int i = 1; i <= n - length + 1; i++)
        {
            int j = i + length - 1;

            dp[i][j] = LLONG_MAX;

            for (int k = i; k < j; k++)
            {
                long long cost =
                    dp[i][k] +
                    dp[k + 1][j] +
                    1LL * p[i - 1] * p[k] * p[j];

                if (cost < dp[i][j])
                {
                    dp[i][j] = cost;
                    split[i][j] = k;
                }
            }
        }
    }

    // Display DP Table
    cout << "\n============================================\n";
    cout << "             DP COST TABLE                  \n";
    cout << "============================================\n";

    cout << setw(8) << " ";

    for (int j = 1; j <= n; j++)
        cout << setw(12) << ("A" + to_string(j));

    cout << endl;

    for (int i = 1; i <= n; i++)
    {
        cout << setw(8) << ("A" + to_string(i));

        for (int j = 1; j <= n; j++)
        {
            if (j < i)
                cout << setw(12) << "-";
            else
                cout << setw(12) << dp[i][j];
        }

        cout << endl;
    }

    // Display Split Table
    cout << "\n============================================\n";
    cout << "              SPLIT TABLE                  \n";
    cout << "============================================\n";

    cout << setw(8) << " ";

    for (int j = 1; j <= n; j++)
        cout << setw(8) << ("A" + to_string(j));

    cout << endl;

    for (int i = 1; i <= n; i++)
    {
        cout << setw(8) << ("A" + to_string(i));

        for (int j = 1; j <= n; j++)
        {
            if (j <= i)
                cout << setw(8) << "-";
            else
                cout << setw(8) << split[i][j];
        }

        cout << endl;
    }

    // Print optimal parenthesization
    cout << "\n============================================\n";
    cout << "           OPTIMAL PARENTHESIZATION         \n";
    cout << "============================================\n";

    auto printOrder = [&](auto&& self, int i, int j) -> void
    {
        if (i == j)
        {
            cout << "A" << i;
            return;
        }

        cout << "(";

        int k = split[i][j];

        self(self, i, k);

        cout << " x ";

        self(self, k + 1, j);

        cout << ")";
    };

    cout << "Best Order: ";
    printOrder(printOrder, 1, n);

    cout << endl;

    // Final result
    cout << "\n============================================\n";
    cout << "               FINAL RESULT                 \n";
    cout << "============================================\n";

    cout << "Total Matrices          : " << n << endl;

    cout << "Minimum Multiplications : "
         << dp[1][n] << endl;

    cout << "\nTime Complexity  : O(n^3)";
    cout << "\nSpace Complexity : O(n^2)";

    cout << "\n\n============================================\n";
    cout << "              PROGRAM ENDED                 \n";
    cout << "============================================\n";

    return 0;
}
