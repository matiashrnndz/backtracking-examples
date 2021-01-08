#pragma once

#ifndef LISTAORD_H
#define LISTAORD_H

#include "Iterable.h"
#include "Puntero.h"

typedef unsigned int nat;

template <class T>
class ListaOrd abstract : public Iterable<T>
{
public:
	virtual ~ListaOrd() {}
	
	// PRE: Est� ordenada
	// POS: e pertenece a la lista. La lista est� ordenada y contiene todos los elementos que hab�a en la lista antes de la inserci�n
	virtual void InsertarOrdenado(const T& e) abstract;

	// PRE: La lista no est� vac�a
	// POS: Retorna el primer elemento de la lista
	virtual const T& Cabeza() const abstract;

	// PRE: -
	// POS: Elimina una ocurrencia del elemento de la lista si existe. De no existir no tiene acci�n.
	virtual void Eliminar(const T& e) abstract;

	// PRE: -
	// POS: Retorna el largo de la lista
	virtual nat Largo() const abstract;

	// PRE: La lista tiene un elemento en la posici�n n. 
	// POS: Retorna el elemento que est� en esa posici�n de la lista. El primer elemento empieza en 0.
	virtual const T& Obtener(const nat n) const abstract;

	// PRE: -
	// POS: Retorna true si y solo si el elemento e pertenece a la lista.
	virtual bool Pertenece(const T& e) const abstract;

	// PRE: -
	// POS: Retorna true si y solo si la lista esta vacia
	virtual bool EstaVacia() const abstract;

	// PRE: -
	// POS: Retorna un clon de la lista que no comparte memoria con ella
	virtual Puntero<ListaOrd<T>> Clon() const abstract;
};


#endif