#ifndef _BLOCTEXT_H_
#define _BLOCTEXT_H_

/**
	* \file lib/blocText.h
	* \brief Définition de l'objet blocText.
	* \author Erwan PECHON
	* \version 0.1
	* \date Lun. 03 Avril 2023 20:43:50
	*
	* L'objet blocText sert à afficher du texte dans un bloc donnée.
	* Il garde en mémoire jusqu'où le texte à était écrit.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include "commun.h"
#include "fenetre.h"
#include "liste.h"
#include "police.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)
#define B_FIN 0
#define B_CONT 1
#define B_PAUSE 2

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)
/** \brief La structure blocText_t.
	* \author Erwan PECHON
	*
	* La structure blocText_t sert à afficher du texte dans un bloc donnée.
	*
	*/
typedef struct blocText_s {
#include "attributs_widget.h"
	liste_t *lstPage; //!< La liste des images de chaque pages ayant était affiché
	int i; // La liste de la page actuellement affiché+1 , 0 si aucune page

	SDL_Point pos; // Le point en bas à droite de la derniere ligne ajouté dans l'image
	SDL_Point posMin; // Le point en haut à gauche de la zone de texte
	SDL_Point posMax; // Le point en bas à droite de la zone de texte
	SDL_Texture *page; // La zone d'affichage de base du bloc de texte

	bouton_t *prec; // Le bouton remontant le texte
	bouton_t *suiv; // Le bouton défilant le texte

	FILE *fichier; //!< Le fichier où lire le texte
	police_t *police; //!< la police d'écriture du texte
} blocText_t;

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
/**\brief La fonction affichant le nombre d'objet non détruit.
	* \author Erwan PECHON
	*
	* La fonction 'afficherSurvivant_blocText' est prévue pour fonctionner dans le fichier 'projet/test/blocText.c'.
	* Cette fonction affiche le nombre de blocText non-détruit, ainsi que le nombre d'objet inclut dans blocText qui n'ont pas était détruit.
	*
	*/
extern void afficherSurvivant_blocText();

/**\brief La fonction créant un objet blocText_t.
	* \author Erwan PECHON
	* \param[in,out] utilite
	* \return un pointeur sur un blocText_t.
	*
	* La fonction 'creer_blocText' crée un objet blocText.
	*
	*/
extern blocText_t * creer_blocText(fenetre_t *fenetre, char *nom, SDL_Rect *dest, police_t **police, SDL_Color *couleur);
extern err_t blocText_precedant(int argc,...);
extern err_t blocText_suivant(int argc,...);

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

#endif
