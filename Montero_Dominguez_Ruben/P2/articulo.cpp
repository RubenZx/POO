#include "articulo.hpp"

/*
El operador de inserción en un flujo de salida << imprimirá referencia, título, año de
publicación y precio con el formato que se muestra en el ejemplo:
[110] "Fundamentos de C++", 1998. 29,95 €
*/

std::ostream& operator <<(std::ostream& os, const Articulo& art)
{
	os << "[" << art.referencia() << "] \"" << art.titulo() << "\", " << art.f_publi().anno() << ". " << art.precio() << " €\n";
	return os;
}