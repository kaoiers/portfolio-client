
#include <stdafx.h>
#include "cGodOption.h"

CGodOption * CGodOption::GetInstance()
{
	static	CGodOption Instance;

	return &Instance;
}
