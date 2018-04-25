#include "usuario.hpp"

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
		if(identificadores.insert(id_user).second == false)
			throw Id_duplicado(id_user);
	}

//	Asociar una tarjeta un usuario.
void Usuario::es_titular_de(Tarjeta& tarj)
{
	if(tarj.titular() == this)
		tarjetas_.insert(std::make_pair(tarj.numero(), &tarj));
}

//	Desligar una tarjeta de un usuario.
void Usuario::no_es_titular_de(Tarjeta& tarj)
{
	if(tarj.titular() == this)
		tarjetas_.erase(const_cast<Numero&>tarj.numero());	
}

//	Eliminar las tarjetas, llamando al método Tarjeta::anula_titular();
Usuario::~Usuario()
{
	Tarjetas::iterator iter = tarjetas_.begin();
	while(!tarjetas_.empty())
	{
		iter->second->anula_titular();
		iter++;
	}
	identificadores.erase(id_);
}

void Usuario::compra(Articulo& art, unsigned cant)
{
	if(cant == 0)				//	Sacar artículo del carrito, es decir, eliminar enlace con el articulo.
		carrito_.erase(art);
	else 						//	Nueva cantidad del articulo en el carrito.
		carrito_[&art] = cant;
}

std::ostream& operator <<(std::ostream& os, const Usuario& user)
{
	os 	<< user.id() << " ["
		<< user.passwd_ << "]"
		<< user.nombre() << " "
		<< user.apellidos() << "\n"
		<< user.direccion() << "\n"
		<< "Tarjetas:\n"; 
		
		Usuario::Tarjetas::iterator iter = user.tarjetas().begin();
		while(iter != user.tarjetas().end())
		{
			os << iter->second;
			iter++;
		}

	return os;
}

std::ostream& mostrar_carro(std::ostream& os, const Usuario& user)
{
	Usuario::Articulos articulos = user.compra();
	Usuario::Articulos::iterator iter = articulos.begin();	

	os 	<< "Carrito de la compra de " << user.id() 
		<< " [Artículos: " << user.n_articulos() 
		<< "]\n" << "Cant.  Artículo\n" 
		<< "===========================================================\n";
		
		while(iter != articulos.end())
		{
			os << iter->second << "    " << iter->first;

			iter++;
		}

	return os;
}