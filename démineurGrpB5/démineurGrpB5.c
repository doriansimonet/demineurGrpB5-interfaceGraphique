 #include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <SDL.h>

#define N 10
#define X 88 // Case non découverte
#define M 77 // Case minée
#define P 80 //drapeau

typedef char tab[N][N];

int a = 3;
int MINE = 10;
int cpt = 0;
void func(a);


void Ini(char a[N][N], char c[N][N]);
void niveauDeJeu(tab, tab);
void AfficheT(tab,tab, SDL_Renderer*, SDL_Texture*);
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
	//Initialisation

	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_Texture* texture_image, * texture_mine, * texture_un, * texture_deux, * texture_trois, * texture_quatre, * texture_cinq, * texture_six, * texture_sept, * texture_huit, * texture_drapeau = NULL;
	SDL_Surface* surface_huit = SDL_LoadBMP("src/Pixil-8.bmp");
	SDL_Surface* surface_drapeau = SDL_LoadBMP("src/Pixil-drapeau.bmp");
	SDL_Surface* surface_un = SDL_LoadBMP("src/Pixil-1.bmp");
	SDL_Surface* surface_deux = SDL_LoadBMP("src/Pixil-2.bmp");
	SDL_Surface* surface_trois = SDL_LoadBMP("src/Pixil-3.bmp");
	SDL_Surface* surface_quatre = SDL_LoadBMP("src/Pixil-4.bmp");
	SDL_Surface* surface_cinq = SDL_LoadBMP("src/Pixil-5.bmp");
	SDL_Surface* surface_six = SDL_LoadBMP("src/Pixil-6.bmp");
	SDL_Surface* surface_sept = SDL_LoadBMP("src/Pixil-7.bmp");
	SDL_Surface* surface_mine = SDL_LoadBMP("src/Pixil-bombe.bmp");
	int statut = EXIT_FAILURE;
	SDL_Event event;
	SDL_bool quit = SDL_FALSE;
	int x, y;
	Uint32 boutons;

	tab TM; // Tableau des mines
	tab TJ; // Tableau de jeu
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
	/*texture_damier = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 50, 50);
	if (NULL == texture_damier)
	{
		fprintf(stderr, "Erreur SDL_CreateTexture : %s", SDL_GetError());
		goto Quit;
	}*/

	if (NULL == surface_un)
	{
		fprintf(stderr, "Erreur SDL_LoadBMP : %s", SDL_GetError());
		goto Quit;
	}

	if (NULL == surface_mine)
	{
		fprintf(stderr, "Erreur SDL_LoadBMP : %s", SDL_GetError());
		goto Quit;
	}

	texture_image = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 50, 50);
	if (NULL == texture_image)
	{
		fprintf(stderr, "Erreur SDL_CreateTexture : %s", SDL_GetError());
		goto Quit;
	}

	texture_un = SDL_CreateTextureFromSurface(renderer, surface_un);
	if (NULL == texture_un)
	{
		fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s", SDL_GetError());
		goto Quit;
	}

	texture_mine = SDL_CreateTextureFromSurface(renderer, surface_mine);
	if (NULL == texture_mine)
	{
		fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s", SDL_GetError());
		goto Quit;
	}

	texture_deux = SDL_CreateTextureFromSurface(renderer, surface_deux);
	if (NULL == texture_deux)
	{
		fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s", SDL_GetError());
		goto Quit;
	}

	texture_drapeau = SDL_CreateTextureFromSurface(renderer, surface_drapeau);
	if (NULL == texture_drapeau)
	{
		fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s", SDL_GetError());
		goto Quit;
	}

	texture_trois = SDL_CreateTextureFromSurface(renderer, surface_trois);
	if (NULL == texture_trois)
	{
		fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s", SDL_GetError());
		goto Quit;
	}

	texture_quatre = SDL_CreateTextureFromSurface(renderer, surface_quatre);
	if (NULL == texture_quatre)
	{
		fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s", SDL_GetError());
		goto Quit;
	}

	texture_cinq = SDL_CreateTextureFromSurface(renderer, surface_cinq);
	if (NULL == texture_cinq)
	{
		fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s", SDL_GetError());
		goto Quit;
	}

	texture_six = SDL_CreateTextureFromSurface(renderer, surface_six);
	if (NULL == texture_six)
	{
		fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s", SDL_GetError());
		goto Quit;
	}

	texture_sept = SDL_CreateTextureFromSurface(renderer, surface_sept);
	if (NULL == texture_sept)
	{
		fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s", SDL_GetError());
		goto Quit;
	}

	texture_huit = SDL_CreateTextureFromSurface(renderer, surface_huit);
	if (NULL == texture_huit)
	{
		fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s", SDL_GetError());
		goto Quit;
	}
	SDL_Texture* tab_texture[10] ;
	tab_texture[0] = texture_mine;
	tab_texture[1] = texture_un;
	tab_texture[2] = texture_deux;
	tab_texture[3] = texture_trois;
	tab_texture[4] = texture_quatre;
	tab_texture[5] = texture_cinq;
	tab_texture[6] = texture_six;
	tab_texture[7] = texture_sept;
	tab_texture[8] = texture_huit;
	tab_texture[9] = texture_drapeau;
	srand((unsigned int)time(NULL));
	Ini(TM, TJ);
	AfficheT(TJ,TM, renderer, tab_texture);
	placeM(TM); // Placement des mines (M)
	
	//boucle jeu
	while (!quit)
	{

		
		SDL_WaitEvent(&event);
		if (event.type == SDL_QUIT)
		{
			quit = SDL_TRUE;
		}
		else if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.scancode == SDL_SCANCODE_A)
				printf("scancode A\n");
			if (event.key.keysym.sym == SDLK_a)
				printf("keysym A\n");
		}
		

		SDL_PumpEvents();
		boutons = SDL_GetMouseState(&x, &y);
		if (boutons & SDL_BUTTON(SDL_BUTTON_RIGHT)) {
			for (int i = 0; i < 500; i += 50) {
				for (int j = 0; j < 500; j += 50) {
					if (i < x && x < i + 50 && j < y && y < j + 50) {
						int abs = i / 50;
						int ord = j / 50;
						if (TJ[abs][ord] == X) {
							TJ[abs][ord] = P;
						}
						else {
							if (TJ[abs][ord] == P) {
								TJ[abs][ord] = X;
							}
						

						}
						AfficheT(TJ,TM, renderer,tab_texture);
					}
				}
			}
		}
					if (boutons & SDL_BUTTON(SDL_BUTTON_LEFT)) {
						printf("Clic droit à la positions %d - %d\n", x, y);

						for (int i = 0; i < 500; i += 50) {
							for (int j = 0; j < 500; j += 50) {
								if (i < x && x < i + 50 && j < y && y < j + 50) {
									int abs = i / 50;
									int ord = j / 50;
									reavealCase(TM, TJ,abs, ord);
									AfficheT(TJ,TM, renderer, tab_texture);
									/*SDL_Rect dst = {i, j, 50, 50};
									SDL_SetRenderTarget(renderer, texture_damier);
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
									SDL_QueryTexture(texture_damier, NULL, NULL, &dst.w, &dst.h);
									SDL_RenderCopy(renderer, texture_damier, NULL, &dst);
									SDL_RenderPresent(renderer);*/
								}
							}
							SDL_Delay(20);
						}
					}
	}



				statut = EXIT_SUCCESS;
				// fin de focntion
			Quit:
				/*if (NULL != texture_damier)
					SDL_DestroyTexture(texture_damier);*/
				if (NULL != renderer)
					SDL_DestroyRenderer(renderer);
				if (NULL != window)
					SDL_DestroyWindow(window);
				SDL_Quit();
				return statut;
			}



				/*char ON = 'o';
				while (ON == 'o') {




					niveauDeJeu(TM, TJ);



					jeu(TM, TJ);

					ON = getInputChar("Voulez vous rejouez ? \n o : oui  n : non \n -> ", "on", 2);
					cpt = 0;

					system("cls");
				}
				if (ON == 'n') {
					printf("\nReessayer une autre fois\n");
				}*/

 void Ini(tab TM ,tab TJ) {
	int i, j;

	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			TM[i][j] = X;
			TJ[i][j] = X;
		}
	}
}

