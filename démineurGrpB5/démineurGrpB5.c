#include <stdio.h>
#define xmax 10
#define ymax 10

void affichegrille(char grille[xmax][ymax], int, int);

int main(void) {
	int x, y;
	
	char grille[xmax][ymax];

	for (x = 0; x < xmax; ++x) {
		for (y = 0; y < ymax; ++y) {
			grille[x][y] = '( )';
		}
	}

	affichegrille(grille, xmax, ymax);
	return 0;
}

void affichegrille(char grille[xmax][ymax], int nb_ligne, int nb_col) {
	int x, y;
	for (x = 0; x < nb_ligne; x++) {
		printf("\n");
		for (y = 0; y < nb_col; y++)
			printf("%c", grille[x][y]);
	}
}