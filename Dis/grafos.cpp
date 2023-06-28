#include <iostream>
#include <vector>
#include <climits>
#include <time.h>
#include <algorithm>

using namespace std;

class Arista
{
public:
    int origen;
    int destino;
    int costo;

    Arista(int origen, int destino, int costo)
    {
        this->origen = origen;
        this->destino = destino;
        this->costo = costo;
    }
};

class Conexiones
{
private:
    vector<Arista *> aristas;

public:
    int buscarCosto(int origen, int destino)
    {
        for (Arista *arista : aristas)
        {
            if (arista->origen == origen && arista->destino == destino)
            {
                return arista->costo;
            }
        }
        return 0;
    }

    void agregarArista(int idOrigen, int idDestino, int costo)
    {
        Arista *arista = new Arista(idOrigen, idDestino, costo);
        aristas.push_back(arista);
    }

    void imprimirAristas()
    {
        cout << "Aristas: " << endl;
        for (Arista *arista : aristas)
        {
            cout << "Desde: " << arista->origen << " Hasta: " << arista->destino << " Costo: " << arista->costo << endl;
        }
    }
};

class Ciudad
{
public:
    int id;
    int valor;
    bool puerto;
    Ciudad *anc;

    vector<Ciudad *> adyacentes;

    Ciudad(int id, int valor, bool puerto, Ciudad *anc)
    {
        this->id = id;
        this->valor = valor;
        this->puerto = puerto;
        this->anc = anc;
    }
};

class GrafoCiudades
{
private:
    vector<Ciudad *> ciudades;

public:
    Ciudad *buscarCiudad(int id)
    {
        for (Ciudad *ciudad : ciudades)
        {
            if (ciudad->id == id)
            {
                return ciudad;
            }
        }
        return nullptr;
    }

    void agregarCiudad(int id, int val, bool puerto, Ciudad *anc)
    {
        if (buscarCiudad(id) == nullptr)
        {
            Ciudad *ciudad = new Ciudad(id, val, puerto, anc);
            ciudades.push_back(ciudad);
        }
    }

    int cantidadCiudades()
    {
        return ciudades.size();
    }

    void agregarPuerto(int id)
    {
        buscarCiudad(id)->puerto = true;
    }
};

bool comparadorMayorMenor(Ciudad *a, Ciudad *b)
{
    return a->valor > b->valor;
}

GrafoCiudades dijkstraDirigido(GrafoCiudades grafo, Conexiones costos, int n, int s)
{
    GrafoCiudades min;
    grafo.buscarCiudad(s)->valor = 0;

    vector<Ciudad *> distOrdenadas;

    for (int i = 1; i <= n; i++)
    {
        Ciudad *c = grafo.buscarCiudad(i);
        distOrdenadas.push_back(c);
    }

    sort(distOrdenadas.begin(), distOrdenadas.end(), comparadorMayorMenor);

    while (distOrdenadas.size() != 0)
    {
        Ciudad *u = distOrdenadas.back();
        distOrdenadas.pop_back();

        min.agregarCiudad(u->id, u->valor, u->puerto, u->anc);

        for (Ciudad *v : u->adyacentes)
        {
            if (v->valor > u->valor + costos.buscarCosto(u->id, v->id))
            {
                v->valor = u->valor + costos.buscarCosto(u->id, v->id);
                v->anc = u;
                distOrdenadas.push_back(v);
                sort(distOrdenadas.begin(), distOrdenadas.end(), comparadorMayorMenor);
            }
        }
    }

    return min;
}

void imprimirMin(GrafoCiudades min)
{
    cout << endl;
    cout << "Ciudades: " << endl;
    cout << "Caminos: " << endl;
    for (int i = 1; i <= min.cantidadCiudades(); i++)
    {
        if (min.buscarCiudad(i)->anc != nullptr)
        {
            cout << "Ciudad: " << min.buscarCiudad(i)->id << " Ancestro: " << min.buscarCiudad(i)->anc->id << endl;
        }
        else
        {
            cout << "Ciudad: " << min.buscarCiudad(i)->id << " Ancestro: "<< "No tiene" << endl;
        }
    }
}

class Isla
{
public:
    int id;
    int valor;
    bool puerto;
    bool visitado;
    Isla *anc;

    vector<Isla *> adyacentes;

    Isla(int id, int valor, bool puerto, bool visitado, Isla *anc)
    {
        this->id = id;
        this->valor = valor;
        this->puerto = puerto;
        this->visitado = visitado;
        this->anc = anc;
    }
};

class GrafoIslas
{
private:
    vector<Isla *> islas;

public:
    Isla *buscarIsla(int id)
    {
        for (Isla *isla : islas)
        {
            if (isla->id == id)
            {
                return isla;
            }
        }
        return nullptr;
    }

    void agregarIsla(int id, int val, bool puerto, bool visitado, Isla *anc)
    {
        if (buscarIsla(id) == nullptr)
        {
            Isla *isla = new Isla(id, val, puerto, visitado, anc);
            islas.push_back(isla);
        }
    }

    int cantidadIslas()
    {
        return islas.size();
    }

