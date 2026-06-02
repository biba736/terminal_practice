#include "multi_line_file.h"
#include "entry.h"
#include <iostream>
#include <vector>
#include <limits>

namespace te {

	MultiLineFile::MultiLineFile(const std::string& name) : Entry(name) {
		std::cout << "File '" << name << "' successfully created.\n";
	}

	MultiLineFile::~MultiLineFile() {
		std::cout << "File '" << entry_name << "' successfully deleted.\n";
	}

	void MultiLineFile::display() const {

		if (lines.empty()) {
			std::cout << "File is empty\n";
			return;
		}

		for (size_t i = 0; i < lines.size(); ++i) {
			std::cout << i + 1 << ": " << lines[i] << "\n";
		}
	}

	void MultiLineFile::edit_line(int id, const std::string& text) {
		if (id >= 0 && static_cast<size_t>(id) < lines.size()) { 
			lines[id] = text;
		}
		else {
			std::cout << "Error: string index " << id << " out of range.\n";
		}
	}

	void MultiLineFile::add_line(const std::string& text) {
		lines.push_back(text); //добавляем строку в конец вектора
	}

	Entry* MultiLineFile::edit() {

		display();
		std::cout << "Enter the line number you want to change (0 to add a new line, -1 to end): ";

		int id;

		while (std::cin >> id) {
			if (id == -1) {
				break;
			}

			else if (id == 0) {
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //Очищаем буфер
				std::cout << "Enter a new line text: ";
				std::string new_text;
				std::getline(std::cin, new_text);
				add_line(new_text);
			}

			else if (id >= 1 && static_cast<size_t>(id) <= lines.size()) {
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очищаем буфер
				std::cout << "Chosen string: " << lines[id - 1] << "\n";
				std::cout << "Enter edited string:";
				std::string new_text;
				std::getline(std::cin, new_text);
				edit_line(id - 1, new_text);
			}

			else {
				std::cout << "String number " << id << " not found.\n";
			}

			display();
			std::cout << "Enter the line number you want to change (0 to add a new line, -1 to end): ";
		}

		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		return this;
	}
	
} 

