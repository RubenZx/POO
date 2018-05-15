#ifndef ARTICULO_HPP_
#define ARTICULO_HPP_

#include <iostream>

#include "cadena.hpp"
#include "fecha.hpp"

class Articulo{
	
public:
	// Constructor de articulo.
	Articulo(const Cadena& ref, const Cadena& titulo, const Fecha& fecha, double p, unsigned num);
	// Métodos públicos de la clase artículo.
	Cadena referencia() const{return ref_code_;}
	Cadena titulo() const{return titulo_;}
	Fecha f_publi() const{return f_publicacion_;}
	double precio() const{return precio_;}
	double& precio(){return precio_;}
	unsigned stock() const{return num_ejemplares_;}
	unsigned& stock(){return num_ejemplares_;}

private:
	Cadena ref_code_, titulo_;
	Fecha f_publicacion_; 
	double precio_;
	unsigned num_ejemplares_;
};

inline Articulo::Articulo(const Cadena& ref, const Cadena& titulo, const Fecha& fecha, double p, unsigned num):
	ref_code_{ref},
	titulo_{titulo}, 
	f_publicacion_{fecha}, 
	precio_{p}, 
	num_ejemplares_{num}{}

std::ostream& operator <<(std::ostream& os, const Articulo& art);

#endif // ARTICULO_HPP_