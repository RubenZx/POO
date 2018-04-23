#include <cstring>
#include <stdexcept>
#include <iterator>
#include "cadena.hpp"

// Constructor
Cadena::Cadena(size_t t, char c) noexcept:tam_(t)
{
	s_ = new char[tam_ + 1];
	
	size_t i;
	for(i = 0; i < tam_; i++)
	{
		s_[i] = c;
	}
	s_[i] = '\0';
}

// Constructor de copia
Cadena::Cadena(const Cadena& cad) noexcept
{
	tam_ = cad.tam_;
	s_ = new char[cad.tam_ + 1];
	strcpy(s_, cad.s_);

}

// Constructor de copia con semantica de movimiento
Cadena::Cadena(Cadena&& cad) noexcept:s_{cad.s_}, tam_{cad.tam_}
{
	cad.s_ = nullptr;
	cad.tam_ = 0;
}

// Constructor de cadena
Cadena::Cadena(const char* cad) noexcept
{
	tam_ = strlen(cad);
	s_ = new char[tam_ + 1];
	
	size_t i;
	for(i = 0; i < tam_; i++)
	{
		s_[i] = cad[i];
	}
	s_[i] = '\0';
}

// Destructor de cadena
Cadena::~Cadena() noexcept
{
	delete[] s_;
}

// Sobrecarga del operador de asignación
Cadena& Cadena::operator=(const Cadena& cad) noexcept
{
	if(tam_ == cad.tam_)
	{
		size_t i;
		for(i = 0; i < tam_; i++)
		{
			s_[i] = cad.s_[i];
		}
		s_[i] = '\0';
	}
	else
	{
		delete[] s_;
		tam_ = cad.tam_;
		s_ = new char[tam_ + 1];

		size_t i;
		for(i = 0; i < tam_; i++)
		{
			s_[i] = cad.s_[i];
		}
		s_[i] = '\0';
	}
	return *this;
}

// Sobrecarga del operador de asignación para una cadena de bajo nivel
Cadena& Cadena::operator=(const char* cad) noexcept
{
	if(tam_ == strlen(cad)) strcpy(s_, cad);
	else
	{
		delete[] s_;
		tam_ = strlen(cad);
		s_ = new char[tam_ + 1];

		strcpy(s_, cad);
	}
	return *this;
}

// Sobrecarga ddel operador de asignación con semántica de movimiento
Cadena& Cadena::operator=(Cadena&& cad) noexcept
{
	if(this != &cad)
	{
		delete[] s_;

		s_ = cad.s_;
		tam_ = cad.tam_;

		cad.s_ = nullptr;
		cad.tam_ = 0;
	}
	return *this;
}

Cadena& Cadena::operator+=(const Cadena& cad) noexcept
{
	Cadena t = *this;

	delete[] s_;
	tam_ += cad.tam_;
	s_ = new char[tam_ + 1];

	strcpy(s_, t.s_);
	strcat(s_, cad.s_);

	return *this; 
}

Cadena Cadena::operator+(const Cadena& cad) noexcept
{
	Cadena t = *this;
	t += cad;
	return t;
}

Cadena operator+(const Cadena& cad1, const Cadena& cad2) noexcept
{
	Cadena t = cad1;
	t += cad2;
	return t;
}

bool operator==(const Cadena& cad1, const Cadena& cad2) noexcept
{
	return(strcmp(cad1.c_str(), cad2.c_str()) == 0);
}

bool operator<(const Cadena& cad1, const Cadena& cad2) noexcept
{
	return(strcmp(cad1.c_str(), cad2.c_str()) < 0);
}

bool operator<=(const Cadena& cad1, const Cadena& cad2) noexcept
{
	return !(cad1 > cad2);
}

bool operator>(const Cadena& cad1, const Cadena& cad2) noexcept
{
	return(strcmp(cad1.c_str(), cad2.c_str()) > 0);
}

bool operator>=(const Cadena& cad1, const Cadena& cad2) noexcept
{
	return !(cad1 < cad2);
}

bool operator!=(const Cadena& cad1, const Cadena& cad2) noexcept
{
	return !(cad1==cad2);
}

char& Cadena::at(size_t index) 
{
	if(index < tam_) return s_[index];
	else
		throw std::out_of_range("Error. Indice fuera de rango.");
}

char Cadena::at(size_t index)const
{
	if(index < tam_) return s_[index];
	else
		throw std::out_of_range("Error. Indice fuera de rango.");
}

Cadena Cadena::substr(size_t index, size_t t) const
{
	if(index < tam_)
	{
		if(tam_ - index >= t)
		{
			Cadena aux{t};
			unsigned j;

			for(j = 0; j < t; j++)
			{
				aux.s_[j] = s_[index + j];
			}
			aux.s_[j] = '\0';

			return aux;		
		}
		else
			throw std::out_of_range{"Error. La subcadena se encuentra fuera de los límites."};
	}
	else
		throw std::out_of_range{"Error. Posición inicial después del último carácter."};			
}

std::ostream& operator <<(std::ostream& os, const Cadena& cad1) noexcept
{
	os << cad1.c_str();
	return os;
}

std::istream& operator >>(std::istream& is, Cadena& cad1) noexcept
{
	size_t i;
	char* aux = new char[33];

	while(isspace(is.get()) && is.good()){}
	is.unget();

	i = 0;
	while(!(isspace(is.peek())) && i < 32 && is.good())
		aux[i++] = is.get();

	aux[i] = '\0';

	cad1 = aux;
	delete[] aux;
	
	return is;
}