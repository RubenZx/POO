#include <iomanip>
#include "articulo.hpp"

//	Operador de insercción de flujo de salida.
std::ostream& operator <<(std::ostream& os, const Articulo& art)
{
	auto it = art.autores().begin();
	os << "[" << art.referencia() << "] \"" << art.titulo() << "\", de ";
	
	os << (*it)->apellidos();

	for(++it; it != art.autores().end(); it++)
	{
		os << ", " << (*it)->apellidos();
	}

	os << ". "; 	

	os << art.f_publi().anno() << ". " << std::fixed << std::setprecision(2) << art.precio() << " €\n\t";
	art.impresion_especifica(os);

	return os;
}
