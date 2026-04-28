// Goe Jie Ying A23CS0224
// Lam Yoke Yu A23CS0233
// Assignment 2 Set 2
// 15/11/2023

#include <iostream>
#include <iomanip>
using namespace std;
int getCarPrice();

int main()
{
	int deposit, loan, year;
	float rate, totInstallment, monthlyInstallment;
	char repeat;
	
	do{
		int price = getCarPrice();
		
		cout << "\nYour car price is RM " << price << endl;
		
		// Get Deposit
		cout << "Insert your deposit(at least 2000): ";
		cin >> deposit;
		
		while (deposit < 2000 || deposit > price)
		{
			cout << "Please insert again: ";
			cin >> deposit;
		}
		
		// Calculate loan
		loan = price - deposit;
		
		// Get rate
		cout << "Insert the rate(not more than 5%): ";
		cin >> rate;
			
		while(rate < 0 || rate > 5)
		{
			cout << "Please insert again: ";
			cin >> rate;
		}
		
		// Get installment period
		cout << "Installment period (1-9): ";
		cin >> year;
		
		while(year < 1 || year > 9)
		{
			cout << "Please insert again: ";
			cin >> year;
		}
		
		// Calulate and display installment
		totInstallment = loan + (loan * rate/100 * year);
		cout << "\nYour total installment is RM " << setprecision(2) << fixed << totInstallment << endl;
		
		monthlyInstallment = totInstallment / (year * 12);
		cout << "Your monthly installment is RM " << setprecision(2) << fixed << monthlyInstallment << endl;
		
		cout << "\nDo you want to enter other data? (0-No, 1-Yes): ";
		cin >> repeat;
		cout << endl;
	}
	while (repeat == 0);
	
	return 0;
}

int getCarPrice()
{
	int carModel, carVariant, location, price;
	
	// Get Car Model
	cout 
	<< "1. SuperFast \n"
	<< "2. FastFast \n"
	<< "3. Speedy\n"
	<< "Please select the car model (1, 2, 3): ";
	cin >> carModel;
		 
	while (carModel < 1 || carModel > 3)
	{
		cout << "Please enter again: ";
		cin >> carModel;
	}

	// Get Car Variant
	cout << endl
	<< "1. Manual\n"
	<< "2. Auto\n"
	<< "Please select the car variant (1, 2): ";
	cin >> carVariant;

	while (carVariant < 1 || carVariant > 2)
	{
		cout << "Please enter again: ";
		cin >> carVariant;
	}
	
	// Get location
	cout << endl
	<< "1. Penisular Malaysia \n"
	<< "2. East Malaysia\n"
	<< "Please select your location (1, 2): ";
	cin >> location;	
	
	while (location != 1 && location != 2)
	{
		cout << "Please enter again: ";
		cin >> location;
	}

	// Car model price
	if (carModel == 1)
		price = 60000;
		
	else if (carModel == 2)
		price = 45000;
		
	else
		price = 52000;
	
	// Car variant price
	if(carVariant == 2)
		price += 2000;
	
	else
		price += 0;
	
	// Location price
	if(location == 2)
		price += 2000;
	
	else
		price += 0;
	
	return price;
}
























