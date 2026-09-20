#ifndef PRICE_H
#define PRICE_H

#include "product.h" 

using namespace std;


struct ListNode {   // для зв'язного списку
	Product product;
	ListNode* next;
};

struct Price {
	const string PRICE_FILENAME = "price.txt";
	ListNode* first = NULL;
	bool init(); // інкапсуляція - перенесення функцій, пов'язаних
	bool load(); // з прайсом до окремої "капсули" - структури Price
	void show() const; //
};

#endif