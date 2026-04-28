//GOE JIE YING A23CS0224 13/12/2023
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

//Task 6 (List function prototype)
void dispStatus(int);
void getInput(int&, int&, int&, int&);  
void dispOutput(int&, const char *,int&, int&, int&, int&);
float calcAverage(int, int);

//Task 1 (Display the status of a zone by the number of active cases)
void dispStatus(int active_cases)
{
    if (active_cases > 40)
        cout << left << setw(21) << "Status" << ": Red zone" << endl;
    else if (active_cases >= 21 && active_cases <= 40)
        cout << left << setw(21) << "Status" << ": Orange zone" << endl;
    else if (active_cases >= 1 && active_cases <= 20)
        cout << left << setw(21) << "Status" << ": Yellow zone" << endl;
    else
        cout << left << setw(21) << "Status" << ": Green zone" << endl;
}

//Task 2 (Get the input for total cases, new cases, total death and total recovered from user)
void getInput(int &total_cases, int &new_cases, int &total_death, int &total_recovered)
{
    cout << left << setw(21) << "Total cases" << ": ";
    cin >> total_cases;

    cout << left << setw(21) << "New cases" << ": ";
    cin >> new_cases;

    cout << left << setw(21) << "Total death" << ": ";
    cin >> total_death;

    cout << left << setw(21) << "Total recovered" << ": ";
    cin >> total_recovered;
}

//Task 3 (Display the summary of all cases)
void dispOutput(int &active_cases, const char *stateName, int &total_cases, int &new_cases, int &total_death, int &total_recovered)
{
    active_cases = total_cases + new_cases - total_death - total_recovered;

    cout << "\n<<<<<<<<<<< SUMMARY >>>>>>>>>> " << endl;
    cout << left << setw(21) << "Active cases" << ": " << active_cases << endl;

    dispStatus(active_cases); //Call the function to display the status
    cout << "\nPress <ENTER> to continue...";

    cin.ignore(); //Ignore the newline left in the buffer
}

//Task 4 (Calculate the average number of active cases per state)
float calcAverage(int total_active_cases, int num_of_states)
{
	if (num_of_states == 0)
        return 0;
    return static_cast<float>(total_active_cases) / num_of_states; //average = total_active_cases / num_of_states
	}

//Task 5 (main function)
int main()
{
	int highest_active_cases = 0, num_of_states = 0;
	int total_cases, new_cases, total_death, total_recovered, active_cases, total_active_cases = 0;
	char stateName[50] = {};
    string highest_active_state = " ";
	
	do{
		cout << "<<<<<<<<<<<<< DATA >>>>>>>>>>>>>" << endl;
		cout << left << setw(21) << "State name " << ": ";
		cin.getline(stateName, 50);
	
		getInput(total_cases, new_cases, total_death, total_recovered);
	
    	dispOutput(active_cases, stateName, total_cases, new_cases, total_death, total_recovered);
		
		total_active_cases += active_cases; //sum all active cases
		num_of_states++;

		if (active_cases > highest_active_cases){  //to find the highest active cases
            highest_active_cases = active_cases;
            highest_active_state = stateName;
        }
	  
    }while(cin.get() == '\n'); //continue the loop when user press ENTER OR press any key to end the loop

	cout << "\n<<<<<<<<< ACTIVE CASES >>>>>>>>>>" << endl; //Display the total, highest & average cases after the loop end

    cout << left << setw(21) << "Total" << ": " << total_active_cases << endl;
    cout << left << setw(21) << "Highest" << ": " << highest_active_cases << "(" << highest_active_state << ")" << endl;
    	
	cout << "Average for " << num_of_states << " states "<< ": " << calcAverage(total_active_cases, num_of_states);
	
	return 0;
}

