#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>

// void inializaDistPrev(int *prev, int *dist, int *heepNumeracaoVetores, int quat)
// {
//     for (int i = 0; i < quat; i++)
//     {
//         dist[i] = 999;
//         prev[i] = -1;
//         heepNumeracaoVetores[i] = i + 1;
//     }
// }

// void adiconarDistNaHeep(int *dist, int *heepArray, int quant)
// {
//     for (int i = 0; i < quant; i++)
//     {
//         heepArray[i] = dist[i];
//     }
// }

// void heep(int *heepArray, int *heepNumeracaoVetores, int quant)
// {
//     int aux;
//     int aux2;
//     for (int i = 0; i < quant; i++)
//     {
//         for (int j = 0; j < quant - 1; j++)
//         {
//             if (heepArray[j] > heepArray[j + 1])
//             {
//                 aux = heepArray[j];
//                 aux2 = heepNumeracaoVetores[j];

//                 heepArray[j] = heepArray[j + 1];
//                 heepNumeracaoVetores[j] = heepNumeracaoVetores[j + 1];

//                 heepArray[j + 1] = aux;
//                 heepNumeracaoVetores[j + 1] = aux2;
//             }
//         }
//     }
// }

// int heepVazia(int *heepArray)
// {
//     if (heepArray[0] == 1000)
//     {
//         return 0;
//     }

//     return 1;
// }

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

    // for (int i = 1; i < 2; i++)
    // {
    for (int j = 0; j < tamanhoDoArquivodeEntrada; j++)
    {
        // printf("**%i\n", j);
        // printf("%i\n", vertces[1][j]);
        if (vertces[1][j] == k)
        {
            // printf("%i ", vertces[1][j]);
            // printf("%i ", vertces[0][j]);
            vizinhosDek[contadorAux] = vertces[0][j];
            pesoDosVizinhos[contadorAux] = j;
            contadorAux++;
        }
    }
    // }
}

// void atualizarDistNaHeep(int *dist, int *heepArray, int *heepNumeracaoVetores, int quantVertices) {
//     for (int i = 0; i < quantVertices; i++)
//     {
//         for (int j = 0; j < quantVertices; j++)
//         {
//             if((i + 1) == heepNumeracaoVetores[j] && heepArray[j] != 1000) 
//             {
//                 heepArray[j] = dist[i];
//             }
//         }
//     }
// }

int calMinDist(int l, int *vizinhosDek, int *pesoDosVizinhos, int quantVertices, int quantArestas, int dist[][quantVertices], int vertces[][50], int *peso) {

    int minimo = 999;

    // Andando Pela Matriz dist
    for (int v = 0; vizinhosDek[v] != -1; v++)
    {   
        if(dist[l][vizinhosDek[v] - 1] != 999){
            if (dist[l][vizinhosDek[v] - 1] + peso[pesoDosVizinhos[v]]  < minimo){
                minimo = dist[l][vizinhosDek[v] - 1] + peso[pesoDosVizinhos[v]];
                // printf("%i ", dist[l][vizinhosDek[v] - 1]);
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

    // for (int i = 0; i < 1; i++)
    // {
    //     for (int j = 0; j < quantVertices; j++)
    //     {
    //         if (1)
    //         {
    //             printf("%i ", dist[i][j]);
    //         }
    //     }
    //     printf("\n");
    // }

    // Calculando a distancia minima da fonte para os outros vertices.
    int l = 1;
    for (int l = 1; l < quantVertices-1; l++)
    {
        for (int k = 1; k <= quantVertices; k++)
        {   
            int vizinhosDek[10];
            int pesoDosVizinhos[10];
            iniciliza(vizinhosDek, pesoDosVizinhos); // Inicializa com -1;

            // printf("*%i \n", k);
            pegarVizinhosDeK(k, vizinhosDek, pesoDosVizinhos, quantVertices, vertces, z);
            
            int distMinimo = calMinDist(l - 1, vizinhosDek, pesoDosVizinhos, quantVertices, quantArestas, dist, vertces, peso);
            
            // printf("%i ", distMinimo);
            // for (int i = 0; i < 5; i++)
            // {
            //     // printf("%i *%i ", vizinhosDek[i], pesoDosVizinhos[i]);
            // }
            // printf("\n");
            

            // printf("***%i\n", distMinimo);

            if(distMinimo < dist[l-1][k-1]) {
                dist[l][k-1] = distMinimo;
            } else {
                dist[l][k-1] = dist[l-1][k-1];
            }
            
            // for (int f = 0; f < 5; f++)
            // {
            //     printf("%i", vizinhosDek[f]);
            // }
            // printf("\n");
        }
    }
    


    // Mostrando a Matris DIST
    // printf("%i ", dist[i][j]);
    printf("L/K ");
    for (int i = 0; i < quantVertices; i++)
    {
        printf("|K=%i ", i+1);
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
            else {
                printf("|%i   ", dist[i][j]);
            }
        }
        printf("\n");
    }
    

    
    // printf("oi");
    
    
    // int prev[quantVertices];

    // int heepArray[quantVertices];
    // int heepNumeracaoVetores[quantVertices];

    // inializaDistPrev(prev, dist, heepNumeracaoVetores, quantVertices);
    // adiconarDistNaHeep(dist, heepArray, quantVertices);
    // heep(heepArray, heepNumeracaoVetores, quantVertices); // Organiza os vertices

    // int visinhosDeV[10]; // Vizinhos do vertice V
    // int pesoDeUparV[10]; // Vizinhos do vertice V

    // while (heepVazia(heepArray))
    // {
    //     int verticeMinimo = heepNumeracaoVetores[0];
    //     heepArray[0] = 1000; // Remove esse vertice da heep.

        // iniciliza(visinhosDeV,pesoDeUparV); // Inicializa com -1;

    //     pegarVisinhosDeV(visinhosDeV, pesoDeUparV, peso, quantVertices, vertces, verticeMinimo, z);
        
    //     for (int i = 0; visinhosDeV[i] != -1; i++) // Andandoo Pelos visinhos de V
    //     {
    //         if(dist[visinhosDeV[i] - 1] > dist[verticeMinimo - 1] + pesoDeUparV[i]) {
    //             dist[visinhosDeV[i] - 1] = dist[verticeMinimo - 1] + pesoDeUparV[i];
    //             prev[visinhosDeV[i] - 1] = verticeMinimo;
    //             atualizarDistNaHeep(dist, heepArray, heepNumeracaoVetores, quantVertices);
    //         }
    //     }        
        
    //     heep(heepArray, heepNumeracaoVetores, quantVertices);
    // }

    // printf("Vertices / Dist / Prev");
    // printf("\n");
    // for (int i = 0; i < quantVertices; i++)
    // {
    //     printf("%i / %i / %i\n", i+1, dist[i], prev[i]);
    // }

    return 0;
}