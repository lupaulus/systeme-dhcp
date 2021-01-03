#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int boucle = 0;
int compteur = 0;

void handlerSIGINT(){
    compteur++;
	printf("\n Un signal SIGINT a été reçu. Valeur du compteur: %d\n", compteur);
}

void handlerSIGTERM(){
	printf("Un signal SIGTERM a été reçu. Fin du programme. \n");
	printf("Valeur du compteur: %d\n", compteur);
	boucle = 1;
}

int main ()
{ 
    printf("Exercice compteur \n");
    printf("Envoyez des signaux SIGINT avec CTRL+C \n");

    // écoutes des signaux avec fonction handler à la réception 
    signal(SIGINT, handlerSIGINT);
    signal(SIGTERM, handlerSIGTERM);
    
    // boucle tant qu'aucun SIGTERM n'est reçu.
    while (boucle == 0)
    {
    } 
    return 0;
}