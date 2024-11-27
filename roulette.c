#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>


int RouletteSpin();
char* FindColor(int number);
void PlayRoulette(int betAmount, char* betType);



int main() {
    int betAmount;
    char betType[15];
    char userChoice;

    srand(time(NULL));

    printf("\nWelcome to the Roulette Table!\n\n");

    do {
    printf("Enter your bet amount: ");
    scanf("%d", &betAmount);
    printf("Enter your bet type (number, odd, even, red, black, zero): ");
    scanf("%s", &betType);

    PlayRoulette(betAmount, betType);

    printf("Do you want to continue playing? (y/n): ");
    scanf(" %c", &userChoice);
    
    }while (userChoice == 'Y' || userChoice == 'y');

    printf("Thanks for playing Roulette with us!\n");


    return 0;
}

int RouletteSpin() {
    return rand() % 37;
}

char* FindColor(int number) {
    if (number == 0){
        return "green";
    }

    int redNumbers[] = {1, 3, 5, 7, 9, 12, 14, 16, 18, 19, 21, 23, 25, 27, 30, 32, 34, 36};
    int blackNumbers[] = {2, 4, 6, 8, 10, 11, 13, 15, 17, 20, 22, 24, 26, 28, 29, 31, 33, 35};
    
    for (int i = 0; i < 18; ++i) {
        if (number == redNumbers[i]) {
            return "red";
        }
        if (number == blackNumbers[i]) {
            return "black";
        }
    }
    return "error";
}

void PlayRoulette(int betAmount, char* betType) {
    int resultNumber = RouletteSpin();
    char* color = FindColor(resultNumber);
    int betNumber;
    int payOut = 0;

    printf ("The Roulette Wheel landed on %d (%s)\n", resultNumber, color);

    if (strcmp(betType, "number") == 0) {
        printf("Enter the number you want to bet on (0-36)\n");
        scanf("%d", &betNumber);
        if (betNumber == resultNumber) {
            if (betNumber == resultNumber && resultNumber == 0) {
                payOut = betAmount * 50;
                printf("YOU HIT JACK POT!\nYou made %d", payOut);
            } 
            else {
                payOut =  betAmount * 35;
                printf("Nice, your number hit!\nYou made %d", payOut);
            }
        }
        else {
            printf("Oops looks like you lost %d\n", betAmount);
        }
    }
    else if (strcmp(betType, "odd") == 0) {
        if (resultNumber != 0 && resultNumber % 2 != 0) {
            
        }
    }
    
}


