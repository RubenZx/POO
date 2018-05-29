#include <cstring>
#include <ctime>
#include <cstdio>
#include <stdexcept>
#include "fecha.hpp"

static const int meses[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; 

// Función para tomar la fecha actual del sistema.
// Devuelve el tiempo descompuesto en una estructura con el dia, el mes y el año.
std::tm* Fecha::f_sistema() noexcept
{
	std::time_t tiempo_calendario = std::time(nullptr);
	std::tm* tiempo_descompuesto = std::localtime(&tiempo_calendario);

	return tiempo_descompuesto;
}

// Función para comprobar si el año es bisiesto o no.
// Devuelve "true" si el año es bisiesto y "false" si no lo es.
int Fecha::bisiesto() noexcept
{
	return ((anno_ % 4 == 0) && (anno_ % 400 == 0 || anno_ % 100 != 0));
}

// Función para comprobar si el día en función del mes, son correctos.
// Devuelve "true" si el mes y el dia son correctos y "false" si no lo son.
void Fecha::validar() 
{
	if(anno_ <= Fecha::AnnoMinimo || anno_ >= Fecha::AnnoMaximo )
		throw Invalida("AÑO ERRONEO");
	if(mes_ < 1 || mes_ > 12)
		throw Invalida("MES ERRONEO");
	if(dia_ < 1 || dia_ > meses[mes_] + bisiesto())
		throw Invalida("DIA ERRONEO");	
}

// Método para sustituir los atributos de la fecha en el caso en que uno de ellos tome valor 0.
void Fecha::sustituir_fecha_actual() noexcept
{
	if(dia_ == 0 || mes_ == 0 || anno_ == 0)
	{
		std::tm* tiempo_descompuesto;
		tiempo_descompuesto = f_sistema();	

		// Si uno de los parámetros es 0, ponemos su atributo a la fecha del sistema.
		if(dia_ == 0)
			dia_ = tiempo_descompuesto->tm_mday;
		if(mes_ == 0)
			mes_ = tiempo_descompuesto->tm_mon + 1; 			// tm_mon: 0 (ene)...11 (dic)
		if(anno_ == 0)
			anno_ = tiempo_descompuesto->tm_year + 1900; 		// tm_year: años desde 1900
	}
}

// Si el año es múltiplo de 4 es bisiesto <=> Febrero tiene 29 días, en otro caso Febrero tiene 28 días.
// Meses con 31 días: Enero, Marzo, Mayo, Julio, Agosto, Octubre y Diciembre. 1,3,5,7,8,10,12
// Meses con 30 días: Abril, Junio, Septiembre y Noviembre. 4,6,9,11
Fecha::Fecha(int dia, int mes, int anno): dia_(dia), mes_(mes), anno_(anno) 
{
	sustituir_fecha_actual();				// Comprobamos si alguno de los parámetros de la fecha es "0", y en caso correcto, se sustituye por el dato de la fecha actual del sistema.
	validar();	 							// Comprobamos si la fecha introducida es correcta.
}

// Constructor mediante una cadena de caracteres de la forma: dd/mm/aaaa.
Fecha::Fecha(const char* f)	
{
	int dia, mes, anno;
	// Tomamos el dia, mes y año de la cadena introducida.
	if(sscanf(f, "%d/%d/%d", &dia, &mes, &anno) == 3)
	{
		Fecha aux(dia, mes, anno);

		dia_ = aux.dia_;
		mes_ = aux.mes_;
		anno_ = aux.anno_;
	}
	else
		throw Invalida{"Error de formato."}; 	
}

// Definicion de la sobrecarga de los operadores a partir del "+="
Fecha& Fecha::operator +=(int n) noexcept
{	
	if(n != 0)
	{
		std::tm f = {0};	// 0 dentro de "{}"
	
		f.tm_mday = dia_ + n;
		f.tm_mon = mes_ - 1;
		f.tm_year = anno_ - 1900;	

		mktime(&f);

		dia_ = f.tm_mday;
		mes_ = f.tm_mon + 1;
		anno_ = f.tm_year + 1900;
	}

	validar();

	return *this;
}

Fecha& Fecha::operator -=(int n) noexcept
{
	return *this += -n;
}

Fecha Fecha::operator +(int n) const noexcept
{
	Fecha t = *this;
	return t += n;
}

Fecha Fecha::operator -(int n) const noexcept
{
	Fecha t = *this;
	return t += -n;
}

Fecha Fecha::operator ++(int) noexcept
{
	static Fecha t = *this;
	*this += 1;
	return t;
}

Fecha& Fecha::operator ++() noexcept
{
	return *this += 1;
}

Fecha Fecha::operator --(int) noexcept
{
	static Fecha t = *this;
	*this += -1;
	return t;	
}

Fecha& Fecha::operator --() noexcept
{
	return *this += -1;
}

// Definición de la sobrecarga de la recarga de operadores de comparación a partir del "==" y el "<".
bool operator ==(const Fecha& f1, const Fecha& f2) noexcept
{
	return (f1.dia() == f2.dia() && f1.mes() == f2.mes() && f1.anno() == f2.anno());
}

bool operator <(const Fecha& f1, const Fecha& f2) noexcept
{	
	bool aux = false;
	if(f1.anno() < f2.anno()) aux = true;
	else 
		if(f1.anno() == f2.anno())
		{
			if(f1.mes() < f2.mes()) aux = true;
			else
				if(f1.mes() == f2.mes())
					if(f1.dia() < f2.dia()) aux = true;

		}

	return aux;
}

bool operator !=(const Fecha& f1, const Fecha& f2) noexcept
{
	return !(f1 == f2);
}

bool operator >(const Fecha& f1, const Fecha& f2) noexcept
{
	return (f2 < f1);
}

bool operator <=(const Fecha& f1, const Fecha& f2) noexcept
{
	return !(f2 < f1);
}

bool operator >=(const Fecha& f1, const Fecha& f2) noexcept
{
	return !(f1 < f2);
}

// Método Fecha::cadena(), que devuelve la cadena de la fecha.
const char* Fecha::cadena() const
{
	static char aux[40];	
	const char* DIASEM[] = {"domingo", "lunes", "martes", "miércoles", "jueves", "viernes", "sábado"};
	const char* MES[] = {"enero", "febrero", "marzo", "abril", "mayo", "junio", "julio", "agosto", "septiembre", "octubre", "noviembre", "diciembre"};

	std::tm fecha = {0}; 

	fecha.tm_mday = this->dia();
	fecha.tm_mon = this->mes() - 1;
	fecha.tm_year = this->anno() - 1900;

	mktime(&fecha);

	sprintf(aux, "%s %d de %s de %d", DIASEM[fecha.tm_wday], fecha.tm_mday, MES[fecha.tm_mon], fecha.tm_year + 1900);
	
	return aux;	
}

// Definición de la sobrecarga de los operadores de insercción y extracción de flujo.
ostream& operator <<(ostream& os, const Fecha& f1)
{
	os << f1.cadena();
	return os;
}

istream& operator >>(istream& is, Fecha& f1)
{
	char fecha[11];	
	is.getline(fecha, 11);

	try{
		f1 = Fecha(fecha);
	}catch(Fecha::Invalida& e)
	{
		is.setstate(ios_base::failbit);
		throw e;
	}
	
	return is;
}
