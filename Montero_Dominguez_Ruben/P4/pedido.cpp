#include "pedido.hpp"
#include "pedido-articulo.hpp"
#include "usuario-pedido.hpp"

int Pedido::N_pedidos = 0; 	//contador de pedidos

// Constructor de pedido.
Pedido::Pedido(Usuario_Pedido& us_pe, Pedido_Articulo& pe_art, Usuario& u, const Tarjeta& t, const Fecha& fp)
	:num_(N_pedidos + 1), total_(0), tarjeta_(&t), fecha_(fp)
{
	if(u.n_articulos() == 0) throw Vacio(u); 	                		//Carrito vacio
	if(t.titular() != &u) throw Impostor(u);                         	//Tarjeta robada
	if(t.caducidad() < fp) throw Tarjeta::Caducada(t.caducidad()); 	 	//Tarjeta caducada

	Usuario::Articulos carroAux = u.compra();    // Carro auxiliar para leer e ir borrando sin que fallen los iteradores
	bool pedido_final_vacio = true;
	for(auto c : carroAux)   //Este for es para restar la cantidad de articulos que nos llevamos, c es un pair<Articulo*, unsigned (cantidad)>
	{
		Articulo* pa = c.first;
		unsigned cantidad = c.second;
		if(ArticuloAlmacenable* const paa = dynamic_cast<ArticuloAlmacenable* const>(pa))
		{
			if (paa->stock() < cantidad)
			{
				const_cast<Usuario::Articulos&>(u.compra()).clear();   //necesitamos quitar el const que nos devuelve u.compra()
				throw SinStock(*c.first);				//Sin stock, c.first es el Articulo*; *c.first es el Articulo
			}
			double precio = pa->precio();
			paa->stock() -= cantidad;
			total_ += precio * cantidad;
			pe_art.pedir(*this, *paa, precio, cantidad);
			pedido_final_vacio = false;
		}
		else 	// No es un ArticuloAlmacenable
			if(LibroDigital* const ld = dynamic_cast<LibroDigital* const>(pa))
			{
				if(ld->f_expir() > fp)
				{
					total_ += ld->precio() * cantidad;
					pe_art.pedir(*this, *ld, ld->precio(), cantidad);
					pedido_final_vacio = false;
				}
			}
			else throw std::logic_error("Pedido::Pedido: error, tipo de artículo desconocido.");
		u.compra(*(c.first), 0);
	}	// end_for

	if(pedido_final_vacio)
		throw Vacio(u);

	us_pe.asocia(u, *this);
	++N_pedidos;
}

// Sobrecargar del operador de insercción de flujo.
std::ostream& operator <<(std::ostream& os, const Pedido& ped)
{
  	os 	<< "Núm. pedido: " << ped.numero() 
  		<< "\nFecha: " << std::setfill(' ') << std::setw(6) << ped.fecha() 	
  		<< "\nPagado con:  " << ped.tarjeta()->tipo() 
  		<< " n.º: " << ped.tarjeta()->numero()
  		<< "\nImporte: " << std::setfill(' ') << std::setw(4) << ped.total() << " €" << std::endl;
  
  	return os;
}