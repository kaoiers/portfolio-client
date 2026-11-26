
#include <stdafx.h>
#include "cGodOption.h"

CGodOption * CGodOption::getInstance()
{
	static	CGodOption instance;

	return &instance;
}
