#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void randarr(int arr[], int length, int seed) { //funzione randarr che prende in ingresso un array, la sua lunghezza e il seed
    
    int i;
    srand(seed); //srand(seed) imposta il punto di partenza per la creazione di una serie di numeri interi pseudocasuali
    for(i=0;i<length;i++){ //ciclo for per assegnare ad ogni elemento dell'array un valore pseudocasuale
        arr[i]=rand();
	}
}

void swap(int *v, int x, int y) /*scambia il valore a cui sta puntando x con il valore a cui sta puntando y,
                                utilizzato per scambiare gli elementi dell'array nella funzione partition*/
{
    int temp = v[x];
    v[x] = v[y];
    v[y] = temp;
}

int partition(int array[], int low, int high) //questa procedura partiziona l'array tra gli indici low e high rispetto a un valore pivot
{    
    int pivot_value = array[high]; //scegliamo arbitrariamente di assegnare l'ultimo elemento dell'array da partizionare come valore del pivot
    
    int i = low-1; /*l'algoritmo di partizionamento posizionerà gli elementi minori del pivot alla sua sinistra, con i che terrà traccia
                    di dove finiscono gli elementi minori del pivot e di dove iniziano gli elementi maggiori del pivot.
                    Questa operazione ci permette di partire dalla posizione precedente alla posizione iniziale dell'array da partizionare*/
    
    for (int j = low; j < high; j++) //ciclo for che scorre l'intero array da partizionare, escluso il pivot
    {
        if (array[j] <= pivot_value) { /*se il valore dell'elemento in posizione j (elemento da posizionare correttamente) è minore del valore del pivot,
                                        scambio j con il primo elemento maggiore del pivot, che si trova in posizione i+1*/
            i++;
            swap(array, i, j);
        }
    }
    
    swap(array, i+1, high); //ora sappiamo che il valore all'indice i+1 è maggiore o uguale al pivot, quindi li scambiamo per completare la partizione
    
    return i+1; /*l'indice i+1 ora contiene il valore del pivot, quindi lo ritorniamo in modo tale che la procedura quicksort sappia
                dove dividere l'array quando applichiamo l'algoritmo ai risultanti sottoarray*/
}

void tail_quicksort(int array[], int low, int high) //applico l'algoritmo tail quicksort tra gli indici low e high di ogni array da esaminare
{
    while (low < high)
    {
        int pivot_index = partition(array, low, high); //partiziona l'array rispetto ad un pivot e ritorna l'indice dell'elemento pivot
        if(pivot_index < (low+high)/2) { //if che permette di scegliere su quale lato dell'array è più conveniente effettuare la chiamata ricorsiva
            tail_quicksort(array, low, pivot_index-1);
            low=pivot_index+1; //faccio avanzare low all'indice del pivot + 1 così da poter eliminare la ricorsione in coda
        } else {
            tail_quicksort(array, pivot_index+1, high);
            high=pivot_index-1; //faccio retrocedere high all'indice del pivot - 1 così da poter eliminare la ricorsione in coda
        }
    }
}

double single_experiment(int length, int max_instances, int seed) {
    double t_start, t_end, t_elapsed, t_tot=0.0;
    for(int i=1; i<=max_instances; i++) {
        int array[length];
        randarr(array, length, seed);
        t_start=clock();
        tail_quicksort(array, 0, length-1);
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
        //printf("Clock cycles: %d --- Elements: %d\n", time, length);
        printf("%lf ", time);
    }
}

int main() {
    int seed=13, min_length=5, max_length=500;
    experiment(min_length, max_length, seed);
    return 0;
}
