#include <iostream>
#include <conio.h>
#include "price.h"

using namespace std;

bool Price::init() {
	ofstream file(PRICE_FILENAME);
	if (!file.is_open()) {
		std::cout << "File open error";
		return false;
	}
	Product product = { "Black Pencil", 14.95f, 20, 0 };
	product.save_to_file(file);

	product = { "Blue Pen", 19.95f, 25, 5 };
	product.save_to_file(file);

	product = { "Green Whiteboard Marker", 17.50f, 10, 10 };
	product.save_to_file(file);

	product = { "Lined Copybook", 7.50f, 20, 10 };
	product.save_to_file(file);

	product = { "Grided Copybook", 36.80f, 5, 10 };
	product.save_to_file(file);

	product = { "Ruler 30cm", 3.50f, 5, 0 };
	product.save_to_file(file);

	product = { "Sticker", 3.50f, 5, 0 };
	product.save_to_file(file);

	product = { "Marker-Black-Dark", 4.50f, 45, 12 };
	product.save_to_file(file);

	file.close();
	return true;
}

bool Price::load() {
	ifstream file(PRICE_FILENAME);
	if (!file.is_open()) {
		cout << "File open error";
		return false;
	}
	ListNode* last = first;
	if (first) {
		do {
			last = first->next;
			delete first;
			//first = last;
		} while (first = last);
	}

	Product product;
	int cnt = 1;
	while (product.load_from_file(file)) {
		product.order = cnt;
		if (last == NULL) {
			first = last = new ListNode;
			first->product = product;
			first->next = NULL;
		}
		else {
			last->next = new ListNode;
			last->next->product = product;
			last->next->next = NULL;
			last = last->next;
		}
		cnt++;
	}
	file.close();
	return true;
}

void Price::show() const {
	if (first == NULL) {
		cout << "Price is empty" << std::endl;
		return;
	}
	ListNode* node = first;
	while (node) {
		cout << node->product.to_string() << std::endl;
		node = node->next;
	}
}

void Price::_swap12() {
	ListNode* tmp;
	tmp = first->next;         // n2
	first->next = tmp->next;   // n1->next = n3
	tmp->next = first;         // n2->next = n1
	first = tmp;
}

void Price::_swap23(ListNode* node) {
	ListNode* tmp;
	tmp = node->next;             // n2
	node->next = tmp->next;       // n1->next = n3
	tmp->next = tmp->next->next;  // n2->next = n4
	node->next->next = tmp;       // n3->next = n2
}

void Price::show_by_price_descending() {
	if (first == NULL) {
		cout << "Price is empty" << endl;
		return;
	}
	if (first->next == NULL) {
		cout << first->product.to_string() << endl;
		return;
	}
	bool is_ordered;
	do {
		is_ordered = true;
		ListNode* node = first;
		// окремо перевіряємо перші два
		if (node->product.price < node->next->product.price) {
			_swap12();
			node = first;
			is_ordered = false;
		}
		while (node->next->next) {
			if (node->next->product.price < node->next->next->product.price) {
				_swap23(node);
				is_ordered = false;
			}
			node = node->next;
		}
	} while (!is_ordered);
	// відображення передаємо на інший метод
	show();
}

void Price::show_by_price_ascending() {
	// сортування - переставляння неправильно впорядкованих елементів
	// до тих пір, поки їх не стане (всі у правильному порядку)
	/* Перестановка у переліку :
	* [p1|n]->[p2|n]->[p3|n]->[p4|n]   поміняти місцями p2 i p3
	* а) поміняти значення Р в двох вузлах (через проміжну змінну)
	*    [p1|n]->[p3|n]->[p2|n]
	*   ! через те, що структури великі, це тягне за собою багато операцій
	* б) поміняти покажчики на вузли
	*    [p1|n]---------->[p3|n]   - більш ефективна операція
			 p4<-[p2|n]<------|

		Для перших двох елементів:
		f
		[p1|n]->[p2|n]->[p3|n]

		 ---->f
			  [p2|n]
		 <--------|
		[p1|n]--------->[p3|n]
	*/
	// окремо обробляємо випадки, коли перелік порожній або в ньому один елемент
	if (first == NULL) {
		cout << "Price is empty" << endl;
		return;
	}
	if (first->next == NULL) {
		cout << first->product.to_string() << endl;
		return;
	}
	bool is_ordered;
	do {
		is_ordered = true;
		ListNode* node = first;
		// окремо перевіряємо перші два
		if (node->product.price > node->next->product.price) {
			_swap12();
			node = first;
			is_ordered = false;
		}
		while (node->next->next) {
			if (node->next->product.price > node->next->next->product.price) {
				_swap23(node);
				is_ordered = false;
			}
			node = node->next;
		}
	} while (!is_ordered);
	// відображення передаємо на інший метод
	show();
}

