#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_SONGS 10
#define MAX_LENGTH 150

void loadFromFile(char songs[][MAX_LENGTH], int *count);
void saveToFile(char songs[][MAX_LENGTH], int count);
void addSong(char songs[][MAX_LENGTH], int *count);
void deleteSong(char songs[][MAX_LENGTH], int *count);
void updateSong(char songs[][MAX_LENGTH], int count);
void searchSong(char songs[][MAX_LENGTH], int count);
void sortSongs(char songs[][MAX_LENGTH], int count);

int main() {
    char songs[MAX_SONGS][MAX_LENGTH];
    int count = 0;
    int choice;

    loadFromFile(songs, &count);

    do {
        printf("\n--- PLAYLIST MENU ---\n");
        printf("1. Add Song\n");
        printf("2. Delete Song\n");
        printf("3. Update Song\n");
        printf("4. Search Song\n");
        printf("5. Show Playlist\n");
        printf("-1. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar();  

        switch (choice) {
            case 1: addSong(songs, &count); break;
            case 2: deleteSong(songs, &count); break;
            case 3: updateSong(songs, count); break;
            case 4: searchSong(songs, count); break;
            case 5:
                sortSongs(songs, count);
                for (int i = 0; i < count; i++)
                    printf("%d. %s\n", i+1, songs[i]);
                break;
            case -1: break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != -1);

    sortSongs(songs, count);
    saveToFile(songs, count);

    printf("\nFinal playlist saved to playlist.txt\n");
    return 0;
}

void loadFromFile(char songs[][MAX_LENGTH], int *count) {
    FILE *fp = fopen("playlist.txt", "r");
    if (!fp) return;

    *count = 0;
    while (fgets(songs[*count], MAX_LENGTH, fp)) {
        songs[*count][strcspn(songs[*count], "\n")] = '\0';  
        (*count)++;
    }
    fclose(fp);
}

void saveToFile(char songs[][MAX_LENGTH], int count) {
    FILE *fp = fopen("playlist.txt", "w");
    for (int i = 0; i < count; i++)
        fprintf(fp, "%s\n", songs[i]);
    fclose(fp);
}


void addSong(char songs[][MAX_LENGTH], int *count) {
    if (*count >= MAX_SONGS) {
        printf("Playlist is full!\n");
        return;
    }

    printf("Enter song title: ");
    fgets(songs[*count], MAX_LENGTH, stdin);
    songs[*count][strcspn(songs[*count], "\n")] = '\0';

    (*count)++;
    saveToFile(songs, *count);

    printf("Song added successfully.\n");
}

void deleteSong(char songs[][MAX_LENGTH], int *count) {
    char title[MAX_LENGTH];
    printf("Enter song title to delete: ");
    fgets(title, MAX_LENGTH, stdin);
    title[strcspn(title, "\n")] = '\0';

    for (int i = 0; i < *count; i++) {
        if (strcmp(songs[i], title) == 0) {
            for (int j = i; j < *count - 1; j++)
                strcpy(songs[j], songs[j+1]);

            (*count)--;
            saveToFile(songs, *count);
            printf("Song deleted.\n");
            return;
        }
    }
    printf("Song not found.\n");
}

void updateSong(char songs[][MAX_LENGTH], int count) {
    char oldTitle[MAX_LENGTH], newTitle[MAX_LENGTH];

    printf("Enter song to update: ");
    fgets(oldTitle, MAX_LENGTH, stdin);
    oldTitle[strcspn(oldTitle, "\n")] = '\0';

    for (int i = 0; i < count; i++) {
        if (strcmp(songs[i], oldTitle) == 0) {
            printf("Enter new title: ");
            fgets(newTitle, MAX_LENGTH, stdin);
            newTitle[strcspn(newTitle, "\n")] = '\0';

            strcpy(songs[i], newTitle);
            saveToFile(songs, count);

            printf("Song updated.\n");
            return;
        }
    }
    printf("Song not found.\n");
}

void searchSong(char songs[][MAX_LENGTH], int count) {
    char title[MAX_LENGTH];

    printf("Enter song title to search: ");
    fgets(title, MAX_LENGTH, stdin);
    title[strcspn(title, "\n")] = '\0';

    for (int i = 0; i < count; i++) {
        if (strcmp(songs[i], title) == 0) {
            printf("Song found at position %d.\n", i + 1);
            return;
        }
    }
    printf("Song not found.\n");
}

void sortSongs(char songs[][MAX_LENGTH], int count) {
    char temp[MAX_LENGTH];
    for (int i = 0; i < count - 1; i++)
        for (int j = i + 1; j < count; j++)
            if (strcmp(songs[i], songs[j]) > 0) {
                strcpy(temp, songs[i]);
                strcpy(songs[i], songs[j]);
                strcpy(songs[j], temp);
            }
}