void AfficheT(tab T, tab TM, SDL_Renderer* renderer, SDL_Texture** tab_texture) {
	int i, j;
	int c = 0;
	for (i = 0; i < 500; i+=50) {
		for (j = 0; j < 500; j+=50) {
			SDL_Rect img = { i,j,50,50 };
			int abs = i / 50;
			int ord = j / 50;
			if (T[abs][ord] == X) {
				int brique = i - j;
				if (brique < 0) {
					brique = brique * (-1);
				}
				brique = (brique / 50);
				if (brique % 2 == 1) {
					SDL_SetRenderDrawColor(renderer, 150, 250, 100, 255);
				}
				else {
					SDL_SetRenderDrawColor(renderer, 120, 200, 50, 255);
				}
				SDL_Rect a = { i,j,50,50 };
				SDL_RenderFillRect(renderer, &a);
			}

			if (T[abs][ord] == 48 && TM[abs][ord]!=M) {
				int zero = i - j;
				if (zero < 0) {
					zero = zero * (-1);
				}
				zero = (zero / 50);
				if (zero % 2 == 1) {
					SDL_SetRenderDrawColor(renderer, 249, 228, 183, 255);
				}
				else {
					SDL_SetRenderDrawColor(renderer, 213, 186, 152, 255);
				}
				SDL_Rect a = { i,j,50,50 };
				SDL_RenderFillRect(renderer, &a);
			}
			if (T[abs][ord] == P) {
				SDL_RenderCopy(renderer, tab_texture[9], NULL, &img);
				SDL_RenderPresent(renderer);
			}
			if (T[abs][ord] == 49 && TM[abs][ord]!=M) {
				SDL_RenderCopy(renderer, tab_texture[1], NULL, &img);
				SDL_RenderPresent(renderer);
			}
			if (T[abs][ord] == 50 && TM[abs][ord] != M) {
				SDL_RenderCopy(renderer, tab_texture[2], NULL, &img);
				SDL_RenderPresent(renderer);
			}
			if (T[abs][ord] == 51 && TM[abs][ord] != M) {
				SDL_RenderCopy(renderer, tab_texture[3], NULL, &img);
				SDL_RenderPresent(renderer);
			}
			if (T[abs][ord] == 52 && TM[abs][ord] != M) {
				SDL_RenderCopy(renderer, tab_texture[4], NULL, &img);
				SDL_RenderPresent(renderer);
			}
			if (T[abs][ord] == 53 && TM[abs][ord] != M) {
				SDL_RenderCopy(renderer, tab_texture[5], NULL, &img);
				SDL_RenderPresent(renderer);
			}
			if (T[abs][ord] == 54 && TM[abs][ord] != M) {
				SDL_RenderCopy(renderer, tab_texture[6], NULL, &img);
				SDL_RenderPresent(renderer);
			}
			if (T[abs][ord] == 55 && TM[abs][ord] != M) {
				SDL_RenderCopy(renderer, tab_texture[7], NULL, &img);
				SDL_RenderPresent(renderer);
			}
			if (T[abs][ord] == 56 && TM[abs][ord] != M) {
				SDL_RenderCopy(renderer, tab_texture[8], NULL, &img);
				SDL_RenderPresent(renderer);
			}
			if (TM[abs][ord] == M && T[abs][ord]!=X &&T[abs][ord] != P) {
				SDL_RenderCopy(renderer, tab_texture[0], NULL, &img);
				SDL_RenderPresent(renderer);
			}
		}
		SDL_RenderPresent(renderer);
	}

}

//pas touche
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
// à modifier
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
//ca va encore servir?
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
//ca va encore servir?
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
// prendre position clique au lieu de rentrer les coordonées
void jeu(tab TM, tab TJ) {
	int CL;
	int CC;
	char CD = 'c';
	int perdu = -1;
	int nbcasesm = N * N - MINE; // Nombre de cases sans mine

	printf("\nJeu du demineur\n\n");

	while ((perdu == -1)) {
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
//normalement c ok
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
//ca aussi je pense
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
//à modifier
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