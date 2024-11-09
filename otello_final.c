#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TAMANO_TABLERO 8
#define VACIO '.'
#define NEGRO 'N'
#define BLANCO 'B'

// Verifica si existe al menos un movimiento válido para el jugador dado
bool existMove(char tablero[TAMANO_TABLERO][TAMANO_TABLERO], char player);

// Comprueba si una posición específica (x, y) es un movimiento válido para el jugador dado
bool moveAvailable(char tablero[TAMANO_TABLERO][TAMANO_TABLERO], int x, int y, char player);

// Obtiene el oponente del jugador dado (NEGRO o BLANCO)
char getOpp(char player);

// Cuenta la cantidad de fichas de un jugador en el tablero
int countChip(char tablero[TAMANO_TABLERO][TAMANO_TABLERO], char player);

// Muestra el estado actual del tablero en la consola
void mostrarTablero(char tablero[TAMANO_TABLERO][TAMANO_TABLERO]);

// Imprime las instrucciones del juego al inicio
void imprimir_instrucciones(void);

//Colocar los caracteres vaios y las primeras 2 fichas de cada jugador
void inicia_el_juego(char tablero[TAMANO_TABLERO][TAMANO_TABLERO]);

//Jugador puede decidir si quiere pasar o no
bool saltar_turno(char jugador);

//Coloca la ficha y verifica si puede voltear otra
void putChip(char tablero[TAMANO_TABLERO][TAMANO_TABLERO], int x, int y, char player);

//Da la posibilidad en cada turno de terminar el juego
bool terminar_juego();



int main(void){
    char tablero[TAMANO_TABLERO][TAMANO_TABLERO];
    int x;
    int y;
    char jugador_Actual = NEGRO;

    imprimir_instrucciones();

    inicia_el_juego(tablero);

    printf("\nAsi es como empieza el juego:\n\n");
    mostrarTablero(tablero);


    while (terminar_juego() == 0 && (existMove(tablero, NEGRO) || existMove(tablero, BLANCO))) {
    if (saltar_turno(jugador_Actual)) {
        printf("Jugador %c ha pasado su turno.\n", jugador_Actual);
    } else {
        printf("\nTurno del jugador %c. Ingresa las coordenadas (fila, columna): ", jugador_Actual);
        scanf("%d %d", &x, &y);
        putChip(tablero, x, y, jugador_Actual);
        mostrarTablero(tablero);
    }
    jugador_Actual = getOpp(jugador_Actual);
    }

    int negras = countChip(tablero, NEGRO);
    int blancas = countChip(tablero, BLANCO);

    printf("\nJuego terminado.\n");
    printf("Fichas negras: %d\n", negras);
    printf("Fichas blancas: %d\n", blancas);

    if (negras > blancas) {
        printf("El jugador NEGRO gana!\n");
    } else if (blancas > negras) {
        printf("El jugador BLANCO gana!\n");
    } else {
        printf("Es un empate!\n");
    }

}

bool existMove(char tablero[TAMANO_TABLERO][TAMANO_TABLERO], char player) {
    for (int i = 0; i < TAMANO_TABLERO; i++) {
        for (int j = 0; j < TAMANO_TABLERO; j++) {
            if (moveAvailable(tablero, i, j, player) == 1) {
                return 1; // Hay al menos un movimiento válido
            }
        }
    }
    return 0; // No hay movimientos válidos para el jugador
}

bool moveAvailable(char tablero[TAMANO_TABLERO][TAMANO_TABLERO], int x, int y, char player) {
    if (tablero[x][y] != VACIO) {
        return 0; // La casilla está ocupada
    }

    char opp = (player == NEGRO) ? BLANCO : NEGRO;
    bool valido = false;

    // Revisar en todas las direcciones (8 en total)
    // (-1, -1) es diagonal arriba izquierda, (-1,0) es arriba, (-1,1) es diagonal arriba derecha, (0,-1) es izquierda, (0,1) es derecha, (1,-1) es diagonal abajo izquierda, (1,0) es abajo, (1,1) es diagonal abajo derecha
    int direcciones[8][2] = {
    {-1, -1}, {-1, 0}, {-1, 1},
    {0, -1},          {0, 1},
    {1, -1},  {1, 0},  {1, 1}
    };
    for (int i = 0; i < 8; i++) {
        int dx = direcciones[i][0];
        int dy = direcciones[i][1];
        int contador = 0;
        int nx = x + dx;
        int ny = y + dy;

        // Avanzar mientras estemos en los límites del tablero
        while (nx >= 0 && nx < TAMANO_TABLERO && ny >= 0 && ny < TAMANO_TABLERO && tablero[nx][ny] == opp) {
            contador++;
            nx += dx;
            ny += dy;
        }

        if (contador > 0 && nx >= 0 && nx < TAMANO_TABLERO && ny >= 0 && ny < TAMANO_TABLERO && tablero[nx][ny] == player) {
            valido = 1;
            break;
        }
    }

    return valido;
}

char getOpp(char player){
    if (player == NEGRO){
        return BLANCO;
    }
    else {
        return NEGRO;
    }
}

int countChip(char tablero[TAMANO_TABLERO][TAMANO_TABLERO], char player){
    int counter = 0;
    for (int i = 0; i<= TAMANO_TABLERO - 1; i++){
        for (int j = 0; j<= TAMANO_TABLERO - 1; j++){
            if (tablero[i][j] == player){
                counter += 1;
            }
        }
    }
    return counter;
}

