#include <stdio.h>

#define TAB_SIZE 10
#define SHIP_SIZE 3
#define HAB_SIZE 5  // tamanho das matrizes de habilidade (5x5)

int main() {
    int tabuleiro[TAB_SIZE][TAB_SIZE];
    int i, j;

    // 1. Inicializar tabuleiro com água (0)
    for(i = 0; i < TAB_SIZE; i++)
        for(j = 0; j < TAB_SIZE; j++)
            tabuleiro[i][j] = 0;

    // 2. Posicionar navios (3)
    // Navio horizontal
    int hShipRow = 1, hShipCol = 1;
    for(i = 0; i < SHIP_SIZE; i++)
        if(hShipCol + i < TAB_SIZE) tabuleiro[hShipRow][hShipCol + i] = 3;

    // Navio vertical
    int vShipRow = 5, vShipCol = 7;
    for(i = 0; i < SHIP_SIZE; i++)
        if(vShipRow + i < TAB_SIZE) tabuleiro[vShipRow + i][vShipCol] = 3;

    // Navio diagonal direita
    int d1ShipRow = 0, d1ShipCol = 0;
    for(i = 0; i < SHIP_SIZE; i++)
        if(d1ShipRow + i < TAB_SIZE && d1ShipCol + i < TAB_SIZE)
            tabuleiro[d1ShipRow + i][d1ShipCol + i] = 3;

    // Navio diagonal esquerda
    int d2ShipRow = 0, d2ShipCol = 9;
    for(i = 0; i < SHIP_SIZE; i++)
        if(d2ShipRow + i < TAB_SIZE && d2ShipCol - i >= 0)
            tabuleiro[d2ShipRow + i][d2ShipCol - i] = 3;

    // 3. Criar matrizes de habilidade (0 = não afeta, 1 = afeta)
    int cone[HAB_SIZE][HAB_SIZE] = {0};
    int cross[HAB_SIZE][HAB_SIZE] = {0};
    int octa[HAB_SIZE][HAB_SIZE] = {0};
    int center = HAB_SIZE / 2;

    // 3a. Cone (triangular apontando para baixo)
    for(i = 0; i < HAB_SIZE; i++)
        for(j = 0; j < HAB_SIZE; j++)
            if(j >= center - i && j <= center + i) cone[i][j] = 1;

    // 3b. Cruz
    for(i = 0; i < HAB_SIZE; i++)
        for(j = 0; j < HAB_SIZE; j++)
            if(i == center || j == center) cross[i][j] = 1;

    // 3c. Octaedro (losango)
    for(i = 0; i < HAB_SIZE; i++)
        for(j = 0; j < HAB_SIZE; j++)
            if(j >= center - (i < center ? i : HAB_SIZE - 1 - i) &&
               j <= center + (i < center ? i : HAB_SIZE - 1 - i)) octa[i][j] = 1;

    // 4. Pontos de origem no tabuleiro
    int coneRow = 2, coneCol = 2;
    int crossRow = 5, crossCol = 5;
    int octaRow = 7, octaCol = 7;

    // 5. Sobrepor habilidades no tabuleiro (5)
    for(i = 0; i < HAB_SIZE; i++) {
        for(j = 0; j < HAB_SIZE; j++) {
            // Cone
            int row = coneRow - center + i;
            int col = coneCol - center + j;
            if(row >= 0 && row < TAB_SIZE && col >= 0 && col < TAB_SIZE && cone[i][j] == 1)
                if(tabuleiro[row][col] == 0) tabuleiro[row][col] = 5;

            // Cruz
            row = crossRow - center + i;
            col = crossCol - center + j;
            if(row >= 0 && row < TAB_SIZE && col >= 0 && col < TAB_SIZE && cross[i][j] == 1)
                if(tabuleiro[row][col] == 0) tabuleiro[row][col] = 5;

            // Octaedro
            row = octaRow - center + i;
            col = octaCol - center + j;
            if(row >= 0 && row < TAB_SIZE && col >= 0 && col < TAB_SIZE && octa[i][j] == 1)
                if(tabuleiro[row][col] == 0) tabuleiro[row][col] = 5;
        }
    }

    // 6. Exibir tabuleiro
    printf("Tabuleiro com navios e habilidades:\n\n");
    for(i = 0; i < TAB_SIZE; i++) {
        for(j = 0; j < TAB_SIZE; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    return 0;
}

    
