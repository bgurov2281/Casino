#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

//void updatetokens(int *tokens, int bet, int multiplier)
//{
//*tokens = *tokens - bet + (bet * winMultiplier);
//}
int tokens;
int bet;
void craps(int max,int min)
{
    int getRandomGenerator(int max, int min);
        srand(time(0));

    max=6; min=1;
    int dsum;
    int dsum2;
    int dice1 = getRandomGenerator(max,min);
    int dice2 = getRandomGenerator(max,min);
    int dice3 = getRandomGenerator(max,min);
    int dice4 = getRandomGenerator(max,min);

    dsum=dice1+dice2;
    dsum2=dice3+dice4;

    printf("\n");
    printf("\nPlace your bet PLEASE:\n");
    scanf("%d", &bet);
    printf("\n");
    if (bet>tokens)
    {
        printf("\n");
        printf("\nPlease place a bet less than or equal to %d, enter new bet:", tokens);
        scanf("%d",&bet);
    }
    else 
    {
    printf("\n");
    }
    printf("\n\n");

    printf("Dice 1 = %d\t",dice1);
    printf("Dice 2 = %d\n",dice2);
    printf("Roll is %d\n",dsum);
    if(dsum==7||dsum==11)
    {
        tokens=tokens+bet+(bet*2);
        printf("What a stroke of luck, you have WON!!\n");
        printf("Tokens: %d", tokens);
    }
    else
    {
        if(dsum==2||dsum==3||dsum==12)
        {
            tokens=tokens-bet;
            printf("You have lost\n");
            printf("Tokens: %d\n", tokens);
        }
        else 
        {
            printf("Pointer is %d\n", dsum);
            printf("Let's roll again.");
            printf("\nDice 1 = %d\t",dice3);
            printf("Dice 2 = %d\n",dice4);
            printf("Roll is %d \n",dsum2);
            if(dsum==dsum2)
            {
                tokens=tokens+bet+(bet*2);
                printf("Winner winner\n");
                printf("Tokens: %d\n", tokens);
            }
            else
            {
                tokens=tokens-bet;
                printf("Unfortunely your luck runs out here\n");
                printf("Tokens: %d\n", tokens);

            }
        }
    }
}

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

    char *suits[] = {"<3", "<>", "&&", "##"};
    char *ranks[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "X", "J", "Q", "K"};
    int values[] = {11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10}; //Blackjack Values

    // deck of cards
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
        printf("\n/-----/\n");
        printf("|%s   |\n", deck[hand[i]].suit);
        printf("|  %s  |\n", deck[hand[i]].rank);
        printf("|   %s|\n", deck[hand[i]].suit);
        printf("/-----/\n");
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
    int bet;

    //Get the player's bet
    printf("\nYou have %d tokens. Enter your bet: ", tokens);
    scanf("%d", &bet);

    if(bet > tokens){
        printf("You don't have enough tokens to make that bet.\n");
        return;
    }

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
        tokens -= bet;
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

    // Determine winner and update tokens
    if (dealerValue > 21 || playerValue > dealerValue){
        if(playerValue == 21 && playerCardCount == 2){
            printf("Blackjack! You win 3 to 2!\n");
            tokens += bet * 1.5;
        }
        else{
            printf("You win! You win 1 to 1!\n");
            tokens += bet;
        }
    }
    else if(playerValue < dealerValue){
        printf("Dealer wins! You lost your bet.\n");
        tokens -= bet;
    }
    else {
        printf("It's a tie! You get your bet back.\n");
    }
    printf("You now have %d tokens.\n", tokens);
}

void blackjack()
{
    Card deck[TOTAL_CARDS];
    while(tokens > 0){
        srand(time(NULL));
        cardDeck(deck);
        shuffleDeck(deck);

        playBlackjack(deck);
        char choice;
        do{
        printf("Play again? (y/n): ");
        scanf(" %c", &choice);

        if (choice == 'y'){
            break;
        }
        else if (choice == 'n'){
            break;
        }
        else 
        {
            printf("INvalid input. Please enter 'y' or 'n'.\n");
        }
    }while(choice != 'y' || choice != 'n');
    if(choice != 'y'){
        break;
    }
    }

    printf("Game over! You ended with %d tokens.\n", tokens);
    //add main menu function

    //return 0;
}

int RouletteSpin();
char* FindColor(int number);
void PlayRoulette(int betAmount, char* betType, int betNumber);



