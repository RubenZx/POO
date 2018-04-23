

Usuario::Usuario(const Cadena& id_user, const Cadena& nombre, const Cadena& apell, const Cadena& dir, const Clave& pass):
	id_{id_user},
	nombre_{nombre},
	apell_{apell},
	dir_{dir},
	passwd_{pass}
	{
		std::pair<unordered_set::iterator, bool> aux;	
		aux = identificadores.insert(id_user);

		if(aux.second() == false)
			throw Id_duplicado(id_user);
	}