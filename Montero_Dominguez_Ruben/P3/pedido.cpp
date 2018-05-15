#include "pedido.hpp"
#include "pedido-articulo.hpp"
#include "usuario-pedido.hpp"

int Pedido::N_pedidos = 0; 	//contador de pedidos

// Constructor de pedido.
Pedido::Pedido(Usuario_Pedido& us_pe, Pedido_Articulo& pe_art, Usuario& u, const Tarjeta& t, const Fecha& fp)
	:num_(N_pedidos + 1), tarjeta_(&t), fecha_(fp), total_(0)
{
	if(u.n_articulos() == 0) throw Vacio(u); 	                		//Carrito vacio
	if(t.titular() != &u) throw Impostor(u);                         	//Tarjeta robada
	if(t.caducidad() < fp) throw Tarjeta::Caducada(t.caducidad()); 	 	//Tarjeta caducada

	for(auto c : u.compra())   //c es pair<Articulo*, unisgned (cantidad)>, Comprobamos que haya stock para los articulos.
	{
		if(c.first->stock() < c.second)   //stock insuficiente
		{
			const_cast<Usuario::Articulos&>(u.compra()).clear();   //necesitamos quitar el const que nos devuelve u.compra()
			throw SinStock(*c.first);				//Sin stock, c.first es el Articulo*; *c.first es el Articulo
		}
	}

	Usuario::Articulos carroAux = u.compra();    // Carro auxiliar para leer e ir borrando sin que fallen los iteradores

	for(auto c : carroAux)   //Este for es para restar la cantidad de articulos que nos llevamos
	{
		Articulo* pa = c.first;
		unsigned cantidad = c.second;
		double precio = pa->precio();

		pa->stock() -= cantidad;

		pe_art.pedir(*this, *pa, precio, cantidad);
		total_ += precio * cantidad;
		u.compra(*pa, 0);
	}

	us_pe.asocia(u, *this);
	++N_pedidos;
}

/* Sobrecargar del operador de insercción de flujo.
-> FORMATO
---------------------------------------------------
Núm. pedido: 1
Fecha: jueves 10 de marzo de 2016
Pagado con: VISA n.o: 4539451203987356
Importe: 149,95 €
*/
std::ostream& operator <<(std::ostream& os, const Pedido& ped)
{
  	os 	<< "Núm. pedido: " << ped.numero() 
  		<< "\nFecha: " << std::setfill(' ') << std::setw(6) << ped.fecha() 	
  		<< "\nPagado con:  " << ped.tarjeta() 
  		<< "\nImporte: " << std::setfill(' ') << std::setw(4) << ped.total() << " €" << std::endl;
  
  	return os;
}
