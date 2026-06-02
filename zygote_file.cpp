#include "entry.h"
#include "zygote_file.h"
#include "single_line_file.h"
#include "multi_line_file.h"
#include <limits>
#include <iostream>

namespace te {

	ZygoteFile::ZygoteFile(const std::string& name) : Entry(name) {}
	ZygoteFile::~ZygoteFile() {}

	Entry* ZygoteFile::edit() {

		std::cout << "Choose the desired file type (s for single-line file, m for multi-line file): ";
		std::string text_type;

		std::getline(std::cin, text_type);

		if (text_type == "s") {
			std::string text;
			std::cout << "Enter the contents of the line: ";
			std::getline(std::cin, text);
			if (text.empty()) {
				return this;
			}
			else {
				return new SingleLineFile(entry_name, text);
			}
		}

		

		else if (text_type == "m") {
			std::vector <std::string> lines;
			std::string line;
			std::cout << "Enter the file lines (an empty line to end): \n";
			while (std::getline(std::cin, line) && !line.empty()) {
				lines.push_back(line);
			}

			if (lines.empty()) {
				return this;
			}

			MultiLineFile* newFile = new MultiLineFile(entry_name);
			for (const auto& l : lines) {
				newFile->add_line(l);
			}
			return newFile;
			
		}

		std::cout << "Unknown type, file is empty.\n";
		return this;
	}
}
