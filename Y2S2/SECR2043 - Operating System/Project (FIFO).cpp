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
    vector<int> memory(frames, -1);
    int pageFaults = 0;

    for(int i = 0; i < n; i++){
        pages[i] = referenceString[i] - '0';
    }

    // Print Information
    cout 
    << "First-In First-Out (FIFO) Implementation for Page Replacement in Virtual Memory\n"
    << "Reference String: " << referenceString << endl
    << "Number of Frames: " << frames << endl << endl;

    // FIFO Implementation
    int currentIndex = 0;
    bool available = 0;
    // Print trace table header
    cout << "Request | Memory | Page Fault\n";
    for(int page : pages){
        // Check if the page is in memory
        available = 0;
        for(int i = 0; i < frames; i++){
            if(memory[i] == page){
                available = 1;
                break;
            }
        }

        // If not available add to the memory
        if(!available){
            pageFaults++;
            memory[currentIndex] = page;
            currentIndex = (currentIndex + 1) % frames;
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