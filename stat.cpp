#include "stat.h"

namespace snu {
	
	void initStat(DSResult& result) {
		result.basicstat = false;
		result.connectstat = false;
	}

	void initStat(USResult& result) {
		result.basicstat = false;
		result.connectstat = false;
		result.countstat = false;
	}

	void initStat(StatResult& result) {
		result.basicstat = false;
		result.connectstat = false;
		result.countstat = false;
	}
}
