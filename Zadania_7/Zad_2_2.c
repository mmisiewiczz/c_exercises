#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_GAMES 100
#define LINE_SIZE 256

typedef struct {
    int id;
    int max_red;
    int max_green;
    int max_blue;
} Game;

void parse_line(char *line, Game *game) {
    int red, green, blue;
    char *token = strtok(line, ";");
    while (token != NULL) {
        // sscanf może nie działać poprawnie, jeśli tokeny są w innej kolejności
        // dodajmy kilka warunków sprawdzających, aby upewnić się, że są poprawnie przypisane
        if (sscanf(token, "%d red, %d green, %d blue", &red, &green, &blue) == 3) {
            if (red > game->max_red) game->max_red = red;
            if (green > game->max_green) game->max_green = green;
            if (blue > game->max_blue) game->max_blue = blue;
        } else if (sscanf(token, "%d red, %d green", &red, &green) == 2) {
            if (red > game->max_red) game->max_red = red;
            if (green > game->max_green) game->max_green = green;
        } else if (sscanf(token, "%d red, %d blue", &red, &blue) == 2) {
            if (red > game->max_red) game->max_red = red;
            if (blue > game->max_blue) game->max_blue = blue;
        } else if (sscanf(token, "%d green, %d blue", &green, &blue) == 2) {
            if (green > game->max_green) game->max_green = green;
            if (blue > game->max_blue) game->max_blue = blue;
        } else if (sscanf(token, "%d red", &red) == 1) {
            if (red > game->max_red) game->max_red = red;
        } else if (sscanf(token, "%d green", &green) == 1) {
            if (green > game->max_green) game->max_green = green;
        } else if (sscanf(token, "%d blue", &blue) == 1) {
            if (blue > game->max_blue) game->max_blue = blue;
        }
        token = strtok(NULL, ";");
    }
}

int main() {
    FILE *file = fopen("input_2.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    char line[LINE_SIZE];
    Game games[MAX_GAMES];
    int game_count = 0;

    while (fgets(line, sizeof(line), file)) {
        Game game = {0, 0, 0, 0};
        sscanf(line, "Game %d:", &game.id);
        char *data = strchr(line, ':') + 1;
        parse_line(data, &game);
        games[game_count++] = game;
    }
    fclose(file);

    int total_power = 0;
    for (int i = 0; i < game_count; i++) {
        int power = games[i].max_red * games[i].max_green * games[i].max_blue;
        total_power += power;
        printf("Game %d: Minimum Red (%d), Minimum Green (%d), Minimum Blue (%d)\n",
               games[i].id, games[i].max_red, games[i].max_green, games[i].max_blue);
    }
    printf("Sum of powers: %d\n", total_power);

    return EXIT_SUCCESS;
}
