#ifndef PEDIDO_ARTICULO_HPP
#define PEDIDO_ARTICULO_HPP

#include <iostream>
#include <iomanip>
#include <map>
#include <utility>

#include "pedido.hpp"
#include "articulo.hpp"

/***************************************************** CLASE LINEAPEDIDO *****************************************************/

class LineaPedido
{
public:
	explicit LineaPedido(double p, unsigned cant = 1):p_vnt_(p), cant_vnt_(cant){};
	double precio_venta()const{return p_vnt_;}
	unsigned cantidad()const{return cant_vnt_;}

private:
	double p_vnt_;
	unsigned cant_vnt_;
};

std::ostream& operator <<(std::ostream& os, const LineaPedido& linP);

/***************************************************** CLASE PEDIDO_ARTICULO *****************************************************/

class OrdenaPedidos{
public:
	bool operator()(const Pedido* ped1, const Pedido* ped2) {return ped1->numero() < ped2->numero();}
};

class OrdenaArticulos{
public:
	bool operator()(const Articulo* art1, const Articulo* art2){return art1->referencia() < art2->referencia();}
};

class Pedido_Articulo
{
public:
	
	typedef std::map<Articulo*, LineaPedido, OrdenaArticulos> ItemsPedido;
	typedef std::map<Pedido*, LineaPedido, OrdenaPedidos> Pedidos;

	// Métodos:
	void pedir(const Pedido& ped, const Articulo& art, double precio, unsigned cant = 1);
	void pedir(const Articulo& art, const Pedido& ped, double precio, unsigned cant = 1);

	ItemsPedido& detalle(Pedido& ped){return directa_[&ped];}
	Pedidos ventas(Articulo& art){return inversa_[&art];}

	//	HACER
	std::ostream& mostrarDetallePedidos(std::ostream& os);
	std::ostream& mostrarVentasArticulos(std::ostream& os);

private:
	std::map<Pedido*, ItemsPedido, OrdenaPedidos> directa_;		// Asociación pedido a artículo
	std::map<Articulo*, Pedidos, OrdenaArticulos> inversa_;		// Asociación artículo a pedido
};

//	HACER
std::ostream& operator <<(std::ostream& os, const Pedido_Articulo::ItemsPedido& items);
std::ostream& operator <<(std::ostream& os, const Pedido_Articulo::Pedidos& peds);

#endif 	//	PEDIDO_ARTICULO_HPP