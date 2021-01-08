#include "Sistema.h"

const int INFINITO = 999999999;

Sistema::Sistema()
{

}

// EJERCICIO 1 - Backtracking - Recursivo

Iterador<Tupla<nat, nat>> Sistema::Laberinto(Tupla<nat, nat> &inicio, Tupla<nat, nat> &fin, Matriz<nat> &laberinto)
{
	Puntero<ListaOrdArray<Tupla<nat, nat>>> solucionActual = new ListaOrdArray<Tupla<nat, nat>>(Comparador<Tupla<nat, nat>>(new ComparacionTupla<nat>()));
	solucionActual->InsertarOrdenado(Tupla<nat, nat>(inicio.ObtenerDato1(), inicio.ObtenerDato2()));

	if (inicio == fin)
	{
		return solucionActual->ObtenerIterador();
	}

	Puntero<ListaOrdArray<Tupla<nat, nat>>> solucion = new ListaOrdArray<Tupla<nat, nat>>();

	int cambiosDireccionMin = INFINITO;

	laberinto[inicio.ObtenerDato1()][inicio.ObtenerDato2()] = 0;

	Array<int> movX = Array<int>(4);
	Array<int> movY = Array<int>(4);

	movX[0] = 0; movX[1] = 0; movX[2] = 1; movX[3] = -1;
	movY[0] = 1; movY[1] = -1; movY[2] = 0; movY[3] = 0;

	LaberintoBT(laberinto, fin, movX, movY,
		solucion, cambiosDireccionMin,
		solucionActual, 0, Tupla<int, int>(-2, -2), inicio);

	if (solucion->Largo() == 1)
	{
		return NULL;
	}

	return solucion->ObtenerIterador();
};

void Sistema::LaberintoBT(Matriz<nat>& laberinto, Tupla<nat, nat>& fin, Array<int> movX, Array<int> movY,
	Puntero<ListaOrdArray<Tupla<nat, nat>>>& solucion, int& cambiosDireccionMin,
	Puntero<ListaOrdArray<Tupla<nat, nat>>> solucionActual, int cambiosDireccionActual, Tupla<int, int> ultimoCambio, Tupla<nat, nat> actual)
{
	if (cambiosDireccionActual < cambiosDireccionMin)
	{
		if (actual == fin)
		{
			solucion = solucionActual->Clon();
			cambiosDireccionMin = cambiosDireccionActual;
		}
		else
		{
			for (int i = 0; i < 4; i++)
			{
				int x = actual.ObtenerDato1() + movX[i];
				int y = actual.ObtenerDato2() + movY[i];

				if (CoordenadaValida(x, y, laberinto))
				{
					Tupla<int, int> cambioActual(movX[i], movY[i]);

					Matriz<nat> copia = ClonarMatriz(laberinto);
					copia[x][y] = 0;

					solucionActual->InsertarOrdenado(Tupla<nat, nat>(x, y));

					if (ultimoCambio != cambioActual && ultimoCambio.ObtenerDato1() != -2)
					{
						LaberintoBT(copia, fin, movX, movY,
							solucion, cambiosDireccionMin,
							solucionActual, cambiosDireccionActual + 1, cambioActual, Tupla<nat, nat>(x, y));
					}
					else
					{
						LaberintoBT(copia, fin, movX, movY,
							solucion, cambiosDireccionMin,
							solucionActual, cambiosDireccionActual, cambioActual, Tupla<nat, nat>(x, y));
					}

					solucionActual->EliminarUltimo();
				}
			}
		}
	}
};

Matriz<nat> Sistema::ClonarMatriz(const Matriz<nat>& mat)
{
	Matriz<nat> ret = Matriz<nat>(mat.ObtenerLargo(), mat.ObtenerAncho());

	for (nat i = 0; i < mat.ObtenerLargo(); i++)
	{
		for (nat j = 0; j < mat.ObtenerAncho(); j++)
		{
			ret[i][j] = mat[i][j];
		}
	}

	return ret;
};

bool Sistema::CoordenadaValida(int x, int y, Matriz<nat> laberinto)
{
	return x >= 0 && y >= 0 && x < (int)laberinto.ObtenerLargo() && y < (int)laberinto.ObtenerAncho() && laberinto[x][y] == 1;
};

// EJERCICIO 2 - Backtracking - Recursivo

