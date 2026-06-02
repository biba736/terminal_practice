#include "entry.h"
#include <string>
#include <vector>

namespace te {

	struct MultiLineFile : Entry {

		//Массив строк
		std::vector <std::string> lines;

		//Конструктор и деструктор
		MultiLineFile(const std::string& name);
		~MultiLineFile() override;

		//Вывести все строки с номерами
		void display() const override;
		//Изменить содержимое 
		Entry* edit() override;

		//Изменение строки по индексу
		void edit_line(int id, const std::string& text);
		//Добавление строки
		void add_line(const std::string& text);

	};
}
