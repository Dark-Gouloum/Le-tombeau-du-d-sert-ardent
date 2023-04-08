/**
	* \file src/commun_perso.c
	* \brief Définition de l'objet personnage.
	* \author Dylan GRAMMONT
	* \version 0.1
	* \date Mer. 22 Mars 2023 23:59:23
	*
	* L'objet personnage sert à gérer les personnages du jeu.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../lib/commun_perso.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
static int lancer_de(int stat, int statMax){
	int rng = rand() % statMax+1;
	if( rng > STAT_NORM(stat,statMax) ){
		printf("\nRng echoue: %d\n", rng);
		return 0;
	} else {
		printf("\nrng pas echoue : %d\n", rng);
		return 1;
	}
}

static void attribuer_personnage_bis(personnage_t * personnage, int force, int intelligence, int PV, int armure, int critique, int agilite, char * nom){
	if( !personnage ){
		return;
	}
	personnage->force = force;
	personnage->intelligence = intelligence;
	personnage->PV = PV;
	personnage->armure = armure;
	personnage->critique = critique;
	personnage->agilite = agilite;
	if( !(personnage->nom) ){
		free( personnage->nom );
		personnage->nom = NULL;
	}
	if( nom ){
		personnage->nom = (char*)malloc( sizeof(char) * (strlen(nom)+1) );
		strcpy( personnage->nom , nom );
	}
}
extern void attribuer_personnage(void * personnage, int force, int intelligence, int PV, int armure, int critique, int agilite, char * nom){
	attribuer_personnage_bis(personnage,force,intelligence,PV,armure,critique,agilite,nom);
}

static void assembleStr(char *msg, char *tmp, char *sType, int vType, int taille, char *pattern){
	int i=0, j=0 , len=strlen(pattern);
	tmp[i++] = '\t';
	tmp[i++] = '-';
	tmp[i++] = '0';
	strncpy(tmp,sType,taille-10);
	i = strlen(tmp);
	while( i < (taille-10) ){
		if( j == len ){
			j = 0;
		}
		tmp[i++] = pattern[j++];
	}
	tmp[i] = '\0';
	char TMP[10];
	sprintf(TMP,"-> : %d\n",vType);
	strcat(tmp,TMP);
	strcat(msg,tmp);
}
static err_t lis_personnage_bis( personnage_t *personnage , char *type, char **msg, int t_Ligne){
	if( !msg ){
		MSG_ERR(E_ARGUMENT,"Pas de zone de retour pour le texte");
		return(E_ARGUMENT);
	}
	if( *msg ){
		MSG_ERR(E_ARGUMENT,"Zone de retour pour le texte déjà occupé");
		return(E_ARGUMENT);
	}
	if( !personnage ){
		MSG_ERR(E_ARGUMENT,"Personnage inexistant");
		return(E_ARGUMENT);
	}
	char *sType = ( (type)?(type):("personnage") );
	*msg = malloc( sizeof(char) * (strlen(sType)+strlen(personnage->nom)+32+140) );
	if( !(*msg) ){
		MSG_ERR(E_MEMOIRE,"malloc à échoué, pas assez d'espace disponible");
		return(E_MEMOIRE);
	}
	char tmp[t_Ligne];
	snprintf(*msg,t_Ligne,"Le %s %s à comme statistique :\n",sType,personnage->nom);
	assembleStr(*msg,tmp,"PV",STAT_NORM(personnage->PV,STAT_MAX_PV),t_Ligne," -");
	assembleStr(*msg,tmp,"Force",STAT_NORM(personnage->force,STAT_MAX_FORCE),t_Ligne," -");
	assembleStr(*msg,tmp,"Agilite",STAT_NORM(personnage->agilite,STAT_MAX_AGILI),t_Ligne," -");
	assembleStr(*msg,tmp,"Armure",STAT_NORM(personnage->armure,STAT_MAX_ARMURE),t_Ligne," -");
	assembleStr(*msg,tmp,"Critique",STAT_NORM(personnage->critique,STAT_MAX_CRITIQ),t_Ligne," -");
	assembleStr(*msg,tmp,"Intelligence",STAT_NORM(personnage->intelligence,STAT_MAX_INTEL),t_Ligne," -");
	return(E_OK);
}
extern err_t lis_personnage( void *personnage , char *type, char **msg, int tailleLigne){
	return lis_personnage(personnage,type,msg,tailleLigne);
}

static void afficher_personnage_bis( personnage_t *personnage , char *type ){
	char *msg = NULL;
	if(( lis_personnage_bis(personnage,type,&msg,10) )){
		MSG_ERR2("Impossible d'écrire la ligne");
		return;
	}
	printf("%s",msg);
	free(msg);
	return;
}
extern void afficher_personnage( void *personnage , char *type ){
	afficher_personnage_bis(personnage,type);
}

static void combat_personnage_bis( personnage_t *att, personnage_t *def ){
	if (lancer_de(def->agilite, EPREUVE_FACILE)){
		printf("L'attaquant a raté son attaque.\n");
	} else {
		int degat = 0;
		if (lancer_de(att->critique, EPREUVE_DIFF)){
			printf("CRITIQUE !\n");
			degat = ((att->force) * 2) - (def->armure);
		} else {
			degat = (att->force) - (def->armure);
		}
		if( degat < 0 ){ degat = 0; }
		def->PV-= degat;
		printf("%s a infligé %i dégats à %s.\n", att->nom, degat, def->nom);
	}
}
extern void combat_personnage( void *attaquant, void *defenseur ){
	combat_personnage_bis( attaquant , defenseur );
}

static int crochetageBis(personnage_t *perso){
	if (lancer_de(perso->agilite, EPREUVE_FACILE)){
		printf("Vous avez Reussi  votre crochetage.\n");
		return 0;
	} else {
		return 1;
	}
}
extern int crochetage(void *perso){
	return crochetageBis(perso);
}
// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