Iterador<Iterador<Puntero<ICiudad>>> Sistema::Viajero(Array<Puntero<ICiudad>> &ciudadesDelMapa, Matriz<nat> &mapa, Puntero<ICiudad> &ciudadPartida, Iterador<Puntero<ICiudad>> &ciudadesPasar, nat costoMax)
{
	Puntero<ListaOrdArray<Iterador<Puntero<ICiudad>>>> soluciones = new ListaOrdArray<Iterador<Puntero<ICiudad>>>();
	Puntero<ListaOrdArray<Puntero<ICiudad>>> caminoActual = new ListaOrdArray<Puntero<ICiudad>>(Comparador<Puntero<ICiudad>>(new ComparacionICiudad()));

	caminoActual->InsertarOrdenado(ciudadPartida);

	int costo = costoMax;
	int ciudades = INFINITO;
	
	ViajeroBT(ciudadesDelMapa, mapa, ciudadPartida, ciudadesPasar,
		soluciones, costo, ciudades,
		caminoActual, 0, 0, ciudadPartida);

	return soluciones->ObtenerIterador();
};

void Sistema::ViajeroBT(Array<Puntero<ICiudad>>& ciudadesDelMapa, Matriz<nat>& mapa, Puntero<ICiudad>& ciudadPartida, Iterador<Puntero<ICiudad>>& ciudadesPasar,
	Puntero<ListaOrdArray<Iterador<Puntero<ICiudad>>>>& soluciones, int& mejorCosto, int& menorCantCiudades,
	Puntero<ListaOrdArray<Puntero<ICiudad>>> caminoActual, int costoActual, int cantidadCiudades, Puntero<ICiudad> ciudadActual)
{
	if (costoActual <= mejorCosto)
	{
		if (ciudadPartida == ciudadActual && PasaPorTodos(ciudadesPasar, caminoActual))
		{
			if (costoActual < mejorCosto || (costoActual == mejorCosto && cantidadCiudades < menorCantCiudades))
			{
				soluciones = new ListaOrdArray<Iterador<Puntero<ICiudad>>>();

				Puntero<ListaOrdArray<Puntero<ICiudad>>> aInsertar = caminoActual->Clon();
				aInsertar->EliminarUltimo();

				soluciones->InsertarOrdenado(aInsertar->ObtenerIterador());

				mejorCosto = costoActual;
				menorCantCiudades = cantidadCiudades;
			}
			else if (cantidadCiudades == menorCantCiudades)
			{
				Puntero<ListaOrdArray<Puntero<ICiudad>>> aInsertar = caminoActual->Clon();
				aInsertar->EliminarUltimo();

				soluciones->InsertarOrdenado(aInsertar->ObtenerIterador());
			}
		}
		else 
		{
			nat columna = 0;
			nat posActual = ObtenerPosCiudad(ciudadesDelMapa, ciudadActual);

			while (columna < mapa.ObtenerAncho())
			{
				if (mapa[posActual][columna] != 0)
				{
					caminoActual->InsertarOrdenado(ciudadesDelMapa[columna]);

					ViajeroBT(ciudadesDelMapa, mapa, ciudadPartida, ciudadesPasar,
						soluciones, mejorCosto, menorCantCiudades,
						caminoActual, costoActual + mapa[posActual][columna], cantidadCiudades + 1, ciudadesDelMapa[columna]);

					caminoActual->EliminarUltimo();
				}
				columna++;
			}
		}
	}
};

bool Sistema::PasaPorTodos(Iterador<Puntero<ICiudad>> &ciudadesPasar, Puntero<ListaOrdArray<Puntero<ICiudad>>>& caminoActual)
{
	ciudadesPasar.Reiniciar();
	Iterador<Puntero<ICiudad>> it = caminoActual->ObtenerIterador();
	it.Reiniciar();

	while (ciudadesPasar.HayElemento())
	{
		bool pertenece = false;

		while (it.HayElemento())
		{
			if (it.ElementoActual() == ciudadesPasar.ElementoActual())
				pertenece = true;

			it.Avanzar();
		}

		if (!pertenece)
			return false;

		it.Reiniciar();
		ciudadesPasar.Avanzar();
	}

	return true;
};

