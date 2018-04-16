#include "fecha.hpp"

int main()
{
	
	Fecha F2{"25/12/1999"};
	Fecha hoy{0};

	hoy++;

	std::cout << "FECHA: " << hoy.dia() << "/" << hoy.mes() << "/" << hoy.anno() << std::endl;

	return 0;
}