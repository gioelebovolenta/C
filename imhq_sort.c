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

void quicksort(int array[], int low, int high) //applico l'algoritmo quick sort tra gli indici low e high di ogni array da esaminare
{
    if (low < high)
    {
        int pivot_index = partition(array, low, high); //partiziona l'array rispetto ad un pivot e ritorna l'indice dell'elemento pivot

        quicksort(array, low, pivot_index - 1); //applico quicksort alla parte sinistra del sottoarray

        quicksort(array, pivot_index + 1, high); //applico quicksort alla parte destra del sottoarray
    }
}

int rand_partition(int array[], int low, int high) /*questa procedura partiziona l'array tra gli indici low e high rispetto a un valore pivot calcolato 
                                                    in maniera randomica tra i due indici*/
{   
    int pivot_index = low + rand() % (high - low + 1);

    swap(array, pivot_index, high); //scambio l'indice del pivot con high, l'ultima posizione dell'array considerato

    int pivot_value = array[high]; //ora ciò che c'è in pivot_value è dato dall'ultimo elemento dell'array, ossia l'indice scelto casualmente
    
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
                dove dividere l'array quando applicare l'algoritmo ai risultanti sottoarray*/
}

void rand_quicksort(int array[], int low, int high) /*applico l'algoritmo randomized quicksort tra gli indici low e high di ogni array da esaminare*/
{
    if (low < high)
    {
        int pivot_index = rand_partition(array, low, high); //partiziona l'array rispetto ad un pivot scelto casualmente e ritorna l'indice dell'elemento pivot

        rand_quicksort(array, low, pivot_index - 1); //applico rand_quicksort alla parte sinistra del sottoarray

        rand_quicksort(array, pivot_index + 1, high); //applico rand_quicksort alla parte destra del sottoarray
    }
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
    int mid=(low+high)/2; //trovo l'indice centrale all'array da partizionare
    int pivot_index = median_of_three(array,low,high,mid); /*calcolo l'indice della mediana dei tre elementi presi in considerazione, ossia il primo
                                                            elemento dell'array da partizionare, l'ultimo, e quello centrale, e lo uso come pivot*/
    
    swap(array, pivot_index, high); //scambio l'elemento pivot con l'elemento in ultima posizione dell'array
    
    int pivot_value = array[high]; //ora ciò che c'è in pivot_value è dato dall'ultimo elemento dell'array, ossia quello scelto con la mediana di 3
    
    int i = low-1; /*l'algoritmo di partizionamento posizionerà gli elementi minori del pivot alla sua sinistra, con i che terrà traccia
                    di dove finiscono gli elementi minori del pivot e di dove iniziano gli elementi maggiori del pivot.
                    Questa operazione ci permette di partire dalla posizione precedente alla posizione iniziale dell'array da partizionare*/
    
    for (int j = low; j < high; j++) //ciclo for che scorre l'intero array da partizionare, escluso il pivot
    {
        if (array[j] <= pivot_value) { /*se il valore dell'elemento in posizione j è minore del valore del pivot, scambio j con
                                        il primo elemento maggiore del pivot, che si trova in posizione i+1*/
            i++;
            swap(array, i, j);
        }
    }
    
    swap(array, i+1, high); //ora sappiamo che il valore all'indice i+1 è maggiore o uguale al pivot, quindi li scambiamo per completare la partizione
    
    return i+1; /*l'indice i+1 ora contiene il valore del pivot, quindi lo ritorniamo in modo tale che la procedura Mo3_quicksort sappia
                dove dividere l'array quando applicare l'algoritmo ai risultanti sottoarray*/
}

