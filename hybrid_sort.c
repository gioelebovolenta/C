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

void merge_sorted_arrays(int a[], int l, int m, int r) //unisce le due porzioni di array ordinate: dall'indice l all'indice m e dall'indice m+1 all'indice r
{
    int left_length = m - l + 1; //calcola la lunghezza delle due porzioni dell'array
    int right_length = r - m;
    
    int temp_left[left_length]; //creo array temporanei per memorizzare queste porzioni di array
    int temp_right[right_length];
    
    int i, j, k; //usati come contatori per i tre array (a, temp_left, temp_right)
    
    for (int i = 1; i < left_length; i++) //copia la porzione sinistra nell'array temp_left
        temp_left[i] = a[l + i - 1];
    
    for (int j = 1; j < right_length; j++) //copia la porzione destra nell'array temp_right
        temp_right[j] = a[m + j];
    
    i = 1; //inizializzo i e j
    j = 1;
    
    for (k = l; k <= r; k++) {  //utilizzo una variabile di controllo k per muovermi all'interno dell'array dalla prima posizione utile all'ultima posizione utile
        if (i <= left_length) { //se non sono arrivato a fine corsa con l'indice i
            if (j <= right_length) { //e se non sono arrivato a fine corsa con l'indice j
                if (temp_left[i] <= temp_right[j]) { //allora eseguo il confronto dei due elementi
                    a[k] = temp_left[i]; //se l'elemento all'indice i è minore di quello ad indice j allora faccio la copia del primo in a[k]
                    i++; //e incremento i
                } else {
                    a[k] = temp_right[j]; //altrimenti faccio la copia dell'elemento ad indice j in a[k]
                    j++; //e incremento j
                }
            } else { //questo accade quando l'indice j è arrivato in fondo
                a[k] = temp_left[i]; //copio i rimanenti elementi dell'array di sinistra in a[k]
                i++;
            }
        } else { //questo accade quando l'indice i è arrivato in fondo
            a[k] = temp_right[j]; //copio i rimanenti elementi dell'array di destra in a[k]
            j++;
        }
    }
}

void merge_sort(int a[], int l, int r) { /* Esecuzione dell'algoritmo merge sort sull'array a tra l'indice sinistro l e l'indice destro r.
                                            Questa funzione implementa l'algoritmo ricorsivo di merge sort, che divide l'array nelle porzioni tra l ed r 
                                            e chiama se stesso in ciascuna porzione, prima di di unire le porzioni ordinate dell'array risultante */
    if (l < r) //fermiamo la ricorsione quando l >= r
    {
    int m = (l+r)/2; //trovo il punto medio di l ed r
    merge_sort(a, l, m); //applico la funzione ricorsivamente alle porzioni sinistra e destra divise dal punto medio
    merge_sort(a, m + 1, r);
    merge_sorted_arrays(a, l, m, r); //a questo punto entrambe le porzioni dell'array sono state ordinate e possiamo quindi unirle
    }
}

void adapted_insertion_sort(int arr[], int l, int r) //funzione insertion sort che prende in ingresso l'array e i suoi estremi per calcolarne la dimensione
{
    int n = r - l + 1; //con questa operazione calcoliamo la dimensione dell'array
	int i, key, j; //svolgimento classico di insertion sort, con i, j e key che si occupano del riordinamento dell'array
	for (i = 1; i < n; i++) { //ciclo for per i che va da 1 alla dimensione dell'array incremento i di 1
		key = arr[i]; //key tiene traccia dell'elemento da comparare
		j = i - 1; //j è impostato a i-1 perché dobbiamo confrontare i con tutti gli elementi precedenti ad esso

		while (j >= l && arr[j] > key) { //le condizioni del while sono che j>=0 per rimanere all'interno dell'array, e che l'elemento indicato da j sia più grande di key
			arr[j + 1] = arr[j]; //questo assegnamento serve a shiftare gli elementi più grandi di key
			j = j - 1; //j=j-1 serve a fare il check all'indietro di tutto l'array
		}
		arr[j + 1] = key;  //inserisco finalmente key nel posto in cui deve stare in modo da ordinare l'array elemento per elemento
	}
}

void hybrid_sort(int a[], int l, int r) { /*funzione hybrid sort che utilizza insertion sort per array con una lunghezza minore di un certo k
                                            (calcolato in base alla macchina su cui si sta lavorando) e merge sort per array di lunghezza
                                            superiore a quel dato k. Questa versione ibrida consente di migliorare il rendimento di merge sort*/
    if ((r - l + 1) > 90) { //su questa macchina k=90, valore della lunghezza dell'array entro il quale insertion sort si comporta meglio di merge sort
        int m = (l + r) / 2; //svolgimento classico di merge sort
        hybrid_sort(a, l, m);
        hybrid_sort(a, m + 1, r);
        merge_sorted_arrays(a, l, m, r);
    }
    else {
        adapted_insertion_sort(a, l, r); //chiamata all'adapted insertion sort se la dimensione dell'array è <= 90
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
        //printf("Clock cycles: %d --- Elements: %d\n", time, length);
        printf("%f ", time);
    }
}

int main() {
    int seed=13, min_length=5, max_length=500;
    experiment(min_length, max_length, seed);
    return 0;
}
