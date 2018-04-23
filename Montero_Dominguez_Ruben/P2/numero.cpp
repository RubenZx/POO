#include "numero.hpp"


Numero::Numero(const Cadena& cad)
{
	Cadena cadaux = cad;

	eliminar_espacios_blancos(cadaux);
	
	if(!comprobar_longitud(cadaux))
		throw Incorrecto(LONGITUD);
	if(!comprobar_digitos(cadaux))
		throw Incorrecto(DIGITOS);
	if(!luhn(cadaux))
		throw Incorrecto(NO_VALIDO);

	num_ = cadaux;
}

void Numero::eliminar_espacios_blancos(Cadena& cad)
{
	Cadena cadaux;
	size_t i = 0;

	while(i < cad.length())
	{
		if(cad[i] != ' ')
			cadaux[i] = cad[i];
		i++;
	}
	cad = cadaux;
}

bool Numero::comprobar_digitos(const Cadena& cad)
{	
	bool comprobar = true;
	size_t i = 0;
	size_t longitud = cad.length();

	while(i < longitud && comprobar)
	{
		if(!isdigit(cad[i]))
			comprobar = false;
		i++;
	}

	return comprobar;
}

bool Numero::comprobar_longitud(const Cadena& cad)
{
	return(cad.length() >= 13 && cad.length <= 19);
}

bool operator<(const Numero& n1, const Numero& n2)
{
	return(n1.num_ < n2.num_);
}