nat Sistema::ObtenerPosCiudad(Array<Puntero<ICiudad>> &ciudadesDelMapa, Puntero<ICiudad> ciudadActual)
{
	for (nat i = 0; i < ciudadesDelMapa.ObtenerLargo(); i++)
	{
		if (ciudadesDelMapa[i] == ciudadActual)
			return i;
	}

	return -1;
};

// EJERCICIO 3 - Divide & Conquer - Iterativo

Array<nat> Sistema::Intercalar(Array<nat> &arreglo, nat i, nat m, nat d)
{
	Array<nat> intercalado(arreglo.ObtenerLargo());
	intercalado.Copiar(arreglo, intercalado);

	nat pos = 0;

	while (pos < i)
	{
		intercalado[pos] = arreglo[pos];
		pos++;
	}

	nat posIzq = pos;
	nat posDer = m + 1;

	while (posIzq <= m && posDer <= d)
	{
		if (arreglo[posIzq] < arreglo[posDer])
		{
			intercalado[pos] = arreglo[posIzq];
			posIzq++;
			pos++;
		}
		else
		{
			intercalado[pos] = arreglo[posDer];
			posDer++;
			pos++;
		}
	}

	while (posIzq <= m)
	{
		intercalado[pos] = arreglo[posIzq];
		posIzq++;
		pos++;
	}

	while (posDer <= d)
	{
		intercalado[pos] = arreglo[posDer];
		posDer++;
		pos++;
	}

	return intercalado;
};

// EJERCICIO 4 - Backtracking - Recursivo

Array<nat> Sistema::Degustacion(Array<Producto> productos, nat maxDinero, nat maxCalorias, nat maxAlcohol)
{
	Array<nat> solucion = Array<nat>(productos.ObtenerLargo());
	Array<nat> solucionActual = Array<nat>(productos.ObtenerLargo());

	nat preferenciaMax = 0;

	DegustacionBT(productos, 0,
		solucion, preferenciaMax, maxDinero, maxCalorias, maxAlcohol,
		solucionActual, 0, 0, 0, 0);

	return solucion;
};

void Sistema::DegustacionBT(Array<Producto>& productos, nat actual,
	Array<nat>& solucion, nat& preferenciaMax, nat& dineroMax, nat& caloriasMax, nat& alcoholMax,
	Array<nat> solucionActual, nat preferenciaActual, nat dineroActual, nat caloriasActual, nat alcoholActual)
{
	if (dineroActual < dineroMax && caloriasActual < caloriasMax && alcoholActual < alcoholMax)
	{
		if (preferenciaActual > preferenciaMax)
		{
			solucion.Copiar(solucionActual, solucion);
			preferenciaMax = preferenciaActual;
		}

		if (actual < productos.ObtenerLargo())
		{
			for (nat i = 0; i <= productos[actual].maxUnidades; i++)
			{
				solucionActual[actual] = i;

				DegustacionBT(productos, actual + 1,
					solucion, preferenciaMax, dineroMax, caloriasMax, alcoholMax,
					solucionActual, preferenciaActual + i*productos[actual].preferencia, dineroActual + i*productos[actual].precio, caloriasActual + i*productos[actual].calorias, alcoholActual + i*productos[actual].alcohol);

				solucionActual[actual] = 0;
			}
		}
	}
};

// EJERCICIO 5

Tupla<TipoRetorno, Iterador<nat>> Sistema::Viajero2(Matriz<Tupla<nat, nat, nat>> relacionesCiudades, Iterador<nat> CiudadesPasar, Iterador<nat> CiudadesNoPasar)
{
	Puntero<ListaOrdArray<nat>> solucion = new ListaOrdArray<nat>(Comparador<nat>(new ComparacionNat()));

	return Tupla<TipoRetorno, Iterador<nat>>(NO_IMPLEMENTADA, solucion->ObtenerIterador());
};

// EJERCICIO 6 - Backtracking - Recursivo

Tupla<TipoRetorno, Array<nat>> Sistema::ProteccionAnimales(Array<Accion> acciones, nat maxVeterinarios, nat maxVehiculos, nat maxDinero, nat maxVacunas, nat maxVoluntarios)
{
	Array<nat> solucion = Array<nat>(acciones.ObtenerLargo());
	Array<nat> solucionActual = Array<nat>(acciones.ObtenerLargo());

	nat maxImpacto = 0;

	ProteccionAnimalesBT(acciones, 0,
		solucion, maxVeterinarios, maxVehiculos, maxDinero, maxVacunas, maxVoluntarios, maxImpacto,
		solucionActual, 0, 0, 0, 0, 0, 0);

	return Tupla<TipoRetorno, Array<nat>>(OK, solucion);
};

