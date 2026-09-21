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
		std::cout << "File open error";
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

	while (product.load_from_file(file)) {
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
	}
	file.close();
	return true;
}

void Price::show() const {
	if (first == NULL) {
		std::cout << "Price is empty" << endl;
		return;
	}
	ListNode* node = first;
	int cnt = 0;
	cout << endl;
	while (node) {
		if (cnt == 2) {
			int choice;
			cout << "> Press a key to continue..."<<endl;
			choice = _getch();
			cnt = 0;
		}
		std::cout << node->product.to_string() << endl;
		node = node->next;
		cnt++;
		
	}
	cout << endl;
}
/*
git - VCS (Version Control System)
система, що дозволяє "зберігати" версії коду з
можливістю повернення до попередніх версій, а також
утворення відгалужень (гілок) з різним розвитком проєкту.
Суть - збереження "різниці" - відмінностей між попереднім
і поточним станом проєкту -коміти (commits).
Це також спрощує сумісну роботу з проєктом різними учасниками.

Github - hub (місце для розміщення) репозиторіїв проєктів.
Репозиторій - частирна проєкту, до якої входить код,
напрацьований розробниками, і не входять загальні ресурси,
які можна довантажити окремо (загальні бібліотеки тощо),
а також результати компіляції та збірки (проміжні та виконавчі
файли).
Відмінність задається спец. файлом ".gitignore"

Для того щоб створити та опублікувати репозиторій необхідно
- ініціалізувати репозиторій Git->Create Git repository
- створити перший коміт
- опублікувати репозиторій (GitHub, Azure DevOps, BitBucket, GitLab...)
= Visual Studio дозволяє поєднати всі ці кроки в меню
	Git->Create Git Repository
*/