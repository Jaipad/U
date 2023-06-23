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

void Caminos(int n, vector<int> &Rotos, vector<int> &Camino, vector<int> &Saltos)
{
    int caminosGuardados[n + 1] = {0};

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

/*     vector<int> caminoCorto;

    if (caminosGuardados[n] > 0)
    {
        int s = Saltos.size();
        int m = n;

        while (s > 0 && (m - s) > 0)
        {
            

            if (caminosGuardados[m - s] > 0)
            {
                caminoCorto.push_back(m - s);
                m -= s;
            }
        }
    } */

    for (int h = 0; h <= n; h++)
        cout << caminosGuardados[h] << "[" << h << "] ";
    cout << endl;

    cout << "Caminos posibles: " << caminosGuardados[n] << endl;

/*     cout << "Camino mas corto: ";
    for (int h = 0; h < caminoCorto.size(); h++)
        cout << caminoCorto[h] << " ";
    cout << endl; */
}

int main(int argc, char **argv)
{
    if (argc != 4)
    {
        cout << "Error. Debe ejecutarse como ./problema n k p" << endl;
        exit(EXIT_FAILURE);
    }

    srand(time(NULL));
    int n = atoi(argv[1]);
    int k = atoi(argv[2]);
    int p = atoi(argv[3]);
    int E[n];

    vector<int> Rotos;
    vector<int> Camino;
    vector<int> Saltos;
    generaEnteros(E, n, k, Rotos, p, Saltos);
    printArray(E, n, Rotos, k, Saltos);

    Caminos(n, Rotos, Camino, Saltos);

    return 0;
}