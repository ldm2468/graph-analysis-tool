#include "stat.h"

namespace snu {
	
	void init_stat(DSResult *result) {
		result->basicstat = result->countstat = false;
	}

	void init_stat(USResult *result) {
		result->basicstat = result->countstat = false;
	}
}