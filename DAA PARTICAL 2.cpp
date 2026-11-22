
#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace chrono;

// Linear Search
int linearSearch(const vector<int>& arr, int key, int& comparisons)
{
    comparisons = 0;

    for (int i = 0; i < arr.size(); i++)
    {
        comparisons++;

        if (arr[i] == key)
            return i;
    }

    return -1;
}

// Binary Search
int binarySearch(const vector<int>& arr, int key, int& comparisons)
{
    int low = 0;
    int high = arr.size() - 1;

    comparisons = 0;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        comparisons++;

        if (arr[mid] == key)
            return mid;

        if (arr[mid] < key)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return -1;
}

// Display Results
void displayResult(string name, int index,
                   int comparisons, long long timeTaken)
{
    cout << "\n" << name << "\n";
    cout << "--------------------------------------\n";

    if (index != -1)
        cout << "Element Position : " << index + 1 << endl;
    else
        cout << "Element Not Found\n";

    cout << "Comparisons      : " << comparisons << endl;
    cout << "Execution Time   : " << timeTaken
         << " microseconds\n";
}

int main()
{
    int n, key;

    cout << "========================================\n";
    cout << "       SEARCHING ALGORITHM ANALYSIS     \n";
    cout << "========================================\n";

    cout << "\nEnter number of elements: ";
    cin >> n;

    if (cin.fail() || n <= 0)
    {
        cout << "Invalid array size!\n";
        return 1;
    }

    vector<int> arr(n);

    cout << "\nEnter " << n << " elements:\n";

    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];

        if (cin.fail())
        {
            cout << "Invalid element input!\n";
            return 1;
        }
    }

    // Sort array for Binary Search
    sort(arr.begin(), arr.end());

    cout << "\nSorted Array:\n";

    for (int x : arr)
        cout << x << " ";

    cout << "\n\nEnter element to search: ";
    cin >> key;

    if (cin.fail())
    {
        cout << "Invalid search element!\n";
        return 1;
    }

    int linearComparisons, binaryComparisons;
    int linearIndex, binaryIndex;

    // Linear Search Timing
    auto start1 = high_resolution_clock::now();

    linearIndex = linearSearch(arr, key, linearComparisons);

    auto stop1 = high_resolution_clock::now();

    long long linearTime =
        duration_cast<microseconds>(stop1 - start1).count();

    // Binary Search Timing
    auto start2 = high_resolution_clock::now();

    binaryIndex = binarySearch(arr, key, binaryComparisons);

    auto stop2 = high_resolution_clock::now();

    long long binaryTime =
        duration_cast<microseconds>(stop2 - start2).count();

    // Display Results
    displayResult("LINEAR SEARCH", linearIndex,
                  linearComparisons, linearTime);

    displayResult("BINARY SEARCH", binaryIndex,
                  binaryComparisons, binaryTime);

    // Comparison
    cout << "\n========================================\n";
    cout << "             FINAL COMPARISON           \n";
    cout << "========================================\n";

    cout << left << setw(22) << "Algorithm"
         << setw(18) << "Comparisons"
         << "Time (microseconds)\n";

    cout << "----------------------------------------\n";

    cout << left << setw(22) << "Linear Search"
         << setw(18) << linearComparisons
         << linearTime << endl;

    cout << left << setw(22) << "Binary Search"
         << setw(18) << binaryComparisons
         << binaryTime << endl;

    cout << "\nTime Complexities:\n";
    cout << "Linear Search : O(n)\n";
    cout << "Binary Search : O(log n)\n";

    cout << "\nPerformance Result:\n";

    if (linearComparisons < binaryComparisons)
        cout << "Linear Search used fewer comparisons.\n";
    else if (binaryComparisons < linearComparisons)
        cout << "Binary Search used fewer comparisons.\n";
    else
        cout << "Both used the same number of comparisons.\n";

    cout << "\nNote: Binary Search requires a sorted array.\n";

    cout << "\n========================================\n";
    cout << "             PROGRAM ENDED              \n";
    cout << "========================================\n";

    return 0;
}