    void agregarPuerto(int id)
    {
        buscarIsla(id)->puerto = true;
    }
};

bool comparadorMaMe(Isla *a, Isla *b)
{
    return a->valor > b->valor;
}

GrafoIslas dijkstraNoDirigido(GrafoIslas archi, Conexiones costos, int m, int s)
{
    GrafoIslas min;

    archi.buscarIsla(s)->valor = 0;

    vector<Isla *> distOrdenadas;

    for (int i = 1; i <= m; i++)
    {
        Isla *c = archi.buscarIsla(i);
        distOrdenadas.push_back(c);
    }

    sort(distOrdenadas.begin(), distOrdenadas.end(), comparadorMaMe);

    while (distOrdenadas.size() != 0)
    {
        Isla *u = distOrdenadas.back();
        distOrdenadas.pop_back();

        if (u->visitado)
        {
            continue;
        }

        u->visitado = true;

        min.agregarIsla(u->id, u->valor, u->puerto, u->visitado, u->anc);

        for (Isla *v : u->adyacentes)
        {
            if (!v->visitado && v->valor > u->valor + costos.buscarCosto(u->id, v->id))
            {
                v->valor = u->valor + costos.buscarCosto(u->id, v->id);
                v->anc = u;
                distOrdenadas.push_back(v);
                sort(distOrdenadas.begin(), distOrdenadas.end(), comparadorMaMe);
            }
        }
    }

    return min;
}

void imprimirMinimo(GrafoIslas min)
{
    cout << endl;
    cout << "Islas: " << endl;
    cout << "Caminos (Puerto 3): " << endl;
    for (int i = 1; i <= min.cantidadIslas(); i++)
    {
        if (min.buscarIsla(i)->anc != nullptr)
        {
            cout << "Ciudad: " << min.buscarIsla(i)->id << " Ancestro: " << min.buscarIsla(i)->anc->id << endl;
        }
        else
        {
            cout << "Ciudad: " << min.buscarIsla(i)->id << " Ancestro: "
                 << "No tiene" << endl;
        }
    }
}

main(int argc, char **argv)
{
    if (argc != 4)
    {
        cout << "Error. Debe ejecutarse como ./problema n k p" << endl;
        exit(EXIT_FAILURE);
    }

    int n = atoi(argv[1]);
    int s = atoi(argv[2]);
    int m = atoi(argv[3]);

    GrafoCiudades grafo;
    GrafoIslas archi;
    Conexiones costos;
    Conexiones costosIslas;

    srand(time(NULL));

    for (int i = 1; i <= n; i++)
    {
        grafo.agregarCiudad(i, INT_MAX, false, nullptr);
    }

    for (int i = 1; i <= m; i++)
    {
        archi.agregarIsla(i, INT_MAX, false, false, nullptr);
    }

    costos.agregarArista(1, 2, 10);
    costos.agregarArista(1, 3, 5);
    costos.agregarArista(2, 4, 1);
    costos.agregarArista(2, 3, 2);
    costos.agregarArista(3, 2, 3);
    costos.agregarArista(3, 4, 9);
    costos.agregarArista(3, 5, 2);
    costos.agregarArista(4, 5, 4);
    costos.agregarArista(5, 1, 7);
    costos.agregarArista(5, 4, 6);

    grafo.agregarPuerto(3);
    grafo.agregarPuerto(4);

    costosIslas.agregarArista(1, 2, 10);
    costosIslas.agregarArista(1, 3, 5);
    costosIslas.agregarArista(2, 4, 1);
    costosIslas.agregarArista(2, 3, 2);
    costosIslas.agregarArista(3, 4, 9);
    costosIslas.agregarArista(3, 5, 2);
    costosIslas.agregarArista(5, 1, 7);
    costosIslas.agregarArista(5, 4, 6);

    archi.agregarPuerto(3);
    archi.agregarPuerto(4);

    for (int z = 1; z <= grafo.cantidadCiudades(); z++)
    {
        for (int k = 1; k <= grafo.cantidadCiudades(); k++)
        {
            if (costos.buscarCosto(z, k) > 0)
            {
                grafo.buscarCiudad(z)->adyacentes.push_back(grafo.buscarCiudad(k));
            }
        }
    }

    for (int z = 1; z <= archi.cantidadIslas(); z++)
    {
        for (int k = 1; k <= archi.cantidadIslas(); k++)
        {
            if (costosIslas.buscarCosto(z, k) > 0 || costosIslas.buscarCosto(k, z) > 0)
            {
                archi.buscarIsla(z)->adyacentes.push_back(archi.buscarIsla(k));
            }
        }
    }

    cout << "Ciudades: " << endl;
    costos.imprimirAristas();

    cout << endl;
    cout << "Islas: " << endl;
    costosIslas.imprimirAristas();

    GrafoCiudades min = dijkstraDirigido(grafo, costos, n, s);
    GrafoIslas minIs = dijkstraNoDirigido(archi, costosIslas, m, 3);

    imprimirMin(min);

    imprimirMinimo(minIs);

    return 0;
}
