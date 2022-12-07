#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>

void inializaDistPrev(int *prev, int *dist, int *heepNumeracaoVetores, int quat)
{
    for (int i = 0; i < quat; i++)
    {
        dist[i] = 999;
        prev[i] = -1;
        heepNumeracaoVetores[i] = i + 1;
    }
}

void adiconarDistNaHeep(int *dist, int *heepArray, int quant)
{
    for (int i = 0; i < quant; i++)
    {
        heepArray[i] = dist[i];
    }
}

void heep(int *heepArray, int *heepNumeracaoVetores, int quant)
{
    int aux;
    int aux2;
    for (int i = 0; i < quant; i++)
    {
        for (int j = 0; j < quant - 1; j++)
        {
            if (heepArray[j] > heepArray[j + 1])
            {
                aux = heepArray[j];
                aux2 = heepNumeracaoVetores[j];

                heepArray[j] = heepArray[j + 1];
                heepNumeracaoVetores[j] = heepNumeracaoVetores[j + 1];

                heepArray[j + 1] = aux;
                heepNumeracaoVetores[j + 1] = aux2;
            }
        }
    }
}

int heepVazia(int *heepArray)
{
    if (heepArray[0] == 1000)
    {
        return 0;
    }

    return 1;
}

void iniciliza(int *visinhosDeV, int *pesoDeUparV)
{
    for (int i = 0; i < 10; i++)
    {
        visinhosDeV[i] = -1;
        pesoDeUparV[i] = -1;
    }
}

int pegarVisinhosDeV(int *visinhosDeV, int *pesoDeUparV, int *peso, int quantVertices, int vertices[][2], int verticeDeIda, int tamanhoDoArquivodeEntrada)
{
    int contadorAux = 0;

    for (int i = 0; i < tamanhoDoArquivodeEntrada; i++)
    {
        if (vertices[i][0] == verticeDeIda+1)
        {
            visinhosDeV[contadorAux] = vertices[i][1];
            pesoDeUparV[contadorAux] = peso[i];
            contadorAux++;
        }
    }
}

void atualizarDistNaHeep(int *dist, int *heepArray, int *heepNumeracaoVetores, int quantVertices) {
    for (int i = 0; i < quantVertices; i++)
    {
        for (int j = 0; j < quantVertices; j++)
        {
            if((i + 1) == heepNumeracaoVetores[j] && heepArray[j] != 1000) 
            {
                heepArray[j] = dist[i];
            }
        }
    }
}

int main(int argc, char *argv[])
{

    // Entrada de parãmetros pelo terminal

    FILE *file;
    file = fopen(argv[1], "r");

    int quantVertices, quantArestas;

    fscanf(file, "%i %i", &quantVertices, &quantArestas);

    int vertices[50][2];
    int peso[50];
    // int verticeFonte = (strtol(argv[2], NULL, 10)) - 1; // Converte caracter em int na base 10.

    int z = 0;

    while (fscanf(file, "%i %i ", &vertices[z][0], &vertices[z][1]) != -1)
    {
        fscanf(file, "%i", &peso[z]);
        z++;
    }

    // COMEÇANDO O ALGORITOMO

    int dist[quantVertices][quantVertices];
    int prev[quantVertices][quantVertices];
    int visinhosDeV[10];
    int pesoDeUparV[10];
    iniciliza(visinhosDeV,pesoDeUparV);

    // CONSTRUINDO UMA PATRIZ PARA INICIALIZAR!
    for (int i = 0; i < quantVertices; i++)
    {
        for (int j = 0; j < quantVertices; j++)
        {
            if(i == j){
                dist[i][j] = 0;
            } else {
                dist[i][j] = 999;
            }
        }
    }

    for (int i = 0; i < quantVertices; i++)
    {
        for (int j = 0; j < quantVertices; j++)
        {
            prev[i][j] = -1;
        }
    }
    
    // CONSTRUINDO A MATRIZ D^0 E PREV;
    for (int i = 0; i < quantVertices; i++)
    {
        iniciliza(visinhosDeV,pesoDeUparV);
        pegarVisinhosDeV(visinhosDeV, pesoDeUparV, peso, quantVertices, vertices, i, z);
       
        for (int j = 0; visinhosDeV[j] != -1; j++)
        {

            int vizinho = visinhosDeV[j]-1;
            dist[i][vizinho] = pesoDeUparV[j];
            prev[i][vizinho] = i+1;

        }
    }
    
    int D = 0;
    // CRIANDO OS K's
    for (int k = 0; k < quantVertices; k++) // Intermediários
    {
        for (int i = 0; i < quantVertices; i++) // Linha
        {
            for (int j = 0; j < quantVertices; j++) // Coluna
            {
                if((dist[i][k] + dist[k][j] < dist[i][j]) && (dist[i][k] != 999) && (dist[k][j] != 999) ){
                    // printf("***%i %i %i %i %i %i\n",i,j,k, dist[i][k], dist[k][j], dist[i][j]);
                    dist[i][j] = dist[i][k] + dist[k][j];
                    prev[i][j] = k+1;
                }
            }
        }
        D = k;
    }
    
    


    // MOSTARDNO A MATRIZ.
    printf("\n", D+1);
    printf("MATRIZ D^%i\n", D+1);
    for (int i = 0; i < quantVertices; i++)
    {
       for (int j = 0; j < quantVertices; j++)
       {
            if(dist[i][j] > 9 || dist[i][j] < 0) {
                printf(" %i  |", dist[i][j]);
            } else {
                printf("  %i  |", dist[i][j]);
            }
       }
        printf("\n");
    }
    printf("************************************\n");
    printf("MATRIZ DO CAMINHO\n");
    for (int i = 0; i < quantVertices; i++)
    {
       for (int j = 0; j < quantVertices; j++)
       {
            if(prev[i][j] > 9 || prev[i][j] < 0) {
                // printf("*", prev[i][j]);
                printf(" %i  |", prev[i][j]);
            } else {
                printf("  %i  |", prev[i][j]);
            }
       }
        printf("\n");
    }

    return 0;
}