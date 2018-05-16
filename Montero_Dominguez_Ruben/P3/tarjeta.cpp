#include "tarjeta.hpp"

/***************************************************** MÉTODOS DE LA CLASE NUMERO *****************************************************/

bool luhn(const Cadena& numero);

Numero::Numero(Cadena cad)
{
  	if(cad.length() == 0)
  		throw Incorrecto(Razon::LONGITUD);

  	// Eliminar espacios en blanco.
  	cad = cad.substr(0, std::remove_if(cad.begin(), cad.end(), EsBlanco()) - cad.begin());

  	// Comprobar digitos.
  	if(std::find_if(cad.begin(), cad.end(), not1(EsDigito())) != cad.end())
  		throw Incorrecto(Razon::DIGITOS);

  	if(cad.length()< 13 || cad.length() > 19)
  		throw Incorrecto(Razon::LONGITUD);
  	if(!luhn(cad))
  		throw Incorrecto(Razon::NO_VALIDO);

  	num_ = cad;

}

/*
CODIGO DE LUIS
Cadena Numero::quitarEspacios(const Cadena& cad)
{
	Cadena aux(cad);
	std::remove_if(aux.begin(),aux.end()+1,[](unsigned char x){return std::isspace(x);});
	return Cadena(aux.c_str());
}


Numero::Numero(const Cadena& num)
{

	if(num.length() == 0)
		throw Incorrecto(Razon::LONGITUD);

	Cadena aux = quitarEspacios(num);

	//if(find_if(aux.begin(), aux.end(), not1(EsDigito)) != aux.end()) 
	if( count_if(aux.begin(), aux.end(), static_cast<int(*)(int)>(isdigit)) != aux.length())
		throw Incorrecto(Razon::DIGITOS);

	if(aux.length() < 13 || aux.length() > 19)  		  //comprobar la longuitud
		throw Incorrecto(Razon::LONGITUD);

	if(!luhn(aux))						  //comprovar la validez
		throw Incorrecto(Razon::NO_VALIDO);

	num_ = aux;
}
*/

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