void Sistema::ProteccionAnimalesBT(Array<Accion>& acciones, nat actual,
	Array<nat>& solucion, nat& veterinariosMax, nat& vehiculosMax, nat& dineroMax, nat& vacunasMax, nat& voluntariosMax, nat& impactoMax,
	Array<nat> solucionActual, nat veterinariosActual, nat vehiculosActual, nat dineroActual, nat vacunasActual, nat voluntariosActual, nat impactoActual)
{
	if (veterinariosActual <= veterinariosMax && vehiculosActual <= vehiculosMax && dineroActual <= dineroMax && vacunasActual <= vacunasMax && voluntariosActual <= voluntariosMax)
	{
		if (impactoActual > impactoMax)
		{
			solucion.Copiar(solucionActual, solucion);
			impactoMax = impactoActual;
		}

		if (actual < acciones.ObtenerLargo())
		{
			nat vetMax = (veterinariosMax / acciones[actual].veterinarios) + 1;
			nat vehMax = (vehiculosMax / acciones[actual].vehiculos) + 1;
			nat dinMax = (dineroMax / acciones[actual].dinero) + 1;
			nat vacMax = (vacunasMax / acciones[actual].vacunas) + 1;
			nat volMax = (voluntariosMax / acciones[actual].voluntarios) + 1;

			for (nat i = 0; (i < vetMax) && (i < vehMax) && (i < dinMax) && (i < vacMax) && (i < volMax); i++)
			{
				solucionActual[actual] = i;

				ProteccionAnimalesBT(acciones, actual + 1,
					solucion, veterinariosMax, vehiculosMax, dineroMax, vacunasMax, voluntariosMax, impactoMax,
					solucionActual, veterinariosActual + i*acciones[actual].veterinarios, vehiculosActual + i*acciones[actual].vehiculos, dineroActual + i*acciones[actual].dinero, vacunasActual + i* acciones[actual].vacunas, voluntariosActual + i*acciones[actual].voluntarios, impactoActual + i*acciones[actual].impacto);

				solucionActual[actual] = 0;
			}
		}
	}
};

// EJERCICIO 7 - Divide & Conquer - Recursivo

Array<nat> Sistema::QuickSort(Array<nat> elementos)
{
	QuickSortDC(elementos, 0, elementos.ObtenerLargo() - 1);

	return elementos;
};

void Sistema::QuickSortDC(Array<nat> elementos, nat inicio, nat fin)
{
	if (inicio < fin)
	{
		nat posPivot = ReOrdenar(elementos, inicio, fin);

		QuickSortDC(elementos, inicio, posPivot);
		QuickSortDC(elementos, posPivot + 1, fin);
	}
};

nat Sistema::ReOrdenar(Array<nat> elementos, nat inicio, nat fin)
{
	nat izq;
	nat der;
	nat pivot;
	nat temp;

	pivot = elementos[inicio];
	izq = inicio;
	der = fin;

	while (izq < der)
	{
		while (elementos[der] > pivot)
		{
			der--;
		}

		while ((izq < der) && (elementos[izq] <= pivot))
		{
			izq++;
		}

		if (izq < der)
		{
			temp = elementos[izq];
			elementos[izq] = elementos[der];
			elementos[der] = temp;
		}
	}

	temp = elementos[der];
	elementos[der] = elementos[inicio];
	elementos[inicio] = temp;

	return der;
};

// EJERCICIO 8 - Backtracking - Recursivo

const nat ORIGEN = 1;
const nat DESTINO = 2;
const nat NEUTRO = 3;
const nat PASAR = 4;
const nat NO_PASAR = 5;
const nat ORIGEN_Y_PASAR = 6;
const nat DESTINO_Y_PASAR = 7;

