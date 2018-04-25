#ifndef CADENA_HPP_
#define CADENA_HPP_

#include <iostream>
#include <functional>

class Cadena
{
public:

	explicit Cadena(size_t t = 0, char c = ' ') noexcept;	// Constructor para una cadena con un numero de veces del caracter que se le pase.
	Cadena(const Cadena& cad) noexcept;						// Constructor de copia.
	Cadena(Cadena&& cad) noexcept;							// Constructor de copia con semántica de movimiento.
	Cadena(const char* cad) noexcept;						// Constructor por char*.

	Cadena& operator=(const Cadena& cad) noexcept;			// Sobrecarga de la asignación.
	Cadena& operator=(const char* cad) noexcept;			// Sobrecarga de la asignación por char*.
	Cadena& operator=(Cadena&& cad) noexcept;				// Sobrecarga de la asignación con semántica con movimiento.
	const char* c_str() const noexcept;						

	// ITERADORES:	
	typedef char* iterator;
	typedef const char* const_iterator;
	typedef std::reverse_iterator<iterator> reverse_iterator;
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

	iterator begin() noexcept{return s_;};
	const_iterator begin() const noexcept{return s_;};
	const_iterator cbegin() const noexcept{return s_;};
	reverse_iterator rbegin() noexcept{return reverse_iterator(end());};
	const_reverse_iterator rbegin() const noexcept{return const_reverse_iterator(end());}
	const_reverse_iterator crbegin() const noexcept{return const_reverse_iterator(end());}
	
	iterator end() noexcept{return s_ + tam_;};
	const_iterator end() const noexcept{return s_ + tam_;};
	const_iterator cend() const noexcept{return s_ + tam_;};
	reverse_iterator rend() noexcept{return reverse_iterator(begin());}
	const_reverse_iterator rend() const noexcept{return const_reverse_iterator(begin());};
	const_reverse_iterator crend() const noexcept{return const_reverse_iterator(begin());};

	Cadena& operator+=(const Cadena& cad) noexcept;			// Concatenar una cadena con otra.
	Cadena operator+(const Cadena& cad1) noexcept;			// Concatenar una cadena con otra devolviendo una nueva.

	char& operator[](size_t index) noexcept;
	char operator[](size_t index)const noexcept;
	char& at(size_t index);
	char at(size_t index)const;

	Cadena substr(size_t index, size_t tam) const;			// Método que devuelve una subcadena dentro de otra cadena, del tamaño que se le especifica.
	const size_t length() const noexcept;					// Método observador que devuelve la longitud de la cadena.
	
	~Cadena() noexcept;

private:

	char* s_;
	size_t tam_;	

};

std::istream& operator >>(std::istream& is, Cadena& cad1) noexcept;
std::ostream& operator <<(std::ostream& os, const Cadena& cadd1) noexcept;

bool operator==(const Cadena& cad1, const Cadena& cad2) noexcept;
bool operator!=(const Cadena& cad1, const Cadena& cad2) noexcept;
bool operator<(const Cadena& cad1, const Cadena& cad2) noexcept;
bool operator<=(const Cadena& cad1, const Cadena& cad2) noexcept;
bool operator>(const Cadena& cad1, const Cadena& cad2) noexcept;
bool operator>=(const Cadena& cad1, const Cadena& cad2) noexcept;

Cadena operator+(const Cadena& cad1, const Cadena& cad2) noexcept;

inline char& Cadena::operator[](size_t index) noexcept{return s_[index];}
inline char Cadena::operator[](size_t index)const noexcept{return s_[index];}

inline const size_t Cadena::length() const noexcept{return tam_;}
inline const char* Cadena::c_str() const noexcept{return s_;}

// Para P2 y ss.
// Especialización de la plantilla hash<T>para definir la
// función hash a utilizar con contenedores desordenados de
// Cadena, unordered_[set|map|multiset|multimap].
namespace std {
	template <> struct hash<Cadena> 
	{
		size_t operator()(const Cadena& cad) const 	// conversión const char* ->string
		{											 
			return hash<string>{}(cad.c_str());
		}
	};
}

#endif // CADENA_HPP_