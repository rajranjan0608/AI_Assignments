#define N 8
#include <stdbool.h> 
#include <stdio.h> 

int solCount = 1;

void solPrint(int chessBoard[N][N]) 
{ 
	printf("%d)\n", solCount);
	for (int i = 0; i < N; i++) { 
		for (int j = 0; j < N; j++) 
			printf(" %d ", chessBoard[i][j]); 
		printf("\n"); 
	}
    printf("\n");	
} 

bool isCorrect(int chessBoard[N][N], int row, int col) { 
	int i, j; 

	for (i = 0; i < col; i++) 
		if (chessBoard[row][i]) 
			return false; 

	for (i = row, j = col; i >= 0 && j >= 0; i--, j--) 
		if (chessBoard[i][j]) 
			return false; 

	for (i = row, j = col; j >= 0 && i < N; i++, j--) 
		if (chessBoard[i][j]) 
			return false; 

	return true; 
} 

void sol(int chessBoard[N][N], int col) { 
	if (col >= N){
		solPrint(chessBoard);
		solCount++;
		return;
	}
	
	for (int i = 0; i < N; i++) { 
		if (isCorrect(chessBoard, i, col)) { 
			chessBoard[i][col] = 1; 

			sol(chessBoard, col + 1); 
			
			chessBoard[i][col] = 0; 
		} 
	}
	return;
} 

int main() { 
	int chessBoard[N][N] = { 
							{ 0, 0, 0, 0, 0, 0, 0, 0 }, 
							{ 0, 0, 0, 0, 0, 0, 0, 0 },
							{ 0, 0, 0, 0, 0, 0, 0, 0 },
							{ 0, 0, 0, 0, 0, 0, 0, 0 },
							{ 0, 0, 0, 0, 0, 0, 0, 0 },
							{ 0, 0, 0, 0, 0, 0, 0, 0 },
							{ 0, 0, 0, 0, 0, 0, 0, 0 },
							{ 0, 0, 0, 0, 0, 0, 0, 0 }
						    };
		

	sol(chessBoard, 0);

	return 0;	
}
