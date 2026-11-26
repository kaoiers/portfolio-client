
#include <stdafx.h>
#include "CGodOption.h"

CGodOption * CGodOption::getInstance()
{
	static	CGodOption instance;

	return &instance;
}
