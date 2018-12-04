#include "stat.h"

namespace snu {
	
	void init_stat(DSResult *result) {
		result->basicstat = false;
		result->connectstat = false;
	}

	void init_stat(USResult *result) {
		result->basicstat = false;
		result->connectstat = false;
		result->countstat = false;
	}
}