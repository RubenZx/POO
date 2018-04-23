#ifndef USUARIO_HPP_
#define USUARIO_HPP_

#include <iostream>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <utility>
#include "cadena.hpp"

class Usuario
{
public:
	typedef std::map<Numero, Tarjeta*> Tarjetas;
	typedef std::unordered_map<Articulo*, unsigned int> Articulos;

	// Constructor. Y eliminación de los constructores de copia y asignación
	Usuario(const Cadena& id_user, const Cadena& nombre, const Cadena& apell, const Cadena& dir, const Clave& pass);
	Usuario(const Usuario& user) = delete;
	Usuario operator=(const Usuario& user) = delete;

	// Métodos observadores.
	Cadena id() const{return id_;};
	Cadena nombre() const{return nombre_;};
	Cadena apellidos() const{return apell_;};
	Cadena direccion() const{return dir_;};
	const Tarjetas& tarjetas() const{tarjetas_;};

	void es_titular_de(const Tarjeta& tarj);
	void no_es_titular_de(const Tarjeta& tarj);

	class Id_duplicado
	{
	public:
		Id_duplicado(const Cadena& cad);
		Cadena idd()const{return idDuplicado_;};
	private:	
		Cadena idDuplicado_;
	};

private:
	Cadena id_, nombre_, apell_, dir_;
	Clave passwd_;
	Tarjetas tarjetas_;
	Articulos carrito_;

	static unordered_set<Cadena> identificadores;
};

#endif	//USUARIO_HPP_