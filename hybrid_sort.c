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

void merge_sorted_arrays(int a[], int l, int m, int r) { //unisce le due porzioni di array ordinate: dall'indice l all'indice m e dall'indice m+1 all'indice r

    int left_length = m - l + 1; //calcola la lunghezza delle due porzioni dell'array
    int right_length = r - m;
    
    int temp_left[left_length]; //creo array temporanei per memorizzare queste porzioni di array
    int temp_right[right_length];
    
    int i, j, k; //usati come contatori per i tre array (a, temp_left, temp_right)
    
    for (int i = 0; i < left_length; i++) //copia la porzione sinistra nell'array temp_left
    temp_left[i] = a[l + i];
    
    for (int i = 0; i < right_length; i++) //copia la porzione destra nell'array temp_right
    temp_right[i] = a[m + 1 + i];
    
    for (i = 0, j = 0, k = l; k <= r; k++)   /* utilizzo l'indice i per muovermi all'interno di temp_left, j per muovermi all'interno di temp_right e k per
                                                muovermi nella porzione dell'array a da l a r. In sostanza, sapendo che entrambi temp_left e temp_right sono ordinati,
                                                controlliamo la testa dei due array temporanei e mettiamo il numero più piccolo tra i due nell'array a (usando i, j e k
                                                per muoverci all'interno degli array). Quando terminano gli elementi in uno degli array temporanei, i restanti elementi
                                                dell'altro array vengono copiati in a*/
    {

    if ((i < left_length) &&
        (j >= right_length || temp_left[i] <= temp_right[j])) /*finché non abbiamo raggiunto la fine dell'array temp_left con la variabile i, e se l'elemento all'indice i
                                                                di temp_left è <= all'elemento all'indice j di temp_right O se abbiamo raggiunto la fine dell'array temp_right,
                                                                allora memorizziamo l'elemento presente all'indice i di temp_left nell'array a all'indice k*/
    {
        a[k] = temp_left[i];
        i++;
    }

    else // altrimenti memorizziamo l'elemento presente all'indice j di temp_right nell'array a all'indice k
    {
        a[k] = temp_right[j];
        j++;
    }
    }  
}

void merge_sort(int a[], int l, int r)  /*Esecuzione dell'algoritmo merge sort sull'array a tra l'indice sinistro l e l'indice destro r.
                                                    Questa funzione implementa l'algoritmo ricorsivo di merge sort, che divide l'array nelle porzioni tra l ed r 
                                                    e chiama se stesso in ciascuna porzione, prima di di unire le porzioni ordinate dell'array risultante.*/
{
    if (l < r) //fermiamo la ricorsione quando l >= r
    {
    int m = l + (r - l) / 2; //trovo il punto medio di l ed r
    merge_sort(a, l, m); //applico la funzione ricorsivamente alle porzioni sinistra e destra divise dal punto medio
    merge_sort(a, m + 1, r);
    merge_sorted_arrays(a, l, m, r); //a questo punto entrambe le porzioni dell'array sono state ordinate e possiamo quindi unirle
    }
}

void adapted_insertion_sort(int arr[], int l, int r) /*funzione insertionSort che prende in ingresso l'array e la sua dimensione*/
{
	int i, key, j; /*svolgimento classico di insertion sort, con i, j e key che si occupano del riordinamento dell'array*/
	for (i = l+1; i <= r; i++) { /*ciclo for per i che va da 1 alla dimensione dell'array incremento i di 1*/
		key = arr[i]; /*key tiene traccia dell'elemento da comparare*/
		j = i - 1; /*j è impostato a i-1 perché dobbiamo confrontare i con tutti gli elementi precedenti ad esso*/

		while (j >= l && arr[j] > key) { /*le condizioni del while sono che j>=0 per rimanere all'interno dell'array, e che l'elemento indicato da j sia più grande di key*/
			arr[j + 1] = arr[j]; /*questo assegnamento serve a shiftare gli elementi più grandi di key*/
			j--; /*j=j-1 serve a fare il check all'indietro di tutto l'array*/
		}
		arr[j + 1] = key;  /*inserisco finalmente key nel posto in cui deve stare in modo da ordinare l'array elemento per elemento*/
	}
}

void hybrid_sort(int a[], int l, int r) {
    if ((r - l + 1) > 90) {
        int m = ((l + r) / 2);
        hybrid_sort(a, l, m);
        hybrid_sort(a, m + 1, r);
        merge_sorted_arrays(a, l, m, r);
    }
    else {
        adapted_insertion_sort(a, l, r);
    }
}

double single_experiment(int length, int max_instances, int seed) {
    double t_start, t_end, t_elapsed, t_tot=0.0;
    for(int i=1; i<=max_instances; i++) {
        int array[length];
        randarr(array, length, seed);
        t_start=clock();
        hybrid_sort(array, 0, length-1);
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
        //printf("%f ", time);
    }
}

int main() {
    int seed=13, min_length=5, max_length=500;
    experiment(min_length, max_length, seed);
    return 0;
}
