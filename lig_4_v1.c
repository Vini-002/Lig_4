#include <stdio.h>
#include <locale.h>
#include <windows.h>
#include <time.h>

# define SEARCH_DEPTH 9
# define false 0
# define true 1

#define ROWS 6
#define COLUMNS 7

int vez = 0, jogadas = 0;
int game[COLUMNS][ROWS];
int col, lin, plac_1 = 0, plac_2 = 0;
int topos[COLUMNS] = {0};

void iniciar();
void mostrar();
void jogar_2p();
void jogar();

void humano();
void jogada_ai();
void ai();

int minimax(int isMaxi, int last_i, int last_j, int alpha, int beta, int depth);
int verifica_ai();
int verifica_2p();

int fim(int i, int j);
int verifica();

typedef enum{BLACK,BLUE,GREEN,CYAN,RED,MAGENTA,BROWN,LIGHTGRAY,DARKGRAY,LIGHTBLUE,LIGHTGREEN,LIGHTCYAN,LIGHTRED,LIGHTMAGENTA,YELLOW,WHITE} COLORS;

int main()
{
	int opt;
	setlocale(LC_ALL, "");
	
	time_t t = time(NULL);
	srand((unsigned) time(&t));

	printf("Ola, bem vindo ao jogo LIG 4!\n");
	ini:
	printf("\nInforme o numero de jogadores - 1 ou 2 jogadores:\n");
	scanf("%d", &opt);
	switch (opt)
	{
		case 1:
			iniciar();
			while(verifica_ai())
				humano();
			break;
		case 2:
			iniciar();
			while (verifica_2p())
				jogar_2p();
			break;
		default:
			printf("\nDesculpe, nao entendi...\n");
			goto ini;
	}
	
	printf("\n\nDeseja jogar novamente?\n1 - sim\n2 - nao\n");
	scanf("%d", &opt);
	switch (opt)
	{
		case 1:
			printf("\nLegal!");
			goto ini;
		default:
			printf("\nOk, volte sempre!");
	}
	
	return 0;
}

void jogar_2p()
{
	mostrar();

	vez %= 2;
	vez ++;
	
	printf("\nVez do ");
	if (vez == 1)
		SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), RED);
	else
		SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), LIGHTBLUE);
	printf("jogador %d", vez);
	jogar();
}

void humano()
{
	mostrar();

	vez %= 2;
	vez ++;

	if (vez == 1)
	{
		SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), RED);
		printf("\nSua vez, humano");
		jogar();
	}
	else
	{
		ai();
	}
}	

void ai()
{
	int ch;
	// system("cls");
	mostrar();
	printf("\nPensando...");
	clock_t t = clock();
	jogada_ai();
	t = clock() - t;
	
	printf("\nVou jogar na coluna %d!", col + 1);
	printf("\nTempo de execucao: %ld ms", t);
	game[col][lin] = vez;
	//sleep(1);
	jogadas ++;
}


void jogar()
{
	SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), WHITE);
	printf("\nEm que coluna deseja jogar?\n");
	coluna:
	scanf("%d", &col);
	if (col < 1 || col > COLUMNS)
	{
		printf("\nColuna invalida! Digite outro valor para a coluna, entre 1 e 7:\n");
		goto coluna;
	}
	col --;
	lin = 5;
	while (game[col][lin] != 0)
	{
		lin -= 1;
		if (lin < 0)
		{
			printf("\nEsta coluna esta cheia!\nInforme outra coluna:\n");
			goto coluna;
		}
	}
	game[col][lin] = vez;
	jogadas ++;
}

void iniciar()
{
	jogadas = 0;
	SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), WHITE);
	for (col = 0; col < COLUMNS; col ++)
		for (lin = 0; lin < ROWS; lin ++)
			game[col][lin] = 0;
}

void mostrar()
{
	//system("cls");
	printf("\n 1 2 3 4 5 6 7\n");
	for (lin = 0; lin < ROWS; lin ++)
	{
		for (col = 0; col < COLUMNS; col ++)
		{
			switch (game[col][lin])
			{
				case 0:
					printf(" o");
					break;
				case 1:
					SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), RED);
					printf(" o");
					break;
				case 2:
					SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE),  LIGHTBLUE);
					printf(" o");
					break;
			}
			SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), WHITE);
		}
		printf("\n");
	}
}

