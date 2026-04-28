/*
Bubble Sort
Assignment 1
Name:   Basel A. A. Abunada
Matric: A22EC4006
*/

#include <iostream> 
using namespace std; 
 
void bubbleSort(int arr[], int n, int &comparisons, int &swaps) { 
    // Initialize counters for comparisons and swaps
    comparisons = 0;
    swaps = 0;
 
    // Outer loop runs for (n - 1) passes
    for (int i = 0; i < n - 1; i++) { 
        // Inner loop for comparing adjacent elements
        for (int j = 0; j < n - i - 1; j++) { 
            comparisons++; // record comparison
            if (arr[j] > arr[j + 1]) { 
                int temp = arr[j]; 
                arr[j] = arr[j + 1]; 
                arr[j + 1] = temp; 
                swaps++; // record swap 
            } 
        } 
    } 
} 
 
int main() { 
    int marks[] = {75, 95, 60, 88, 70}; 
    int n = sizeof(marks) / sizeof(marks[0]); 
 
    int comparisons, swaps; 
 
    bubbleSort(marks, n, comparisons, swaps); 
 
    // Display the sorted array
    cout << "Sorted Marks: "; 
    for (int i = 0; i < n; i++) { 
        cout << marks[i] << " "; 
    } 
    cout << endl; 

    // Display the total number of comparisons and swaps
    cout << "Total Comparisons: " << comparisons << endl; 
    cout << "Total Swaps: " << swaps << endl; 
 
    return 0; 
}