void Mo3_quicksort(int array[], int low, int high) //applico l'algoritmo median of three quicksort tra gli indici low e high di ogni array esaminato
{
    if (low < high)
    {
        int pivot_index = Mo3_partition(array, low, high); /*partiziona l'array rispetto ad un pivot scelto con la mediana di 3 e ritorna l'indice dell'elemento pivot*/

        Mo3_quicksort(array, low, pivot_index - 1); //applico median of three quicksort alla parte sinistra del sottoarray

        Mo3_quicksort(array, pivot_index + 1, high); //applico median of three quicksort alla parte destra del sottoarray
    }
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

void Mo3_tail_quicksort(int array[], int low, int high) //applico l'algoritmo tail median of three quicksort tra gli indici low e high di ogni array da esaminare
{
    while (low < high)
    {
        int pivot_index = Mo3_partition(array, low, high); //partiziona l'array rispetto ad un pivot scelto con la mediana di 3 e ritorna l'indice dell'elemento pivot
        if(pivot_index < (low+high)/2) { //procedura standard di quicksort con l'eliminazione della ricorsione in coda
            Mo3_tail_quicksort(array, low, pivot_index-1);
            low=pivot_index+1;
        } else {
            Mo3_tail_quicksort(array, pivot_index+1, high);
            high=pivot_index-1;
        }
    }
}

double single_experiment(int length, int max_instances, char alg[], int seed) { /*single experiment riproduce l'ordinamento degli array in base all'algoritmo
                                                                                di ordinamento selezionato. Vengono utilizzati i cicli di clock per poter comparare
                                                                                la durata effettiva dei vari ordinamenti e delle variabili di controllo per poterli calcolare*/
    double t_start, t_end, t_elapsed, t_tot=0.0;
    for(int i=1; i<=max_instances; i++) {
        int array[length];
        randarr(array, length, seed);
        if (strcmp(alg, "IS")==0) {
            t_start=clock();
            insertion_sort(array, length);
            t_end=clock();
            t_elapsed=t_end-t_start;
            t_tot=t_tot+t_elapsed;
        } else if (strcmp(alg, "MS")==0) {
            t_start=clock();
            merge_sort(array, 0, length-1);
            t_end=clock();
            t_elapsed=t_end-t_start;
            t_tot=t_tot+t_elapsed;
        } else if (strcmp(alg, "HS")==0) {
            t_start=clock();
            hybrid_sort(array, 0, length-1);
            t_end=clock();
            t_elapsed=t_end-t_start;
            t_tot=t_tot+t_elapsed;
        } else if (strcmp(alg, "QS")==0) {
            t_start=clock();
            quicksort(array, 0, length-1);
            t_end=clock();
            t_elapsed=t_end-t_start;
            t_tot=t_tot+t_elapsed;
        } else if (strcmp(alg, "RQS")==0) {
            t_start=clock();
            rand_quicksort(array, 0, length-1);
            t_end=clock();
            t_elapsed=t_end-t_start;
            t_tot=t_tot+t_elapsed;
        } else if (strcmp(alg, "M3QS")==0) {
            t_start=clock();
            Mo3_quicksort(array, 0, length-1);
            t_end=clock();
            t_elapsed=t_end-t_start;
            t_tot=t_tot+t_elapsed;
        } else if (strcmp(alg, "TQS")==0) {
            t_start=clock();
            tail_quicksort(array, 0, length-1);
            t_end=clock();
            t_elapsed=t_end-t_start;
            t_tot=t_tot+t_elapsed;
        } else if (strcmp(alg, "M3TQS")==0) {
            t_start=clock();
            Mo3_tail_quicksort(array, 0, length-1);
            t_end=clock();
            t_elapsed=t_end-t_start;
            t_tot=t_tot+t_elapsed; //utile a calcolare il valore medio per ogni istanza
        }
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
        //double timeIS=single_experiment(length, max_instances, "IS", seed);
        double timeMS=single_experiment(length, max_instances, "MS", seed);
        double timeHS=single_experiment(length, max_instances, "HS", seed);
        double timeQS=single_experiment(length, max_instances, "QS", seed);
        double timeRQS=single_experiment(length, max_instances, "RQS", seed);
        double timeM3QS=single_experiment(length, max_instances, "M3QS", seed);
        double timeTQS=single_experiment(length, max_instances, "TQS", seed);
        double timeM3TQS=single_experiment(length, max_instances, "M3TQS", seed);

        printf("Clock cycles: %lf MS -- %lf HS -- %lf QS -- %lf RQS -- %lf M3QS -- %lf TQS -- %lf M3TQS <----------> Elements: %d\n", 
        timeMS, timeHS, timeQS, timeRQS, timeM3QS, timeTQS, timeM3TQS, length);
    }
}

int main() {
    int seed=13, min_length=5, max_length=500;
    experiment(min_length, max_length, seed);
    return 0;
}
