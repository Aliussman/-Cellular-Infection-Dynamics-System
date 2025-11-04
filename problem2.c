#include <stdio.h>

#define MAX 25

int main() {
    int R, C;
    scanf("%d %d", &R, &C);

    int N;
    scanf("%d", &N);

    char grid[MAX][MAX];
    int infected_time[MAX][MAX] = {0};
    int immune_time[MAX][MAX] = {0};

    // Initialize all cells as healthy
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            grid[i][j] = '.';
        }
    }

    // Read initially infected cells
    for (int k = 0; k < N; k++) {
        int r, c;
        scanf("%d %d", &r, &c);
        grid[r][c] = 'X';
        infected_time[r][c] = 1;
    }

    int T;
    scanf("%d", &T);

    // Direction arrays for orthogonal neighbors
    int dr[4] = {-1, 1, 0, 0};
    int dc[4] = {0, 0, -1, 1};

    // Simulate over time
    for (int step = 0; step < T; step++) {
        char next[MAX][MAX];
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                next[i][j] = grid[i][j]; // start with current state
            }
        }

        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                if (grid[i][j] == '.') {
                    // Healthy -> check infection
                    for (int d = 0; d < 4; d++) {
                        int ni = i + dr[d], nj = j + dc[d];
                        if (ni >= 0 && ni < R && nj >= 0 && nj < C && grid[ni][nj] == 'X') {
                            next[i][j] = 'X';
                            infected_time[i][j] = 1;
                            break;
                        }
                    }
                } else if (grid[i][j] == 'X') {
                    // Infected duration
                    infected_time[i][j]++;
                    if (infected_time[i][j] > 2) {
                        next[i][j] = 'I';
                        infected_time[i][j] = 0;
                        immune_time[i][j] = 1;
                    }
                } else if (grid[i][j] == 'I') {
                    // Immune duration
                    immune_time[i][j]++;
                    if (immune_time[i][j] > 3) {
                        next[i][j] = '.';
                        immune_time[i][j] = 0;
                    }
                }
            }
        }

        // Update grid
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                grid[i][j] = next[i][j];
            }
        }
    }

    // Print final grid
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            printf("%c", grid[i][j]);
            if (j < C - 1) printf(" ");
        }
        printf("\n");
    }

    return 0;
}
