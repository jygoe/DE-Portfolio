// ? EXERCISE 2: CLASS AND OBJECT MANIPULATIONS

// Programming Technique II
// Semester 2, 2021/2022

// Section: 01
// Member 1's Name: Goe Jie Ying    Location: Kluang, Johor (i.e. where are you currently located)
// Member 2's Name: Lam Yoke Yu     Location: UTM Skudai、
//
// Date and time of pair programming sessions:
//   5/5/2024 4:20pm 2hours(Date, time and estimate duration)
//   _________  (Date, time and estimate duration)
//
// Video link:
//   _________

// ? Notes: Choose the debug mode "Console Program" to run the program.

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

#define MAX_SUBJECT_COUNT 10

class Subject
{
private:
	string name;
	string code;
	int score;

public:
	Subject();
	int credit() const;
	string grade() const;
	double point() const;
	void print() const;

	bool operator < (Subject&) const;

    friend int readUserInput(Subject subjects[]);
	friend Subject lower(Subject, Subject);
};

int main()
{
	// a. Declare an array to hold a list of subjects
	Subject subjects[MAX_SUBJECT_COUNT];

	// b. Read inputs and store in array
	int subjectCount = readUserInput(subjects);

	cout << endl
 		 << "THE RESULT"
		 << endl
		 << endl;

	// Print the output table header
	cout << left << setw(15) << "Subject Code";
	cout << left << setw(30) << "Subject Name";
	cout << left << setw(10) << "Credit";
	cout << left << setw(10) << "Score";
	cout << left << setw(10) << "Grade";
	cout << left << setw(10) << "Point";
	cout << left << setw(10) << "Sub Total";
	cout << endl
		 << endl;
	
	double totalPoint = 0.0;
    int totalCredit = 0;
    for (int i = 0; i < subjectCount; ++i)
    {
        subjects[i].print();
        totalPoint += subjects[i].credit() * subjects[i].point();
        totalCredit += subjects[i].credit();
    }

	cout << endl;
	cout << "TOTAL POINT  : " << totalPoint << endl;
	cout << "TOTAL CREDIT : " << totalCredit << endl;
	cout << "GPA          : " << fixed << setprecision(2) << totalPoint / totalCredit << endl << endl;

	// d. Determine the subject that earns the lowest score
	Subject lowest = subjects[0];
	for(int i = 1; i < subjectCount; i++)
	{
		lowest = lower(subjects[i], lowest);
	}

	cout << "LOWEST SUBJECT : " << endl;
	cout << endl;
	lowest.print();

	system("pause");

	return 0;
}

// The definition of the default constructor is fully given
Subject::Subject() : name(""), code(""), score(0) {}

// The definition of the getter for the 'credit()' is fully given
int Subject::credit() const { return code[7] - '0'; }

// The definition of the getter for the 'grade()' is fully given
string Subject::grade() const
{
	if (score >= 90)
		return "A+";
	if (score >= 80)
		return "A";
	if (score >= 75)
		return "A-";
	if (score >= 70)
		return "B+";
	if (score >= 65)
		return "B";
	if (score >= 60)
		return "B-";
	if (score >= 55)
		return "C+";
	if (score >= 50)
		return "C";
	if (score >= 45)
		return "C-";
	if (score >= 40)
		return "D+";
	if (score >= 35)
		return "D";
	if (score >= 30)
		return "D-";
	return "E";
}

// 1. Define an accessor method that determines the point value of the grade earned
double Subject::point() const
{
    if (grade() == "A+" || grade() == "A")
        return 4.00;
    else if (grade() == "A-")
        return 3.67;
    else if (grade() == "B+")
        return 3.33;
    else if (grade() == "B")
        return 3.00;
    else if (grade() == "B-")
        return 2.67;
    else if (grade() == "C+")
        return 2.33;
    else if (grade() == "C")
        return 2.00;
    else if (grade() == "C-")
        return 1.67;
    else if (grade() == "D+")
        return 1.33;
    else if (grade() == "D")
        return 1.00;
    else if (grade() == "D-")
        return 0.67;
    else
        return 0.00;
}

// 2. Define an accesor method that prints the subject's information
void Subject::print() const{
	cout << left << fixed << setprecision(2) 
	<< setw(15) << code
	<< setw(30) << name
	<< setw(10) << this->credit()
	<< setw(10) << score
	<< setw(10) << this->grade()
	<< setw(10) << this->point()
	<< setw(10) << this->credit() * this->point()
	<< endl;
}

// 3. Define an overloaded operator in the class for the ‘less than’ operator ( < ) that determines whether a subject is smaller than the other subject
bool Subject::operator<(Subject &s) const{
	if (this->score < s.score){
		return true;
	}
	else 
		return false;
};

// 5. Define a friend function that read a list of subjects from user input
int readUserInput(Subject subjects[])
{
    int subjectNum;
    cout << "How many subjects do you want to enter? => ";
    cin >> subjectNum;
    while(subjectNum <= 0 && subjectNum > MAX_SUBJECT_COUNT){
		cout << "Invalid value.\n";
		cout << "How many subjects do you want to enter? => ";
		cin >> subjectNum;
	}
	cout << endl;
    cin.ignore();

    for (int i = 0; i < subjectNum; i++)
    {
        cout << "Enter info for subject #" << i + 1 << ": " << endl;
        cout << "Subject Code => ";
        getline(cin, subjects[i].code);
        cout << "Subject name => ";
        getline(cin, subjects[i].name);
        cout << "Score earned => ";
        cin >> subjects[i].score;
        cin.ignore();
		cout << endl;
    }
    return subjectNum;
}


// 4. Define a regular function that determines the lower subject.
Subject lower(Subject a, Subject b)
{
	if(a < b){
		return a;
	}
	else
		return b;
}