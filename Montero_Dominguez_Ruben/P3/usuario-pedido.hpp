#include <iostream>

class Usuario_Pedido
{
public:
	typedef std::set<Pedido*> Pedidos;
	
	void asocia(Usuario& user, Pedido& pedido);
	void asocia(Pedido& pedido, Usuario& user);

	const Pedidos& pedidos(Usuario& user) const;
	const Usuario* cliente(Pedido& pedido) const;

private:
	std::map<Usuario*, Pedidos> directa_;
	std::map<Pedido*, Usuario*> inversa_;
};

void Usuario_Pedido::asocia(Usuario& user, Pedido& pedido)
{
	directa_[&user].insert(&pedido);
	inversa_[&pedido] = &user;
}

void Usuario_Pedido::asocia(Pedido& pedido, Usuario& user)
{
	asocia(user, pedido);
}

const Usuario_Pedido::Pedidos& Usuario_Pedido::pedidos(Usuario& user) const
{
	if(!directa_.find(&user).second) return Pedidos();
	else return directa_[&user];
}

const Usuario* Usuario_Pedido::cliente(Pedido& pedido) const
{
	if(!inversa_.find(&pedido).second) return nullptr;
	else return inversa_[&pedido];
}