void mostrarTablero(char tablero[TAMANO_TABLERO][TAMANO_TABLERO]) {
    printf("    0   1   2   3   4   5   6   7\n");
    printf("  ---------------------------------\n");
    for (int i = 0; i < TAMANO_TABLERO; i++) {
        printf("%d |", i );
        for (int j = 0; j < TAMANO_TABLERO; j++) {
            printf(" %c |", tablero[i][j]);
        }
        printf("\n  |---|---|---|---|---|---|---|---|\n");
    }
    printf("\n");
}



void imprimir_instrucciones(void){
    system("cls");
    printf("Este programa es para simular el juego de mesa reversi.\n");
    printf("\nEl objetivo de Reversi es terminar la partida con el mayor numero de fichas de tu color en el tablero.\n");
    printf("\nEste sera el tablero del juego.\n");
    printf("    0   1   2   3   4   5   6   7\n");
    printf("  ---------------------------------\n");
    printf("0 |   |   |   |   |   |   |   |   |\n");
    printf("  |---|---|---|---|---|---|---|---|\n");
    printf("1 |   |   |   |   |   |   |   |   |\n");
    printf("  |---|---|---|---|---|---|---|---|\n");
    printf("2 |   |   |   |   |   |   |   |   |\n");
    printf("  |---|---|---|---|---|---|---|---|\n");
    printf("3 |   |   |   |   |   |   |   |   |\n");
    printf("  |---|---|---|---|---|---|---|---|\n");
    printf("4 |   |   |   |   |   |   |   |   |\n");
    printf("  |---|---|---|---|---|---|---|---|\n");
    printf("5 |   |   |   |   |   |   |   |   |\n");
    printf("  |---|---|---|---|---|---|---|---|\n");
    printf("6 |   |   |   |   |   |   |   |   |\n");
    printf("  |---|---|---|---|---|---|---|---|\n");
    printf("7 |   |   |   |   |   |   |   |   |\n");
    printf("  |---|---|---|---|---|---|---|---|\n");

    printf("\nDebes seleccionar la columna y la fila donde deseas poner tu ficha,cuando sea tu turno.\n");
    printf("\nPuedes seleccionar por ejemplo la fila 4 columna 1 (4,1),dejando un espacio de ambos numeros y si no esta ocupada podras colocar la ficha.\n");
    printf("\nConsidera que desde un inicio las cordenadas E4 y D5 son negras, mientras que D4 y E5 son blancas\n");
    printf("\nEl jugador 1 siempre iniciara usando fichas negras.\n");
    printf("\n");
}

void inicia_el_juego(char tablero[TAMANO_TABLERO][TAMANO_TABLERO]){
    // Esto es para llenar el tablero de vacios
    for (int i = 0; i < TAMANO_TABLERO; i++) {
        for (int j = 0; j < TAMANO_TABLERO; j++) {
            tablero[i][j] = VACIO;
        }
    }
    //LLenar las casillas iniciales:
    tablero[3][3] = BLANCO;
    tablero[4][4] = BLANCO;
    tablero[3][4] = NEGRO;
    tablero[4][3] = NEGRO;
}

bool saltar_turno(char jugador){
    char saltar;
    printf("\nJugador %c, es tu turno. Deseas ceder tu turno y pasar? (s/(cualquier tecla)): ", jugador);
    scanf(" %c", &saltar);
    if (saltar == 's' || saltar == 'S') {
            return 1;
    }else{
        return 0;
    }
}

void putChip(char tablero[TAMANO_TABLERO][TAMANO_TABLERO], int x, int y, char player){
    if (moveAvailable(tablero, x, y, player) == 0){
        printf("\nMovimiento no valido.\n");
        printf("\nPerdiste tu turno.\n");
        return;
    }
    tablero[x][y] = player;
    char opp = getOpp(player);
    int direcciones[8][2] = {
    {-1, -1}, {-1, 0}, {-1, 1},
    {0, -1},          {0, 1},
    {1, -1},  {1, 0},  {1, 1}
    };

    for (int i = 0; i < 8; i++){
        int dx = direcciones[i][0];
        int dy = direcciones[i][1];
        int contador = 0;
        int nx = x + dx;
        int ny = y + dy;

        while (nx >= 0 && nx < TAMANO_TABLERO && ny >= 0 && ny < TAMANO_TABLERO && tablero[nx][ny] == opp){
            contador++;
            nx += dx;
            ny += dy;
        }

        if (contador > 0 && nx >= 0 && nx < TAMANO_TABLERO && ny >= 0 && ny < TAMANO_TABLERO && tablero[nx][ny] == player){
            nx = x + dx;
            ny = y + dy;
            while (nx >= 0 && nx < TAMANO_TABLERO && ny >= 0 && ny < TAMANO_TABLERO && tablero[nx][ny] == opp){
                tablero[nx][ny] = player;
                nx += dx;
                ny += dy;
            }
        }
    }
}

bool terminar_juego() {
    char terminar;
    printf("\nDesean acabar ya el juego, porque la partida no puede continuar? (s para si / cualquier otra tecla para continuar): ");
    scanf(" %c", &terminar);

    if(terminar == 's' || terminar == 'S'){
        return 1;
    }else{

        return 0;
    }
}
