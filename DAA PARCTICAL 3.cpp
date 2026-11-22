
#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;
using namespace chrono;

// MAX HEAPIFY
void maxHeapify(vector<int>& arr, int size,
                int index, long long& comparisons)
{
    int largest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < size)
    {
        comparisons++;

        if (arr[left] > arr[largest])
            largest = left;
    }

    if (right < size)
    {
        comparisons++;

        if (arr[right] > arr[largest])
            largest = right;
    }

    if (largest != index)
    {
        swap(arr[index], arr[largest]);

        maxHeapify(arr, size, largest, comparisons);
    }
}

// MAX HEAP SORT
void maxHeapSort(vector<int>& arr, long long& comparisons)
{
    int n = arr.size();

    comparisons = 0;

    // Build Max Heap
    for (int i = n / 2 - 1; i >= 0; i--)
        maxHeapify(arr, n, i, comparisons);

    // Extract elements
    for (int i = n - 1; i > 0; i--)
    {
        swap(arr[0], arr[i]);

        maxHeapify(arr, i, 0, comparisons);
    }
}

// MIN HEAPIFY
void minHeapify(vector<int>& arr, int size,
                int index, long long& comparisons)
{
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < size)
    {
        comparisons++;

        if (arr[left] < arr[smallest])
            smallest = left;
    }

    if (right < size)
    {
        comparisons++;

        if (arr[right] < arr[smallest])
            smallest = right;
    }

    if (smallest != index)
    {
        swap(arr[index], arr[smallest]);

        minHeapify(arr, size, smallest, comparisons);
    }
}

// MIN HEAP SORT
void minHeapSort(vector<int>& arr, long long& comparisons)
{
    int n = arr.size();

    comparisons = 0;

    // Build Min Heap
    for (int i = n / 2 - 1; i >= 0; i--)
        minHeapify(arr, n, i, comparisons);

    // Extract elements
    for (int i = n - 1; i > 0; i--)
    {
        swap(arr[0], arr[i]);

        minHeapify(arr, i, 0, comparisons);
    }

    // Convert descending to ascending
    reverse(arr.begin(), arr.end());
}

// CHECK SORTED ARRAY
bool isSorted(const vector<int>& arr)
{
    return is_sorted(arr.begin(), arr.end());
}

// DISPLAY ARRAY
void displayArray(const vector<int>& arr)
{
    int limit = min(15, (int)arr.size());

    for (int i = 0; i < limit; i++)
        cout << arr[i] << " ";

    if (arr.size() > limit)
        cout << "...";

    cout << endl;
}

// MAIN FUNCTION
int main()
{
    int n, choice;

    srand(static_cast<unsigned int>(time(nullptr)));

    cout << "\n============================================\n";
    cout << "         HEAP SORT PERFORMANCE ANALYSIS     \n";
    cout << "============================================\n";

    cout << "\n1. Generate Random Array";
    cout << "\n2. Enter Array Manually";

    cout << "\n\nEnter your choice: ";
    cin >> choice;

    if (cin.fail() || (choice != 1 && choice != 2))
    {
        cout << "Invalid choice!\n";
        return 1;
    }

    cout << "\nEnter number of elements: ";
    cin >> n;

    if (cin.fail() || n <= 0)
    {
        cout << "Invalid array size!\n";
        return 1;
    }

    vector<int> original(n);

    // INPUT ARRAY
    if (choice == 1)
    {
        for (int i = 0; i < n; i++)
            original[i] = rand() % 100000;
    }
    else
    {
        cout << "\nEnter array elements:\n";

        for (int i = 0; i < n; i++)
        {
            cin >> original[i];

            if (cin.fail())
            {
                cout << "Invalid array element!\n";
                return 1;
            }
        }
    }

    vector<int> maxArray = original;
    vector<int> minArray = original;

    long long maxComparisons = 0;
    long long minComparisons = 0;

    // MAX HEAP SORT TIMING
    auto startMax = high_resolution_clock::now();

    maxHeapSort(maxArray, maxComparisons);

    auto endMax = high_resolution_clock::now();

    // MIN HEAP SORT TIMING
    auto startMin = high_resolution_clock::now();

    minHeapSort(minArray, minComparisons);

    auto endMin = high_resolution_clock::now();

    // EXECUTION TIME
    double maxTime =
        duration<double, milli>(endMax - startMax).count();

    double minTime =
        duration<double, milli>(endMin - startMin).count();

    // DISPLAY INPUT
    cout << "\n============================================\n";
    cout << "                 INPUT DATA                 \n";
    cout << "============================================\n";

    cout << "Total Elements : " << n << endl;

    cout << "\nOriginal Array:\n";
    displayArray(original);

    // MAX HEAP RESULTS
    cout << "\n============================================\n";
    cout << "              MAX HEAP SORT                 \n";
    cout << "============================================\n";

    cout << "Comparisons    : " << maxComparisons << endl;
    cout << fixed << setprecision(6);

    cout << "Execution Time: " << maxTime << " ms\n";

    cout << "Sorted Status : "
         << (isSorted(maxArray) ? "YES" : "NO") << endl;

    cout << "\nSorted Array:\n";
    displayArray(maxArray);

    // MIN HEAP RESULTS
    cout << "\n============================================\n";
    cout << "              MIN HEAP SORT                 \n";
    cout << "============================================\n";

    cout << "Comparisons    : " << minComparisons << endl;

    cout << "Execution Time: " << minTime << " ms\n";

    cout << "Sorted Status : "
         << (isSorted(minArray) ? "YES" : "NO") << endl;

    cout << "\nSorted Array:\n";
    displayArray(minArray);

    // COMPARISON TABLE
    cout << "\n============================================\n";
    cout << "              FINAL COMPARISON              \n";
    cout << "============================================\n";

    cout << left << setw(18) << "Algorithm"
         << setw(18) << "Comparisons"
         << "Time (ms)\n";

    cout << "--------------------------------------------\n";

    cout << left << setw(18) << "Max Heap Sort"
         << setw(18) << maxComparisons
         << maxTime << endl;

    cout << left << setw(18) << "Min Heap Sort"
         << setw(18) << minComparisons
         << minTime << endl;

    // PERFORMANCE RESULT
    cout << "\n============================================\n";
    cout << "             PERFORMANCE RESULT             \n";
    cout << "============================================\n";

    if (maxTime < minTime)
        cout << "Max Heap Sort is faster in this test.\n";
    else if (minTime < maxTime)
        cout << "Min Heap Sort is faster in this test.\n";
    else
        cout << "Both algorithms took equal time.\n";

    cout << "\nTime Complexity:\n";
    cout << "Max Heap Sort : O(n log n)\n";
    cout << "Min Heap Sort : O(n log n)\n";

    cout << "\nSpace Complexity:\n";
    cout << "O(log n) auxiliary recursion stack\n";

    cout << "\n============================================\n";
    cout << "               PROGRAM ENDED                \n";
    cout << "============================================\n";

    return 0;
}
