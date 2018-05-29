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
	const Cadena& referencia() const{return ref_code_;}
	const Cadena& titulo() const{return titulo_;}
	const Fecha& f_publi() const{return f_publicacion_;}
	const Autores& autores() const{return autores_;}
	double precio() const{return precio_;}
	double& precio(){return precio_;}
	
	//	Se eliminan los métodos stock, ya que hay clases que heredan que no tienen stock
	//unsigned stock() const{return num_ejemplares_;}
	//unsigned& stock(){return num_ejemplares_;}

	virtual void impresion_especifica(std::ostream& os)const = 0;
	virtual ~Articulo(){}

private:
	Cadena ref_code_, titulo_;
	Fecha f_publicacion_; 
	double precio_;
	//unsigned num_ejemplares_;
	const Autores autores_;
};

inline Articulo::Articulo(const Autores& autores, const Cadena& ref, const Cadena& titulo, const Fecha& fecha, double p):
	ref_code_{ref},
	titulo_{titulo}, 
	f_publicacion_{fecha}, 
	precio_{p},
	autores_{autores}
	{
		if(autores_.size() == 0)
			throw Autores_vacios();
	}

std::ostream& operator <<(std::ostream& os, const Articulo& art);

class ArticuloAlmacenable: public Articulo
{
public:
	ArticuloAlmacenable(const Autores& autores, const Cadena& ref, const Cadena& titulo, const Fecha& fecha, double p, unsigned num_ejemp = 0)
		: Articulo(autores, ref, titulo, fecha, p), stock_(num_ejemp){}

	unsigned stock() const{return stock_;}
	unsigned& stock(){return stock_;}

protected:
	unsigned stock_;
};

class Libro: public ArticuloAlmacenable
{
public:
	Libro(const Autores& autores, const Cadena& ref, const Cadena& titulo, const Fecha& fecha, double p, unsigned num_pags, unsigned num_ejemp = 0)
		: ArticuloAlmacenable(autores, ref, titulo, fecha, p, num_ejemp), n_pag_(num_pags){}

	unsigned n_pag() const{return n_pag_;}
	void impresion_especifica(std::ostream& os) const{os << n_pag_ << " págs., " << stock_ << " unidades.";}

private:
	const unsigned n_pag_;
};

class Cederron: public ArticuloAlmacenable
{
public:
	Cederron(const Autores& autores, const Cadena& ref, const Cadena& titulo, const Fecha& fecha, double p, unsigned tam, unsigned num_ejemp = 0)
		: ArticuloAlmacenable(autores, ref, titulo, fecha, p, num_ejemp), tam_(tam){}

	unsigned tam() const{return tam_;}
	void impresion_especifica(std::ostream& os) const{os << tam_ << " MB, " << num_ejemplares_ << " unidades.";}

private:
	const unsigned tam_;
};

class LibroDigital: public Articulo
{
public:
	LibroDigital(const Autores& autores, const Cadena& ref, const Cadena& titulo, const Fecha& fecha, double p, const Fecha& fexpr)
		: Articulo(autores, ref, titulo, fecha, p), f_expir_(fexpr){}
	const Fecha& f_expir() const{return f_expir_;};
	void impresion_especifica(std::ostream& os) const{os << "A la venta hasta el " << f_expir_ << ".";}

private:
	const Fecha f_expir_;

};

#endif // ARTICULO_HPP_