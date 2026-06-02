#include "terminal.h"
#include "directory.h"
#include "zygote_file.h"
#include "entry.h"
#include <vector>
#include <string>
#include <iostream>
#include <sstream>

namespace te {

//Конструктор, инициализируем root переданным значением, добавляем наш корень в вектор пути (при запуске терминала мы находимся в корневой директории)
Terminal::Terminal(Directory* rootDirectory) : root(rootDirectory) {
	path.push_back(root);
}

//Возвращаем текущую рабочую директорию
Directory* Terminal::cwd() const {
	return path.back();
}

//Генератор приглашения командной строки
std::string Terminal::prompt() const {
	std::string full_path;

	//Проходим по всему пути, узнаем имена директорий и возвращаем результат
	for (size_t i = 0; i < path.size(); ++i) {
		full_path += "/" + path[i]->getName();
	}
	return full_path;
}

//Цикл обработки команд
void Terminal::run() {
	std::string input; //Переменная для хранения введенной строки
	std::cout << "\nText Editor Terminal. Type 'help' for commands name.\n";
	while (true) {
		std::cout << prompt();

		//На случай EOF
		if (!std::getline(std::cin, input)) {
			std::cout << "\nAll the best!";
			break;
		}

		//Пропускаем пустю строку
		if (input.empty()) {
			continue;
		}

		std::istringstream iss(input); //Разибраем строку как поток
		std::string cmd;
		iss >> cmd; //Читаем первое слово

		//Обработка команд 

		if (cmd == "exit") {
			std::cout << "\nAll the best!";
			break;
		}

		else if (cmd == "help") {
			std::cout << "  ls                 - show the content of the current directory\n"
				<< "  cd <name|..>       - change a directory\n"
				<< "  cat <name>         - show a file content\n"
				<< "  touch <name>       - create a new file in the current directory\n"
				<< "  mkdir <name>       - create a new directory\n"
				<< "  rm <name>          - delete (hide) a file or directory\n"
				<< "  restore <name>     - restore the earlier hidden entity\n"
				<< "  mv <old> <new>     - rename a file or directory\n"
				<< "  edit <name>        - change the file content\n"
				<< "  exit               - exit\n";
		}

		//Показ содержимого текущей директории
		else if (cmd == "ls") {
			for (Entry* entry : cwd()->list()) {
				std::cout << "  " << entry->displayName();
			}
			std::cout << "\n";
		}

		//Сменить директорию
		else if (cmd == "cd") {
			//Читаем имя директории 
			std::string dir_name;
			iss >> dir_name;


			//Нет имени директории
			if (dir_name.empty()) {
				std::cout << "Enter the command in the format cd <name|..>.\n";
				continue;
			}

			//Поднимаемся к корню
			else if (dir_name == "..") {
				if (path.size() > 1) {
					path.pop_back();
				}
				else {
					std::cout << "This directory is the root directory.\n";
				}
			}

			//Меняем директорию
			else {
				Entry* entry = cwd()->find(dir_name); //Ищем сущность с нужным именем в текущей директории

				if (!entry) {
					std::cout << "Directory: '" << dir_name << "' not found.\n";
				}
				else if (!entry->asDirectory()) {
					std::cout << "'" << dir_name << "' is not a directory.\n";
				}
				else {
					path.push_back(entry->asDirectory());
				}
			}
		}

		//Вывести содержимое файла
		else if (cmd == "cat") {
			std::string file_name;
			iss >> file_name;

			if (file_name.empty()) {
				std::cout << "Enter the command in the format cat <name>.\n";
				continue;
			}

			Entry* entry = cwd()->find(file_name); //Ищем дочернюю сущность с нужным именем в текущей директории

			if (!entry) {
				std::cout << "File '" << file_name << "' not found.\n";
			}

			else if (entry->asDirectory()) {
				std::cout << "You cannot use the cat command to display the contents of a directory.\n";
			}
			else {
				entry->display();
			}
		}

		//Создать файл
		else if (cmd == "touch") {
			std::string file_name;
			iss >> file_name;

			if (file_name.empty()) {
				std::cout << "Enter the command in the format touch <name>.\n";
				continue;
			}

			else if (cwd()->find(file_name)){
				std::cout << "'" << file_name << "' already exists.\n";
			}

			else {
				cwd()->addEntry(new ZygoteFile(file_name));
			}

		}

		//Создать директорию
		else if (cmd == "mkdir") {
			std::string dir_name;
			iss >> dir_name;

			if (dir_name.empty()) {
				std::cout << "Enter the command in the format mkdir <name>.\n";
				continue;
			}

			else if (cwd()->find(dir_name)) {
				std::cout << "'" << dir_name << "' already exists.\n";
			}

			else {
				cwd()->addEntry(new Directory(dir_name));
			}

		}

		//Удаление (сокрытие) файла или директории
		else if (cmd == "rm") {
			std::string name;
			iss >> name;

			Entry* entry = cwd()->find(name);

			if (name.empty()) {
				std::cout << "Enter the command in the format rm <name>.\n";
				continue;
			}

			else if (!cwd()->find(name)) {
				std::cout << "An entity with the name '" << name << "' not found.\n";
			}

			else {
				entry->hide();
				std::cout << "An entity '" << name << "' is hidden.\n";
			}
		}

		//Восстановить сущность
		else if (cmd == "restore") {
			std::string name;
			iss >> name;

			Entry* entry = cwd()->find(name);

			if (name.empty()) {
				std::cout << "Enter the command in the format restore <name>.\n";
				continue;
			}

			else if (!cwd()->find(name)) {
				std::cout << "An entity with the name '" << name << "' not found.\n";
			}

			else {
				entry->restore();
				std::cout << "An entity '" << name << "' restored.\n";
			}
		}

		//Переименовать файл или директорию
		else if (cmd == "mv") {
			std::string old_name, new_name;
			iss >> old_name >> new_name;

			Entry* entry = cwd()->find(old_name);

			if (old_name.empty() || new_name.empty()) {
				std::cout << "Enter the command in the format mv <old> <new>.\n";
				continue;
			}

			else if (!cwd()->find(old_name)) {
				std::cout << "A file or directory named '" << old_name << "' not found.\n";
			}

			else if (cwd()->find(new_name)) {
				std::cout << "A file or directory named '" << new_name << "' already exists.\n";
			}

			else {
				entry->rename(new_name);
			}
		}

		//Изменить содержимое файла
		else if (cmd == "edit") {
			std::string name;
			iss >> name;

			Entry* entry = cwd()->find(name);

			if (name.empty()) {
				std::cout << "Enter the command in the format edit <name>.\n";
				continue;
			}

			else if (entry->asDirectory()) {
				std::cout << "'" << name << "' is a directory.\n";
			}

			else {
				Entry* result = entry->edit();
				if (result != entry){
					cwd()->replaceEntry(entry, result);
					delete entry;
				}
			}
		}

		//Несуществующая команда
		else {
			std::cout << "Unknown command, try again.\n";
		}		
	}
}

}