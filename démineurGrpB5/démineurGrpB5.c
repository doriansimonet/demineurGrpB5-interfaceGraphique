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
int MINE = 0;
int cpt = 0;
void func(a);


void Ini(char a[N][N], char c[N][N]);
void niveauDeJeu(tab, tab);
void AfficheT(tab,tab, SDL_Renderer*, SDL_Texture*);
void Jeu(tab, tab, SDL_Renderer*, SDL_Texture*);
void placeM(tab);
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
	SDL_Texture* texture_image, * texture_mine, * texture_win, * texture_hard, * texture_medium, * texture_easy, * texture_start, * texture_restart,* texture_quit, * texture_over,* texture_un, * texture_deux, * texture_trois, * texture_quatre, * texture_cinq, * texture_six, * texture_sept, * texture_huit, * texture_drapeau = NULL;
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
	SDL_Surface* surface_over = SDL_LoadBMP("src/gameOver.bmp");
	SDL_Surface* surface_restart = SDL_LoadBMP("src/restart.bmp");
	SDL_Surface* surface_quit = SDL_LoadBMP("src/quit.bmp");
	SDL_Surface* surface_start = SDL_LoadBMP("src/start.bmp");
	SDL_Surface* surface_easy = SDL_LoadBMP("src/easy.bmp");
	SDL_Surface* surface_medium = SDL_LoadBMP("src/medium.bmp");
	SDL_Surface* surface_hard = SDL_LoadBMP("src/hard.bmp");
	SDL_Surface* surface_win = SDL_LoadBMP("src/win.bmp");
	int statut = EXIT_FAILURE;
	SDL_Event event;
	SDL_bool quit = SDL_FALSE;
	int x, y;
	int boom;
	Uint32 boutons;
	int nbcasesm =0;

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

	texture_easy = SDL_CreateTextureFromSurface(renderer, surface_easy);
	if (NULL == texture_easy)
	{
		fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s", SDL_GetError());
		goto Quit;
	}

	texture_medium = SDL_CreateTextureFromSurface(renderer, surface_medium);
	if (NULL == texture_medium)
	{
		fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s", SDL_GetError());
		goto Quit;
	}

	texture_hard = SDL_CreateTextureFromSurface(renderer, surface_hard);
	if (NULL == texture_hard)
	{
		fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s", SDL_GetError());
		goto Quit;
	}

	texture_start = SDL_CreateTextureFromSurface(renderer, surface_start);
	if (NULL == texture_start)
	{
		fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s", SDL_GetError());
		goto Quit;
	}

	texture_quit = SDL_CreateTextureFromSurface(renderer, surface_quit);
	if (NULL == texture_quit)
	{
		fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s", SDL_GetError());
		goto Quit;
	}

	texture_restart = SDL_CreateTextureFromSurface(renderer, surface_restart);
	if (NULL == texture_restart)
	{
		fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s", SDL_GetError());
		goto Quit;
	}

	texture_over = SDL_CreateTextureFromSurface(renderer, surface_over);
	if (NULL == texture_over)
	{
		fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s", SDL_GetError());
		goto Quit;
	}

	texture_win = SDL_CreateTextureFromSurface(renderer, surface_win);
	if (NULL == texture_win)
	{
		fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s", SDL_GetError());
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
	SDL_Texture* tab_texture[18] ;
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
	tab_texture[10] = texture_over;
	tab_texture[11] = texture_start;
	tab_texture[12] = texture_quit;
	tab_texture[13] = texture_easy;
	tab_texture[14] = texture_medium;
	tab_texture[15] = texture_hard;
	tab_texture[16] = texture_win;
	tab_texture[17] = texture_restart;
	
	Jeu(TM, TJ, renderer, tab_texture);
	boom = 2;
	//boucle jeu
	while (!quit)
	{		
		SDL_WaitEvent(&event);
		if (event.type == SDL_QUIT)
		{
			quit = SDL_TRUE;
		}
		boutons = SDL_GetMouseState(&x, &y);
		if (boom == 2) {
			SDL_Rect start = { 0,0,500,500 };
			SDL_Rect easy = { 20,300,125,125 };
			SDL_Rect medium = { 185,300,125,125 };
			SDL_Rect hard = { 355,300,125,125 };
			SDL_RenderCopy(renderer, tab_texture[11], NULL, &start);
			SDL_RenderCopy(renderer, tab_texture[13], NULL, &easy);
			SDL_RenderCopy(renderer, tab_texture[14], NULL, &medium);
			SDL_RenderCopy(renderer, tab_texture[15], NULL, &hard);
			SDL_RenderPresent(renderer);
			if (event.type == SDL_MOUSEBUTTONDOWN) {
				if (boutons & SDL_BUTTON(SDL_BUTTON_LEFT)) {
					if (145 > x && x > 20 && 425 > y && y > 300) {
						MINE = 10;
						nbcasesm = N * N - MINE;
						Jeu(TM, TJ, renderer, tab_texture);
						boom = 0;
					}
					if (300 > x && x > 185 && 425 > y && y > 300) {
						MINE = 20;
						nbcasesm = N * N - MINE;
						Jeu(TM, TJ, renderer, tab_texture);
						boom = 0;
					}
					if (480 > x && x > 355 && 425 > y && y > 300) {
						MINE = 30;
						nbcasesm = N * N - MINE;
						Jeu(TM, TJ, renderer, tab_texture);
						boom = 0;
					}
				}
			}
		}
		if (boom == 1) {
			if (event.type == SDL_MOUSEBUTTONDOWN) {
				if (boutons & SDL_BUTTON(SDL_BUTTON_LEFT)) {
					if (450 > x && x > 375 && 450 > y && y > 425)
					{
						quit = SDL_TRUE;

					}
					if (145 > x && x > 20 && 450 > y && y > 425)
					{
						boom = 2;
						Jeu(TM, TJ, renderer, tab_texture);
						
					}
				}
			}
		}
		while (boom == 0) 
		{
			SDL_WaitEvent(&event);
			if (event.type == SDL_QUIT)
			{
				quit = SDL_TRUE;
				boom = 1;
			}
			SDL_PumpEvents();
			boutons = SDL_GetMouseState(&x, &y);
			if (event.type == SDL_MOUSEBUTTONDOWN) {
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
								AfficheT(TJ, TM, renderer, tab_texture);
							}
						}
					}
				}
			}
			if (event.type == SDL_MOUSEBUTTONDOWN) {
				if (boutons & SDL_BUTTON(SDL_BUTTON_LEFT)) {
					for (int i = 0; i < 500; i += 50) {
						for (int j = 0; j < 500; j += 50) {
							if (i < x && x < i + 50 && j < y && y < j + 50) {
								int abs = i / 50;
								int ord = j / 50;
								reavealCase(TM, TJ, abs, ord);
								AfficheT(TJ, TM, renderer, tab_texture);
								if (TM[abs][ord] == M) {
									boom = 1;
								}
								if (cpt == nbcasesm) {
									boom = 1;
									cpt = 0;
								}
								
							}
						}
					}
				}
			}
			SDL_RenderPresent(renderer);
		}
	}

