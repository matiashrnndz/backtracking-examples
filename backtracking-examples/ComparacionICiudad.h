#ifndef COMPARACIONICIUDAD_H
#define COMPARACIONICIUDAD_H

#include "Comparador.h"
#include "Iterador.h"
#include "ICiudad.h"

class ComparacionICiudad : public Comparacion<Puntero<ICiudad>> {

public:

	ComparacionICiudad() {};

	CompRetorno Comparar(const Puntero<ICiudad>& e1, const Puntero<ICiudad>& e2) const
	{
		return MENOR;
	};

};

#endif