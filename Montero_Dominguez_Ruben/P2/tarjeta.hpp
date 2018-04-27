#ifndef TARJETA_HPP_
#define TARJETA_HPP_

#include <cctype>
#include <iostream>
#include <algorithm>
#include <iomanip>

#include "cadena.hpp"
#include "fecha.hpp"
#include "usuario.hpp"

class Usuario;

/***************************************************** CLASE NUMERO *****************************************************/

class Numero
{
public:
	enum Razon{LONGITUD, DIGITOS, NO_VALIDO};
	
	Numero(Cadena cad);
	operator const char*()const{return num_.c_str();};

	class Incorrecto
	{
		Razon fallo_;
	public:
		Incorrecto(Razon r): fallo_{r}{};
		Razon razon() const{return fallo_;};	
	};

	friend bool operator<(const Numero& n1, const Numero& n2); 

private:
	Cadena num_;
};

bool operator<(const Numero& n1, const Numero& n2); 

/***************************************************** CLASE TARJETA *****************************************************/

class Tarjeta
{
public:
	enum Tipo{VISA, Mastercard, Maestro, JCB, AmericanExpress};
	
	// Constructor, y eliminación de la asignación y la copia.
	Tarjeta(Tipo t, const Numero& num, Usuario& user, const Fecha& fech);
	Tarjeta(const Tarjeta& user) = delete;
	Tarjeta operator=(const Tarjeta& user) = delete;

	// Métodos observadores.
	Tipo tipo() const{return tipo_;};
	Numero numero() const{return num_;};
	Fecha caducidad() const{return caducidad_;};
	Cadena titular_facial() const{return titular_;};
	const Usuario* titular() const{return user_;};

	void anula_titular(){user_ = nullptr;};

	// Destructor
	~Tarjeta();

	class Caducada
	{
	public:
		Caducada(const Fecha& f):caducada_{f}{};
		Fecha cuando()const{return caducada_;};

	private:
		Fecha caducada_;
	};

private:
	Tipo tipo_;
	Numero num_; 	
	const Usuario* user_;
	Fecha caducidad_;
	Cadena titular_;
};

std::ostream& operator <<(std::ostream& os, const Tarjeta::Tipo& tipo);
std::ostream& operator <<(std::ostream& os, const Tarjeta& tarj);

bool operator<(const Tarjeta& t1, const Tarjeta& t2);

#endif	// TARJETA_HPP_