Tupla<TipoRetorno, Iterador<Iterador<Tupla<int, int>>>> Sistema::CaminoCaballo(Tupla<int, int>& salida, Tupla<int, int>& destino, nat cantAPasar, nat tamTablero, Iterador<Tupla<int, int>>& pasar, Iterador<Tupla<int, int>>& noPasar)
{
	Matriz<nat> tablero = InitMatrizCaminoCaballo(tamTablero, salida, destino, pasar, noPasar);

	Puntero<ListaOrdArray<Iterador<Tupla<int, int>>>> soluciones = new ListaOrdArray<Iterador<Tupla<int, int>>>();
	Puntero<ListaOrdArray<Tupla<int, int>>> solActual = new ListaOrdArray<Tupla<int, int>>(Comparador<Tupla<int, int>>(new ComparacionTupla<int>()));

	solActual->InsertarOrdenado(salida);

	nat cantMovimientosMin = INFINITO;

	Array<int> movX = InitMovXCaballo();
	Array<int> movY = InitMovYCaballo();

	CaminoCaballoBT(salida, Tupla<int, int>(-1, -1), tablero, movX, movY,
		soluciones, cantAPasar, cantMovimientosMin,
		solActual, 0, 0);

	return Tupla<TipoRetorno, Iterador<Iterador<Tupla<int, int>>>>(OK, soluciones->ObtenerIterador());
};

void Sistema::CaminoCaballoBT(Tupla<int, int> actual, Tupla<int, int> anterior, Matriz<nat>& tablero, Array<int>& movX, Array<int>& movY,
	Puntero<ListaOrdArray<Iterador<Tupla<int, int>>>>& soluciones, nat& cantAPasar, nat& cantMovimientosMin,
	Puntero<ListaOrdArray<Tupla<int, int>>> solActual, nat cantAPasarActual, nat cantMovimientosActual)
{
	if (cantMovimientosActual <= cantMovimientosMin)
	{
		int f = actual.ObtenerDato1();
		int c = actual.ObtenerDato2();

		if ((tablero[f][c] == DESTINO || tablero[f][c] == DESTINO_Y_PASAR) && cantAPasarActual >= cantAPasar)
		{
			if (cantMovimientosActual < cantMovimientosMin)
			{
				soluciones = new ListaOrdArray<Iterador<Tupla<int, int>>>();
				cantMovimientosMin = cantMovimientosActual;
			}

			soluciones->InsertarOrdenado(solActual->Clon()->ObtenerIterador());
		}
		else
		{
			for (nat i = 0; i < movX.ObtenerLargo(); i++)
			{
				int nuevoX = f + movX[i];
				int nuevoY = c + movY[i];

				Tupla<int, int> mov = Tupla<int, int>(nuevoX, nuevoY);

				if (PerteneceAlTablero(nuevoX, nuevoY, tablero.ObtenerLargo()) && !solActual->Pertenece(mov) && tablero[nuevoX][nuevoY] != NO_PASAR)
				{
					solActual->InsertarOrdenado(mov);

					if (tablero[nuevoX][nuevoY] == PASAR || tablero[nuevoX][nuevoY] == DESTINO_Y_PASAR || tablero[nuevoX][nuevoY] == ORIGEN_Y_PASAR)
					{
						CaminoCaballoBT(mov, Tupla<int, int>(f, c), tablero, movX, movY,
							soluciones, cantAPasar, cantMovimientosMin,
							solActual, cantAPasarActual + 1, cantMovimientosActual + 1);
					}
					else
					{
						CaminoCaballoBT(mov, Tupla<int, int>(f, c), tablero, movX, movY,
							soluciones, cantAPasar, cantMovimientosMin,
							solActual, cantAPasarActual, cantMovimientosActual + 1);
					}

					solActual->EliminarUltimo();
				}
			}
		}
	}
};

Matriz<nat> Sistema::InitMatrizCaminoCaballo(nat tamTablero, Tupla<int, int>& salida, Tupla<int, int>& destino, Iterador<Tupla<int, int>>& pasar, Iterador<Tupla<int, int>>& noPasar)
{
	Matriz<nat> tablero (tamTablero);

	for (nat f = 0; f < tamTablero; f++)
	{
		for (nat c = 0; c < tamTablero; c++)
		{
			tablero[f][c] = NEUTRO;
		}
	}

	tablero[salida.ObtenerDato1()][salida.ObtenerDato2()] = ORIGEN;
	tablero[destino.ObtenerDato1()][destino.ObtenerDato2()] = DESTINO;

	pasar.Reiniciar();
	noPasar.Reiniciar();

	while (pasar.HayElemento())
	{
		Tupla<int,int> elementoActual = pasar.ElementoActual();

		if (tablero[elementoActual.ObtenerDato1()][elementoActual.ObtenerDato2()] == ORIGEN)
		{
			tablero[elementoActual.ObtenerDato1()][elementoActual.ObtenerDato2()] = ORIGEN_Y_PASAR;
		}
		else if (tablero[elementoActual.ObtenerDato1()][elementoActual.ObtenerDato2()] == DESTINO)
		{
			tablero[elementoActual.ObtenerDato1()][elementoActual.ObtenerDato2()] = DESTINO_Y_PASAR;
		}
		else
		{
			tablero[elementoActual.ObtenerDato1()][elementoActual.ObtenerDato2()] = PASAR;
		}

		pasar.Avanzar();
	}

	while (noPasar.HayElemento())
	{
		Tupla<int, int> elementoActual = noPasar.ElementoActual();

		tablero[elementoActual.ObtenerDato1()][elementoActual.ObtenerDato2()] = NO_PASAR;

		noPasar.Avanzar();
	}

	return tablero;
};

