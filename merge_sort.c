#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void randarr(int arr[], int length, int max){ /*funzione randarr che prende in ingresso l'array e ci inserisce numeri casuali dati dalla funzione rand con seed 13*/
    
    int i, j;
    for(i=0;i<length;i++){ /*ciclo for per assegnare ad ogni elemento dell'array un valore casuale*/
        arr[i]=rand()%max; /*ad arr[i] assegno un valore casuale compreso tra 0 e max*/
	}
}

void merge_sorted_arrays(int a[], int l, int m, int r) //unisce le due porzioni di array ordinate: dall'indice l all'indice m e dall'indice m+1 all'indice r
{
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

int main()
{
    srand(13); /*srand con seed 13*/
    
	int length, max=1000000, t_start, t_end, t_elapsed, t_tot=0; /*variabili per la creazione dell'array e per il calcolo dei cicli di clock necessari per il sort*/
    for(length=1; length <= 500; length++){
	//printf("\nSize of array: %d", length);
    
	int randArray[length]; /*imposto la dimensione di randArray*/
    
    randarr(randArray, length, max); /*chiamo la funzione randarr*/

    //int n = sizeof(randArray) / sizeof(randArray[0]); /*ad n assegno la dimensione dell'array non in byte, utile successivamente alla funzione insertion sort*/
    
	t_start = clock(); /*assegno a t_start i cicli di clock effettuati fino ad allora*/
	merge_sort(randArray, 0, length - 1); /*chiamata ad merge sort*/
	t_end = clock(); /*assegno a t_end i cicli di clock effettuati fino ad allora; chiaramente saranno di più di t_start perché nel mentre sono state effettuate delle istruzioni*/
	t_elapsed = t_end - t_start; /*t_elapsed contiene la differenza fra t_end e t_start, in modo tale da avere il numero di cicli effettuati da insertion sort in questo porgramma*/
	t_tot = t_tot + t_elapsed; /*t_tot accumula i cicli effettuati di volta in volta*/
	printf("\n\nTime needed to sort %d elements: %d clock cycles\n", length, t_tot); /*printf per stampare a video i cicli di clock necessari a riordinare ogni array*/
    }

    printf("\n");

    return 0;
}
