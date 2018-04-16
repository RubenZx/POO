#ifndef ARTICULO_HPP_
#define ARTICULO_HPP_

#include "cadena.hpp"
#include "fecha.hpp"

class Articulo{
	
public:
	Articulo(const Cadena& ref, const Cadena& titulo, const Fecha& fecha, double p, unsigned ejemplares);
	



private:
	Cadena ref_code_, titulo_;
	Fecha f_publicacion_; 
	double precio_;
	unsigned num_ejemplares_;
}

#endif // ARTICULO_HPP_