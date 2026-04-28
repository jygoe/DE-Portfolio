/*
Improved Bubble Sort
Assignment 1
Name:   Goe Jie Ying
Matric: A23CS0224
*/

#include <iostream>
using namespace std;

void bubbleSort (int data[], int n)
{ 
    int temp;
    bool sorted = false; // false when swaps occur
    int comparisons = 0; // counter for comparisons
    int swaps = 0;       // counter for swaps

    for (int pass = 1; (pass < n) && !sorted; ++pass)
    { 
        sorted = true; // assume sorted
        cout << "\nPass " << pass << endl;

        for (int x = 0; x < n-pass; ++x)
        {   
            comparisons++;

            if (data[x] > data[x+1])
            { // exchange items
                temp = data[x];
                data[x] = data[x+1];
                data[x+1] = temp;
                sorted = false; // signal exchange
                swaps++;
                cout << "Swap at index [" << x << "]" << endl;            
            } // end if
        } // end for

        // Display array after each pass
        cout << "Array after pass " << pass << ": ";
        for (int i = 0; i < n; i++) 
        {
            cout << data[i] << " ";
        }
        cout << endl;

    } // end for
    
    cout << "\nTotal comparisons: " << comparisons << endl;
    cout << "Total swaps: " << swaps << endl;

} // end bubbleSort

int main()
{
    int data[] = {75, 95, 60, 88, 70};
    int n = 5;

    // Display the original array
    cout << "Original array: ";
    for (int i = 0; i < n; i++)
        cout << data[i] << " ";
    cout << endl;

    bubbleSort(data, n); // call the bubble sort function

    cout << endl;

    // Display the sorted array
    cout << "Sorted array: ";
    for (int i = 0; i < n; i++)
        cout << data[i] << " ";
    cout << endl << endl;

    return 0;
}



