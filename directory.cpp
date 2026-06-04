#include "directory.h"
#include "entry.h"
#include <iostream>
#include <vector>

namespace te {

	//Конструктор
	Directory::Directory(const std::string& name) : Entry(name) 
	{
		std::cout << "Directory '" << name << "' created.\n";
	}

	//Деструктор
	Directory::~Directory() {
		std::cout << "Delete directory '" << entry_name 
			<< "'.\n";
		for (auto e : entries) {
			delete e;
		}
	}

	//Скрытие директории и всех ее детей (рекурсивно)
	void Directory::hide() {
		//Проходим по детям, если не скрыты - скрываем
		for (auto* child : entries) {
			if (!child->is_hidden()) {
				child->hide();
			}
		}
		Entry::hide();
	}

	//Восстановление директории и всех ее детей (рекурсивно)
	void Directory::restore() {
		//Восстанавливаем саму директорию
		Entry::restore();

		//Восстанавливаем детей
		for (auto* child : entries) {
			if (child->is_hidden()) {
				child->restore();
			}
		}
	}

	//Отображение имени директории (добавили / в конце)
	std::string Directory::displayName() const {
		return entry_name + "/";
	}

	//Показать список дочерних элементов
	std::vector <Entry*> Directory::list() {
		std::vector<Entry*> result; //вектор для результата

		//Проходим по всем детям и добавляем нескрытые
		for (auto* e : entries) {
			if (!e->is_hidden()) {
				result.push_back(e);
			}
		}
		return result;
	}

	//Проверка на директорийность (для файлов вернет nullptr)
	Directory* Directory::asDirectory() {
		return this;
	}

	//Добавить новый дочерний элемент
	void Directory::addEntry(Entry* entry) {
		entries.push_back(entry);
	}

	//Меняем дочерний элемент
	void Directory::replaceEntry(Entry* old, Entry* replacement) 
	{
		for (size_t i = 0; i < entries.size(); ++i) {
			//Сравниваем указатели и меняем, если нашли
			if (entries[i] == old) {
				entries[i] = replacement;
				return;
			}
		}
	}

	//
	Entry* Directory::find(const std::string& n) const {
		for (auto* e : entries) {
			if (e->getName() == n) {
				return e;
			}

			if (e->is_hidden() && e->getName().substr(1) == n)
			{
				return e;
			}
		}
		return nullptr;
	}

	//Прячем конкретную сущность (рекурсивно)
	bool Directory::hideEntry(const std::string& n) {
		auto* entry = find(n);

		//Не нашли или уже скрыта
		if (!entry || entry->is_hidden()) {
			return false;
		}

		//Скрываем
		entry->hide();
		return true;
	}

	//Раскрываем конкретную сущность
	bool Directory::restoreEntry(const std::string& n) {
		auto* entry = find(n);

		//Не нашли или уже открыта
		if (!entry || !entry->is_hidden()) {
			return false;
		}

		//Раскрываем
		entry->restore();
		return true;
	}

}