void roulette()
{
    int betAmount;
    char betType[15];
    char userChoice;
    int betNumber = -1;

    srand(time(NULL));

    printf("\n\n\n\n\n\n\n\nWelcome to the Roulette Table!\n\n\n\n");

    do {
        printf("Enter your bet amount: ");
        scanf("%d", &betAmount);


        printf("Enter your bet type (number, odd, even, red, black, zero): ");
        scanf("%s", betType);

        if (strcmp(betType, "number") == 0) {
            printf("Enter the number you are betting on (0-36): ");
            scanf("%d", &betNumber);
            printf("\n\n");
        }

        PlayRoulette(betAmount, betType, betNumber);

        printf("Do you want to continue playing? (y/n): ");
        scanf(" %c", &userChoice);
        printf("\n\n\n\n\n\n");
    
    } 
    while (userChoice == 'Y' || userChoice == 'y');

    printf("Thanks for playing Roulette with us!\n\n\n\n");

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

void PlayRoulette(int betAmount, char* betType, int betNumber) {
    int payOut;
    if (betAmount > tokens || tokens <= 0) {
        printf("\n\nYou cannot bet more tokens than what you have!\n\n\n");
        return;
    }
    int resultNumber = RouletteSpin();
    char* color = FindColor(resultNumber);

    printf ("\nThe Roulette Wheel landed on %d (%s).\n\n\n", resultNumber, color);


    if (strcmp(betType, "number") == 0) {
        if (betNumber == resultNumber) {
            if (betNumber == resultNumber && resultNumber == 0) {
                payOut = betAmount * 50;
                tokens += betAmount * 50;
                printf("YOU HIT JACK POT!\n\nYou made %d tokens!\n\nYou now have %d tokens!\n\n\n\n", payOut, tokens);
            } 
            else {
                payOut = betAmount * 35;
                tokens +=  betAmount * 35;
                printf("Nice, your number hit!\n\nYou made %d tokens!\n\nYou now have %d tokens!\n\n\n\n", payOut, tokens);
            }
        }
        else {
            tokens -= betAmount;
            printf("Oops looks like you lost %d tokens!\n\nYou now have %d tokens!\n\n\n\n", betAmount, tokens);
        }
    }
    else if (strcmp(betType, "odd") == 0) {
        if (resultNumber != 0 && resultNumber % 2 != 0) {
            payOut = betAmount * 2;
            tokens += betAmount * 2;
            printf("Your bet landed!\n\nYou made %d tokens!\n\nYou now have %d tokens!\n\n\n\n", payOut, tokens);
        }
        else {
            tokens -= betAmount;
            printf("You lost!\n\nThe house took %d tokens from you!\n\nYou now have %d tokens!\n\n\n\n", betAmount, tokens);
        }
    }
    else if (strcmp(betType, "even") == 0) {
        if (resultNumber != 0 && resultNumber % 2 == 0) {
            payOut = betAmount * 2;
            tokens += betAmount * 2;
            printf("Yippy your bet hit!\n\nYou made %d tokens!\n\nYou now have %d tokens!\n\n\n\n", payOut, tokens);
        }
        else {
            tokens -= betAmount;
            printf("Better luck next time!\n\nYou lost %d tokens!\n\nYou now have %d tokens!\n\n\n\n", betAmount, tokens);
        }
    }
    else if (strcmp(betType, "red") == 0) {
        if (strcmp(color, "red") == 0) {
            payOut = betAmount * 2;
            tokens += betAmount * 2;
            printf("Good job, your bet hit!\n\nYou made %d tokens!\n\nYou now have %d tokens!\n\n\n\n", payOut, tokens);
        }
        else {
            tokens -= betAmount;
            printf("Oh no your bet didn't land!\n\nYou lost %d tokens!\n\nYou now have %d tokens!\n\n\n\n", betAmount, tokens);
        }
    }
    else if (strcmp(betType, "black") == 0) {
        if (strcmp(color, "black") == 0) {
            payOut = betAmount * 2;
            tokens += betAmount * 2;
            printf("You're a pro, you should gamble more!\n\nYou made %d tokens!\n\nYou now have %d tokens!\n\n\n\n", payOut, tokens);
        }
        else {
            tokens -= betAmount;
            printf("Wow, that was a lousy bet!\n\nYou lost %d tokens!\n\nYou now have %d tokens!\n\n\n\n", betAmount, tokens);
        }
    }
    else if (strcmp(betType, "zero") == 0) {
        if (resultNumber == 0) {
            payOut = betAmount * 50;
            tokens += betAmount * 50;
            printf("CONGRATULATIONS YOU HIT JACKPOT!\n\nYou made %d tokens!\n\nYou now have %d tokens!\n\n\n\n", payOut, tokens);
        }
        else {
            tokens -= betAmount;
            printf("What the Sigma!\n\nYou lost %d tokens!\n\nYou now have %d tokens!\n\n\n\n", betAmount, tokens);
        }
    }
    else {
        printf("Invalid bet type\n\n\n\n");
    }
}

void cashout(int cash)
{
    printf("cash");
}


//function for random number generator for the reels
int getRandomGenerator(int max, int min){
    return (rand() % (max - min + 1)) + min; 
}
void GameOne(int max, int min)
{
//initialize the time for the generator
    srand(time(0));

//name each integer/variable
    int jckptodds;
    int scndodds;  
    int pout;     
    int jckptout;
    int wout;

    
    int reel1 = getRandomGenerator(max,min);
    int reel2 = getRandomGenerator(max,min);
    int reel3 = getRandomGenerator(max,min);
    
//odds calculator that will calculate payout
pout=max*max*max;
jckptout=max;
wout=3*max*(max-1);
jckptodds=pout/jckptout;
scndodds=pout/wout;

    printf("\n");
    printf("\nPlace your bet PLEASE:\n");
    scanf("%d", &bet);
    printf("\n");
    if (bet>tokens)
    {
        printf("\n");
        printf("\nPlease place a bet less than or equal to %d, enter new bet:", tokens);
        scanf("%d",&bet);
    }
    else 
    {
    printf("\n");
    }
    printf("\n\n");
    printf("%d  %d  %d",reel1,reel2,reel3);
    printf("\n");
    if(reel1==reel2 && reel2==reel3)   
    { 
        tokens=tokens+bet+(bet*jckptodds);
        printf("Winner winner chicken dinner\n");
        printf("Tokens: %d\n", tokens); 
    }
    else 
    {
        if((reel1==reel2 && reel3!=reel2)||(reel2==reel3 && reel1!=reel3)||(reel1==reel3 && reel2!=reel3))
        {
            tokens=tokens+bet+(bet*scndodds);
            printf("Better luck next time but you're not going home with nothing\n");
            printf("Tokens: %d\n", tokens);
        }
        else
        {
            tokens=tokens-bet;
            printf("Yeah just put the frys in the bag bro\n");
            printf("Tokens: %d\n", tokens);
        }
    }
}
void GameTwo(int max,int min, int lck)
{

    int jckptodds; int pairout;
    int scndodds;  int pairodds;
    int pout;     
    int jckptout;
    int wout;
    int specificjckpt;

    int reel1 = getRandomGenerator(max,min);
    int reel2 = getRandomGenerator(max,min);
    int reel3 = getRandomGenerator(max,min);
   
    pout=max*max*max;
    wout=3*max*(max-1);
    scndodds=pout/wout;
    specificjckpt=pout/1;

    printf("\n");
    printf("\nPlace your bet PLEASE:\n");
    scanf("%d", &bet);
    printf("\n");
    if (bet>tokens)
    {
        printf("\n");
        printf("\nPlease place a bet less than or equal to %d, enter new bet:", tokens);
        scanf("%d",&bet);
    }
    else 
    {
    printf("\n");
    }
    printf("\n\n");
    printf("%d  %d  %d",reel1,reel2,reel3);
    printf("\n");
    if(reel1==lck && reel2==lck && reel3==lck)   
    { 
        tokens=tokens+bet+(bet*specificjckpt);
        printf("Winner winner chicken dinner\n");
        printf("Tokens: %d\n", tokens); 
    }
    else 
    {
        if((reel1==reel2 && reel3!=reel2)||(reel2==reel3 && reel1!=reel3)||(reel1==reel3 && reel2!=reel3))
        {
            tokens=tokens+bet+(bet*scndodds);
            printf("Better luck next time but you're not going home with nothing\n");
            printf("Tokens: %d\n", tokens);
        }
        else
        {
            tokens=tokens-bet;
            printf("Yeah just put the frys in the bag bro\n");
            printf("Tokens: %d\n", tokens);
        }
    }
}
void GameThree(int max,int min, int lck2)
{
    
    int jckptodds; int pairout;
    int scndodds;  int pairodds;
    int pout;     
    int jckptout;
    int wout;

    int reel1 = getRandomGenerator(max,min);
    int reel2 = getRandomGenerator(max,min);
    int reel3 = getRandomGenerator(max,min);

    wout=3*max*(max-1);
    pout=max*max*max;
    jckptout=max;
    pairout=max*(max-1);
    pairodds=pout/pairout;
    jckptodds=pout/jckptout;
    scndodds=pout/wout;

    printf("\n");
    printf("\nPlace your bet PLEASE:\n");
    scanf("%d", &bet);
    printf("\n");
    if (bet>tokens)
    {
        printf("\n");
        printf("\nPlease place a bet less than or equal to %d, enter new bet:", tokens);
        scanf("%d",&bet);
    }
    else 
    {
    printf("\n");
    }
    printf("\n\n");
    printf("%d  %d  %d",reel1,reel2,reel3);
    printf("\n");
    if(reel1==reel2 && reel2==reel3)   
    { 
        tokens=tokens+bet+(bet*jckptodds);
        printf("Winner winner chicken dinner\n");
        printf("Tokens: %d\n", tokens); 
    }
    else 
    {
        if((reel1==reel2 && reel3!=reel2 && reel1==lck2)||(reel2==reel3 && reel1!=reel3 && reel2==lck2)||(reel1==reel3 && reel2!=reel3 && reel1==lck2))
        {
            tokens=tokens+bet+(bet*pairodds);
            printf("Seems like those lucky numbers did have some magic after all\n");
            printf("Tokens: %d\n", tokens);
        }
        else
        {
                if((reel1==reel2 && reel3!=reel2)||(reel2==reel3 && reel1!=reel3)||(reel1==reel3 && reel2!=reel3))
                {
                    tokens=tokens+bet+(bet*scndodds);
                    printf("Better luck next time but you're not going home with nothing\n");
                    printf("Tokens: %d\n", tokens);
                }
                        else 
                        {
                            tokens= tokens-bet;
                            printf("Yeah just put the frys in the bag bro\n");
                            printf("Tokens: %d\n", tokens);
                            printf("\n\n");
                        }
        }
    }
}
void slots(int lck,int lck2,int max,int min, int choice)
{
    
    /*tokens=10; 
    int lck,lck2;
    int choice;
    int max, min=1;*/
    min=1;
while(1)
{
printf("\n\n");
printf("Choose a game any game: \n");
printf("1.Traditional Jackpot \n");
printf("2.Super Jackpot \n");
printf("3.Pairs Parade \n");
printf("4.Back to Main Menu \n\n\n");
scanf("%d", &choice);

switch(choice)
{
    case 1:
            printf("Welcome to Traditional Jackpot, rules are simple, there is a standard payout with 3 different payout possibilites \n 100 to 1 payout for 10 symbols \n 400 to 1 payout for 20 symbols \n 900 to 1 payout for 30 symbols\n");
            printf("Choose your odds, 10, 20 or 30: \n");
            scanf("%d", &max);
            GameOne( max, min);
    break;

    case 2:
            printf("Welcome to Super Jackpot, rules are simple pick a specific Jackpot number for 20 times the payout, rest of payouts are standard\n");
            printf("Choose your lucky number(1-20): \n");
            scanf("%d", &lck);
            max=20;
            GameTwo( max, min, lck);
    break;

    case 3:
            printf("Welcome to Pairs Parade, rules are simple pick a specific pair for 3 times the payouts on pairs, rest of payouts are standard\n");
            printf("Choose your lucky pair(1-20): \n");
            scanf("%d", &lck2);
            max=20;
            GameThree( max, min, lck2);
    break;

    case 4:
            return;
            exit(0);
    
     default:
                printf("Invalid Choice. Feel free to try again. \n");
}
}
//return 0;
}

void gameinfo(int choice)
{
    while(1)
    {
        printf("******************************************\n");
        printf("*                                        *\n");
        printf("*        1. Information on Slots         *\n");
        printf("*        2. Information on Blackjack     *\n");
        printf("*        3. Information on Roulette      *\n");
        printf("*        4. Information on Craps         *\n");
        printf("*        5. Back to Main Menu            *\n");
        printf("*                                        *\n");
        printf("******************************************\n");
        scanf("%d", &choice);
        switch(choice)
        {
        case 1:

        break;

        case 2:
            printf("\nCard Values\n");
            printf("1: Number Cards (2-10) are worth their face value.\n");
            printf("2: Face cards (Jack, Queen, King) are worth 10 points each.\n");
            printf("3: Aces can be worth 1 or 11, depending on whcih value benefits the hand most.\n\n");
            printf("\nGameplay\n");
            printf("1: Player is dealt two cards face-up.\n");
            printf("2: The dealer is dealt one card face-up and one face down (the 'hole card').\n");
            printf("3: Player decides to hit or stand\n");
            printf("\t3.1: Hit- to take another card. Player can hit as many times as they want until hand totals 21 or player 'busts.'\n");
            printf("\t3.2: Stand- to keep the current total and end the turn.\n");
            printf("4: The dealer reveals their 'hole card' once the player finishes their turn.\n");
            printf("\t4.1: The dealer must 'hit' until their hand totals at least 17.\n\n");
            printf("\nWinning and Losing\n");
            printf("1: Blackjack- A hand totaling 21 with an Ace and a 10-point card on the first two cards.\n");
            printf("\t1.1: The payout is 3 to 2\n");
            printf("2: Win- Player hand total is closer to 21 than the dealers without exceeding 21.\n");
            printf("3: Bust- If the player's hand total exceeds 21, player lose automatically, even if the dealer also busts.\n");
            printf("4: Push- If the player and the dealer have the same hand total, its a tie, and the bet is returned.\n");
            printf("5: Dealer Bust- If the dealer exceeds 21, all remaining players win.\n");
        break;

        case 3:
            printf("\nBet Types: \n");
            printf("1: Black or Red are the colors (excluding 0 because it is green) of the slots 1-36 that you can bet on.\n");
            printf("2: Numbers bet is a bet where you can choose what number (0-36) that you think the wheel will land on.\n");
            printf("3: Odd or Even bet is a bet where you choose if you think the wheel will land on an odd or even number.\n");
            printf("4: Zero bet is where you bet on the number 0 which is the only Green slot on the wheel.\n");
            printf("\t4.1: Because zero is the only green slot on the wheel we decided to make it our Jackpot slot.\n");
            printf("\t4.2: You can choose to bet on 0 by typing 'zero' or typing 'number' and entering the number 0 after asked for bet type.\n");
            printf("\nPay Outs:\n");
            printf("Black, Red, Odd, and Even type bets all have a 1 to 1 pay out, meaning you double your tokens if your bet lands.\n");
            printf("Number type bets (except 0) have a times 35 pay out, meaning your pay out will be your bet amount times 35 if your number lands.\n");
            printf("Zero bet (including betting 'number' then typing number '0') is the jackpot with a bet amount times 50 pay out if 0 lands.\n");
            printf("In all bet types if your bet does not land you will lose the amount of tokens you bet on for your type of bet, so play recklessly!\n");
            printf("\nNow let your addiction to gambling begin, have fun, stay committed, and remember 100%% of gamblers quit before making millions!\n\n\n");
        break;

        case 4:

        break;

        case 5:
        return;
        exit(0);

        default:
                        printf("Invalid Choice. Feel free to try again. ");
        }
    }
}

int main()
{

    int yeah,yee,cash,max,min,lck,lck2,choice;
     printf("\n\nWelcome to Ohms Casino how many tokens would you like to buy: \n");
     scanf("%d", &tokens);
    //int choice;
    while(1)
    {
        printf("\n\n");
        printf("******************************************\n");
        printf("*                                        *\n");
        printf("*           $$ OHM'S CASINO $$           *\n");
        printf("*                                        *\n");
        printf("******************************************\n");
        printf("*                                        *\n");
        printf("*           1. Play Slots                *\n");
        printf("*           2. Play Blackjack            *\n");
        printf("*           3. Play Roulette             *\n");
        printf("*           4. Play Craps                *\n");
        printf("*           5. View Tokens               *\n");
        printf("*           6. Game Information          *\n");
        printf("*           7. Exit                      *\n");
        printf("*                                        *\n");
        printf("******************************************\n");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                    slots(lck,lck2,max,min,choice);
            break;

            case 2:
                    blackjack();
            break;
            
            case 3:
                    roulette();
            break;

            case 4:
                    min=1;
                    max=6;
                    craps(max,min);
            break;

            case 5:
                    printf("You have %d tokens!", tokens);
            break;

            case 6:
                    gameinfo(choice);
            break;

            case 7:
                    printf("Thank you for playing. \n");
                    exit(0);

                default:
                        printf("Invalid Choice. Feel free to try again. ");
        }
    }
}
