#include "usuario.hpp"
#include <random>

/***************************************************** MÉTODOS DE LA CLASE CLAVE *****************************************************/

Clave::Clave(const char* key)
{
	if(std::strlen(key) < 5) throw Incorrecta(CORTA);				// La contraseña ha de tener al menos 5 caracteres, si no, se considerará demasiado corta.
	
  	static const char *const cv = "./0123456789"
  	"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
  	static const size_t longtd = sizeof(cv) - 1;					// "size_t" es el tipo que devuelva "sizeof".

  	static std::random_device r;
  	static std::uniform_int_distribution<size_t> distribucion(0, longtd - 1);		//	"distribución", objeto función.

  	const char salt[] = {cv[distribucion(r)], cv[distribucion(r)]};
  		
  	if(const char *const pcc = crypt(key, salt)) passwd_ = pcc;  		
	else throw Incorrecta(ERROR_CRYPT);
}

bool Clave::verifica(const char* key)
{
	if(const char *const pcc = crypt(key, passwd_.c_str())) 
		return (passwd_ == pcc);
	throw Incorrecta(ERROR_CRYPT);
}

/***************************************************** MÉTODOS DE LA CLASE USUARIO *****************************************************/

//	Constructor de usuario.
Usuario::Usuario(const Cadena& id_user, const Cadena& nombre, const Cadena& apell, const Cadena& dir, const Clave& pass):
	id_{id_user},
	nombre_{nombre},
	apell_{apell},
	dir_{dir},
	passwd_{pass}
	{
		std::pair<unordered_set::iterator, bool> aux;	
		aux = identificadores.insert(id_user);

		if(aux.second == false)
			throw Id_duplicado(id_user);
	}

//	Asociar una tarjeta un usuario.
//	Declaración del map Tarjetas:		typedef std::map<Numero, Tarjeta*> Tarjetas;
void Usuario::es_titular_de(const Tarjeta& tarj)
{
	if(tarj.titular() == )
	tarjetas_.insert(tarj);
}

//	Desligar una tarjeta de un usuario.
void Usuario::no_es_titular_de(const Tarjeta& tarj)
{

}