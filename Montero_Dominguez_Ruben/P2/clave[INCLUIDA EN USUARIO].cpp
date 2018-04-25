#include <ctime>
#include <unistd.h>
#include <crypt.h>
#include "clave.hpp"

Clave::Clave(const char* key)
{
	Cadena contrasenna{key};
	if(contrasenna.length() < 5)	// La contraseña ha de tener al menos 5 caracteres, si no, se considerará demasiado corta
		throw Incorrecta(CORTA);
	else
	{
		char salt[2];
  		const char* encrypt = "./0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
  		
  		// srand(time(NULL));
  		salt[0] = encrypt[rand() % 64];
  		salt[1] = encrypt[rand() % 64];

	  	if(crypt(key, salt) == NULL)
	  		throw Incorrecta(ERROR_CRYPT);

	  	passwd_ = crypt(key, salt);
	}	
}

bool Clave::verifica(const char* key)
{
	char* result;
	
  	result = crypt(key, passwd_);
  	return(result == passwd_);
}