Array<int> Sistema::InitMovXCaballo()
{
	Array<int> movX = Array<int>(8);
	
	movX[0] = 2;
	movX[1] = 1;
	movX[2] = -2;
	movX[3] = -2;
	movX[4] = -1;
	movX[5] = 1;
	movX[6] = 2;
	movX[7] = -1;

	return movX;
};

Array<int> Sistema::InitMovYCaballo()
{
	Array<int> movY = Array<int>(8);

	movY[0] = 1;
	movY[1] = -2;
	movY[2] = -1;
	movY[3] = 1;
	movY[4] = 2;
	movY[5] = 2;
	movY[6] = -1;
	movY[7] = -2;

	return movY;
};

Matriz<nat> Sistema::ClonarTablero(Matriz<nat> tablero)
{
	int largo = tablero.ObtenerLargo();

	Matriz<nat> clon = Matriz<nat>(largo);

	for (int f = 0; f < largo; f++)
	{
		for (int c = 0; c < largo; c++)
		{
			clon[f][c] = tablero[f][c];
		}
	}

	return clon;
};

bool Sistema::PerteneceAlTablero(int x, int y, int largo)
{
	return (x >= 0 && x < largo) && (y >= 0 && y < largo);
};

// EJERCICIO 9 - Backtracking - Recursivo

Tupla<TipoRetorno, Array<nat>> Sistema::OptimizarGranja(Array<Tupla<nat, nat, nat>>& semillas, nat dinero, nat tierra, nat agua)
{
	Array<nat> solucion(semillas.ObtenerLargo());

	nat gananciaMax = 0;

	OptimizarGranjaBT(semillas,
		dinero, tierra, agua, gananciaMax, solucion,
		0, 0, 0, 0, Array<nat>(semillas.ObtenerLargo()), 0);

	return Tupla<TipoRetorno, Array<nat>>(OK, solucion);
};

void Sistema::OptimizarGranjaBT(Array<Tupla<nat, nat, nat>>& semillas,
	nat& dinero, nat& tierra, nat& agua, nat& gananciaMax, Array<nat>& solucion,
	nat dineroActual, nat tierraActual, nat aguaActual, nat gananciaActual, Array<nat> solucionActual, nat actual)
{
	if (dinero >= dineroActual && tierra >= tierraActual && agua >= aguaActual)
	{
		if (gananciaMax < gananciaActual)
		{
			solucion.Copiar(solucionActual, solucion);
			gananciaMax = gananciaActual;
		}

		if (actual < semillas.ObtenerLargo())
		{
			nat dineroMax = (dinero / semillas[actual].ObtenerDato1()) + 1;
			nat aguaMax = (agua / semillas[actual].ObtenerDato2()) + 1;

			for (nat i = 0; (i < dineroMax) && (i < aguaMax); i++)
			{
				solucionActual[actual] = i;

				OptimizarGranjaBT(semillas,
					dinero, tierra, agua, gananciaMax, solucion,
					dineroActual + i*semillas[actual].ObtenerDato1(), tierraActual + i, aguaActual + i*semillas[actual].ObtenerDato2(), gananciaActual + i*semillas[actual].ObtenerDato3(), solucionActual, actual + 1);

				solucionActual[actual] = 0;
			}
		}
	}
};

// EJERCICIO 10 - Backtracking - Recursivo

