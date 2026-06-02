#include "single_line_file.h"
#include "entry.h"
#include <iostream>
#include <limits>

namespace te {

	//Конструктор
	//Вызываем констуктор базового класса Entry, инициализируем entry_name - name, поле content текстом
	SingleLineFile::SingleLineFile(const std::string& name, const std::string& text) : Entry(name), content(text) {
		std::cout << "File '" << name << "' successfully created.\n";
	}

	//Деструктор 
	//Вызываем деструктор 
	SingleLineFile::~SingleLineFile() {
		std::cout << "File '" << entry_name << "' successfully deleted.\n";
	}

	//Выведем контент из файла
	void SingleLineFile::display() const {
		std::cout << content << "\n";
	}

	//Изменим содержимое файла
	Entry* SingleLineFile::edit() {
		std::cout << "Old content: " << content << "\n";
		std::cout << "New content:\n";

		std::string NewContent;
		std::getline(std::cin, NewContent);
		setContent(NewContent);
		return this; //Тип не изменился
	}

	//Установить новое содержимое
	void SingleLineFile::setContent(const std::string& new_content) {
		content = new_content;
	}
}