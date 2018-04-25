#ifndef USUARIO_HPP_
#define USUARIO_HPP_

#include <iostream>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <utility>
#include <cstring>
#include <ctime>
#include <random>
extern "C" {
#include <unistd.h>
}

#include "fecha.hpp"
#include "cadena.hpp"
#include "articulo.hpp"
#include "tarjeta.hpp"

class Tarjeta;
class Articulo;

/***************************************************** CLASE CLAVE *****************************************************/

class Clave
{
public:
	enum Razon{CORTA, ERROR_CRYPT};
	
	Clave(const char* key);
	Cadena clave() const{return passwd_;};
	bool verifica(const char*);

	class Incorrecta
	{
		Razon fallo_;
	public:
		Incorrecta(const Razon r):fallo_{r}{};
		Razon razon() const{return fallo_;};		
	};

private:
	Cadena passwd_;
};

/***************************************************** CLASE USUARIO0 *****************************************************/

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
	const Tarjetas& tarjetas() const{return tarjetas_;};
	
	const Articulos& compra() const{return carrito_;};
	size_t n_articulos() const{return carrito_.size();};

	void compra(Articulo& art, unsigned cant);

	void es_titular_de(Tarjeta& tarj);
	void no_es_titular_de(Tarjeta& tarj);

	class Id_duplicado
	{
		Cadena idDuplicado_;
	public:
		Id_duplicado(const Cadena& cad);
		const Cadena& idd()const{return idDuplicado_;};	
	};

	// Destructor.
	~Usuario();

	friend std::ostream& operator <<(std::ostream& os, const Usuario& user);

private:
	Cadena id_, nombre_, apell_, dir_;
	Clave passwd_;
	Tarjetas tarjetas_;
	Articulos carrito_;
	static unordered_set<Cadena> identificadores;
};

std::ostream& operator <<(std::ostream& os, const Usuario& user);
std::ostream& mostrar_carro(std::ostream& os, const Usuario& user);

#endif	//USUARIO_HPP_