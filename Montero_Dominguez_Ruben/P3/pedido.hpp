#include <iostream>
#include "pedido-articulo.hpp"

#include "usuario.hpp"
#include "articulo.hpp"
#include "tarjeta.hpp"
#include "fecha.hpp"

class Pedido
{
public:
  // Constructor
  Pedido(Usuario_Pedido&, Pedido_Articulo&, Usuario&, const Tarjeta&, const Fecha&);
  // Clases de excepciones.
  // 1-
  class Vacio
  {
    Usuario* user_;
  public:
    Vacio(const Usuario& u):user_(&u){};
    const Usuario& usuario() const {return *user_;};
  };
  // 2-
  class Impostor
  {
    Usuario* user_;
  public:
    Impostor(const Usuario& u):user_(&u){};
    const Usuario& usuario() const {return *user_;};
  }
  // 3-
  class SinStock
  {
    Articulo* art_;
  public:
    SinStock(const Articulo& art):art_(&art){};
    const Articulo& articulo(){return *art_;};
  }

  // Métodos observadores.
  int numero() const{return num_;}
  const Tarjeta* tarjeta(){return tarjeta_;}
  Fecha fecha() const{return fecha_;}
  double total() const{return total_;}

private:
  static int N_pedidos;
  int num_;
  double total_;
  const Tarjeta* tarjeta_;
  Fecha fecha_;
}

std::ostream& operator <<(std::ostream& os, const Pedido& ped);
