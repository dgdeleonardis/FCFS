#include <stdio.h>
#include <stdlib.h>

struct s_elemento{ //definizione elemento della lista
    int value;
    struct s_elemento *next;
};

typedef struct s_elemento elemento;

elemento* aggiungiTesta(elemento* first, int value);//prototipo funzione di aggiunta in testa per calcolo del tempo d'attesa inverso
elemento* aggiungiCoda(elemento* first, int value);//protipo funzione di aggiunta in coda per calcolo del tempo d'attesa diretto
float calcolaTempo(elemento* first, int numeroProcessi);//prototipo funzione che calcola il tempo d'attesa dato un puntatore ad una lista e contatore di processi
void svuotaLista(elemento* first);//prototipo funzione che svuota la lista.

int main(int argc, char** argv) {
    int flag, ordine, i = 0;
    int ExecuteTime;
    float tempoMedio;
    elemento *primo = NULL;
    
    printf("Ordine normale | Ordine inverso (1|0) : ");//Scelta del metodo di calcolo del tempo d'attesa.
    scanf("%d", &ordine);
    do{
        i++;
        printf("Inserisci il tempo d'esecuzione del processo n.%d :", i);
        scanf("%d", &ExecuteTime);
        if (ordine==0){//Se è 1 ogni elemento verrà aggiunto in coda. Se è 0 ogni elemento verrà salvato in testa
            primo=aggiungiTesta(primo, ExecuteTime);
        }
        else{
            primo=aggiungiCoda(primo, ExecuteTime);
        }
        printf("Vuoi inserire un nuovo processo (1|0) : ");;//Conferma dell'utente nel caso voglia inserire un altro processo
        scanf("%d", &flag);
    }while(flag!=0);

    tempoMedio=calcolaTempo(primo, i);//Calcolo del tempo d'attesa tramite funzione apposita
    printf("Tempo di attesa medio: %f\n", tempoMedio);
    
    return (EXIT_SUCCESS);
}

elemento* aggiungiTesta(elemento* first, int value){
    elemento* temp;
    temp = (elemento*) malloc(sizeof(elemento));
    if(temp == NULL) {
        exit(1);
    }
    temp->value=value;
    temp->next = first;
    first = temp;
    return first;
}

elemento* aggiungiCoda(elemento* first, int value){
    elemento* scorri=first;
    elemento* temp;
    temp = (elemento*) malloc(sizeof(elemento));
    if(temp == NULL) {
        exit(1);
    }
    temp->value=value;
    if (first!=NULL){
        while(scorri->next!=NULL){
            scorri=scorri->next;
        }
       scorri->next=temp; 
    }
    else {
        first=temp;
    }
    return first;
}

float calcolaTempo(elemento* first, int numeroProcessi){
    elemento* scorri=first;
    float acc,accExecuteTime=0;
    float tempo=0;
    
    while(scorri->next!=NULL){
        accExecuteTime+=scorri->value;
        acc+=accExecuteTime;
        scorri=scorri->next;
    }
    tempo=acc/numeroProcessi;
    return tempo;
}

void svuotaLista (elemento* first){
    elemento* temp;
    printf("Svuotamento lista in corso...\n");
    while(first!=NULL){
        temp=first->next;
        free(first);
        first=temp;
    }
    printf("Completato.");
}