void Price::show_by_popularity_descending() {
	// сортування - переставляння неправильно впорядкованих елементів
	// до тих пір, поки їх не стане (всі у правильному порядку)
	/* Перестановка у переліку :
	* [p1|n]->[p2|n]->[p3|n]->[p4|n]   поміняти місцями p2 i p3
	* а) поміняти значення Р в двох вузлах (через проміжну змінну)
	*    [p1|n]->[p3|n]->[p2|n]
	*   ! через те, що структури великі, це тягне за собою багато операцій
	* б) поміняти покажчики на вузли
	*    [p1|n]---------->[p3|n]   - більш ефективна операція
			 p4<-[p2|n]<------|

		Для перших двох елементів:
		f
		[p1|n]->[p2|n]->[p3|n]

		 ---->f
			  [p2|n]
		 <--------|
		[p1|n]--------->[p3|n]
	*/
	// окремо обробляємо випадки, коли перелік порожній або в ньому один елемент
	if (first == NULL) {
		cout << "Order is empty" << endl;
		return;
	}
	if (first->next == NULL) {
		cout << first->product.to_string() << endl;
		return;
	}
	bool is_ordered;
	do {
		is_ordered = true;
		ListNode* node = first;
		// окремо перевіряємо перші два
		if (node->product.order > node->next->product.order) {
			_swap12();
			node = first;
			is_ordered = false;
		}
		while (node->next->next) {
			if (node->next->product.order > node->next->next->product.order) {
				_swap23(node);
				is_ordered = false;
			}
			node = node->next;
		}
	} while (!is_ordered);
	// відображення передаємо на інший метод
	show();
}

void Price::show_by_popularity_ascending() {
	// сортування - переставляння неправильно впорядкованих елементів
	// до тих пір, поки їх не стане (всі у правильному порядку)
	/* Перестановка у переліку :
	* [p1|n]->[p2|n]->[p3|n]->[p4|n]   поміняти місцями p2 i p3
	* а) поміняти значення Р в двох вузлах (через проміжну змінну)
	*    [p1|n]->[p3|n]->[p2|n]
	*   ! через те, що структури великі, це тягне за собою багато операцій
	* б) поміняти покажчики на вузли
	*    [p1|n]---------->[p3|n]   - більш ефективна операція
			 p4<-[p2|n]<------|

		Для перших двох елементів:
		f
		[p1|n]->[p2|n]->[p3|n]

		 ---->f
			  [p2|n]
		 <--------|
		[p1|n]--------->[p3|n]
	*/
	// окремо обробляємо випадки, коли перелік порожній або в ньому один елемент
	if (first == NULL) {
		cout << "Order is empty" << endl;
		return;
	}
	if (first->next == NULL) {
		cout << first->product.to_string() << endl;
		return;
	}
	bool is_ordered;
	do {
		is_ordered = true;
		ListNode* node = first;
		// окремо перевіряємо перші два
		if (node->product.order < node->next->product.order) {
			_swap12();
			node = first;
			is_ordered = false;
		}
		while (node->next->next) {
			if (node->next->product.order < node->next->next->product.order) {
				_swap23(node);
				is_ordered = false;
			}
			node = node->next;
		}
	} while (!is_ordered);
	// відображення передаємо на інший метод
	show();
}


