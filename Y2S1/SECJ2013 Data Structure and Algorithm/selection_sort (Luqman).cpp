/*
Selection Sort
Assignment 1
Name:   LUQMAN HARITH BIN MOHD SHAHAR
Matric: A23CS3009
*/

#include <iostream>
using namespace std;

void selectionSort(int arr[], int n, int &comparisonCount, int &swapCount)
{
    comparisonCount = 0;
    swapCount = 0;

    for (int i = 0; i < n - 1; i++)
    {
        int minIndex = i;
        for (int j = i + 1; j < n; j++)
        {
            comparisonCount++; // Count the comparison
            if (arr[j] < arr[minIndex])
            {
                minIndex = j;
            }
        }
        if (minIndex != i)
        {
            swap(arr[i], arr[minIndex]); // Swap elements
            swapCount++;                 // Count the swap
        }
    }
}

int main()
{
    int arr[] = {75, 95, 60, 88, 70};
    int n = sizeof(arr) / sizeof(arr[0]);
    int comparisonCount, swapCount;

    // Print unsorted array
    cout << "Unsorted array: ";
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;

    selectionSort(arr, n, comparisonCount, swapCount);

    // Print sorted array
    cout << "Sorted array: ";
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;

    // Print metrics
    cout << "Total comparisons: " << comparisonCount << endl;
    cout << "Total swaps: " << swapCount << endl;

    return 0;
}
