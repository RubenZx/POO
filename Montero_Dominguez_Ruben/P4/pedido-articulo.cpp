#include "pedido-articulo.hpp"	

/***************************************************** CLASE PEDIDO_ARTICULO *****************************************************/

void Pedido_Articulo::pedir(Pedido& ped, Articulo& art, double precio, unsigned cant)
{
	directa_[&ped].insert(std::make_pair(&art, LineaPedido(precio, cant)));
	inversa_[&art].insert(std::make_pair(&ped, LineaPedido(precio, cant)));
}

void Pedido_Articulo::pedir(Articulo& art, Pedido& ped, double precio, unsigned cant)
{
	pedir(ped, art, precio, cant);
}

std::ostream& Pedido_Articulo::mostrarDetallePedidos(std::ostream& os)
{
	double toti = 0.0;

	// iter->first  <=> Pedido*
	// iter->second <=> ItemsPedido
	for(auto iter = directa_.begin(); iter != directa_.end(); iter++)
	{
		os 	<< "Pedido núm. " << (iter->first)->numero() << "\n"
			<< "Cliente: " << (iter->first)->tarjeta()->titular()->nombre() << "\t"
			<< "Fecha: " << (iter->first)->fecha() << std::endl << iter->second;
		toti += (iter->first)->total();
	}

	os << "TOTAL VENTAS\t" << std::fixed << std::setprecision(2) << toti << " €" << std::endl;
	return os;
}

std::ostream& Pedido_Articulo::mostrarVentasArticulos(std::ostream& os)
{
	// iter->first  <=> Articulo*
	// iter->second <=> Pedidos
	for(auto iter = inversa_.begin(); iter != inversa_.end(); iter++)
	{
		os 	<< "Ventas de [" << (iter->first)->referencia() << "]  " << "\"" 
			<< (iter->first)->titulo() << "\"\n" 
			<< iter->second << std::endl; 
	}

	return os;
}

std::ostream& operator <<(std::ostream& os, const Pedido_Articulo::ItemsPedido& items)
{
	double toti = 0.0;

	os 	<< " PVP\tCantidad\t\tArtículo\n" << Cadena(80, '=') << std::endl;

	// iter->first  <=> Articulo*
	// iter->second <=> LineaPedido
	for(auto iter = items.begin(); iter != items.end(); iter++)
	{
		os 	<< std::fixed << std::setprecision(2) << (iter->first)->precio() << " €\t" 
			<< (iter->second).cantidad() << "\t\t" << (iter->first)->referencia() << " \"" << (iter->first)->titulo() << "\"" << std::endl;

		toti += (iter->first)->precio() * (iter->second).cantidad();
	}

	os 	<< Cadena(80, '=') << "\n"
		<< "Total\t" << toti << std::endl;

	return os;
}

std::ostream& operator <<(std::ostream& os, const Pedido_Articulo::Pedidos& peds)
{
	double toti = 0.0;

	os 	<< "[Pedidos: " << peds.size() << "]\n"
		<< Cadena(80, '=') << "\n"
		<< "  PVP\tCantidad\tFecha de venta\n"
		<< Cadena(80, '=') << std::endl;

	// iter->first  <=> Pedido*
	// iter->second <=> LineaPedido
	for(auto iter = peds.begin(); iter != peds.end(); iter++)
	{
		os 	<< iter->second << "\t\t" << (iter->first)->fecha() << std::endl;
		
		toti += (iter->second).precio_venta() * (iter->second).cantidad();
	}

	os 	<< Cadena(80, '=') << "\n" << toti << " €" << std::endl;

	return os;
}


/***************************************************** CLASE LINEAPEDIDO *****************************************************/

std::ostream& operator <<(std::ostream& os, const LineaPedido& linP)
{
	return os << std::fixed << std::setprecision(2) << linP.precio_venta() << " €\t" << linP.cantidad();
}
