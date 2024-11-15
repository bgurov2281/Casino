#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int getRandomGenerator(int max, int min){
    return (rand() % (max - min + 1)) + min; 
}
int main()
{
    srand(time(0));

    int max=3;
    int min=1;
    int reel1 = getRandomGenerator(max,min);
    int reel2 = getRandomGenerator(max,min);
    int reel3 = getRandomGenerator(max,min);
    printf("%d  %d  %d",reel1,reel2,reel3);
    printf("\n");
    if(reel1==reel2 && reel2==reel3)   
    {
        printf("Winner winner chicken dinner");
    }
    else 
    {
        if((reel1==reel2 && reel3!=reel2)||(reel2==reel3 && reel1!=reel3)||(reel1==reel3 && reel2!=reel3))
        {
            printf("Better luck next time but you're not going home with nothing");
        }
        else
        {
            printf("Yeah just put the frys in the bag bro");
        }
    }
}