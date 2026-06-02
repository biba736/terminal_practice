#ifndef TERMINAL_H
#define TERMINAL_H

#include "directory.h"
#include "entry.h"
#include <vector>
#include <string>

namespace te {

struct Terminal {

	Directory* root; //Корневая директория

	std::vector<Directory*> path; //Список директорий текущего пути к рабочему каталогу

	Terminal(Directory* root); 

	Directory* cwd() const; //Возвращаем текущую рабочую директорию
	std::string prompt() const; //Функция генерации промпта (приглашение командной строки)
	void run(); //Цикл обработки команд

};
}

#endif