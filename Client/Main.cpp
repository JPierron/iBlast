#include <iostream>
#include "Client.h"

int		main ()
{
	Client	_Network("10.12.180.73", 3400);

	_Network.RunIBlast();

	return 0;
}
