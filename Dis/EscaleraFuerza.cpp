#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <climits>
using namespace std;

float generaEnteros(int *E, int n, int k, vector<int> &Rotos, int p, vector<int> &Saltos)
{
    for (int i = 1; i <= (n + 1); i++)
    {
        E[i] = i;
    }

    for (int j = 1; j <= k; j++)
    {
        int a = rand() % n;
        if (E[a] != 0)
        {
            E[a] = 0;
            Rotos.push_back(a);
        }
        else
        {
            j--;
        }
    }
    for (int h = 1; h <= n; h *= p)
    {
        Saltos.push_back(h);
    }

    return 0;
}

void printArray(int *E, int n, vector<int> &Rotos, int k, vector<int> &Saltos)
{
    cout << "E = ";
    for (int i = 1; i < (n + 1); i++)
        cout << E[i] << " ";
    cout << endl;

    cout << "Rotos = ";
    for (int j = 0; j < k; j++)
        cout << Rotos[j] << " ";
    cout << endl;
    cout << "Saltos = ";
    for (int h = 0; h < Saltos.size(); h++)
        cout << Saltos[h] << " ";
    cout << endl;
}

bool esEscalonRoto(int escalon, const vector<int> &Rotos)
{
    for (int escalonRoto : Rotos)
    {
        if (escalon == escalonRoto)
        {
            return true;
        }
    }
    return false;
}

void Caminos(int n, vector<int> &Rotos, vector<int> &Camino, int escalon, vector<int> &Saltos, int &contador, vector<int> &caminoCorto)
{
    // Alcanzar la estrella
    if (escalon == n)
    {
        contador++;

        if (Camino.size() < caminoCorto.size())
        {
            caminoCorto = Camino;
        }
        return;
    }

    for (int s : Saltos)
    {
        int siguienteEscalon = escalon + s;

        if (siguienteEscalon <= n && !esEscalonRoto(siguienteEscalon, Rotos))
        {
            Camino.push_back(siguienteEscalon);
            Caminos(n, Rotos, Camino, siguienteEscalon, Saltos, contador, caminoCorto);
            Camino.pop_back();
        }
    }
}

int main(int argc, char **argv)
{
    if (argc != 4)
    {
        cout << "Error. Debe ejecutarse como ./problema n k p" << endl;
        exit(EXIT_FAILURE);
    }

    // srand(time(NULL));
    int n = atoi(argv[1]);
    int k = atoi(argv[2]);
    int p = atoi(argv[3]);
    int E[n];
    vector<int> Rotos;
    vector<int> Camino;
    vector<int> Saltos;
    generaEnteros(E, n, k, Rotos, p, Saltos);
    printArray(E, n, Rotos, k, Saltos);
    int totalCaminos = 0;
    vector<int> caminoCorto(n + 1, INT_MAX);
    Caminos(n, Rotos, Camino, 0, Saltos, totalCaminos, caminoCorto);
    cout << "Total de caminos posibles: " << totalCaminos << endl;
    cout << "Camino más corto: ";
    for (int e : caminoCorto)
    {
        if (e != INT_MAX)
        {
            cout << e << " ";
        }
    }
    cout << endl;
    return 0;
}
