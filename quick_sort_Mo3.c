#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void randarr(int arr[], int length, int seed){ /*funzione randarr che prende in ingresso l'array e ci inserisce numeri casuali dati dalla funzione rand con seed 13*/
    
    int i;
    srand(seed);
    for(i=0;i<length;i++){ /*ciclo for per assegnare ad ogni elemento dell'array un valore casuale*/
        arr[i]=rand(); /*ad arr[i] assegno un valore casuale compreso tra 0 e max*/
	}
}

void swap(int *v, int x, int y) /*scambia il valore a cui sta puntando x con il valore a cui sta puntando y,
                            utilizzato per scambiare gli elementi dell'array nella funzione partition*/
{
    int temp = v[x];
    v[x] = v[y];
    v[y] = temp;
}

int median_of_three(int array[], int i, int j, int k){ /*questa procedura ci restituisce l'indice della mediana tra i, j e k.
                                                        Una volta trovato l'indice, usiamo quello come pivot e poi partizioniamo rispetto a quel pivot*/
    if(array[i] > array[j]) {
        if(array[j] >= array[k]) {
            return j;
        } else if(array[i] < array[k]) {
            return i;
        } else return k;
    } else 
        if(array[i] >= array[k]) {
            return i;
        } else if(array[j] < array[k]) {
            return j;
        } else return k;
}

int Mo3_partition(int array[], int low, int high) /*questa procedura partiziona l'array tra gli indici low e high rispetto a un valore pivot calcolato con la
                                                    procedura median_of_three e ritorna l'indice del pivot*/
{
    int mid=(low+high)/2;
    int pivot_index = median_of_three(array,low,high,mid); /*calcolo l'indice della mediana dei tre elementi presi in considerazione, ossia il primo
                                                            elemento dell'array da partizionare, l'ultimo, e quello centrale, e lo uso come pivot*/
    
    swap(array, pivot_index, high); /*scambio l'elemento pivot con l'elemento in ultima posizione dell'array*/
    
    int pivot_value = array[high]; /*ora ciò che c'è in pivot_value è dato dall'ultimo elemento dell'array*/
    
    int i = low-1; /*l'algoritmo di partizionamento posizionerà gli elementi minori del pivot alla sua sinistra, con i che terrà traccia
                    di dove finiscono gli elementi minori del pivot e di dove iniziano gli elementi maggiori del pivot*/
    
    for (int j = low; j < high; j++) /*ciclo for che scorre l'intero array da partizionare, escluso il pivot*/
    {
        if (array[j] <= pivot_value) { /*se il valore dell'elemento in posizione j è minore del valore del pivot, scambio j con
                                        il primo elemento maggiore del pivot, che si trova in posizione i+1*/
            i++;
            swap(array, i, j);
        }
    }
    
    swap(array, i+1, high); /*ora sappiamo che il valore all'indice i+1 è maggiore o uguale al pivot, quindi li scambiamo per completare la partizione*/
    
    return i+1; /*l'indice i+1 ora contiene il valore del pivot, quindi lo ritorniamo in modo tale che la procedura Mo3_quicksort sappia
                dove dividere l'array quando applicare l'algoritmo ai risultanti sottoarray*/
}

void Mo3_quicksort(int array[], int low, int high) /*applico l'algoritmo quicksort median of three tra gli indici low e high di ogni array esaminato*/
{
    if (low < high)
    {
        int pivot_index = Mo3_partition(array, low, high); /*partiziona l'array rispetto ad un pivot e ritorna l'indice dell'elemento pivot*/

        Mo3_quicksort(array, low, pivot_index - 1); /*applico quicksort alla parte sinistra del sottoarray*/

        Mo3_quicksort(array, pivot_index + 1, high); /*applico quicksort alla parte destra del sottoarray*/
    }
}

double single_experiment(int length, int max_instances, int seed) {
    double t_start, t_end, t_elapsed, t_tot=0.0;
    for(int i=1; i<=max_instances; i++) {
        int array[length];
        randarr(array, length, seed);
        t_start=clock();
        Mo3_quicksort(array, 0, length-1);
        t_end=clock();
        t_elapsed=t_end-t_start;
        t_tot=t_tot+t_elapsed;
        /*for(int j=0; j<length; j++) {
            printf("%d ", array[j]);
        }
        printf("\n");*/
    }
    return t_tot/max_instances;
}

void experiment(int min_length, int max_length, int seed) {
    int max_instances=30000, step=5;
    for(int length=min_length; length<=max_length; length+=step) {
        double time=single_experiment(length, max_instances, seed);
        printf("Clock cycles: %d --- Elements: %d\n", time, length);
        //printf("%lf ", time);
    }
}

int main() {
    int seed=13, min_length=5, max_length=500;
    experiment(min_length, max_length, seed);
    return 0;
}
