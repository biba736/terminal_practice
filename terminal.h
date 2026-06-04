#ifndef TERMINAL_H
#define TERMINAL_H

#include "directory.h"
#include "entry.h"
#include <vector>
#include <string>

namespace te {

struct Terminal {

	Directory* root; //Корневая директория

	//Список директорий текущего пути к рабочему каталогу
	std::vector<Directory*> path; 

	Terminal(Directory* root); 

	//Возвращаем текущую рабочую директорию
	Directory* cwd() const; 
	//Функция генерации промпта (приглашение командной строки)
	std::string prompt() const; 
	void run(); //Цикл обработки команд

};
}

#endif
