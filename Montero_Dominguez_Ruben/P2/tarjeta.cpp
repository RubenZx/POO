#include "tarjeta.hpp"

/***************************************************** MÉTODOS DE LA CLASE NUMERO *****************************************************/

bool luhn(const Cadena& numero);

Numero::Numero(Cadena cad)
{
  	if(cad.length() == 0) 
  		throw Incorrecto(Razon::LONGITUD);
	
	eliminar_espacios(cad);
	comprobar_digitos(cad);

  	if(cad.length()< 13 || cad.length() > 19) 
  		throw Incorrecto(Razon::LONGITUD);
  	if(!luhn(cad))
  		throw Incorrecto(Razon::NO_VALIDO);
  
  num_ = cad;
}

void Numero::eliminar_espacios(Cadena& cad)
{
	Cadena cadaux(cad.length());

	Cadena::iterator i = cad.begin();
  	size_t j = 0;
  	while(i != cad.end())
  	{
  		if(!isspace(*i))
  			cadaux[j++] = *i;
  		i++;
  	}
  	cad = cadaux.substr(0, j);
}
void Numero::comprobar_digitos(const Cadena& cad)
{
	Cadena::const_iterator i = cad.begin();
  	while(i != cad.end())
  	{
  		if(!isdigit(*i))
  			throw Incorrecto(Razon::DIGITOS);
  		i++;
  	}
}

bool operator<(const Numero& n1, const Numero& n2)
{
	return(n1.num_ < n2.num_);
}

/***************************************************** MÉTODOS DE LA CLASE TARJETA *****************************************************/

Tarjeta::Tarjeta(Tipo t, const Numero& num, Usuario& user, const Fecha& fech):
	tipo_{t},
	num_{num},
	user_{&user},
	caducidad_{fech},
	titular_{user.nombre()+" "+user.apellidos()}
	{
		if(fech < Fecha()) 
			throw Caducada(fech);
		else 
			user.es_titular_de(*this);
	}

std::ostream& operator <<(std::ostream& os, const Tarjeta::Tipo& tipo)
{
	switch(tipo)
	{
		case Tarjeta::Tipo::VISA: os << "VISA"; break;
		case Tarjeta::Tipo::Mastercard: os << "Mastercard"; break;
		case Tarjeta::Tipo::Maestro: os << "Maestro"; break;
		case Tarjeta::Tipo::JCB: os << "JCB"; break;
		case Tarjeta::Tipo::AmericanExpress: os << "AmericanExpress"; break;
	};

	return os;
}

std::ostream& operator <<(std::ostream& os,const Tarjeta& tarj)
{
 	os << tarj.tipo() << std::endl;
  	os << tarj.numero() << std::endl;
  	os << tarj.titular_facial() << std::endl;
  	os << "Caduca: " << std::setfill('0') << std::setw(2) << tarj.caducidad().mes()
       << '/' << std::setw(2) << (tarj.caducidad().anno() % 100);
  	
  	return os;
}

Tarjeta::~Tarjeta()
{	
	if(Usuario* us = const_cast<Usuario*>(user_))
		us->no_es_titular_de(*this);
}

bool operator<(const Tarjeta& t1, const Tarjeta& t2)
{
	return(t1.numero() < t2.numero());
}