int fim(int i, int j)
{
	int al_dir = 1, al_esq = 1;
	//Verifica a horizontal, primeiro pra direita e depois pra esquerda
	while (game[i][j] == game[i + al_dir][j] && i + al_dir < 7)
		al_dir ++;

	while (game[i][j] == game[i - al_esq][j] && i - al_esq >= 0)
		al_esq ++;

	if (al_dir + al_esq - 1 >= 4)
		return 0;
	else
	{
		//Verifica a vertical
		int al_vert = 1;
		while (game[i][j] == game[i][j + al_vert] && j + al_vert < ROWS)
			al_vert ++;
		
		if (al_vert >= 4)
			return 0;
		else
		{
			//Verifica a diagonal principal
			int al_cd = 1, al_be = 1;
			while (game[i][j] == game[i + al_cd][j + al_cd] && i + al_cd < 7 && j + al_cd < ROWS)
				al_cd ++;
			while (game[i][j] == game[i - al_be][j - al_be] && i - al_be >= 0 && j - al_be >= 0)
				al_be ++;
				
			if (al_cd + al_be - 1 >= 4)
				return 0;
			else
			{
				//Verifica a diagonal secund�ria
				int al_ce = 1, al_bd = 1;
				while (game[i][j] == game[i + al_ce][j - al_ce] && i + al_ce < 7 && j - al_ce >= 0)
					al_ce ++;
				while (game[i][j] == game[i - al_bd][j + al_bd] && i - al_bd >= 0 && j + al_bd < ROWS)
					al_bd ++;
				
				if (al_ce + al_bd - 1 >= 4)
					return 0;
				else
					return 1;
			}
		}
	}
}

int verifica(){
	if (jogadas < 7)
		return 1;
	else if (jogadas == 42)
	{
		system("cls");
		mostrar();
		printf ("\nEmpate!!!");
		return 0;
	}
}

int verifica_2p()
{
	int ver = verifica();
	if (ver == 1 || ver == 0)
		return ver;
	
	int end = fim(col, lin);
	
	if (end == 0)
	{
		// system("cls");
		mostrar();
		printf ("\nParabens ");
		if (vez == 1)
			SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), RED);
		else
			SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), LIGHTBLUE);
		printf("jogador %d", vez);
		SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), WHITE);
		printf(" Voce Venceu!!!");
	}	
	return end;
}


int verifica_ai()
{
	int ver = verifica();
	if (ver == 1 || ver == 0)
		return ver;
		
	int end = fim(col, lin);
	
	if (end == 0)
	{
		// system("cls");
		mostrar();
		if (vez == 1)
		{
			printf ("\nParabens, ");
			SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), RED);
			printf("humano!");
			SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), WHITE);
			printf("\nVoce venceu!!!");
		}	
		else
		{
			printf("Humano, voce perdeu... Vitoria da ");
			SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), LIGHTBLUE);
			printf("maquina!");
			SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), WHITE);
		}
	}	
	return end;
}

void jogada_ai()
{
	int i, j, score, bestScore = INT_MIN, best_column[COLUMNS] = {0}, n_columns = 0;
	for (i = 0; i < 7; i++)
	{
		if (game[i][0] == 0)
		{
			j = 5;
			while(game[i][j] != 0)
				j--;
			game[i][j] = 2;
			score = minimax(false, i, j, INT_MIN, INT_MAX, SEARCH_DEPTH);
			
			game[i][j] = 0;
			//printf("\nO score pra a coluna %d � de %d", i + 1, score);
			if (score > bestScore)
			{
				bestScore = score;
				col = i;
				lin = j;
				n_columns = 0;
			}
			if (score >= bestScore)
			{
				best_column[n_columns] = i;
				n_columns++;
			}
		}
	}
	if (n_columns > 1)
	{
		i = best_column[rand()%n_columns];
		j = 5;
		while(game[i][j] != 0)
			j--;
		col = i;
		lin = j;
	}
}

int minimax(int isMaxi, int last_i, int last_j, int alpha, int beta, int depth)
{
	int i, j;
	int pontuacao = fim(last_i, last_j);
	if (pontuacao == 0)
	{
		if (isMaxi)
			return -depth;
		else
			return depth;
	}else if (depth == 0)
		return 0;
	else if (isMaxi)
	{
		int bestScore = INT_MIN;
		for (i = 0; i < 7; i ++)
		{
			
			if(game[i][0] == 0)
			{
				j = 5;
				while (game[i][j] != 0)
					j --;
				game[i][j] = 2;
				int score = minimax(false, i, j, alpha, beta, depth - 1);
				game[i][j] = 0;
				
				bestScore = max(score, bestScore);
				alpha = max(score, alpha);
				if (beta < alpha)
					break;
				
			}
		}
		return bestScore;
	}
	else
	{
		int bestScore = INT_MAX;
		for (i = 0; i < 7; i++)
		{
			if (game[i][0] == 0)
			{
				j = 5;
				while (game[i][j] != 0)
					j--;
				game[i][j] = 1;
				int score = minimax(true, i, j, alpha, beta, depth - 1);
				game[i][j] = 0;
				
				bestScore = min(score, bestScore);



				beta = min(score, beta);
				if (beta < alpha)
					break;
				
			}
		}
		return bestScore;
	}
}

