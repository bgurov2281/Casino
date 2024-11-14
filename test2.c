#include <stdio.h>

int main() {
    int jerseyNumbers[5];
    int ratings[5];
    char option = ' ';
    int i;

    // Prompt user to input jersey numbers and ratings
    for (i = 0; i < 5; i++) {
        printf("Enter player %d's jersey number:\n", i + 1);
        scanf("%d", &jerseyNumbers[i]);
        printf("Enter player %d's rating:\n", i + 1);
        scanf("%d", &ratings[i]);
        printf("\n");
    }

    // Output roster
    printf("ROSTER\n");
    for (i = 0; i < 5; i++) {
        printf("Player %d -- Jersey number: %d, Rating: %d\n", i + 1, jerseyNumbers[i], ratings[i]);
    }

    // Menu of options
    while (option != 'q') {
        printf("\nMENU\nu - Update player rating\na - Output players above a rating\nr - Replace player\no - Output roster\nq - Quit\n");
        printf("\nChoose an option:\n");
        scanf(" %c", &option);

        if (option == 'o') {
            // Output roster
            printf("\nROSTER\n");
            for (i = 0; i < 5; i++) {
                printf("Player %d -- Jersey number: %d, Rating: %d\n", i + 1, jerseyNumbers[i], ratings[i]);
            }
        } else if (option == 'u') {
            // Update player rating
            int jerseyNumber, newRating;
            printf("Enter a jersey number: ");
            scanf("%d", &jerseyNumber);
            printf("Enter a new rating for player: ");
            scanf("%d", &newRating);
            for (i = 0; i < 5; i++) {
                if (jerseyNumbers[i] == jerseyNumber) {
                    ratings[i] = newRating;
                }
            }
        } else if (option == 'a') {
            // Output players above a rating
            int rating;
            printf("Enter a rating: ");
            scanf("%d", &rating);
            printf("ABOVE %d\n", rating);
            for (i = 0; i < 5; i++) {
                if (ratings[i] > rating) {
                    printf("Player %d -- Jersey number: %d, Rating: %d\n", i + 1, jerseyNumbers[i], ratings[i]);
                }
            }
        } else if (option == 'r') {
            // Replace player
            int jerseyNumber, newJerseyNumber, newRating;
            printf("Enter a jersey number: ");
            scanf("%d", &jerseyNumber);
            printf("Enter a new jersey number: ");
            scanf("%d", &newJerseyNumber);
            printf("Enter a rating for the new player: ");
            scanf("%d", &newRating);
            for (i = 0; i < 5; i++) {
                if (jerseyNumbers[i] == jerseyNumber) {
                    jerseyNumbers[i] = newJerseyNumber;
                    ratings[i] = newRating;
                }
            }
        }
    }

    return 0;
}