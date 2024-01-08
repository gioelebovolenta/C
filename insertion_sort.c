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

void insertion_sort(int arr[], int n) //funzione insertion sort che prende in ingresso l'array e la sua dimensione
{
	int i, key, j; //svolgimento classico di insertion sort, con i, j e key che si occupano del riordinamento dell'array
	for (i = 1; i < n; i++) { //ciclo for per i che va da 1 alla dimensione dell'array con incremento di 1
		key = arr[i]; //key tiene traccia dell'elemento da comparare
		j = i - 1; //j è impostato a i-1 perché dobbiamo confrontare i con tutti gli elementi precedenti ad esso

		while (j >= 0 && arr[j] > key) { //le condizioni del while sono che j>=0 per rimanere all'interno dell'array, e che l'elemento indicato da j sia più grande di key
			arr[j + 1] = arr[j]; //questo assegnamento serve a shiftare gli elementi più grandi di key
			j = j - 1; //j=j-1 serve a fare il check all'indietro di tutto l'array
		}
		arr[j + 1] = key; //inserisco finalmente key nel posto in cui deve stare in modo da ordinare l'array elemento per elemento
	}
}

double single_experiment(int length, int max_instances, int seed) { /*single experiment riproduce l'ordinamento degli array in base all'algoritmo
                                                                    di ordinamento selezionato. Vengono utilizzati i cicli di clock per poter comparare
                                                                    la durata effettiva dei vari ordinamenti e delle variabili di controllo per poterli calcolare*/
    double t_start, t_end, t_elapsed, t_tot=0.0;
    for(int i=1; i<=max_instances; i++) {
        int array[length];
        randarr(array, length, seed);
        t_start=clock();
        insertion_sort(array, length);
        t_end=clock();
        t_elapsed=t_end-t_start;
        t_tot=t_tot+t_elapsed;
        /*for(int j=0; j<length; j++) {
            printf("%d ", array[j]);
        }
        printf("\n");*/
    }
    return t_tot/max_instances; //per calcolare il valore medio di ogni istanza
}

void experiment(int min_length, int max_length, int seed) {
    int max_instances=30000, step=5;
    for(int length=min_length; length<=max_length; length+=step) {
        double time=single_experiment(length, max_instances, seed);
        //printf("Clock cycles: %d --- Elements: %d\n", time, length);
        printf("%f ", time);
    }
}

int main() {
    int seed=13, min_length=5, max_length=500;
    experiment(min_length, max_length, seed);
    return 0;
}
