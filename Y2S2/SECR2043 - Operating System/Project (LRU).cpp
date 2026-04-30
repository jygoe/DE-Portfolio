#include<iostream>
#include<vector>
#include<string>
using namespace std;

int main(){
    // Initialisation
    string referenceString = "7012030423030321201701";
    int n = referenceString.length();
    vector<int> pages(n);
    int frames = 3;
    // Variable to track memory
    vector<int> memory(frames, -1);
    // Variable to track frequency
    vector<int> frequency(frames, 100);
    int pageFaults = 0;

    for(int i = 0; i < n; i++){
        pages[i] = referenceString[i] - '0';
    }

    // Print Information
    cout 
    << "Least Recently Used (LRU) Implementation for Page Replacement in Virtual Memory\n"
    << "Reference String: " << referenceString << endl
    << "Number of Frames: " << frames << endl << endl;

    // LRU Implementation
    bool available = 0;
    // Print trace table header
    cout << "Request | Memory | Page Fault\n";
    for(int page : pages){
        // Check if the page is in memory
        available = 0;
        for(int i = 0; i < frames; i++){
            if(memory[i] == page){
                available = 1;
                frequency[i] = 0;
                for(int j = 0; j < frames; j++){
                    frequency[j]++;
                }
                break;
            }
        }

        // If not available add to the memory
        if(!available){
            pageFaults++;
            int maxIndex = 0;
            for(int i = 1; i < frames; i++){
                if(frequency[i] > frequency[maxIndex]){
                    maxIndex = i;
                }
            }
            memory[maxIndex] = page;
            frequency[maxIndex] = 0;
            for(int j = 0; j < frames; j++){
                    frequency[j]++;
                }
        }

        // Print trace table
        cout << "   " << page << "    | ";
        for (int frame : memory){
            if(frame != -1){
                cout << frame << " ";
            }
            else{
                cout << "_ ";
            }
        }
        cout << " | ";
        if(!available){
            cout << "True\n";
        }
        else{
            cout << "\n";
        }
    }
    cout << "Total page faults: " << pageFaults << "\n";
    return 0;
}