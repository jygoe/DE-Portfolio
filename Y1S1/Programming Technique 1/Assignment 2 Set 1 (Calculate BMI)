// Goe Jie Ying A23CS0224
// Lam Yoke Yu A23CS0233
// Assignment 2 Set 1
// 15/11/2023

# include <iostream>
# include <iomanip>
# include <cmath>
using namespace std;

float getHeight(int);
float getWeight(int);

int main()
{
	int age,
		gender,
		unitChoice,
		height,
		weight;
		
	float MSJ, RHB;
	char repeat;
	
	do{
		cout << "*** Basal Metabolic Rate (BMR) Calculator ***\n";
		
		// Get age
		cout << "Age [15-80]: ";
		cin >> age;
		while (age < 15 || age > 80){
			cout << "That is an invalid value, please re-enter...\n";
			cout << "Age [15-80]: ";
			cin >> age;
		}
		
		// Get gender
		cout << "Gender [1-Male][2-Female]: ";
		cin >> gender;
		while (gender != 1 && gender != 2){
			cout << "That is an invalid value, please re-enter...\n";
			cout << "Gender [1-Male][2-Female]: ";
			cin >> gender;
		}
		
		// Get unitChoice
		cout 
		<< "\nAre you using US Unit or Metric Unit for your height & weight?\n"
		<< "1-US Unit (feet, inches & pound) \n"
		<< "2-Metric Unit (cm & kg)\n"
		<< "Unit Choice [1-US Unit][2-Metric Unit]: ";
		cin >> unitChoice;
		while (unitChoice != 1 && unitChoice != 2){
			cout << "That is an invalid value, please re-enter...\n";
			cout << "Unit Choice [1-US Unit][2-Metric Unit]: ";
			cin >> unitChoice;
		}
		cout << endl;
		
		// Get Height & Weight
		height = getHeight(unitChoice);
		weight = getWeight(unitChoice);
		
		// Calculate MSJ & RHB
		if (gender == 1){
			MSJ = (10 * weight) + (6.25 * height) - (5 * age) + 5;
			RHB = (13.397 * weight) + (4.799 * height) - (5.677 * age) + 88.362;
		}
		else if (gender == 2){
			MSJ = (10 * weight) + (6.25 * height) - (5 * age) - 161;
			RHB = (9.247 * weight) + (3.098 * height) - (4.330 * age) + 447.593;
		}
		
		// Display
		cout 
		<< "\nBMR Calculated using Mifflin-St Jeor Equation: " << MSJ << " calories / day" << endl
		<< "BMR Calculated using Revised Harris-Benedict Equation: " << RHB << " calories / day" << endl << endl;
	
		cout 
		<< left
		<< "*** Daily calorie needs based on activity level ***\n"
		<< setw(50) << "Activity level" 								<< " | " << "Calorie\n"
		<< setw(50) << "Sedentary: little or no exercise"				<< " | " << round(MSJ * 1.2)  << endl
		<< setw(50) << "Exercise 1-3 times / week"						<< " | " << round(MSJ * 1.375) << endl
		<< setw(50) << "Exercise 4-5 times / week"						<< " | " << round(MSJ * 1.465) << endl
		<< setw(50) << "Daily exercise or intense exercise 3-4 / week"	<< " | " << round(MSJ * 1.55) << endl
		<< setw(50) << "Intense exercise 6-7 times / week"				<< " | " << round(MSJ * 1.725) << endl
		<< setw(50) << "Very intense exercise daily, or physical job"	<< " | " << round(MSJ * 1.9)  << endl << endl;
		
		cout 
		<< "*** Definitions ***\n"
		<< left
		<< setw(25) << "Exercise: " << "15-30 minutes of elevated heart rate activity\n"
		<< setw(25) << "Intense exercise: " << "45-120 minutes of elevated heart rate activity\n"
		<< setw(25) << "Very intense exercise: " << "2+ hours of elevated hear rate activity\n\n";
		
		cout << "Do you want to enter other data? [0-No][1-Yes]: ";
		cin >> repeat;
	}
	while (repeat == 0);
	
	cout << "Thank you!";
	
	return 0;
}

float getHeight(int unitChoice)
{
	int feet, inches, height;
	if (unitChoice == 1){
		cout << "Height (feet): ";
		cin >> feet;
		cout << "Height (inches): ";
		cin >> inches;
		height = feet * 30.48 + inches * 2.54;
	}
	else{
		cout << "Height (cm): ";
		cin >> height;
	}
	
	return height;
}

float getWeight(int unitChoice)
{
	int pounds, kg;
	if (unitChoice == 1){
		cout << "Weight (pounds): ";
		cin >> pounds;
		kg = pounds * 0.45;
	}
	else{
		cout << "Weight (kg): ";
		cin >> kg;
	}
	
	return kg;
}
