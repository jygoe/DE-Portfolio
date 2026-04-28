// ? EXERCISE 1: INTRODUCTION TO CLASSES AND OBJECTS

// Programming Technique II
// Semester 2, 2023/2024

// Section: 01
// Member 1's Name: Lam Yoke Yu     Location: Ipoh, Perak
// Member 2's Name: Goe Jie Ying    Location: Kluang, Johor
//
// Date and time of pair programming sessions:
//   04/04/2024 4.00pm-5.10pm
// 
// Video link: N/A


// ? Notes: Choose the debug mode "Console Program" to run the program.

#include <iostream>
#include <string>

using namespace std;

class Subject{
	private:
		string name;
        string code;
        float score;
        string gradeEarned;
        float gradePoint;
        float pointEarned;

	public:
		// Constructor
		Subject(string n, string c, float s){
            name = n;
            code = c;
            score = s;
			gradeEarned = "";
			gradePoint = 0.0;
			pointEarned = 0.0;
        };
        
		// Destructor
        ~Subject()
		{}

		// Setter
		void setName(string n)
			{ name = n; }
		void setCode(string c)
			{ code = c; }
		void setScore(float s)
			{score = s; }
		// Getter
		string getName() const
			{ return name; };
		string getCode() const
			{ return code; };
		float getScore() const
			{ return score; };
		string getGrade() const
			{ return gradeEarned; };
		float getGradePoint() const
			{ return gradePoint; };

		float calcPointEarned()
            { return gradePoint * getCreditHour(); }
		void calcGrade(){
            if(score < 30){ gradeEarned = "E"; gradePoint = 0.00; }
            else if(score < 35){ gradeEarned = "D-"; gradePoint = 0.67; }
            else if(score < 40){ gradeEarned = "D";  gradePoint = 1.00; }
            else if(score < 45){ gradeEarned = "D+"; gradePoint = 1.33; }
            else if(score < 50){ gradeEarned = "C-"; gradePoint = 1.67; }
            else if(score < 55){ gradeEarned = "C";  gradePoint = 2.00; }
            else if(score < 60){ gradeEarned = "C+"; gradePoint = 2.33; }
            else if(score < 65){ gradeEarned = "B-"; gradePoint = 2.67; }
            else if(score < 70){ gradeEarned = "B";  gradePoint = 3.00; }
            else if(score < 75){ gradeEarned = "B+"; gradePoint = 3.33; }
            else if(score < 80){ gradeEarned = "A-"; gradePoint = 3.67; }
            else if(score < 90){ gradeEarned = "A";  gradePoint = 4.00; }
            else{ gradeEarned = "A+"; gradePoint = 4.00; }
        }
		int getCreditHour(){
			return code[code.size() - 1] - 48;
		}
};

int main()
{
    string name, code;
    float score = 0;

	// Get data
	cout << "Enter the following data: " << endl;
	cout << "  Subject name => ";
	getline(cin, name);
	cout << endl;

	cout << "  Subject code => ";
	getline(cin, code);
	cout << endl;

	cout << "  Score earned => ";
	cin >> score;
	while (score < 0 || score > 100){
        cout << "Invalid score... Please re-enter...\n";
        cout << "  Score earned => ";
        cin >> score;
    }
	cout << endl;

	// Constructor
	Subject data(name, code, score);
    data.calcGrade();

	cout << endl << endl;

	// Print Result
	cout << "THE RESULT" << endl << endl;

	cout << "Subject Code : " << data.getCode() << endl;
	cout << "Subject Name : " << data.getName() << endl;
	cout << "Credit Hour  : " << data.getCreditHour() << endl;
	cout << "Score Earned : " << data.getScore() << endl;
	cout << "Grade Earned : " << data.getGrade() << endl;
	cout << "Grade Point  : " << data.getGradePoint() << endl;
	cout << "Point Earned : " << data.calcPointEarned() << endl;
	cout << endl;

	system("pause");

	return 0;
}