/*
Опис методів:
!!!show_by_price_descending() - від дорогих цін до дешевих!!!

1.Перевірка (first==NULL) - виводимо, що список порожній
			(first->next == NULL) - виводимо єдиний елемент
2.Сортування (В циклі, допоки покажчик is_ordered == false)
    1)Створюємо прапорець is_ordered для перевірки повного сортування і ставимо його на true
	  Встановлюємо покажчик node на перший елемент списку
	2)Перевіряємо чи ціна першого елементу (node->product.price) < другого (node->next->product.price). 
	  Якщо так, то змінюємо ці 2 елементи місцями за таким алгоритмом:
	  f
	  [p1|n]->[p2|n]->[p3|n]

	     ---->f
		     [p2|n]
	  <--------|
	  [p1|n]--------->[p3|n]
	  - повертаємо node на first ("новий" початок)
	  - ставимо прапорець is_ordered на false
	3)Поки існує node->next->next
	  Якщо node->next->product.price < node->next->next->product.price:
	  -Змінюємо ці 2 елементи місцями:
	  p1 = node
	  [p1|n]->[p2|n]->[p3|n]->[p4|n]
	  [p1|n]--------->[p3|n]
			[p4|n] <- [p2|n] <-----|
	  - ставимо прапорець is_ordered на false
	  переходимо до наступного вузла (node = node->next;)
3.Виводимо результат методом show() після завершення циклу (is_ordered == true)
	  
!!!show_by_discount_percent_ascending() - від малих знижок до великих!!!

1.Перевірка (first==NULL) - виводимо, що список порожній
			(first->next == NULL) - виводимо єдиний елемент
2.Сортування (В циклі, допоки покажчик is_ordered == false)
	1)Створюємо прапорець is_ordered для перевірки повного сортування і ставимо його на true
	  Встановлюємо покажчик node на перший елемент списку
	2)Перевіряємо чи знижка першого елементу (node->product.discount_percent) > другого (node->next->product.discount_percent).
	  Якщо так, то змінюємо ці 2 елементи місцями за таким алгоритмом:
	  f
	  [p1|n]->[p2|n]->[p3|n]

		 ---->f
			 [p2|n]
	  <--------|
	  [p1|n]--------->[p3|n]
	  - повертаємо node на first ("новий" початок)
	  - ставимо прапорець is_ordered на false
	3)Поки існує node->next->next
	  Якщо node->next->product.discount_percent > node->next->next->product.discount_percent:
	  -Змінюємо ці 2 елементи місцями:
	  p1 = node
	  [p1|n]->[p2|n]->[p3|n]->[p4|n]
	  [p1|n]--------->[p3|n]
			[p4|n] <- [p2|n] <-----|
	  - ставимо прапорець is_ordered на false
	  переходимо до наступного вузла (node = node->next;)
3.Виводимо результат методом show() після завершення циклу (is_ordered == true)

!!!show_by_discount_percent_descending() - від великих знижок до малих!!!

1.Перевірка (first==NULL) - виводимо, що список порожній
			(first->next == NULL) - виводимо єдиний елемент
2.Сортування (В циклі, допоки покажчик is_ordered == false)
	1)Створюємо прапорець is_ordered для перевірки повного сортування і ставимо його на true
	  Встановлюємо покажчик node на перший елемент списку
	2)Перевіряємо чи знижка першого елементу (node->product.discount_percent) < другого (node->next->product.discount_percent).
	  Якщо так, то змінюємо ці 2 елементи місцями за таким алгоритмом:
	  f
	  [p1|n]->[p2|n]->[p3|n]

		 ---->f
			 [p2|n]
	  <--------|
	  [p1|n]--------->[p3|n]
	  - повертаємо node на first ("новий" початок)
	  - ставимо прапорець is_ordered на false
	3)Поки існує node->next->next
	  Якщо node->next->product.discount_percent < node->next->next->product.discount_percent:
	  -Змінюємо ці 2 елементи місцями:
	  p1 = node
	  [p1|n]->[p2|n]->[p3|n]->[p4|n]
	  [p1|n]--------->[p3|n]
			[p4|n] <- [p2|n] <-----|
	  - ставимо прапорець is_ordered на false
	  переходимо до наступного вузла (node = node->next;)
3.Виводимо результат методом show() після завершення циклу (is_ordered == true)

*/
/*
Задача: реалізувати методи сортування та виведення
за величиною знижки (discount)

Д.З. До структури Product додати поле order, яке
заповнювати послідовно при зчитуванні файлу.
Розуміючи це поле як "популярність" товару додати
пункт меню "за популярністю" (можна змінити п.3).

Підготувати до захисту персональні проєкти
*/