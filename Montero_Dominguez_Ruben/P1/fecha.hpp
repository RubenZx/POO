#ifndef FECHA_HPP_
#define FECHA_HPP_

#include <iostream>

using namespace std;

class Fecha
{
public:
	static const int AnnoMinimo = 1902;
	static const int AnnoMaximo = 2037;

	explicit Fecha(int dia = 0, int mes = 0, int anno = 0);			// Constructor para, 3, 2, 1, o 0 parámetros.
	Fecha(const char* f);											// Constructor para fecha en formato: "dd/mm/aaaa".
	
	// Sobrecarga de operadores miembro.
	Fecha& operator +=(int n) noexcept;								
	Fecha& operator -=(int n) noexcept;								
	Fecha operator +(int n) const noexcept;								
	Fecha operator -(int n) const noexcept;								
	Fecha operator ++(int) noexcept; 								// ++ Postfijo.
	Fecha& operator ++() noexcept;									// ++ Prefijo.
	Fecha operator --(int) noexcept;								// -- Postfijo.
	Fecha& operator --() noexcept;									// -- Prefijo.

	// Método explícito de conversión llamado Fecha::cadena
    const char* cadena() const;

	// Métodos observadores de dia, mes y año.
	int dia()const noexcept;
	int mes()const noexcept;
	int anno()const noexcept;
	
	class Invalida
	{
	public:
		Invalida(const char* e);							// Constructor.  
		const char* por_que() const;						// Método observador que devolverá la excepción.
	
	private:
		const char* error_;
	};

private:
	void sustituir_fecha_actual() noexcept;					// Método para cambiar la fecha en el caso en el que tome un valor 0.
	int bisiesto() noexcept;								// Método para comprobar si un año es bisiesto o no.
	void validar();											// Método para comprobar si una fecha es válida o no.
	std::tm* f_sistema() noexcept;							// Método para tomar la fecha actual del sistema.

	int dia_, mes_, anno_;
};

// Sobrecarga de los operadores de comparación.
bool operator ==(const Fecha& f1, const Fecha& f2) noexcept;
bool operator <(const Fecha& f1, const Fecha& f2) noexcept;
bool operator !=(const Fecha& f1, const Fecha& f2) noexcept;
bool operator >(const Fecha& f1, const Fecha& f2) noexcept;
bool operator <=(const Fecha& f1, const Fecha& f2) noexcept;
bool operator >=(const Fecha& f1, const Fecha& f2) noexcept;

// Sobrecarga  de operadores de flujo.
istream& operator >>(istream& is, Fecha& f1);
ostream& operator <<(ostream& os, const Fecha& f1);

inline int Fecha::dia()const noexcept{return dia_;}
inline int Fecha::mes()const noexcept{return mes_;}
inline int Fecha::anno()const noexcept{return anno_;}

// Constructor de inválida con el mensaje de error.
inline Fecha::Invalida::Invalida(const char* e):error_{e}{}
// Método por_que() el cual devuelve el error concreto que lanza cada excepción en forma de cadena de bajo nivel.
inline const char* Fecha::Invalida::por_que() const{return error_;}

#endif // FECHA_HPP_