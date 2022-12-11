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

int pegarVisinhosDeV(int *visinhosDeV, int *pesoDeUparV, int *peso, int quantVertices, int vertces[][50], int verticeMinimo, int tamanhoDoArquivodeEntrada)
{
    int contadorAux = 0;

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < tamanhoDoArquivodeEntrada; j++)
        {
            if (vertces[i][j] == verticeMinimo && i == 0)
            {
                visinhosDeV[contadorAux] = vertces[1][j];
                pesoDeUparV[contadorAux] = peso[j];
                contadorAux++;
            }
            else if (vertces[i][j] == verticeMinimo && i == 1)
            {
                visinhosDeV[contadorAux] = vertces[0][j];
                pesoDeUparV[contadorAux] = peso[j];
                contadorAux++;
            }
        }
    }
}

void atualizarDistNaHeep(int verticeAtualizar, int *dist, int *heepArray, int *heepNumeracaoVetores, int quantVertices) {
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

int vizinhoMorreu(int visinho, int *heepArray, int *heepNumeracaoVetores, int quantVertices) {
    
    for (int i = 0; i < quantVertices; i++)
    {    
        if(heepNumeracaoVetores[i] == visinho) {
            if(heepArray[i] == 1000) {
                return 0;
            } else {
                return 1;
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

    int dist[quantVertices];
    int prev[quantVertices];
    int matrizDist[quantVertices][quantVertices];
    int matrizPrev[quantVertices][quantVertices];
    
    // Inicializar a matrizDist e matrizPrev
    for (int i = 0; i < quantVertices; i++)
    {
        for (int j = 0; j < quantVertices; j++)
        {
            matrizDist[i][j] = 999;
            matrizPrev[i][j] = -1;
        }
    }
    

    int heepArray[quantVertices];
    int heepNumeracaoVetores[quantVertices];

    inializaDistPrev(prev, dist, heepNumeracaoVetores, quantVertices);
    dist[verticeFonte] = 0;
    matrizDist[0][verticeFonte] = 0;
    adiconarDistNaHeep(dist, heepArray, quantVertices);
    heep(heepArray, heepNumeracaoVetores, quantVertices); // Organiza os vertices

    int visinhosDeV[10]; // Vizinhos do vertice V
    int pesoDeUparV[10]; // Vizinhos do vertice V


    int cont = 1;
    int contaMostrar = 0;

    // printf("\n---------------------\n");
    printf("\n");
    printf("999 = Infinito     \n");
    // printf("| custo/prev         |");
    // printf("\n---------------------\n\n");
    
    printf("\n");
    printf("Vertices\n");
    // printf("\n");
    for (int i = 0; i < quantVertices; i++)
    {
        printf("-------");
    }
    printf("\n");


    for (int i = 0; i < quantVertices; i++)
    {
        printf("v= %i  |", i+1);
    }

    printf("\n");
    for (int i = 0; i < quantVertices; i++)
    {
        printf("-------");
    }
    printf("\n");
    

    while (heepVazia(heepArray))
    {  
        int verticeMinimo = heepNumeracaoVetores[0];

        iniciliza(visinhosDeV,pesoDeUparV); // Inicializa com -1;

        pegarVisinhosDeV(visinhosDeV, pesoDeUparV, peso, quantVertices, vertces, verticeMinimo, z);
        
        if(cont > 1) {
            for (int j = 0; j < quantVertices; j++)
            {
                matrizDist[cont][j] = matrizDist[cont-1][j];
                matrizPrev[cont][j] = matrizPrev[cont-1][j];
            }
        }


        for (int j = 0; visinhosDeV[j] != -1; j++)
        {
            if(vizinhoMorreu(visinhosDeV[j], heepArray, heepNumeracaoVetores, quantVertices)) 
            {
                if(matrizDist[cont-1][visinhosDeV[j] - 1] > pesoDeUparV[j]) 
                {
                    matrizDist[cont][visinhosDeV[j] - 1] = pesoDeUparV[j];
                    matrizPrev[cont][visinhosDeV[j] - 1] = verticeMinimo;
                    dist[visinhosDeV[j] - 1] = pesoDeUparV[j];
                    atualizarDistNaHeep(visinhosDeV[j] - 1, dist, heepArray, heepNumeracaoVetores, quantVertices);
                }                               
            } 
        }
        
        for (int j = 0; j < quantVertices; j++)
        {
            if(contaMostrar < 1) {
                if(matrizDist[contaMostrar][j] == 999 ) {
                    printf("%i/%i|", matrizDist[contaMostrar][j], matrizPrev[contaMostrar][j]);
                } 
                else if (matrizDist[contaMostrar][j] < 0 || matrizDist[contaMostrar][j] == 0)
                {
                    printf("%i/%i  |", matrizDist[contaMostrar][j], matrizPrev[contaMostrar][j]);
                } else if (matrizDist[contaMostrar][j] > 9) {
                    printf("%i/%i |", matrizDist[contaMostrar][j], matrizPrev[contaMostrar][j]);
                } else 
                {
                    printf("%i/%i   |", matrizDist[contaMostrar][j], matrizPrev[contaMostrar][j]);
                }
            }
            else if(!vizinhoMorreu(j+1, heepArray, heepNumeracaoVetores, quantVertices)) {
                printf("      |");
            } else {
                if(matrizDist[contaMostrar][j] == 999) 
                {
                    printf("%i/%i|", matrizDist[contaMostrar][j], matrizPrev[contaMostrar][j]);
                } 
                else if (matrizDist[contaMostrar][j] < 0)
                {
                    printf("%i/%i |", matrizDist[contaMostrar][j], matrizPrev[contaMostrar][j]);
                } else if (matrizDist[contaMostrar][j] > 9) {
                    printf("%i/%i |", matrizDist[contaMostrar][j], matrizPrev[contaMostrar][j]);
                } else 
                {
                    printf("%i/%i   |", matrizDist[contaMostrar][j], matrizPrev[contaMostrar][j]);
                }
            }
        }
        printf("\n");

        cont++;
        contaMostrar++;
        heepArray[0] = 1000; // Remove esse vertice da heep.
        heep(heepArray, heepNumeracaoVetores, quantVertices); // Reordeno a heep   
    }

    printf("\n");
    return 0;
}