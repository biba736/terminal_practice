#ifndef ENTRY_H
#define ENTRY_H

#include <vector>
#include <string>

namespace te {

//Предварительно объявим директорию
struct Directory;

//Структура Entry
struct Entry {
	std::string entry_name;

	//Конструктор и деструктор
	Entry(const std::string& name) : entry_name(name) {}
	virtual ~Entry() {}

	//Проверка на скрытость 
	bool is_hidden() const {
		return (!entry_name.empty() && entry_name[0] == '.');
	}

	std::string getName() const{
		return entry_name;
	}

	//Виртуальные функции (могут быть переопределены в наследниках)
	virtual std::string displayName() const { 
		return entry_name; 
	}

	virtual void rename(const std::string n) {
		entry_name = n;
	}

	virtual void hide() {
		if (!is_hidden()) {
			entry_name = "." + entry_name;
		}
	}

	virtual void restore() {
		if (is_hidden()) {
			entry_name = entry_name.substr(1);
		}
	}

	virtual void display() const{}
	
	virtual Directory* asDirectory() {
		return (nullptr);
	}

	virtual Entry* edit() {
		return this;
	}

	virtual std::vector<Entry*> list() {
		return {};
	}

};

}

#endif