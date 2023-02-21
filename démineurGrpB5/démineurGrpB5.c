#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define N 10
#define MINE 20
#define X 'X' // Case non découverte
#define M 'M' // Case minée

typedef char tab[N][N];

void Ini(tab, tab);
void AfficheT(tab);
void placeM(tab);
void jeu(tab, tab);
void CBM(tab, tab, int, int);

int main() {
	tab TM; // Tableau des mines
	tab TJ; // Tableau de jeu

	srand((unsigned int)time(NULL));

	Ini(TM, TJ);

	placeM(TM); // Placement des mines (M)

	jeu(TM, TJ);

	return 0;
}

void Ini(tab TM, tab TJ) {
	int i, j;

	for (i = 00; i < N; i++) {
		for (j = 00; j < N; j++) {
			TM[i][j] = X;
			TJ[i][j] = X;
		}
	}
}

void AfficheT(tab T) {
	int i, j;
	int c = 00;

	printf("   ");
	for (c = 00; c < N; c++) {
		printf("%d  ", c);
	}
	c = 00;
	printf("\n\n");

	for (i = 00; i < N; i++) {
		printf("%d  ", c);
		c++;
		for (j = 00; j < N; j++) {
			printf("%c  ", T[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void placeM(tab TM) {
	int i, j;
	int cm;

	for (cm = 0; cm < MINE; cm++) {
		i = rand() % N;
		j = rand() % N;
		if (TM[i][j] == M) {
			while (TM[i][j] == M) {
				i = rand() % N;
				j = rand() % N;
			}
			TM[i][j] = M;
		}
		else {
			TM[i][j] = M;
		}
	}
}

void ClearInput()
{
	while (getchar() != '\n');
}

void jeu(tab TM, tab TJ) {
	int CL;
	int CC;
	int perdu = -1;
	int compteur = 0; // Pour compter combien de cases ont été découverte
	int nbcasesm = N * N - MINE; // Nombre de cases sans mine

	printf("\nJeu du demineur\n\n");

	while ((perdu == -1) && (compteur != nbcasesm)) {
		AfficheT(TJ);

		int error;
		do {
			printf("Ligne : ");
			error = scanf_s("%d", &CL);
			ClearInput();
		} while ((error == 0) || (CL < 0) || (CL >= N));


		do {
			printf("Colonne : ");
			error = scanf_s("%d", &CC);
			ClearInput();
		} while ((error == 0) || (CC < 0) || (CC >= N));

		printf("\n");
		system("cls");

		if (TM[CL][CC] == M) {
			perdu = 1; // HAHA! VOUS AVEZ PERDU!
			printf("C'est une mine :O\n\n");
		}
		else {
			if (TJ[CL][CC] != X) {
				printf("Vous avez deja rentre cette valeur.\n\n");
			}
			else {
				CBM(TM, TJ, CL, CC); // Recherche du nombre de mines aux alentours
				compteur++; // Accrémentation du compteur de case
			}
		}
	}

	if (perdu == 1) {
		printf("Game Over\n\n");
	}
	else {
		printf("Vous avez gagné!\n\n");
	}
}
void CBM(tab T, tab TJ, int i, int j) {
	int c = 0;

	if ((i == N - 1) && (j == N - 1)) { // Case "En bas à droite"
		if (T[i - 1][j - 1] == M) {
			c++;
		}
		if (T[i][j - 1] == M) {
			c++;
		}
		if (T[i - 1][j] == M) {
			c++;
		}
		switch (c) { // Attribution de la valeur
		case 0:
			TJ[i][j] = '0';
			break;
		case 1:
			TJ[i][j] = '1';
			break;
		case 2:
			TJ[i][j] = '2';
			break;
		case 3:
			TJ[i][j] = '3';
			break;
		}
	}
	else if ((i == 0) && (j == N - 1)) { // Case "En haut à droite"
		if (T[i][j - 1] == M) {
			c++;
		}
		if (T[i - 1][j - 1] == M) {
			c++;
		}
		if (T[i - 1][j] == M) {
			c++;
		}
		switch (c) { // Attribution de la valeur
		case 0:
			TJ[i][j] = '0';
			break;
		case 1:
			TJ[i][j] = '1';
			break;
		case 2:
			TJ[i][j] = '2';
			break;
		case 3:
			TJ[i][j] = '3';
			break;
		}
	}
	else if ((i == 0) && (j == 0)) { // Case "En haut à gauche"
		if (T[i][j + 1] == M) {
			c++;
		}
		if (T[i + 1][j + 1] == M) {
			c++;
		}
		if (T[i + 1][j] == M) {
			c++;
		}
		switch (c) { // Attribution de la valeur
		case 0:
			TJ[i][j] = '0';
			break;
		case 1:
			TJ[i][j] = '1';
			break;
		case 2:
			TJ[i][j] = '2';
			break;
		case 3:
			TJ[i][j] = '3';
			break;
		}
	}
	else if ((i == N - 1) && (j == 0)) { // Case "En bas à gauche"
		if (T[i - 1][j] == M) {
			c++;
		}
		if (T[i - 1][j + 1] == M) {
			c++;
		}
		if (T[i][j + 1] == M) {
			c++;
		}
		switch (c) { // Attribution de la valeur
		case 0:
			TJ[i][j] = '0';
			break;
		case 1:
			TJ[i][j] = '1';
			break;
		case 2:
			TJ[i][j] = '2';
			break;
		case 3:
			TJ[i][j] = '3';
			break;
		}
	}
	else if (i == 0) { // Ligne du haut
		if (T[i][j - 1] == M) {
			c++;
		}
		if (T[i + 1][j - 1] == M) {
			c++;
		}
		if (T[i + 1][j] == M) {
			c++;
		}
		if (T[i + 1][j + 1] == M) {
			c++;
		}
		if (T[i][j + 1] == M) {
			c++;
		}
		switch (c) { // Attribution de la valeur
		case 0:
			TJ[i][j] = '0';
			break;
		case 1:
			TJ[i][j] = '1';
			break;
		case 2:
			TJ[i][j] = '2';
			break;
		case 3:
			TJ[i][j] = '3';
			break;
		case 4:
			TJ[i][j] = '4';
			break;
		case 5:
			TJ[i][j] = '5';
			break;
		}
	}
	else if (j == 0) { // Colonne de gauche
		if (T[i - 1][j] == M) {
			c++;
		}
		if (T[i - 1][j + 1] == M) {
			c++;
		}
		if (T[i][j + 1] == M) {
			c++;
		}
		if (T[i + 1][j + 1] == M) {
			c++;
		}
		if (T[i + 1][j] == M) {
			c++;
		}
		switch (c) { // Attribution de la valeur
		case 0:
			TJ[i][j] = '0';
			break;
		case 1:
			TJ[i][j] = '1';
			break;
		case 2:
			TJ[i][j] = '2';
			break;
		case 3:
			TJ[i][j] = '3';
			break;
		case 4:
			TJ[i][j] = '4';
			break;
		case 5:
			TJ[i][j] = '5';
			break;
		}
	}
	else if (i == N - 1) { // Ligne du bas
		if (T[i][j - 1] == M) {
			c++;
		}
		if (T[i - 1][j - 1] == M) {
			c++;
		}
		if (T[i - 1][j] == M) {
			c++;
		}
		if (T[i - 1][j + 1] == M) {
			c++;
		}
		if (T[i][j + 1] == M) {
			c++;
		}
		switch (c) { // Attribution de la valeur
		case 0:
			TJ[i][j] = '0';
			break;
		case 1:
			TJ[i][j] = '1';
			break;
		case 2:
			TJ[i][j] = '2';
			break;
		case 3:
			TJ[i][j] = '3';
			break;
		case 4:
			TJ[i][j] = '4';
			break;
		case 5:
			TJ[i][j] = '5';
			break;
		}
	}
	else if (j == N - 1) { // Colonne de droite
		if (T[i - 1][j] == M) {
			c++;
		}
		if (T[i - 1][j - 1] == M) {
			c++;
		}
		if (T[i][j - 1] == M) {
			c++;
		}
		if (T[i + 1][j - 1] == M) {
			c++;
		}
		if (T[i + 1][j] == M) {
			c++;
		}
		switch (c) { // Attribution de la valeur
		case 0:
			TJ[i][j] = '0';
			break;
		case 1:
			TJ[i][j] = '1';
			break;
		case 2:
			TJ[i][j] = '2';
			break;
		case 3:
			TJ[i][j] = '3';
			break;
		case 4:
			TJ[i][j] = '4';
			break;
		case 5:
			TJ[i][j] = '5';
			break;
		}
	}
	else { // N'importe où ailleurs
		if (T[i][j + 1] == M) {
			c++;
		}
		if (T[i + 1][j + 1] == M) {
			c++;
		}
		if (T[i + 1][j] == M) {
			c++;
		}
		if (T[i + 1][j - 1] == M) {
			c++;
		}
		if (T[i][j - 1] == M) {
			c++;
		}
		if (T[i - 1][j - 1] == M) {
			c++;
		}
		if (T[i - 1][j] == M) {
			c++;
		}
		if (T[i - 1][j + 1] == M) {
			c++;
		}
		switch (c) { // Attribution de la valeur
		case 0:
			TJ[i][j] = '0';
			break;
		case 1:
			TJ[i][j] = '1';
			break;
		case 2:
			TJ[i][j] = '2';
			break;
		case 3:
			TJ[i][j] = '3';
			break;
		case 4:
			TJ[i][j] = '4';
			break;
		case 5:
			TJ[i][j] = '5';
			break;
		case 6:
			TJ[i][j] = '6';
			break;
		case 7:
			TJ[i][j] = '7';
			break;
		case 8:
			TJ[i][j] = '8';
			break;
		}
	}
}
