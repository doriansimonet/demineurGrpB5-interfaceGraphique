#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define N 10

#define X 88 // Case non découverte
#define M 77 // Case minée

typedef char tab[N][N];

int a = 3;
int MINE = 0;
void func(a);


void Ini(char a[N][N], char c[N][N]);
void niveauDeJeu(tab, tab);
void AfficheT(tab);
void placeM(tab);
void jeu(tab, tab);
void ClearInput();
char getInputChar(const char* message, const char* authorizedCharacter, int length);
int getInputInt(const char* message, int min, int max);
int isMine(tab T, int i, int j);
int getMineArround(tab TM,tab TJ, int i, int j);
int NbMinesAutour(tab TM, tab TJ, int i, int j);

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

void niveauDeJeu(tab TM, tab TJ) {
	int niveau;
		niveau = getInputInt("Quel niveau souhaitez-vous ? [1, 2, 3]", 1, 4);

	switch (niveau) {
	case 1:
		MINE = 4;
		printf("La difficulte est de %d et il y as %d mines dans tout le tableaux\n" , niveau, MINE);
		break;
	case 2:
		MINE = 8;
		printf("La difficulte est de %d et il y as %d mines dans tout le tableaux\n" , niveau, MINE);
		break;
	case 3:
		MINE = 25;
		printf("La difficulte est de %d et il y as %d mines dans tout le tableaux\n" , niveau, MINE);
		break;
	}
}


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
	int result = 0;
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
			perdu = 1; // VOUS AVEZ PERDU!
			printf("C'est une mine :O\n\n");
			break;
		}

		if (TJ[CL][CC] != X) {
			printf("Vous avez deja rentre cette valeur.\n\n");
			continue;
		}

		result = getMineArround(TM, TJ, CL, CC); // Recherche du nombre de mines aux alentours
		compteur++; // Accrémentation du compteur de case

		if (result == 48){
			NbMinesAutour(TM, TJ, CL, CC);
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

int isMine(tab T, int i, int j)
{
	if (i < 0 || i >= N)
		return 0;

	if (j < 0 || j >= N)
		return 0;

	if (T[i][j] != M)
		return 0;

	return 1;
}
int getMineArround(tab TM,tab TJ, int i, int j)
{
	int mineCount = 48;

	mineCount += isMine(TM, i - 1, j);
	mineCount += isMine(TM, i + 1, j);
	mineCount += isMine(TM, i - 1, j - 1);
	mineCount += isMine(TM, i - 1, j + 1);
	mineCount += isMine(TM, i + 1, j - 1);
	mineCount += isMine(TM, i + 1, j + 1);
	mineCount += isMine(TM, i, j - 1);
	mineCount += isMine(TM, i, j + 1);
	/*if (mineCount = 48) {
		if (TJ[i][j] != X) {
			return mineCount;
		}
		getMineArround(TM, TJ, i - 1, j);
		getMineArround(TM, TJ, i + 1, j);
		getMineArround(TM, TJ, i - 1, j - 1);
		getMineArround(TM, TJ, i - 1, j + 1);
		getMineArround(TM, TJ, i + 1, j - 1);
		getMineArround(TM, TJ, i + 1, j + 1);
		getMineArround(TM, TJ, i, j - 1);
		getMineArround(TM, TJ, i, j + 1);
	}*/
	TJ[i][j] = mineCount;

	return mineCount;
}

int NbMinesAutour(tab TM, tab TJ, int i, int j)//Il n'y a pas de mines autour donc detruire autour du 0
{
	int place = 0;
	if (TJ[i][j] != X) {
		place += getMineArround(TM, TJ, i - 1, j);
		place += getMineArround(TM, TJ, i + 1, j);
		place += getMineArround(TM, TJ, i - 1, j - 1);
		place += getMineArround(TM, TJ, i - 1, j + 1);
		place += getMineArround(TM, TJ, i + 1, j - 1);
		place += getMineArround(TM, TJ, i + 1, j + 1);
		place += getMineArround(TM, TJ, i, j - 1);
		place += getMineArround(TM, TJ, i, j + 1);
	}

	return place;
}