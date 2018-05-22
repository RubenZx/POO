#ifndef ARTICULO_HPP_
#define ARTICULO_HPP_

#include <iostream>
#include <set>

#include "cadena.hpp"
#include "fecha.hpp"

class Autor{
public:
	Autor(const Cadena& nombre, const Cadena& apellidos, const Cadena& direccion) noexcept
		: nombre_(nombre), apellidos_(apellidos), direccion_(direccion){}

	const Cadena& nombre() const{return nombre_;}
	const Cadena& apellidos() const{return apellidos_;}
	const Cadena& direccion() const{return direccion_;}

private:
	Cadena nombre_, apellidos_, direccion_;

};

class Articulo{
public:
	typedef std::set<Autor*> Autores;
	
	class Autores_vacios{};

	// Constructor de articulo.
	Articulo(const Autores& autores, const Cadena& ref, const Cadena& titulo, const Fecha& fecha, double p);
	
	// Métodos públicos de la clase artículo.
	Cadena referencia() const{return ref_code_;}
	Cadena titulo() const{return titulo_;}
	Fecha f_publi() const{return f_publicacion_;}
	double precio() const{return precio_;}
	double& precio(){return precio_;}
	
	//	Se eliminan los métodos stock, ya que hay clases que heredan que no tienen stock
	//unsigned stock() const{return num_ejemplares_;}
	//unsigned& stock(){return num_ejemplares_;}

	virtual void impresion_especifica(std::ostream& os) = 0;

private:
	Cadena ref_code_, titulo_;
	Fecha f_publicacion_; 
	double precio_;
	//unsigned num_ejemplares_;
	const Autores autores_;
};

inline Articulo::Articulo(const Cadena& ref, const Cadena& titulo, const Fecha& fecha, double p):
	autores_{autores},
	ref_code_{ref},
	titulo_{titulo}, 
	f_publicacion_{fecha}, 
	precio_{p}{}


std::ostream& operator <<(std::ostream& os, const Articulo& art);

class ArticuloAlmacenable: public Articulo
{
public:
	ArticuloAlmacenable(const Autores& autores, const Cadena& ref, const Cadena& titulo, const Fecha& fecha, double p, unsigned num_ejemp = 0)
		: Articulo(autores, ref, titulo, fecha, p), num_ejemplares_(num_ejemp){}

	unsigned stock() const{return num_ejemplares_;}
	unsigned& stock(){return num_ejemplares_;}

private:
	unsigned num_ejemplares_;
};

class Libro: public ArticuloAlmacenable
{
public:
	Libro(const Autores& autores, const Cadena& ref, const Cadena& titulo, const Fecha& fecha, double p, unsigned num_pags, unsigned num_ejemp = 0)
		: ArticuloAlmacenable(autores, ref, titulo, fecha, p, num_ejemp), num_paginas_(num_pags){}

	unsigned n_pag() const{return num_paginas_;}

private:
	const unsigned num_paginas_;
};

class Cederron: public ArticuloAlmacenable
{
public:
	Cederron(const Autores& autores, const Cadena& ref, const Cadena& titulo, const Fecha& fecha, double p, unsigned tam, unsigned num_ejemp = 0)
		: ArticuloAlmacenable(autores, ref, titulo, fecha, p, num_ejemp), tam_(tam){}

	unsigned tam() const{return tam_;}

private:
	const unsigned tam_;
};

#endif // ARTICULO_HPP_