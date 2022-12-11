#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>

void iniciliza(int *vizinhosDek, int *pesoDosVizinhos)
{
    for (int i = 0; i < 10; i++)
    {
        vizinhosDek[i] = -1;
        pesoDosVizinhos[i] = -1;
    }
}

void pegarVizinhosDeK(int k, int *vizinhosDek, int *pesoDosVizinhos,int quantVertices, int vertces[][50], int tamanhoDoArquivodeEntrada)
{
    int contadorAux = 0;
    
    for (int j = 0; j < tamanhoDoArquivodeEntrada; j++)
    {
        if (vertces[1][j] == k)
        {
            vizinhosDek[contadorAux] = vertces[0][j];
            pesoDosVizinhos[contadorAux] = j;
            contadorAux++;
        }
    }
    // }
}

int calMinDist(int l, int *vizinhosDek, int *pesoDosVizinhos, int quantVertices, int quantArestas, int dist[][quantVertices], int vertces[][50], int *peso) {

    int minimo = 999;

    // Andando Pela Matriz dist
    for (int v = 0; vizinhosDek[v] != -1; v++)
    {   
        if(dist[l][vizinhosDek[v] - 1] != 999){
            if (dist[l][vizinhosDek[v] - 1] + peso[pesoDosVizinhos[v]]  < minimo){
                minimo = dist[l][vizinhosDek[v] - 1] + peso[pesoDosVizinhos[v]];
            }
        }
    }

    return minimo;
}

int main(int argc, char *argv[])
{

    // Entrada de parãmetros pelo terminal

    FILE *file;
    file = fopen(argv[1], "r");

    int quantVertices, quantArestas;

    fscanf(file, "%i %i", &quantVertices, &quantArestas);

    int vertces[2][50];
    int peso[50];
    int verticeFonte = (strtol(argv[2], NULL, 10)) - 1; // Converte caracter em int na base 10.

    int z = 0;

    while (fscanf(file, "%i %i ", &vertces[0][z], &vertces[1][z]) != -1)
    {
        fscanf(file, "%i", &peso[z]);
        z++;
    }

    // COMEÇANDO O ALGORITOMO

    int dist[quantArestas][quantVertices]; // l/v

    dist[0][verticeFonte] = 0; // Inializando o vertice fonte
    
    // Inicializando l = 0
    for (int l = 0; l < 1; l++)
    {
        for (int j = 0; j < quantVertices; j++)
        {
            if (j != verticeFonte)
            {
                dist[l][j] = 999; 
            }
        }
    }

    // Calculando a distancia minima da fonte para os outros vertices.
    int l = 1;
    for (int l = 1; l < quantVertices-1; l++)
    {
        for (int k = 1; k <= quantVertices; k++)
        {   
            int vizinhosDek[10];
            int pesoDosVizinhos[10];
            iniciliza(vizinhosDek, pesoDosVizinhos); // Inicializa com -1;

            pegarVizinhosDeK(k, vizinhosDek, pesoDosVizinhos, quantVertices, vertces, z);
            
            int distMinimo = calMinDist(l - 1, vizinhosDek, pesoDosVizinhos, quantVertices, quantArestas, dist, vertces, peso);
            
            if(distMinimo < dist[l-1][k-1]) {
                dist[l][k-1] = distMinimo;
            } else {
                dist[l][k-1] = dist[l-1][k-1];
            }
        }
    }
    
    // Mostrando a Matris DIST
    printf("\n");
    printf("L/V ");
    for (int i = 0; i < quantVertices; i++)
    {
        printf("|V=%i ", i+1);
    }
    printf("\n");
    
    for (int i = 0; i < quantVertices-1; i++)
    {
        printf("L=%i ", i);
        for (int j = 0; j < quantVertices; j++)
        {
            if(dist[i][j] == 999 && dist[i][j+1] < 999) {
                printf("|%i ", dist[i][j]);
            }
            else if(dist[i][j] == 999) {
                printf("|%i ", dist[i][j]);
            }
            else if(dist[i][j] < 0) {
                printf("|%i  ", dist[i][j]);
            }
            else if(dist[i][j] > 9) {
                printf("|%i  ", dist[i][j]);
            }
            else {
                printf("|%i   ", dist[i][j]);
            }
        }
        printf("\n");
    }
    printf("\n");

    return 0;
}