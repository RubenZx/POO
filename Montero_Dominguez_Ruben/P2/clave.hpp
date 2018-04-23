#ifndef CLAVE_HPP_
#define CLAVE_HPP_

#include <iostream>
#include "cadena.hpp"

class Clave
{
public:
	
	enum Razon{CORTA, ERROR_CRYPT};
	
	Clave(const char* key);
	Cadena clave() const;
	bool verifica(const char*);

	class Incorrecta
	{
	public:
		Incorrecta(const Razon r):fallo_{r}{};
		Razon razon() const;
	private:
		Razon fallo_;
	};

private:

	Cadena passwd_;
};

inline Cadena Clave::clave() const{return passwd_;}
inline Razon Clave::Incorrecta::razon() const{return fallo_;}

#endif	// CLAVE_HPP_