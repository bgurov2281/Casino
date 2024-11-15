#include<stdio.h>
#include<stdlib.h>
#include<time.h>

//function for random number generator for the reels
int getRandomGenerator(int max, int min){
    return (rand() % (max - min + 1)) + min; 
}
void GameOne(int max, int min, int tokens)
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


    printf("%d  %d  %d",reel1,reel2,reel3);
    printf("\n");
    if(reel1==reel2 && reel2==reel3)   
    { 
        tokens=tokens+(tokens*jckptodds);
        printf("Winner winner chicken dinner\n");
        printf("Tokens: %d\n", tokens); 
    }
    else 
    {
        if((reel1==reel2 && reel3!=reel2)||(reel2==reel3 && reel1!=reel3)||(reel1==reel3 && reel2!=reel3))
        {
            tokens=tokens+(tokens*scndodds);
            printf("Better luck next time but you're not going home with nothing\n");
            printf("Tokens: %d\n", tokens);
        }
        else
        {
            printf("Yeah just put the frys in the bag bro\n");
            printf("Tokens: %d\n", tokens);
        }
    }
}
void GameTwo(int max,int min,int tokens, int lck)
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
    printf("%d  %d  %d",reel1,reel2,reel3);
    printf("\n");
    if(reel1==lck && reel2==lck && reel3==lck)   
    { 
        tokens=tokens+(tokens*specificjckpt);
        printf("Winner winner chicken dinner\n");
        printf("Tokens: %d\n", tokens); 
    }
    else 
    {
        if((reel1==reel2 && reel3!=reel2)||(reel2==reel3 && reel1!=reel3)||(reel1==reel3 && reel2!=reel3))
        {
            tokens=tokens+(tokens*scndodds);
            printf("Better luck next time but you're not going home with nothing\n");
            printf("Tokens: %d\n", tokens);
        }
        else
        {
            printf("Yeah just put the frys in the bag bro\n");
            printf("Tokens: %d\n", tokens);
        }
    }
}
void GameThree(int max,int min, int tokens, int lck2)
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

    printf("%d  %d  %d",reel1,reel2,reel3);
    printf("\n");
    if(reel1==reel2 && reel2==reel3)   
    { 
        tokens=tokens+(tokens*jckptodds);
        printf("Winner winner chicken dinner\n");
        printf("Tokens: %d\n", tokens); 
    }
    else 
    {
        if((reel1==reel2 && reel3!=reel2 && reel1==lck2)||(reel2==reel3 && reel1!=reel3 && reel2==lck2)||(reel1==reel3 && reel2!=reel3 && reel1==lck2))
        {
            tokens=tokens+(tokens*pairodds);
            printf("Better luck next time but you're not going home with nothing\n");
            printf("Tokens: %d\n", tokens);
        }
        else
        {
                if((reel1==reel2 && reel3!=reel2)||(reel2==reel3 && reel1!=reel3)||(reel1==reel3 && reel2!=reel3))
                {
                    tokens=tokens+(tokens*scndodds);
                    printf("Better luck next time but you're not going home with nothing\n");
                    printf("Tokens: %d\n", tokens);
                }
                        else 
                        {
                            printf("Yeah just put the frys in the bag bro\n");
                            printf("Tokens: %d\n", tokens);
                        }
        }
    }
}
int main()
{
    int tokens=10;
    int lck,lck2;
    int choice;
    int max, min=1;
while(1)
{
printf("Choose a game any game: \n");
printf("1.Traditional Jackpot \n");
printf("2.Super Jackpot \n");
printf("3.Pairs Parade \n");
printf("4.Back to Main Menu \n");
scanf("%d", &choice);

switch(choice)
{
    case 1:
            printf("Welcome to Traditional Jackpot, rules are simple, there is a standard payout with 3 different payout possibilites \n 100 to 1 payout for 10 symbols \n 400 to 1 payout for 20 symbols \n 900 to 1 payout for 30 symbols\n");
            printf("Choose your odds, 10, 20 or 30: \n");
            scanf("%d", &max);
            GameOne( max, min, tokens);
    break;

    case 2:
            printf("Welcome to Super Jackpot, rules are simple pick a specific Jackpot number for 20 times the payout, rest of payouts are standard\n");
            printf("Choose your lucky number(1-20): \n");
            scanf("%d", &lck);
            max=20;
            GameTwo( max, min, tokens, lck);
    break;

    case 3:
            printf("Welcome to Pairs Parade, rules are simple pick a specific pair for 3 times the payouts on pairs, rest of payouts are standard\n");
            printf("Choose your lucky pair(1-20): \n");
            scanf("%d", &lck2);
            max=20;
            GameThree( max, min, tokens, lck2);
    break;

    case 4:
            printf("Main Menu\n");
            exit(0);
    
     default:
                printf("Invalid Choice. Feel free to try again. \n");
}
}
return 0;
}