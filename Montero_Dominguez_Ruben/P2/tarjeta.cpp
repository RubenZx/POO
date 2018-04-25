#include "tarjeta.hpp"

using namespace std;

/***************************************************** MÉTODOS DE LA CLASE NUMERO *****************************************************/

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
	return(cad.length() >= 13 && cad.length() <= 19);
}

bool operator<(const Numero& n1, const Numero& n2)
{
	return(n1.num_ < n2.num_);
}

/***************************************************** MÉTODOS DE LA CLASE TARJETA *****************************************************/

/*
Cadena Tarjeta::pasar_mayus(const Usuario& user)
{
	Cadena cadaux;
	int i = 0, j = 0;
	while(i < user.nombre().length() + user.apellidos().length() + 1)
	{
		if(i < user.nombre().length())
			cadaux += static_cast<char>(toupper(user.nombre()[i]));
		else
			if(i == user.nombre().length())
				cadaux += " ";
			else
			{	
				cadaux += static_cast<char>(toupper(user.apellidos()[j]));
				j++;
			}
		i++;
	}
	return cadaux;		
}*/

Tarjeta::Tarjeta(Tipo t, const Numero& num, Usuario& user, const Fecha& fech):
	tipo_{t},
	num_{num},
	user_{nullptr},
	caducidad_{fech},
	titular_{user.nombre()+" "+user.apellidos()}
	{
		if(fech < Fecha())
			throw Caducada(fech);
		else 
			user_->es_titular_de(*this);
	}

std::ostream& operator <<(std::ostream& os, const Tipo& tipo)
{
	switch(const_cast<Tarjeta::Tipo>(tipo))
	{
		case 0: os << "VISA"; break;
		case 1: os << "Mastercard"; break;
		case 2: os << "Maestro"; break;
		case 3: os << "JCB"; break;
		case 4: os << "AmericanExpress"; break;
	};

	return os;
}

std::ostream& operator <<(std::ostream& os, const Tarjeta& tarj)
{
	os 	<< tarj.tipo() << "\n" 
		<< tarj.numero() << "\n"
		<< tarj.titular_facial() << "\n"
		<< "Caduca: " << tarj.caducidad().mes() << "/" << tarj.caducidad().anno() % 100 << endl;

	return os;
}


bool operator<(const Tarjeta& t1, const Tarjeta& t2)
{
	return(t1.numero() < t2.numero());
}