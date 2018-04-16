#include "articulo.hpp"

Articulo::Articulo(const Cadena& ref, const Cadena& titulo, const Fecha& fecha, double p, unsigned ejemplares)
:ref_code_{ref}, titulo_{titulo}, f_publicacion_{fecha}, precio_{p}, num_ejemplares_{ejemplares}{}