#include "entry.h"
#include <string>
#include <vector>

namespace te {

	struct ZygoteFile : Entry {

		ZygoteFile(const std::string& name); 
		~ZygoteFile() override;


		Entry* edit() override;
	};
}