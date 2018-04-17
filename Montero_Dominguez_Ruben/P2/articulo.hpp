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
	Cadena referencia() const;
	Cadena titulo() const;
	Fecha f_publi() const;
	double precio() const;
	double& precio();
	unsigned stock() const;
	unsigned& stock();

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

inline Cadena Articulo::referencia() const{return ref_code_;}
inline Cadena Articulo::titulo() const{return titulo_;}
inline Fecha Articulo::f_publi() const{return f_publicacion_;}
inline double Articulo::precio() const{return precio_;}
inline double& Articulo::precio(){return precio_;}
inline unsigned Articulo::stock() const{return num_ejemplares_;}
inline unsigned& Articulo::stock(){return num_ejemplares_;}

std::ostream& operator <<(std::ostream& os, const Articulo& art);


#endif // ARTICULO_HPP_