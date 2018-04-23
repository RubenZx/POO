#ifndef NUMERO_HPP_
#define NUMERO_HPP_

#include <iostream>
#include "cadena.hpp"

bool luhn(const Cadena& numero);

class Numero
{
public:

	enum Razon{LONGITUD, DIGITOS, NO_VALIDO};
	Numero(const Cadena& cad);
	operator const char*()const{return num_.c_str();};

	class Incorrecto
	{
	public:
		Razon(Razon r): fallo_{r}{};
		Razon razon() const{return fallo_;};
	private:
		Razon fallo_;
	};

	friend bool operator<(const Numero& n1, const Numero& n2); 

private:
	void eliminar_espacios_blancos(Cadena& cad);
	bool comprobar_digitos(const Cadena& cad);
	bool comprobar_longitud(const Cadena& cad);
	Cadena num_;
};

bool operator<(const Numero& n1, const Numero& n2); 

#endif 	//NUMERO_HPP_