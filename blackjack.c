#include<stdio.h>
#include<stdlib.h>
#include<time.h>

const int NUM_SUITS = 4;
const int NUM_RANKS = 13;
const int NUM_CARDS = 52;
const int TOTAL_CARDS = 104; //two decks

typedef struct {
    char *suit;
    char *rank;
} Card;

void cardDeck(Card *deck){

    char *suits[] = {"Hearts", "Diamonds", "Clubs", "Spades"};
    char *ranks[] = {"Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King"};

    // First deck
    for(int i = 0; i < NUM_SUITS; i++){
        for(int j = 0; j < NUM_RANKS; j++){
            deck[i * NUM_RANKS + j].suit = suits[i];
            deck[i * NUM_RANKS + j].rank = ranks[j];
        }
    }

    // Second deck
    for(int i = 0; i < NUM_SUITS; i++){
        for(int j = 0; j < NUM_RANKS; j++){
            deck[NUM_CARDS + i * NUM_RANKS + j].suit = suits[i];
            deck[NUM_CARDS + i * NUM_RANKS + j].rank = ranks[j];
        }
    }
}

void shuffleDeck(Card *deck){
    Card temp;
    for(int i = 0; i < TOTAL_CARDS; i++){
        int j = i + rand() % (TOTAL_CARDS - i);
        temp = deck[i];
        deck[i] = deck[j];
        deck[j] = temp;
    }
}

void printDeck(Card *deck){
    for(int i = 0; i < TOTAL_CARDS; i++){
        printf("%s of %s\n", deck[i].rank, deck[i].suit);
    }
}

int drawCard(Card *deck, int *cardDrawn){
    for(int i = 0; i < TOTAL_CARDS; i++){
        if(!cardDrawn[i]){
            cardDrawn[i] = 1;
            printf("Drawn card: %s of %s\n", deck[i].rank, deck[i].suit);
            return i;
        }
    }
    return -1;
}

int main(){
    Card deck[TOTAL_CARDS];
    int cardDrawn[TOTAL_CARDS];
    for(int i = 0; i < TOTAL_CARDS; i++){
        cardDrawn[i] = 0;
    }
    srand(time(NULL));

    cardDeck(deck);
    shuffleDeck(deck);
    printDeck(deck);

    printf("\nDrawing cards:\n");
    for(int i = 0; i < TOTAL_CARDS; i++){
        if(drawCard(deck, cardDrawn) == -1){
            printf("All cards have been drawn.\n");
            break;
        }
    }
    return 0;
}