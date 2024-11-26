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
    int value;
} Card;

void cardDeck(Card *deck){

    char *suits[] = {"Hearts", "Diamonds", "Clubs", "Spades"};
    char *ranks[] = {"Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King"};
    int values[] = {11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10}; //Blackjack Values

    // First deck
    for(int deckNum = 0; deckNum < 2; deckNum++){
        for(int i = 0; i < NUM_SUITS; i++){
            for(int j = 0; j < NUM_RANKS; j++){
                int index = deckNum * NUM_CARDS + i * NUM_RANKS + j;
                deck[index].suit = suits[i];
                deck[index].rank = ranks[j];
                deck[index].value = values[j];
            }
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

int drawCard(Card *deck, int *cardDrawn, int *currentIndex){
    if(*currentIndex < TOTAL_CARDS){
        int index = *currentIndex;
        cardDrawn[index] = 1;
        (*currentIndex)++;
        return index;
    }
    return -1; //No more cards
}

int calculateHandValue(Card *deck, int *hand, int numCards){
    int totalValue = 0, numAces = 0;
    for(int i = 0; i < numCards; i++){
        int cardValue = deck[hand[i]].value;
        totalValue += cardValue;
        if(cardValue == 11){
            numAces++;
        }
    }
    while(totalValue > 21 && numAces > 0){
        totalValue -= 10;
        numAces--;
    }
    return totalValue;
}

void printHand(Card *deck, int *hand, int numCards){
    for (int i = 0; i < numCards; i++){
        printf("%s of %s\n", deck[hand[i]].rank, deck[hand[i]].suit);
    }
}

void playBlackjack(Card *deck){
    int cardDrawn[TOTAL_CARDS];
    for(int i = 0; i < TOTAL_CARDS; i++){
        cardDrawn[i] = 0;
    }
    int currentIndex = 0;
    int playerHand[10], dealerHand[10];
    int playerCardCount = 0, dealerCardCount = 0;

    // Starting Hands
    playerHand[playerCardCount++] = drawCard(deck, cardDrawn, &currentIndex);
    playerHand[playerCardCount++] = drawCard(deck, cardDrawn, &currentIndex);
    dealerHand[dealerCardCount++] = drawCard(deck, cardDrawn, &currentIndex);

    printf("\nYour hand:\n");
    printHand(deck, playerHand, playerCardCount);

    printf("\nDealer's visible card:\n");
    printHand(deck, dealerHand, 1);

    // Player's turn
    int playerValue = calculateHandValue(deck, playerHand, playerCardCount);
    char choice;
    while (playerValue < 21){
        printf("\nYour total: %d. Hit (h) or Stand (s)? ", playerValue);
        scanf(" %c", &choice);
        if(choice == 's'){
            break;
        }
        else if(choice == 'h'){
            playerHand[playerCardCount++] = drawCard(deck, cardDrawn, &currentIndex);
            printf("\nYour hand:\n");
            printHand(deck, playerHand, playerCardCount);
            playerValue = calculateHandValue(deck, playerHand, playerCardCount);
        }
    }
    if (playerValue > 21){
        printf("\nYou busted! Dealer wins.\n");
        return;
    }

    //Dealer's turn
    printf("\nDealer's turn:\n");
    while(calculateHandValue(deck, dealerHand, dealerCardCount) < 17){
        dealerHand[dealerCardCount++] = drawCard(deck, cardDrawn, &currentIndex);
    }
    printf("\nDealer's hand:\n");
    printHand(deck, dealerHand, dealerCardCount);

    int dealerValue = calculateHandValue(deck, dealerHand, dealerCardCount);
    printf("\nYour total: %d, Dealer's total: %d\n", playerValue, dealerValue);

    // Determine winner
    if (dealerValue > 21 || playerValue > dealerValue){
        printf("You win!\n");
    }
    else if(playerValue < dealerValue){
        printf("Dealer wins!\n");
    }
    else {
        printf("It's a tie!\n");
    }
}

int main(){
    Card deck[TOTAL_CARDS];
    srand(time(NULL));
    cardDeck(deck);
    shuffleDeck(deck);
    playBlackjack(deck); 


    return 0;
}