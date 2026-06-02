#ifndef DIRECTORY_H
#define DIRECTORY_H

#include "entry.h"
#include <vector>
#include <string>

namespace te {

	struct Directory : Entry {
		std::vector<Entry*> entries; //Вектор указателей на дочерние элементы

		Directory(const std::string& name);
		~Directory() override;

		void hide() override;
		void restore() override;
		std::string displayName() const override;
		std::vector <Entry*> list() override;
		Directory* asDirectory() override;

		void addEntry(Entry* entry);
		void replaceEntry(Entry* old, Entry* replacement);
		Entry* find(const std::string& n) const;
		bool hideEntry(const std::string& n);
		bool restoreEntry(const std::string& n);
	};
}

#endif