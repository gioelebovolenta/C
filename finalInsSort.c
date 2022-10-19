#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void randarr(int arr[], int length, int max){ /*funzione randarr che prende in ingresso l'array e ci inserisce numeri casuali dati dalla funzione rand con seed 13*/
    
    int i, j;
    for(i=0;i<length;i++){ /*ciclo for per assegnare ad ogni elemento dell'array un valore casuale*/
        arr[i]=rand()%max; /*ad arr[i] assegno un valore casuale compreso tra 0 e max*/
	}
}

void insertionSort(int arr[], int n) /*funzione insertionSort che prende in ingresso l'array e la sua dimensione*/
{
	int i, key, j; /*svolgimento classico di insertion sort, con i, j e key che si occupano del riordinamento dell'array*/
	for (i = 1; i < n; i++) { /*ciclo for per i che va da 1 alla dimensione dell'array incremento i di 1*/
		key = arr[i]; /*key tiene traccia dell'elemento da comparare*/
		j = i - 1; /*j è impostato a i-1 perché dobbiamo confrontare i con tutti gli elementi precedenti ad esso*/

		while (j >= 0 && arr[j] > key) { /*le condizioni del while sono che j>=0 per rimanere all'interno dell'array, e che l'elemento indicato da j sia più grande di key*/
			arr[j + 1] = arr[j]; /*questo assegnamento serve shiftare gli elementi più grandi di key*/
			j = j - 1; /*j=j-1 serve a fare il check all'indietro di tutto l'array*/
		}
		arr[j + 1] = key;  /*inserisco finalmente key nel posto in cui deve stare in modo da ordinare l'array elemento per elemento*/
	}
}

int main()
{
	srand(13); /*srand con seed 13*/
    
	int length, max=1000, t_start, t_end, t_elapsed, t_tot=0; /*variabili per la creazione dell'array e per il calcolo dei cicli di clock necessari per il sort*/
    for(length=10; length <= 100; length += 10){
	printf("\nSize of array: %d", length); /*can go from 0 to 2094329*/
    
	int randArray[length]; /*imposto la dimensione di randArray*/
    
    randarr(randArray, length, max); /*chiamo la funzione randarr*/

    int n = sizeof(randArray) / sizeof(randArray[0]); /*ad n assegno la dimensione dell'array non in byte, utile successivamente alla funzone insertion sort*/
    
	t_start = clock(); /*assegno a t_start i cicli di clock effettuati fino ad allora*/
	insertionSort(randArray, n); /*chiamata ad insertion sort*/
	t_end = clock(); /*assegno a t_end i cicli di clock effettuati fino ad allora; chiaramente saranno di più di t_start perché nel mentre sono state effettuate delle istruzioni*/
	t_elapsed = t_end - t_start; /*t_elapsed contiene la differenza fra t_end e t_start, in modo tale da avere il numero di cicli effettuati da insertion sort in questo porgramma*/
	t_tot = t_tot + t_elapsed; /*t_tot accumula i cicli effettuati di volta in volta*/
	printf("\n\nTime needed to sort %d elements: %d clock cycles\n", length, t_tot); /*printf per stampare a video i cicli di clock necessari a riordinare ogni array*/
    }

    printf("\n");

    return 0;
}