#include "articulo.hpp"

//	Operador de insercción de flujo de salida.
std::ostream& operator <<(std::ostream& os, const Articulo& art)
{
	os << "[" << art.referencia() << "] \"" << art.titulo() << "\", " << art.f_publi().anno() << ". " << art.precio() << " €\n";
	return os;
}