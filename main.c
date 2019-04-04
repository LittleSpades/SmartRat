#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct maboyinfo{
    int x_cur;
    int y_cur;

    int x_prev;
    int y_prev;

    int dir;
    int nsteps;
}maboy;

maboy* initrat(int _bsize);
int** initboard(int _bsize, maboy* _rat);
void printb(int** _board, int _bsize);
void nextstep(maboy* _rat);
void delay(int number_of_seconds) ;
void freeall(int** _board, int _bsize, maboy* _rat);

maboy* initrat(int _bsize){
    maboy* _rat= (maboy*)malloc(sizeof(maboy));;

    _rat->x_cur = _bsize/2;
    _rat->y_cur = _bsize/2;

    _rat->nsteps = 0;

    return(_rat);
}

int** initboard(int _bsize, maboy* _rat){
    
    int i, a;
    int** b = (int**)malloc(_bsize * sizeof(int*));

    for(i=0; i<_bsize; i++){
       b[i] = (int*)malloc(_bsize * sizeof(int));
    }

   for(i=0; i<_bsize; i++){
        for(a=0; a<_bsize; a++){
            if(i==_rat->x_cur && a==_rat->y_cur){
                b[i][a]=8;
            }
            else if(i==0 || i==_bsize-1 || a==0 || a==_bsize-1){
                b[i][a]=1;
            }
            else{
                b[i][a]=0;
            }
            
        }
    }

   return(b);
}

void printb(int** _board, int _bsize){
    
    int i,a;

    for(i=0; i<_bsize; i++){
        for(a=0; a<_bsize; a++){

            if(_board[i][a]==8)
            {
                printf("@ ");
            }
            else
            {
                printf("%d ", _board[i][a]);
            }
        }
        printf("\n");
    }
}

void nextstep(maboy* _rat){
    
    srand(time(NULL));
    int _dir = rand()%4;

    _rat->dir = _dir;
    (_rat->nsteps)++;

    _rat->x_prev = _rat->x_cur;
    _rat->y_prev = _rat->y_cur;

    switch(_dir)
    {
        case 0:     //up
            (_rat->x_cur)--;
            break;

        case 1:     //down
            (_rat->x_cur)++;
            break;

        case 2:     //right
            (_rat->y_cur)++;
            break;

        case 3:     //left
            (_rat->y_cur)--;
            break;
    }
}

void delay(int number_of_seconds) 
{ 
    // Converting time into milli_seconds 
    int milli_seconds = 1000 * number_of_seconds; 
  
    // Stroing start time 
    clock_t start_time = clock(); 
  
    // looping till required time is not acheived 
    while (clock() < start_time + milli_seconds) 
        ; 
} 

void freeall(int** _board, int _bsize, maboy* _rat){

    int i;

    free(_rat);

    for(i=0; i<_bsize; i++){
       free(_board[i]);
   }
    free(_board);
}

int main()
{   
   int bsize; 
   int i, a;
   int GameOver=0;
   int** board;
   maboy* rat;

    printf("Board's Size:\n");
    scanf("%d", &bsize);

    rat = initrat(bsize);

    board = initboard(bsize, rat);

    printb(board, bsize);

    while(1){
        //=============================
        //Mov
        nextstep(rat); //rand mov e atualizar rato
        
        if(board[rat->x_cur][rat->y_cur] == 1)  //Verfificação GAME OVER
        {
            GameOver=1;
        }

        board[rat->x_prev][rat->y_prev] = 0;    //atualizar matriz
        board[rat->x_cur][rat->y_cur] = 8;      //================

        //imprimir
        printb(board, bsize);

        if(GameOver == 1)
        {
            printf("GAME OVER!!!\n");
            break;
        }

        delay(1);
    }
    
    freeall(board, bsize, rat);
    return 0;
}