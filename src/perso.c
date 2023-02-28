/**
	* \file src/perso.c
	* \brief Définition de l'objet perso.
	* \author Dylan GRAMMONT
	* \version 0.1
	* \date Mar. 28 Févr. 2023 14:38:44
	*
	* L'objet perso sert à FaitQuelqueChose.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "../lib/perso.h"





// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)
static int unsigned cmpt_perso = 0;

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
	// Fonctions spéciale d'un objet perso

	// Methode commune à tout les objets
static void afficher_perso( personage_t *perso ){
	printf("\nStatistique{\nPV: %d",perso->PV);
	printf("\nForce: %d",perso->force);
	printf("\nAgilite: %d",perso->agilite);
	printf("\nArmure: %d",perso->Armure);
	printf("\nCritique: %d",perso->critique);
	printf("\nintelligence: %d}",perso->intelligence);
	if(liste_taille(perso->listItem)>0){
		perso->listItem->afficher(perso->listItem);
	}

}


static err_t detruire_perso( personage_t **perso ){
	// Suppression des attributs de l'objet perso

    // Écriture des valeurs
	// Suppression de l'objet perso
	
	(*perso)->listItem->detruire(&(*perso)->listItem);
	free( (*perso) );
	(*perso) = NULL;
	// Destruction de l'objet perso réussie
	cmpt_perso--;
	return(E_OK);
}

extern void afficherSurvivant_perso(){
	printf("Il reste %i personage_t.\n",cmpt_perso);
	afficherSurvivant_liste();
	afficherSurvivant_item();
}

extern personage_t * creer_perso(){
	// Définission des variables utiles
	char *nomFonction = "creer_perso : ";

	// Créer l'objet perso
	personage_t *perso = malloc( sizeof(personage_t) );
	if( !perso ){ // malloc à échouer :
		printf("%s%smalloc : malloc à échouer, pas assez de place de place disponible en mémoire.\n",MSG_E,nomFonction);
		return (personage_t*)NULL;
	}

	perso->listItem=creer_liste();

	// Affecter les attributs
	
	perso->agilite=perso->Armure=perso->critique=perso->force=perso->intelligence =0;
	perso->nbObjet=0;

	// Affecter les methodes
	perso->detruire = (err_t (*)(void *))detruire_perso;
	perso->afficher = (void (*)(void *))afficher_perso;

	// Renvoyer le bouton
	cmpt_perso++;
	return perso;
}

extern void sauvegard(personage_t * perso){
    // Ouverture du fichier en mode écriture
    FILE *f = fopen("save.txt", "w");

    // Écriture des valeurs de la structure dans le fichier
    fprintf(f, "%d\n%d\n%d\n%d\n%d\n%d", perso->force, perso->intelligence, perso->PV, perso->Armure, perso->critique, perso->agilite);

    // Fermeture du fichier
    fclose(f);


}

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

