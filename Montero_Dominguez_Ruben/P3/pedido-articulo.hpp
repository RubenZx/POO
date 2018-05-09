#include <iostream>
#include <iomanip>
#include "articulo.hpp"

class Pedido;

class Pedido_Articulo
{
public:
	typedef std::map<Articulo*, LineaPedido, OrdenaArticulos> ItemsPedido;
	typedef std::map<Pedido*, LineaPedido, OrdenaPedidos> Pedidos;

	class OrdenaPedidos{
  	public:
  		bool operator()(const Pedido& ped1, const Pedido& ped2) {return ped1.numero() < ped2.numero();}
	};

	class OrdenaArticulos{
	public:
		bool operator()(const Articulo& art1, const Articulo& art2){return art1.referencia() < art2.referencia();}
	};

	//	Métodos:
	void pedir(const Pedido& ped, const Articulo& art, double precio, unsigned cant = 1);
	void pedir(const Articulo& art, const Pedido& ped, double precio, unsigned cant = 1);

	const ItemsPedido& detalle(const Pedido& ped, double prv, unsigned cant);				//	HACER
	const Pedidos& ventas(const Articulo& art);

private:
	std::map<Pedido*, ItemsPedido, OrdenaPedidos> directa_;
	std::map<Articulo*, Pedidos, OrdenaArticulos> inversa_;
};

class LineaPedido
{
public:
	explicit LineaPedido(double p, unsigned cant = 1):p_vnt_(p), cant_vnt_(cant);
	double precio_venta()const{return p_vnt_;};
	unsigned cantidad()const{return cant_vnt_;};

private:
	double p_vnt_;
	unsigned cant_vnt_;
};

std::ostream& operator <<(std::ostream& os, const LineaPedido& linP);
