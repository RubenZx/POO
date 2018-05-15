#ifndef PEDIDO_HPP
#define PEDIDO_HPP

#include <iostream>

#include "usuario.hpp"
#include "articulo.hpp"
#include "tarjeta.hpp"
#include "fecha.hpp"

class Usuario_Pedido;
class Pedido_Articulo;

class Pedido
{
public:
  // Constructor
  Pedido(Usuario_Pedido& us_pe, Pedido_Articulo& pe_art, Usuario& u, const Tarjeta& t, const Fecha& fp = Fecha());
  // Clases de excepciones.
  // 1-
  class Vacio
  {
    Usuario* user_;
  public:
    Vacio(Usuario& u):user_(&u){};
    Usuario& usuario() const {return *user_;}
  };
  // 2-
  class Impostor
  {
    Usuario* user_;
  public:
    Impostor(Usuario& u):user_(&u){};
    Usuario& usuario() const {return *user_;}
  };
  // 3-
  class SinStock
  {
    Articulo* art_;
  public:
    SinStock(Articulo* art):art_(art){};
    Articulo& articulo() const {return *art_;}
  };

  // Métodos observadores.
  int numero() const{return num_;}
  const Tarjeta* tarjeta() const {return tarjeta_;}
  Fecha fecha() const{return fecha_;}
  double total() const{return total_;}

private:
  static int N_pedidos;
  int num_;
  double total_;
  const Tarjeta* tarjeta_;
  Fecha fecha_;
};

std::ostream& operator <<(std::ostream& os, const Pedido& ped);

#endif  //  PEDIDO_HPP
