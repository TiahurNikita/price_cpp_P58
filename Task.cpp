#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include "product.h"
#include "price.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "UA");
	Price* price = new Price();
	while (true) {
		int choice;
		cout << "Choice an action:\n"
			<< "1: init price\n"
			<< "2: load price\n"
			<< "3: show price\n"
			<< "0: exit\n";

		choice = _getch();
		switch (choice) {
		case 49:  // '1'
			if (price->init()) {
				cout << "Price init success" << endl;
			}
			else {
				cout << "Price init error" << endl;
			}
			break;
		case 50:  // '2'
			if (price->load()) {
				cout << "Price load success" << endl;
			}
			else {
				cout << "Price load error" << endl;
			}
			break;
		case 51:  // '3'
			price->show();
			break;
		case 48:  // '0'
			return 0;
		default:
			cout << "Invalid choice" << endl;
		}
	}
	delete price;
	return 0;
}
