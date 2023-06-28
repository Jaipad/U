#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <climits>
#include <ctime>
#include <chrono>
using namespace std;
using namespace std::chrono;

float generaEnteros(int *E, int n, int k, vector<int> &Rotos, int p, vector<int> &Saltos)
{
    for (int i = 1; i <= (n + 1); i++)
    {
        E[i] = i;
    }
    for (int j = 1; j <= k; j++)
    {

        int a = (rand() % (n - 1)) + 1;
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

void printArray(int *E, int n, vector<int> &Rotos, int k, vector<int> &Saltos, long long int *caminosGuardados, vector<int> cCorto, int totalCaminos, vector<int> &caminoCorto)
{
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

void posiblesCaminos(int n, vector<int> &Rotos, vector<int> &Camino, vector<int> &Saltos, long long int *caminosGuardados)
{
    caminosGuardados[0] = 1;

    for (int i = 1; i <= n; i++)
    {
        if (!esEscalonRoto(i, Rotos))
        {
            for (int saltos : Saltos)
            {
                if ((i - saltos) >= 0)
                {
                    caminosGuardados[i] += caminosGuardados[i - saltos];
                }
            }
        }
    }
}

void caminoCorto(vector<int> &cCorto, vector<int> &Saltos, long long int *caminosGuardados, int n, int s, int es)
{
    if (caminosGuardados[n] > 0)
    {
        while (es < n)
        {
            if (caminosGuardados[Saltos[s] + es] > 0 && (Saltos[s] + es) <= n)
            {
                cCorto.push_back(Saltos[s] + es);
                es = Saltos[s] + es;
                s = Saltos.size() - 1;
            }
            else
            {
                s -= 1;
            }
        }
    }
}

// por fuerza bruta
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
    clock_t inicio, fin;
    double duracion;

    srand(time(NULL));
    int n = atoi(argv[1]);
    int k = atoi(argv[2]);
    int p = atoi(argv[3]);
    int E[n];
    long long int *caminosGuardados = new long long int[n + 1];
    vector<int> Rotos;
    vector<int> Camino;
    vector<int> Saltos;
    vector<int> cCorto;
    generaEnteros(E, n, k, Rotos, p, Saltos);
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
    // Bloque de programación dinámica
    auto startPD = high_resolution_clock::now();
    posiblesCaminos(n, Rotos, Camino, Saltos, caminosGuardados);
    caminoCorto(cCorto, Saltos, caminosGuardados, n, Saltos.size() - 1, 0);
    auto stopPD = high_resolution_clock::now();
    auto durationPD = duration_cast<duration<double>>(stopPD - startPD);
    cout << "Vector caminos posibles Pd = ";
    for (int h = 0; h <= n; h++)
        cout << caminosGuardados[h] << "[" << h << "] ";
    cout << endl;
    cout << "Caminos posibles Pd: " << caminosGuardados[n] << endl;
    cout << "Camino mas corto Pd: ";
    for (int h = cCorto.size() - 1; h >= 0; h--)
        cout << cCorto[h] << " ";
    cout << endl;
    cout << "Tiempo de ejecución de programación dinámica: " << durationPD.count() << " segundos" << endl;

    // Bloque de fuerza bruta
    auto startFB = high_resolution_clock::now();
    vector<int> caminoCorto(n + 1, INT_MAX);
    int totalCaminos = 0;
    Caminos(n, Rotos, Camino, 0, Saltos, totalCaminos, caminoCorto);
    auto stopFB = high_resolution_clock::now();
    auto durationFB = duration_cast<duration<double>>(stopFB - startFB);
    printArray(E, n, Rotos, k, Saltos, caminosGuardados, cCorto, totalCaminos, caminoCorto);
    cout << endl;
    cout << "Total de caminos posibles Pf: " << totalCaminos << endl;
    cout << "Camino más corto Pf: ";
    for (int e : caminoCorto)
    {
        if (e != INT_MAX)
        {
            cout << e << " ";
        }
    }
    cout << endl;

    cout << "Tiempo de ejecución de fuerza bruta: " << durationFB.count() << " segundos" << endl;

    cout << endl;

    return 0;
}