statut = EXIT_SUCCESS;
// fin de focntion
Quit:
	if (NULL != renderer)
		SDL_DestroyRenderer(renderer);
	if (NULL != window)
		SDL_DestroyWindow(window);
	SDL_Quit();
	return statut;
}

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
	 int nbcasesm = N * N - MINE;
	 for (i = 0; i < 500; i += 50) {
		 for (j = 0; j < 500; j += 50) {
			 SDL_Rect img = { i,j,50,50 };
			 SDL_Rect end = { 0,0,500,500 };
			 SDL_Rect quit = { 350,400,125,125 };
			 SDL_Rect restart = { 20,400,125,125 };
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

			 if (T[abs][ord] == 48 && TM[abs][ord] != M) {
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
			 }
			 if (T[abs][ord] == 49 && TM[abs][ord] != M) {
				 SDL_RenderCopy(renderer, tab_texture[1], NULL, &img);
			 }
			 if (T[abs][ord] == 50 && TM[abs][ord] != M) {
				 SDL_RenderCopy(renderer, tab_texture[2], NULL, &img);
			 }
			 if (T[abs][ord] == 51 && TM[abs][ord] != M) {
				 SDL_RenderCopy(renderer, tab_texture[3], NULL, &img);
			 }
			 if (T[abs][ord] == 52 && TM[abs][ord] != M) {
				 SDL_RenderCopy(renderer, tab_texture[4], NULL, &img);
			 }
			 if (T[abs][ord] == 53 && TM[abs][ord] != M) {
				 SDL_RenderCopy(renderer, tab_texture[5], NULL, &img);
			 }
			 if (T[abs][ord] == 54 && TM[abs][ord] != M) {
				 SDL_RenderCopy(renderer, tab_texture[6], NULL, &img);
			 }
			 if (T[abs][ord] == 55 && TM[abs][ord] != M) {
				 SDL_RenderCopy(renderer, tab_texture[7], NULL, &img);
			 }
			 if (T[abs][ord] == 56 && TM[abs][ord] != M) {
				 SDL_RenderCopy(renderer, tab_texture[8], NULL, &img);
			 }
			 if (TM[abs][ord] == M && T[abs][ord] != X && T[abs][ord] != P) {
				 for (int i = 0; i < 500; i+=50) {
					 for (int j = 0; j < 500; j+=50) {
						 SDL_Rect mine = { i,j,50,50 };
						 int absM = i / 50;
						 int ordM = j / 50;
						 if (TM[absM][ordM] == M) {
							 T[absM][ordM] = M;
							 SDL_RenderCopy(renderer, tab_texture[0], NULL, &mine);
							 
						 }
					 }
				 }
				 SDL_RenderCopy(renderer, tab_texture[10], NULL, &end);
				 SDL_RenderCopy(renderer, tab_texture[12], NULL, &quit);
				 SDL_RenderCopy(renderer, tab_texture[17], NULL, &restart);
			 }
			 if (cpt == nbcasesm)
			 {
				 SDL_RenderCopy(renderer, tab_texture[16], NULL, &end);
				 SDL_RenderCopy(renderer, tab_texture[12], NULL, &quit);
				 SDL_RenderCopy(renderer, tab_texture[17], NULL, &restart);
				 
			 }
		 }

	 }
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
	
	
	TJ[i][j] = getMineArround(TM, TJ, i, j);
	if (TM[i][j] == M)
		return;
	cpt++;
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

void Jeu (tab TM,tab TJ, SDL_Renderer*renderer, SDL_Texture* tab_texture){
	srand((unsigned int)time(NULL));
	Ini(TM, TJ);
	AfficheT(TJ, TM, renderer, tab_texture);
	placeM(TM); // Placement des mines (M)
}