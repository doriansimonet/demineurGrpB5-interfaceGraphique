#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "SDL.h"

#define N 10
#define X 88 // Case non découverte
#define M 77 // Case minée


typedef char tab[N][N];

int a = 3;
int MINE = 0;
int cpt = 0;
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
int getMineArround(tab TM, tab TJ, int i, int j);
void reavealCase(tab TM, tab TJ, int i, int j);



SDL_bool test(SDL_Point point, SDL_Rect rect)
{
	if (point.x >= rect.x && point.x <= (rect.x + rect.w) &&
		point.y >= rect.y && point.y <= (rect.y + rect.h))
		return SDL_TRUE;
	else
		return SDL_FALSE;
}

int setWindowColor(SDL_Renderer* renderer, SDL_Color color)
{
	if (SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a) < 0)
		return -1;
	if (SDL_RenderClear(renderer) < 0)
		return -1;
	return 0;
}

int main()
{
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_Texture* texture = NULL;
	SDL_Surface* tmp = SDL_LoadBMP("ImageBmp.bmp");
	int statut = EXIT_FAILURE;

	/* Initialisation, création de la fenêtre et du renderer. */
	if (0 != SDL_Init(SDL_INIT_VIDEO))
	{
		fprintf(stderr, "Erreur SDL_Init : %s", SDL_GetError());
		goto Quit;
	}
	window = SDL_CreateWindow("SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		500, 500, SDL_WINDOW_SHOWN);
	if (NULL == window)
	{
		fprintf(stderr, "Erreur SDL_CreateWindow : %s", SDL_GetError());
		goto Quit;
	}
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (NULL == renderer)
	{
		fprintf(stderr, "Erreur SDL_CreateRenderer : %s", SDL_GetError());
		goto Quit;
	}
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET, 50, 50);
	if (NULL == texture)
	{
		fprintf(stderr, "Erreur SDL_CreateTexture : %s", SDL_GetError());
		goto Quit;
	}
	if (NULL == tmp)
	{
		fprintf(stderr, "Erreur SDL_LoadBMP : %s", SDL_GetError());
		goto Quit;
	}
	texture = SDL_CreateTextureFromSurface(renderer, tmp);
	SDL_FreeSurface(tmp); /* On libère la surface, on n’en a plus besoin */
	if (NULL == texture)
	{
		fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s", SDL_GetError());
		goto Quit;
	}

	/* C’est à partir de maintenant que ça se passe. */
	for (int i = 0; i < 500; i += 50) {
		for (int j = 0; j < 500; j += 50) {
			int brique = i - j;
			if (brique < 0) {
				brique = brique * (-1);
			}
			brique = (brique / 50);
			if ( brique % 2 == 1 ) {
				SDL_SetRenderDrawColor(renderer, 120, 255, 120, 255);
			}
			else {
				SDL_SetRenderDrawColor(renderer, 100, 200, 0, 255);
			}
			SDL_Rect a = { i,j,50,50 };
			SDL_RenderFillRect(renderer, &a);

		}
	}


	SDL_RenderPresent(renderer);



	SDL_Event event;
	SDL_bool quit = SDL_FALSE;

	while (!quit)
	{
		SDL_WaitEvent(&event);
		if (event.type == SDL_QUIT)
			quit = SDL_TRUE;
		else if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.scancode == SDL_SCANCODE_A)
				printf("scancode A\n");
			if (event.key.keysym.sym == SDLK_a)
				printf("keysym A\n");
		}

		else if (event.type == SDL_MOUSEBUTTONUP)
		{
			if (event.button.button == SDL_BUTTON_LEFT && event.button.clicks >= 2)
				printf("Au moins un double clic gauche\n");
		}

		int x, y;
		Uint32 boutons;

		SDL_PumpEvents();
		boutons = SDL_GetMouseState(&x, &y);
		if (boutons & SDL_BUTTON(SDL_BUTTON_LEFT)) {
			printf("Clic droit à la positions %d - %d\n", x, y);
			for (int i = 0; i < 500; i += 50) {
				for (int j = 0; j < 500; j += 50) {
					if (i < x && x<i+50 && j < y && y<j+50) {
						SDL_Rect dst = { i, j, 50, 50 };
						SDL_SetRenderTarget(renderer, texture);
						int terre = i - j;
						if (terre < 0) {
							terre = terre * (-1);
						}
						terre = (terre / 50);
						if (terre % 2 == 1) {
							SDL_SetRenderDrawColor(renderer, 249, 228, 183, 255);
						}
						else {
							SDL_SetRenderDrawColor(renderer, 213, 186, 152, 255);
						}
						SDL_RenderClear(renderer);
						SDL_SetRenderTarget(renderer, NULL);
						SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h);
						SDL_RenderCopy(renderer, texture, NULL, &dst);
						SDL_RenderPresent(renderer);
					}
				}
				SDL_Delay(20);
			}
		}
	}

	


	statut = EXIT_SUCCESS;

