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
	void show() const;
	void show_by_price_ascending();   // ascending  order (asc)  - за зростанням
	void show_by_price_descending();  // descending order (desc) - за зменшенням
	void show_by_popularity_descending();
	void show_by_popularity_ascending();

private:   // приватні методи - доступні лише для інших методів
	void _swap12();
	void _swap23(ListNode* node);
};

#endif