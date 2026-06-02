#include "entry.h"
#include <string>
#include <vector>

namespace te {

	struct SingleLineFile : Entry {
		std::string content;

		SingleLineFile(const std::string& name, const std::string& text);
		~SingleLineFile() override;

		void display() const override;
		Entry* edit() override;

		void setContent(const std::string& new_content);
	};
}