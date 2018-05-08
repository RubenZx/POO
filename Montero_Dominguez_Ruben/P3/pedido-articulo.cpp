#include "pedido-articulo.hpp"

std::ostream& operator <<(std::ostream& os, const LineaPedido& linP)
{
	os << std::setprecision(2) << linP.precio_venta() << " €\t" << linP.cantidad() << std::endl;

	return os;
}

