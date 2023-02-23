#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define N 10
#define MINE 20
#define X 'X' // Case non découverte
#define M 'M' // Case minée

typedef char tab[N][N];

int a = 3;
void func(a);


void Ini(char a[N][N], char c[N][N]);
//______________________________________________________________________________________________________
void niveauDeJeu(tab, tab);
void AfficheT(tab);
void placeM(tab);
void jeu(tab, tab);
char CBM(tab, tab, int, int);
void ClearInput();
char getInputChar(const char* message, const char* authorizedCharacter, int length);

int main() {
	tab TM; // Tableau des mines
	tab TJ; // Tableau de jeu
	char ON = 'o';
	while (ON == 'o') {
		srand((unsigned int)time(NULL));

		Ini(TM, TJ);

		niveauDeJeu(TM, TJ);

		placeM(TM); // Placement des mines (M)

		jeu(TM, TJ);

		ON = getInputChar("Voulez vous rejouez ? \n o : oui  n : non", "on", 2);

		system("cls");
	}
	if (ON == 'n') {
		printf("\nReessayer une autre fois\n");
	}
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
//______________________________________________________________________________________________________
void niveauDeJeu(tab TM, tab TJ) {
	int niveau;
	niveau = getInputInt("Quel niveau souhaitez-vous ? [1, 2, 3]", 1, 4);

	switch (niveau) {
	case 1:
		MINE == 4;
		N == 5;
		break;
	case 2:
		MINE == 8;
		N == 7;
		break;
	case 3:
		MINE == 25;
		N == 10;
		break;
	}
}
//______________________________________________________________________________________________________

void ClearInput()
{
	while (getchar() != '\n');
}

int getInputInt(const char* message, int min, int max)
{
	int value;
	int error;
	do {
		printf("%s", message);
		error = scanf_s("%d", &value);
		ClearInput();
	} while ((error == 0) || (value < min) || (value >= max));
	return value;
}

char getInputChar(const char* message, const char* authorizedCharacter, int length)
{
	int error_scan;
	int error_char;
	char caract;

	do {
		printf("%s\n", message);
		error_scan = scanf_s("%c", &caract);
		ClearInput();

		error_char = 0;
		for (int i = 0; i < length; ++i) {
			if (caract == authorizedCharacter[i]) {
				error_char = 1;
			}
		}
	} while ((error_scan == 0) || (error_char == 0));

	return caract;
}

void jeu(tab TM, tab TJ) {
	char* result;
	int CL;
	int CC;
	int perdu = -1;
	int compteur = 0; // Pour compter combien de cases ont été découverte
	int nbcasesm = N * N - MINE; // Nombre de cases sans mine

	printf("\nJeu du demineur\n\n");

	while ((perdu == -1) && (compteur != nbcasesm)) {
		AfficheT(TJ);

		CL = getInputInt("ligne : ", 0, N);

		CC = getInputInt("Colonne : ", 0, N);

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
				result = CBM(TM, TJ, CL, CC); // Recherche du nombre de mines aux alentours
				compteur++; // Accrémentation du compteur de case
				if (result == '0') {
					CBM(TM, TJ, CL, CC + 1);
					CBM(TM, TJ, CL + 1, CC);
					CBM(TM, TJ, CL + 1, CC + 1);
					CBM(TM, TJ, CL, CC - 1);
					CBM(TM, TJ, CL + 1, CC + 1);
				}
			}
		}
	}

	if (perdu == 1) {
		printf("Game Over\n\n");

	}
	else {
		if (compteur == nbcasesm)
		{
			printf("Vous avez gagne!\n\n");
		}
	}
}

int getMineArround(tab T)
{
}

char CBM(tab T, tab TJ, int i, int j) {
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
			return TJ[i][j];
		case 1:
			TJ[i][j] = '1';
			return TJ[i][j];
		case 2:
			TJ[i][j] = '2';
			return TJ[i][j];
		case 3:
			TJ[i][j] = '3';
			return TJ[i][j];
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
			return TJ[i][j];
		case 1:
			TJ[i][j] = '1';
			return TJ[i][j];
		case 2:
			TJ[i][j] = '2';
			return TJ[i][j];
		case 3:
			TJ[i][j] = '3';
			return TJ[i][j];
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
			return TJ[i][j];
		case 1:
			TJ[i][j] = '1';
			return TJ[i][j];
		case 2:
			TJ[i][j] = '2';
			return TJ[i][j];
		case 3:
			TJ[i][j] = '3';
			return TJ[i][j];
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
			return TJ[i][j];
		case 1:
			TJ[i][j] = '1';
			return TJ[i][j];
		case 2:
			TJ[i][j] = '2';
			return TJ[i][j];
		case 3:
			TJ[i][j] = '3';
			return TJ[i][j];
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
			return TJ[i][j];
		case 1:
			TJ[i][j] = '1';
			return TJ[i][j];
		case 2:
			TJ[i][j] = '2';
			return TJ[i][j];
		case 3:
			TJ[i][j] = '3';
			return TJ[i][j];
		case 4:
			TJ[i][j] = '4';
			return TJ[i][j];
		case 5:
			TJ[i][j] = '5';
			return TJ[i][j];
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
			return TJ[i][j];
		case 1:
			TJ[i][j] = '1';
			return TJ[i][j];
		case 2:
			TJ[i][j] = '2';
			return TJ[i][j];
		case 3:
			TJ[i][j] = '3';
			return TJ[i][j];
		case 4:
			TJ[i][j] = '4';
			return TJ[i][j];
		case 5:
			TJ[i][j] = '5';
			return TJ[i][j];
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
			return TJ[i][j];
		case 1:
			TJ[i][j] = '1';
			return TJ[i][j];
		case 2:
			TJ[i][j] = '2';
			return TJ[i][j];
		case 3:
			TJ[i][j] = '3';
			return TJ[i][j];
		case 4:
			TJ[i][j] = '4';
			return TJ[i][j];
		case 5:
			TJ[i][j] = '5';
			return TJ[i][j];
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
			return TJ[i][j];
		case 1:
			TJ[i][j] = '1';
			return TJ[i][j];
		case 2:
			TJ[i][j] = '2';
			return TJ[i][j];
		case 3:
			TJ[i][j] = '3';
			return TJ[i][j];
		case 4:
			TJ[i][j] = '4';
			return TJ[i][j];
		case 5:
			TJ[i][j] = '5';
			return TJ[i][j];
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
			return TJ[i][j];
		case 1:
			TJ[i][j] = '1';
			return TJ[i][j];
		case 2:
			TJ[i][j] = '2';
			return TJ[i][j];
		case 3:
			TJ[i][j] = '3';
			return TJ[i][j];
		case 4:
			TJ[i][j] = '4';
			return TJ[i][j];
		case 5:
			TJ[i][j] = '5';
			return TJ[i][j];
		case 6:
			TJ[i][j] = '6';
			return TJ[i][j];
		case 7:
			TJ[i][j] = '7';
			return TJ[i][j];
		case 8:
			TJ[i][j] = '8';
			return TJ[i][j];
		}
	}
}