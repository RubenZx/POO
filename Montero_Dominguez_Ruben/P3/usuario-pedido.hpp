#ifndef USUARIO_PEDIDO_HPP
#define USUARIO_PEDIDO_HPP

#include <iostream>
#include <set>
#include <map>
#include <utility>

class Usuario;
class Pedido;

class Usuario_Pedido
{
public:
	typedef std::set<Pedido*> Pedidos;

	void asocia(Usuario& user, Pedido& pedido);
	void asocia(Pedido& pedido, Usuario& user);

	const Pedidos& pedidos(Usuario& user) {return directa_[&user];}
	const Usuario* cliente(Pedido& pedido) {return inversa_[&pedido];}

private:
	std::map<Usuario*, Pedidos> directa_;
	std::map<Pedido*, Usuario*> inversa_;
};

inline void Usuario_Pedido::asocia(Usuario& user, Pedido& pedido)
{
	directa_[&user].insert(&pedido);
	inversa_[&pedido] = &user;
}

inline void Usuario_Pedido::asocia(Pedido& pedido, Usuario& user)
{
	asocia(user, pedido);
}

#endif 	// 	USUARIO_PEDIDO_HPP