Quit:
	if (NULL != texture)
		SDL_DestroyTexture(texture);
	if (NULL != renderer)
		SDL_DestroyRenderer(renderer);
	if (NULL != window)
		SDL_DestroyWindow(window);
	SDL_Quit();
	return statut;


	/*tab TM; // Tableau des mines
	tab TJ; // Tableau de jeu
	char ON = 'o';
	while (ON == 'o') {
		srand((unsigned int)time(NULL));

		Ini(TM, TJ);

		niveauDeJeu(TM, TJ);

		placeM(TM); // Placement des mines (M)

		jeu(TM, TJ);

		ON = getInputChar("Voulez vous rejouez ? \n o : oui  n : non \n -> ", "on", 2);
		cpt = 0;

		system("cls");
	}
	if (ON == 'n') {
		printf("\nReessayer une autre fois\n");
	}
	return 0;*/

}
void Ini(tab TM, tab TJ) {
	int i, j;

	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			TM[i][j] = X;
			TJ[i][j] = X;
		}
	}
}

void AfficheT(tab T) {
	int i, j;
	int c = 0;

	printf("   ");
	for (c = 0; c < N; c++) {
		printf("%d  ", c);
	}
	c = 0;
	printf("\n\n");

	for (i = 0; i < N; i++) {
		printf("%d  ", c);
		c++;
		for (j = 0; j < N; j++) {
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
		MINE = 10;
		printf("La difficulte est de %d et il y as %d mines dans tout le tableaux\n", niveau, MINE);
		break;
	case 2:
		MINE = 20;
		printf("La difficulte est de %d et il y as %d mines dans tout le tableaux\n", niveau, MINE);
		break;
	case 3:
		MINE = 30;
		printf("La difficulte est de %d et il y as %d mines dans tout le tableaux\n", niveau, MINE);
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
		printf("%s", message);
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
	int CL;
	int CC;
	char CD = 'c';
	int perdu = -1;
	int nbcasesm = N * N - MINE; // Nombre de cases sans mine

	printf("\nJeu du demineur\n\n");

	while ((perdu == -1)) {
		AfficheT(TJ);
		//AfficheT(TM);
		CD = getInputChar("Voulez vous jouer : c ou poser un drapeau : d ou retirer un drapeau : r -> ", "cdr", 3);
		if (CD == 'd') {
			CL = getInputInt("\nEntrer le numero de la ligne : ", 0, N);

			CC = getInputInt("Entrer le numero de la colonne : ", 0, N);
			if (TJ[CL][CC] == 'X') {
				TJ[CL][CC] = 80;
			}

			printf("\n");
			system("cls");

			if (TJ[CL][CC] != X) {
				printf("Vous avez deja rentre cette valeur.\n\n");
			}
		}
		if (CD == 'r') {
			CL = getInputInt("\nEntrer le numero de la ligne : ", 0, N);

			CC = getInputInt("Entrer le numero de la colonne : ", 0, N);
			if (TJ[CL][CC] == 80) {
				TJ[CL][CC] = 88;
			}


			printf("\n");
			system("cls");
		}
		if (CD == 'c') {
			CL = getInputInt("\nEntrer le numero de la ligne : ", 0, N);

			CC = getInputInt("Entrer le numero de la colonne : ", 0, N);
			printf("\n");
			system("cls");
			if (TJ[CL][CC] != X && TJ[CL][CC] != 80) {
				printf("Vous avez deja rentre cette valeur.\n\n");
				continue;
			}

			if (TM[CL][CC] == M) {
				perdu = 1; // VOUS AVEZ PERDU!
				printf("C'est une mine :O\n\n");
				break;
			}
			reavealCase(TM, TJ, CL, CC); // Recherche du nombre de mines aux alentours
			if (cpt == nbcasesm)
			{
				perdu = 0;
				printf("Vous avez gagne!\n\n");
			}
		}
	}

	if (perdu == 1) {
		printf("Game Over\n\n");

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
int getMineArround(tab TM, tab TJ, int i, int j)
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
	return mineCount;
}

void reavealCase(tab TM, tab TJ, int i, int j)//Il n'y a pas de mines autour donc detruire autour du 0
{
	if (i < 0 || i >= N)
		return;

	if (j < 0 || j >= N)
		return;

	if (TJ[i][j] != 'X')
		return;

	cpt++;
	TJ[i][j] = getMineArround(TM, TJ, i, j);
	if (TJ[i][j] != 48)
		return;

	reavealCase(TM, TJ, i - 1, j - 1);
	reavealCase(TM, TJ, i - 1, j);
	reavealCase(TM, TJ, i - 1, j + 1);

	reavealCase(TM, TJ, i, j + 1);
	reavealCase(TM, TJ, i, j - 1);

	reavealCase(TM, TJ, i + 1, j - 1);
	reavealCase(TM, TJ, i + 1, j);
	reavealCase(TM, TJ, i + 1, j + 1);
}