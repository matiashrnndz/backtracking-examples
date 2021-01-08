#pragma once

#ifndef LISTAORDARRAY_H
#define LISTAORDARRAY_H

#include "Iterable.h"
#include "Puntero.h"
#include "Array.h"
#include "ListaOrd.h"

typedef unsigned int nat;

template <class T>
class ListaOrdArray : public ListaOrd<T>
{

public:

	// ORDEN PEOR CASO: O(1)
	//ListaOrdArray();

	// ORDEN PEOR CASO: O(1)
	ListaOrdArray(const Comparador<T> &c = Comparador<T>::Default);

	// ORDEN PEOR CASO: O(1)
	~ListaOrdArray();

	// ORDEN PEOR CASO: O(n)
	// PRE: Está ordenada
	// POS: e pertenece a la lista. La lista está ordenada y contiene todos los elementos que había en la lista antes de la inserción
	void InsertarOrdenado(const T& e);

	// ORDEN PEOR CASO: O(1)
	// PRE: La lista no está vacía
	// POS: Retorna el primer elemento de la lista
	const T& Cabeza() const;

	// ORDEN PEOR CASO: O(n)
	// PRE: -
	// POS: Elimina el primer elemento
	void EliminarPrimero();

	// ORDEN PEOR CASO: O(n)
	// PRE: -
	// POS: Elimina una ocurrencia del elemento de la lista si existe. De no existir no tiene acción
	void Eliminar(const T& e);

	// ORDEN PEOR CASO: O(n)
	// PRE: -
	// POS: Elimina el ultimo elemento
	void EliminarUltimo();

	// ORDEN PEOR CASO: O(1)
	// PRE: -
	// POS: Retorna el largo de la lista
	nat Largo() const;

	// ORDEN PEOR CASO: O(1)
	// PRE: La lista tiene un elemento en la posición n. 
	// POS: Retorna el elemento que está en esa posición de la lista. El primer elemento empieza en 0
	const T& Obtener(const nat n) const;

	// ORDEN PEOR CASO: O(n)
	// PRE: -
	// POS: Retorna true si y solo si el elemento e pertenece a la lista
	bool Pertenece(const T& e) const;

	// ORDEN PEOR CASO: O(1)
	// PRE: -
	// POS: Retorna true si y solo si la lista esta vacia
	bool EstaVacia() const;

	// ORDEN PEOR CASO: O(n)
	// PRE: -
	// POS: Retorna un clon de la lista que no comparte memoria con ella
	Puntero<ListaOrd<T>> Clon() const;

	// ORDEN PEOR CASO: O(1)
	// PRE: -
	// POS: Retorna el iterador del array
	Iterador<T> ObtenerIterador() const;

private:

	Array<T> elementos;
	Comparador<T> comp;
	nat largo;

};

#include "ListaOrdArray.cpp"

#endif

