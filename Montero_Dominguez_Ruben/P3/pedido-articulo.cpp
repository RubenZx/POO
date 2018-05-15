#include "pedido-articulo.hpp"	

/***************************************************** CLASE PEDIDO_ARTICULO *****************************************************/

void Pedido_Articulo::pedir(const Pedido& ped, const Articulo& art, double precio, unsigned cant = 1)
{
	directa_[&ped].insert(std::make_pair(&art, LineaPedido(precio, cant)));
	inversa_[&art].insert(std::make_pair(&ped, LineaPedido(precio, cant)));
}

void Pedido_Articulo::pedir(const Articulo& art, const Pedido& ped, double precio, unsigned cant = 1)
{
	pedir(ped, art, precio, cant);
}

std::ostream& Pedido_Articulo::mostrarDetallePedidos()
{
	double toti = 0.0;

	for(auto iter = directa_.begin(); iter != directa_.end(); iter++)
	{
		os 	<< "Pedido núm. " << (iter->first)->numero() << "\n"
			<< "Cliente: " << (iter->first)->tarjeta()->titular()->nombre() << "\t"
			<< "Fecha: " << (iter->first)->fecha() << std::endl;
		toti += (iter->first)->total();
	}

	os << "TOTAL VENTAS\t" << std::setprecision(2) << toti << " €" << std::endl;
	return os;
}

std::ostream& Pedido_Articulo::mostrarVentasArticulos()
{
	for(auto iter = inversa_.begin(); iter != inversa_.end(); iter++)
	{
		os 	<< "Ventas de " << (iter->first)
	}

	return os;
}

std::ostream& operator <<(std::ostream& os, const Pedido_Articulo::ItemsPedido& items)
{

}

std::ostream& operator <<(std::ostream& os, const Pedido_Articulo::Pedidos& peds)
{

}


/***************************************************** CLASE LINEAPEDIDO *****************************************************/

std::ostream& operator <<(std::ostream& os, const LineaPedido::LineaPedido& linP)
{
	os << std::setprecision(2) << linP.precio_venta() << " €\t" << linP.cantidad() << std::endl;
	return os;
}
