#include <iostream>
#include <string>
using namespace std;

const int amountoftabs = 10; // Max size of the stack
const int undoSize = 10;     // Max size of the undo stack

class stack
{
private:
    int top;                   // Tracks the top of the stack
    string data[amountoftabs]; // Stores open tabs

    int undoTop;               // Tracks the top of the undo stack
    string undoData[undoSize]; // Stores recently closed tabs for recovery

public:
    void createStack()
    {
        top = -1;     // Initialize main stack
        undoTop = -1; // Initialize undo stack
    }

    void push(string newtab)
    {
        if (isFull())
        {
            cout << "Cannot open a new tab, stack is FULL." << endl;
        }
        else
        {
            top += 1;
            data[top] = newtab;
        }
    }

    void pop(int &userinput)
    {
        if (isEmpty())
        {
            cout << "Cannot close a tab, stack is EMPTY." << endl;
        }
        else
        {
            cout << "Closed tab: " << data[top] << endl;

            // Save the closed tab into the undo stack
            if (!isUndoFull())
            {
                undoTop += 1;
                undoData[undoTop] = data[top];
            }
            else
            {
                cout << "Undo stack is full. Cannot save this closed tab." << endl;
            }

            top -= 1; // Remove the tab from the main stack

            // Check if the stack is empty and trigger exit
            if (isEmpty())
            {
                cout << "All tabs are closed. Exiting browser automatically..." << endl;
                userinput = 5; // Trigger exit condition
            }
        }
    }

    void recoverTab()
    {
        if (isUndoEmpty())
        {
            cout << "No recently closed tabs to recover." << endl;
        }
        else
        {
            string recoveredTab = undoData[undoTop];
            undoTop -= 1;       // Remove the recovered tab from the undo stack
            push(recoveredTab); // Add it back to the main stack
            cout << "Recovered tab: " << recoveredTab << endl;
        }
    }

    void displayStack()
    {
        if (isEmpty())
        {
            cout << "No open tabs." << endl;
        }
        else
        {
            cout << "\n-- OPENED TABS --" << endl;
            for (int i = 0; i <= top; i++) // Display tabs from bottom to top horizontally
            {
                cout << "| " << i + 1 << ". " << data[i] << " ";
            }
            cout << "|" << endl; // End with a pipe for formatting
        }
    }

    bool isFull()
    {
        return (top == amountoftabs - 1);
    }

    bool isEmpty() // checks whether the main stack is empty
    {
        return (top == -1);
    }

    bool isUndoFull() // checks whether the undo stack is full
    {
        return (undoTop == undoSize - 1);
    }

    bool isUndoEmpty()
    {
        return (undoTop == -1);
    }

    int getTabCount()
    {
        return top + 1; // Return the number of open tabs
    }

    string stackTop()
    {
        if (isEmpty())
        {
            cout << "Stalk is empty!" << endl;
            return " ";
        }
        else
        {
            return data[top];
        }
    }
};

int main()
{
    stack browserStack;         // Create a stack object
    browserStack.createStack(); // Initialize the stack

    int userinput; // For menu navigation
    string tabName;

    do
    {
        cout << "\n-- -- -- OPERA BROWSER -- -- -- -- --" << endl;
        browserStack.displayStack();
        cout << "\nMenu Options:" << endl;
        cout << "1. Add Tab" << endl;
        cout << "2. Close Tab" << endl;
        cout << "3. Recover Tab" << endl;
        cout << "4. Show Top Tab" << endl;
        cout << "5. Exit Browser" << endl;
        cout << "Enter your choice: ";
        cin >> userinput;

        switch (userinput)
        {
        case 1: // Add a tab
            cout << "Enter tab name: ";
            cin.ignore(); // Clear input buffer
            getline(cin, tabName);
            browserStack.push(tabName);
            break;

        case 2: // Close a tab
            browserStack.pop(userinput);
            break;

        case 3: // Recover a tab
            browserStack.recoverTab();
            break;

        case 4: // Display the top tab
            if (!browserStack.isEmpty())
            {
                cout << "The top tab is: " << browserStack.stackTop() << endl;
            }
            break;

        case 5:                                  // Exit with logic
            if (browserStack.getTabCount() == 1) // If only one tab is open
            {
                cout << "One tab open. Closing browser automatically..." << endl;
            }
            else if (browserStack.getTabCount() > 1) // If more than one tab is open
            {
                char confirm;
                cout << "You have multiple open tabs. Are you sure you want to close the browser? (y/n): ";
                cin >> confirm;

                if (confirm == 'y' || confirm == 'Y')
                {
                    cout << "Exiting browser..." << endl;
                }
                else
                {
                    userinput = 0; // Reset input to stay in the loop
                    cout << "Exit cancelled. Returning to menu..." << endl;
                }
            }
            else // If no tabs are open
            {
                cout << "Exiting browser..." << endl;
            }
            break;

        default: // Invalid input
            cout << "Invalid choice! Please try again." << endl;
        }

    } while (userinput != 5);

    return 0;
}