Tupla<TipoRetorno, Iterador<Tupla<Cadena, bool>>> Sistema::InscribirMaterias(Iterador<Tupla<Cadena, nat, nat>> matutino, Iterador<Tupla<Cadena, nat, nat>> nocturno, nat horasM, nat horasN)
{
	Comparador<Tupla<Cadena, bool>> comp = Comparador<Tupla<Cadena, bool>>(new ComparacionMaterias());

	Puntero<ListaOrdArray<Tupla<Cadena, bool>>> solucion = new ListaOrdArray<Tupla<Cadena, bool>>(comp);
	Puntero<ListaOrdArray<Tupla<Cadena, bool>>> actualSolucion = new ListaOrdArray<Tupla<Cadena, bool>>(comp);

	Puntero<ListaOrdArray<Tupla<Cadena, nat, nat>>> listaMatutino = new ListaOrdArray<Tupla<Cadena, nat, nat>>();
	Puntero<ListaOrdArray<Tupla<Cadena, nat, nat>>> listaNocturno = new ListaOrdArray<Tupla<Cadena, nat, nat>>();

	matutino.Reiniciar();
	nocturno.Reiniciar();

	while (matutino.HayElemento())
	{
		Tupla<Cadena, nat, nat> curso = matutino.ElementoActual();
		listaMatutino->InsertarOrdenado(curso);
		matutino.Avanzar();
	}

	while (nocturno.HayElemento())
	{
		Tupla<Cadena, nat, nat> curso = nocturno.ElementoActual();
		listaNocturno->InsertarOrdenado(curso);
		nocturno.Avanzar();
	}

	nat maxCreditos = 0;

	InscribirMateriasBT(listaMatutino, listaNocturno,
		solucion, horasM, horasN, maxCreditos,
		actualSolucion, 0, 0, 0);

	return Tupla<TipoRetorno, Iterador<Tupla<Cadena, bool>>>(OK, solucion->ObtenerIterador());
};

void Sistema::InscribirMateriasBT(Puntero<ListaOrdArray<Tupla<Cadena, nat, nat>>> matutino, Puntero<ListaOrdArray<Tupla<Cadena, nat, nat>>> nocturno,
	Puntero<ListaOrdArray<Tupla<Cadena, bool>>>& solucion, nat maxHorasM, nat maxHorasN, nat& maxCreditos,
	Puntero<ListaOrdArray<Tupla<Cadena, bool>>>& actualSolucion, nat actualHorasM, nat actualHorasN, nat actualCreditos)
{
	if (actualHorasM <= maxHorasM && actualHorasN <= maxHorasN)
	{
		if (maxCreditos < actualCreditos)
		{
			solucion = actualSolucion->Clon();
			maxCreditos = actualCreditos;
		}
	}

	for (nat i = 0; i < matutino->Largo(); i++)
	{
		Tupla<Cadena, nat, nat> materiaActual = matutino->Obtener(i);

		if (!actualSolucion->Pertenece(Tupla<Cadena, bool>(materiaActual.ObtenerDato1(), true)))
		{
			actualSolucion->InsertarOrdenado(Tupla<Cadena, bool>(materiaActual.ObtenerDato1(), true));

			InscribirMateriasBT(matutino, nocturno,
				solucion, maxHorasM, maxHorasN, maxCreditos,
				actualSolucion, actualHorasM + materiaActual.ObtenerDato3(), actualHorasN, actualCreditos + materiaActual.ObtenerDato2());

			actualSolucion->Eliminar(Tupla<Cadena, bool>(materiaActual.ObtenerDato1(), true));
		}
	}

	for (nat i = 0; i < nocturno->Largo(); i++)
	{
		Tupla<Cadena, nat, nat> materiaActual = nocturno->Obtener(i);

		if (!actualSolucion->Pertenece(Tupla<Cadena, bool>(materiaActual.ObtenerDato1(), false)))
		{
			actualSolucion->InsertarOrdenado(Tupla<Cadena, bool>(materiaActual.ObtenerDato1(), false));

			InscribirMateriasBT(matutino, nocturno,
				solucion, maxHorasM, maxHorasN, maxCreditos,
				actualSolucion, actualHorasM, actualHorasN + materiaActual.ObtenerDato3(), actualCreditos + materiaActual.ObtenerDato2());

			actualSolucion->Eliminar(Tupla<Cadena, bool>(materiaActual.ObtenerDato1(), false));
		}
	}
};