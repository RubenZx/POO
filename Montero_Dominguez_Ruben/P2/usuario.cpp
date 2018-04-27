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

bool Clave::verifica(const char* key) const
{
	if(const char *const pcc = crypt(key, passwd_.c_str())) 
		return (passwd_ == pcc);
	throw Incorrecta(ERROR_CRYPT);
}

/***************************************************** MÉTODOS DE LA CLASE USUARIO *****************************************************/

Usuario::Usuarios Usuario::usuarios_;
//	Constructor de usuario.
Usuario::Usuario(const Cadena& id_user, const Cadena& nombre, const Cadena& apell, const Cadena& dir, const Clave& pass):
	id_{id_user},
	nombre_{nombre},
	apell_{apell},
	dir_{dir},
	passwd_{pass}
	{
		if(!usuarios_.insert(id_user).second)
			throw Id_duplicado(id_);
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
		tarjetas_.erase(tarj.numero());	
}

//	Eliminar las tarjetas, llamando al método Tarjeta::anula_titular();
Usuario::~Usuario()
{
	auto iter = tarjetas_.begin();
	while(iter != tarjetas_.end())
	{
		iter->second->anula_titular();
		iter++;
	}
	usuarios_.erase(id_);
}

void Usuario::compra(Articulo& art, unsigned cant)
{
	if(cant == 0)				//	Sacar artículo del carrito, es decir, eliminar enlace con el articulo.
		carrito_.erase(&art);
	else 						//	Nueva cantidad del articulo en el carrito.
		carrito_[&art] = cant;
}

std::ostream& operator <<(std::ostream& os, const Usuario& user)
{
	os 	<< user.id() << " ["
		<< user.passwd_.clave().c_str() << "]"
		<< user.nombre() << " "
		<< user.apellidos() << "\n"
		<< user.direccion() << "\n"
		<< "Tarjetas:\n"; 
		
		auto iter = user.tarjetas().begin();
		while(iter != user.tarjetas().end())
		{
			os << *iter->second;
			iter++;
		}

	return os;
}

std::ostream& mostrar_carro(std::ostream& os, const Usuario& user)
{
  	os 	<< "Carrito de compra de " << user.id() << " [Artículos: "
     	<< user.n_articulos() << "]" << std::endl;
    os 	<< " Cant. Artículo" << std::endl
        << std::setw(95) << std::setfill('=') << '\n'  << std::setfill(' ');
  	
  	int tmp = user.n_articulos();
  	while(tmp > 0)
  	{
    	for (auto const& i : user.compra())
        {
          	os 	<< std::setw(4) << i.second << "   "
             	<< "[" << (*i.first).referencia() << "] \""
             	<< (*i.first).titulo() << "\", " << (*i.first).f_publi().anno()
             	<< ". " << std::fixed << std::setprecision(2) << (*i.first).precio()
             	<< " €" << std::endl;
          	--tmp;
        }
  }
  
  return os;
}