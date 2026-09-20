#include <format>      // на відміну від стандартних бібліотек, що підключаються <>, 
#include "product.h"  // власні бібліотеки підключаються ""

using namespace std;

// реалізуємо методи структури через доступ "struct::method"
bool Product::load_from_file(ifstream& file) {
	getline(file, name);
	if (name.empty()) {
		return false;
	}
	string line;
	getline(file, line);
	price = stof(line);

	getline(file, line);
	stock = stoi(line);

	getline(file, line);
	discount_percent = stoi(line);

	return true;
}

void Product::save_to_file(ofstream& file) const {
	file << name << "\n"
		<< price << "\n"
		<< stock << "\n"
		<< discount_percent << "\n";
}

string Product::to_string() {
	return name + ", $" + std::format("{:.2f}", price)
		+ " (discount " + std::to_string(discount_percent)
		+ "), available " + std::to_string(stock) + " pcs";
}