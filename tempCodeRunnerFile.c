#include<stdio.h>
#include<stdlib.h>
#include<time.h>

//function for random number generator for the reels
int getRandomGenerator(int max, int min){
    return (rand() % (max - min + 1)) + min; 
}
int main()
{
//initialize the time for the generator
    srand(time(0));

//name each integer/variable
    int tokens=10;
    int jckptodds; 
    int scndodds;
    int pout;
    int jckptout;
    int wout;
    int max=20;
    int min=1;
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
        printf("Tokens: %d", tokens); 
    }
    else 
    {
        if((reel1==reel2 && reel3!=reel2)||(reel2==reel3 && reel1!=reel3)||(reel1==reel3 && reel2!=reel3))
        {
            tokens=tokens+(tokens*scndodds);
            printf("Better luck next time but you're not going home with nothing\n");
            printf("Tokens: %d", tokens);
        }
        else
        {
            printf("Yeah just put the frys in the bag bro\n");
            printf("Tokens: %d", tokens);
        }
    }
}