#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>   

char board[3][3];
char player1[30],player2[30];
char mark1,mark2;

void loading();
void initializeboard();
void displayboard();
void playermove(char name[], char mark);
void computermove();
char checkwinner();
int isboardfull();

int main()
{
    char winner= ' ';
    int mode;
    loading();
    printf("==Welcome to Tic Tac Toe==\n");

    printf("Enter Player 1 name: ");
    scanf("%[^\n]",player1);
    printf("Choose your mark:\n %s for (X or O): ",player1);
    scanf(" %c",&mark1);

    if(mark1 == 'X' || mark1 == 'x')
    {
        mark1 = 'X';
        mark2 = 'O';
    }
    else
    {
        mark1 = 'O';
        mark2 = 'X';
    }

    printf("CHoose mode of gameplay: \n 1 for Player vs player!\n 2 for Player vs Computer!\n ");
    scanf("%d",&mode);
    if(mode == 1)
    {
        printf("Enter Player 2 name: ");
        scanf(" %[^\n]",player2);
    }
    else
    {
        sprintf(player2,"Computer");
    }
    
    initializeboard();
    displayboard();
    
    for(int chance=0; chance<9; chance++)
    {
        if(chance%2==0)
        {
            playermove(player1,mark1);
        }
        else
        {
            if(mode==1)
            {
                playermove(player2,mark2);
            }
            else
            {
                computermove();
            }
        }
        displayboard();
        winner = checkwinner();
        if(winner != ' ')
        {
            if(winner == mark1)
            {
                printf("\n Congratulations %s!! You won!\n",player1);
            }
            else
            {
                printf("\n Congratulations %s !!! You won!\n",player2);
            }
            return 0;
        }
        if(isboardfull())
        {
            printf("\n Its a draw!!!\n");
            return 0;
        }
    } 
 }

void loading()
{
    char *dots[]= {"",".","..","..."};
    for(int i=0; i<4; i++)
    {
        printf("\rLoading the game%s  ",dots[i]);
        fflush(stdout);
        sleep(1);
    }
    printf("\n");
}

void initializeboard()
{
    int num=1;
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            board[i][j]='0'+num;
            num++;
        }
    }
}

void displayboard()
{
    printf("\n");
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            printf(" %c ",board[i][j]);
            if(j<3-1)
            {
                printf("|");
            }
        }
         printf("\n");
         if(i<3-1)
         {
            printf("---|---|---\n");
         }   
    }
    printf("\n");
}

void playermove(char name[],char mark)
{
    int move,row,col;
    printf("%s (%c), enter a number (1-9): ",name,mark);
    scanf("%d",&move);
    while(move<1||move>9 || board[(move-1)/3][(move-1)%3]== 'X'|| board[(move-1)/3][(move-1)%3]=='O')
    {
        printf("Invalid move... Please try again: ");
        scanf("%d",&move);
    }
    row = (move-1)/3;
    col = (move-1)%3;
    board[row][col]= mark;
}

void computermove()
{
    int move,row,col;
    srand(time(0));
    while(1)
    {
        move = rand() % 9 +1;
        row = (move-1)/3;
        col = (move-1)%3;

        if(board[row][col] != 'X' && board[row][col] != 'O')
        {
            board[row][col]=mark2;
            printf("Computer chose %d\n",move);
            break;
        }
    }
}

char checkwinner()
{
    for(int i=0; i<3; i++)
    {
        if(board[i][0]==board[i][1] && board[i][1]==board[i][2])
            return board[i][0];
        if(board[0][i]==board[1][i] && board[1][i]==board[2][i])
            return board[0][i];
    }
    if(board[0][0]==board[1][1] && board[1][1]==board[2][2])
    {
        return board[0][0];
    }
    if(board[0][2]==board[1][1] && board[1][1]==board[2][0])
    {
        return board[0][2];
    }

    return ' ';
}

int isboardfull()
{
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            if(board[i][j] != 'X' && board[i][j] != 'O')
            {
                return 0;
            }
        }
    }
    return 1;
}
