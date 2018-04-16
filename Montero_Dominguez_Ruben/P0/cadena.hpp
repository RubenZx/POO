#ifndef CADENA_HPP_
#define CADENA_HPP_
#include <iostream>
#include <cstring>

class Cadena
{
public:
	
	explicit Cadena(size_t t = 0, char c = ' ') noexcept;	// Constructor para una cadena con un numero de veces del caracter que se le pase.
	Cadena(const Cadena& cad) noexcept;						// Constructor de copia.
	Cadena(const char* cad) noexcept;						// Constructor por char*.

	Cadena& operator=(const Cadena& cad) noexcept;			// Sobrecarga de la asignación.
	Cadena& operator=(const char* cad) noexcept;			// Sobrecarga de la asignación por char*.
	operator const char*() const noexcept;					// Sobrecarga del "operator const char*", usado para poder pasar una "Cadena" a un "char*".

	const size_t length() const noexcept;					// Método observador que devuelve la longitud de la cadena.

	Cadena& operator+=(const Cadena& cad) noexcept;			// Concatenar una cadena con otra.
	Cadena operator+(const Cadena& cad1) noexcept;			// Concatenar una cadena con otra devolviendo una nueva.

	char& operator[](size_t index);
	char operator[](size_t index)const;
	char& at(size_t index);
	char at(size_t index)const;

	Cadena substr(size_t index, size_t tam) const;
	
	~Cadena() noexcept;


private:

	char* s_;
	size_t tam_;	

};

bool operator==(const Cadena& cad1, const Cadena& cad2) noexcept;
bool operator!=(const Cadena& cad1, const Cadena& cad2) noexcept;
bool operator<(const Cadena& cad1, const Cadena& cad2) noexcept;
bool operator<=(const Cadena& cad1, const Cadena& cad2) noexcept;
bool operator>(const Cadena& cad1, const Cadena& cad2) noexcept;
bool operator>=(const Cadena& cad1, const Cadena& cad2) noexcept;

Cadena operator+(const Cadena& cad1, const Cadena& cad2) noexcept;

inline char& Cadena::operator[](size_t index){return s_[index];}
inline char Cadena::operator[](size_t index)const{return s_[index];}

inline Cadena::operator const char*()const noexcept{return s_;}
inline const size_t Cadena::length()const noexcept{return tam_;}

#endif // CADENA_HPP_