/*
Insertion Sort
Assignment 1
Name:   LUVINESH A/L SUDESH
Matric: A21EC0198
*/

#include <iostream>
#include <vector>
using namespace std;


void insertionSort(vector<int>& arr, int& comparisons, int& swaps) {
    int n = arr.size(); // Get the size of the array
    comparisons = 0; 
    swaps = 0;       

    for (int i = 1; i < n; ++i) {
        int key = arr[i]; // Element to be placed at the correct position
        int j = i - 1; // Index to compare with the sorted part of the array

                while (j >= 0 && arr[j] > key) {
            ++comparisons; // counter for comparisons
            arr[j + 1] = arr[j]; // Shift element to the right
            --j; // Move to the next element
            ++swaps; // Count a shift (swap)
        }

        arr[j + 1] = key; // Place the 'key' at the correct position
        if (j >= 0) ++comparisons; 
    }
}

// Function to display the elements of an array
void displayArray(const vector<int>& arr) {
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
}

int main() {

    vector<int> marks = {75, 95, 60, 88, 70};
    
    int comparisons = 0, swaps = 0;

    // Display the original array
    cout << "Original Array: ";
    displayArray(marks);

    // Perform Insertion Sort
    insertionSort(marks, comparisons, swaps);

    // Display the sorted array
    cout << "Sorted Array: ";
    displayArray(marks);

    // Output the number of comparisons and swaps
    cout << "Total Comparisons: " << comparisons << endl;
    cout << "Total Swaps: " << swaps << endl;

    return 0;
}