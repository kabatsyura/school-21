#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define clear() printf("\033[H\033[J")

#define FIELD_WIDTH 80
#define FIELD_HEIGHT 25
#define CELL 35
#define EMPTY 32
#define DOT 46

void fill_in_the_field(int f_width, int f_height, int y_figure, int x_figure, int y, int x, int figure[f_height][f_width], int** matrix);
void field_init(int f_width, int f_height, int y_figure, int x_figure, int y, int x, int figure[f_height][f_width], int*** matrix, int*** fresh_matrix);
void render_field(int y, int x, int** matrix);
void get_figure_spawn_coordinates(int* y_figure, int* x_figure);
void check_neighbour_values(int y, int x, int** old_matrix, int **new_matrix);
void grid_nuller(int y, int x, int** old_matrix);



int main() {
    int x = FIELD_WIDTH;
    int y = FIELD_HEIGHT;
    int x_figure;
    int y_figure;
    int** grid;
    int** new_grid;
    int index = 0;
    
    int f_width = 6;
    int f_height = 6;
    int figure[6][6] = {{0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 1, 0, 0},
                        {0, 0, 0, 0, 1, 0},
                        {0, 0, 1, 1, 1, 0},
                        {0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0}};

    int mode, s;
    float speed;
    clear();
    printf("1. Динамический\n2. Пошаговый (по нажатию Enter)\nВыберите режим: \n");
    if (scanf("%d", &mode) == 1 && mode == 1) {
        clear();
        printf("1. Медленно\n2. Быстро\nВыберите скорость: \n");
        scanf("%d", &s);
        switch(s) {
            case 1:
                speed = 2;
                break;
            case 2:
                speed = 1;
                break;
        }
    }
    clear();
    get_figure_spawn_coordinates(&y_figure, &x_figure);
    field_init(f_width, f_height, y_figure, x_figure, y, x, figure, &grid, &new_grid);
    grid_nuller(y, x, new_grid);
    getchar();
    render_field(y, x, grid);
    getchar();
    
    while(index < 1000) {
        clear();
        grid_nuller(y, x, new_grid);
        check_neighbour_values(y, x, grid, new_grid);
        
        if (mode == 1) {
            sleep(speed);
        } else {
            getchar();
        }
        index++;
    }
    return 0;
}

void render_field(int y, int x, int** matrix) {
    for (int i = 0; i < y-1; i++) {
        for (int j = 0; j < x-1; j++) {
            if (j != x - 1) {
                if(matrix[i][j]) {
                    printf("%c ", CELL);
                } else {
                    printf("%c ", EMPTY);
                }
            }
        }
        if (i != y - 1) {
            printf("\n");
        }
    }
}

void field_init(int f_width, int f_height, int y_figure, int x_figure, int y, int x, int figure[f_height][f_width], int*** matrix, int*** fresh_matrix) {
    int** new_matrix = malloc(x * y * sizeof(int) + y * sizeof(int*));
    int* pointer = (int*)(new_matrix + y);
    for (int i = 0; i < y; i++) {
        new_matrix[i] = pointer + x * i;
    }
    *matrix = new_matrix;

    int** brand_new_matrix = malloc(x * y * sizeof(int) + y * sizeof(int*));
    int* new_pointer = (int*)(brand_new_matrix + y);
    for (int i = 0; i < y; i++) {
        brand_new_matrix[i] = new_pointer + x * i;
    }
    *fresh_matrix = brand_new_matrix;
    fill_in_the_field(f_width, f_height, y_figure, x_figure, y, x, figure, *matrix);
}

void fill_in_the_field(int f_width, int f_height, int y_figure, int x_figure, int y, int x, int figure[f_height][f_width], int** matrix) {
    int figure_i = 0;
    int figure_j = 0;
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            if ((i >= y_figure && i < y_figure + f_height) && (j >= x_figure && j < x_figure + f_width)) {
                    if (figure[figure_i][figure_j] == 1) {
                        matrix[i][j] = 1;
                        figure_j++;
                    } else {
                        matrix[i][j] = 0;
                        figure_j++;
                    }
            }
        }
    }
}

void get_figure_spawn_coordinates(int* y_figure, int* x_figure) {
    *y_figure = rand()%FIELD_WIDTH;
    *x_figure = rand()%FIELD_HEIGHT;
}

void check_neighbour_values(int y, int x, int** old_matrix, int **new_matrix) {
    for (int i = 1; i < y - 1; i++) {
        for (int j = 1; j < x - 1; j++) {
            int checker = old_matrix[i - 1][j - 1] + old_matrix[i][j - 1] + old_matrix[i + 1][j - 1] + old_matrix[i - 1][j] + 
            old_matrix[i + 1][j] + old_matrix[i - 1][j + 1] + old_matrix[i][j +1 ] + old_matrix[i + 1][j + 1];
            if (old_matrix[i][j] && (checker < 2 || checker > 3)) {
                new_matrix[i][j] = 0;
            } else if ((old_matrix[i][j] && (checker == 2 || checker == 3)) || (!old_matrix[i][j] && checker == 3)) {
                new_matrix[i][j] = 1;
            }
        }
    }
    render_field(y, x, new_matrix);
    for (int i = 1; i < y - 1; i++) {
        for (int j = 1; j < x - 1; j++) {
            old_matrix[i][j] = new_matrix[i][j];
        }
    }
}

void grid_nuller(int y, int x, int** old_matrix) {
    for (int i = 1; i < y - 1; i++) {
        for (int j = 1; j < x - 1; j++) {
            old_matrix[i][j] = 0;
        }
    }
}