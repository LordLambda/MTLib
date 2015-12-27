#include "../Common.h"
#include "AtomicBoolean.hpp"

namespace MTLib {
	bool AtomicBoolean::SetVal(bool val) {
		unsigned long oldval = 0;

		if (val)
			oldval = Value.SetVal(1);
		else
			oldval = Value.SetVal(0);

		return (oldval & 1);
	}
}
