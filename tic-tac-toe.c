#include <stdbool.h>
#include <stdio.h>

void printGrid(char grid [6][6]);
void updateGame(char move,char player,char grid [6][6]);
void launchGame();
bool gameEnded(char grid[6][6]);

// this flags whether this position is available or not, 1 means available, and zero means not.
bool positionFlag = 1;
int main()
{
    printf("\t\t\tWELCOME!\n");
    printf("type 's' to start the game or any other key to exit\n");
    // taking input from the user to start the game
    char inputFromUser = ' ';
    scanf(" %c", &inputFromUser);
    if(inputFromUser == 's'){
        //changing the input to prepare it after the game is finished to be able to restart the game
        inputFromUser = 'r';
        while(inputFromUser == 'r') {
            // starting the game using launchGame function
            launchGame();
            //checking whether the user wants to play again or not.
            printf("type 'r' to reload the game, or any other key to exit.\n");
            scanf(" %c", &inputFromUser);
     }

    }
}

void launchGame(){
    // initializing the two players 1 and 2.
    char player1 = ' ';
    char player2 ;
    // implementing the two players
    while(1) {
        // taking the first player preference.
        printf("Choose 'X' or 'O' for player1 \n");
        scanf(" %c", &player1);
        //Assigning the other character (either 'X' or 'O') to the other player
        if (player1 == 'X' || player1 == 'x') {
            player1 = 'X';
            player2 = 'O';
            break;
        } else if(player1 == 'o' || player1 == 'O') {
            player1 = 'O';
            player2 = 'X';
            break;
        } else
            // if the first player entered other characters than the capital and small 'x' and 'o' he will be kept asked for a valid character until he enters one.
            printf("Please enter a valid player\n");
    }
    //stating the two player preferences.
    printf("Player1 is '%c' and Player2 is '%c'\n", player1,player2);
    printf("GAME STARTED\n");
    // initializing the game grid
    char grid[6][6] = {"1|2|3", "_ _ _", "4|5|6", "_ _ _", "7|8|9"};
    // printing the grid using the printGrid function
    printGrid(grid);
    // creating 2 counters one for each player, they will help if any user entered an invalid input or the game ended with tie.
    int countplayer1 = 0;
    int countplayer2 = 0;

    // game logic
    while(1) {
        // re initializing the global variable position flag.
        positionFlag = 1;

        // checking for tie.
        if(countplayer1 == 5 && countplayer2 == 4){
            printf("GAME ENDED\n");
            printf("It is a tie!\n");
            break;
        }
        // This if statement will be true unless player 2 entered an invalid input. it helps such that it skips the player 1 turn to go player 2 to enter a valid input.
        if((countplayer2 + 1) != countplayer1) {
            // taking the movement number from player 1.
            printf("type the movement number for player 1\n");
            char move1;
            scanf(" %c", &move1);
            // using the updateGame function to set the player 1 move
            updateGame(move1, player1, grid);
            // // the updateGame function will skip the movement and will change the position flag value to zero if the player chose invalid place.
            if (positionFlag) {
                printf("Invalid place, please select an empty place!\n");
                printGrid(grid);
                // the continue keyword will skip th rest of the while loop code and restart from the beginning of the loop.
                continue;
            }
            printGrid(grid);
            countplayer1++;
            // checking whether player 1 has won the game or not using endedGame function.
            bool checkGame_p1 =gameEnded(grid);
            if(checkGame_p1){
                printf("GAME ENDED\n");
                printf("Player1 won!\n");
                break;}
        }
        // reinitializing the position flag to start the second player turn
        positionFlag = 1;
        // the code for player 2
        printf("type the movement number for player 2\n");
        char move2;
        scanf(" %c", &move2);

        updateGame(move2, player2, grid);
        if (positionFlag) {
            printf("Invalid place, please select an empty place!\n");
            printGrid(grid);
            continue;
        }
        printGrid(grid);
        countplayer2++;
        bool checkGame =gameEnded(grid);
        if(checkGame){
            printf("Player2 won!\n");
            printf("GAME ENDED\n");
            break;}


    }
}
// printing the grid of the game
void printGrid(char grid [6][6]){

    for(int row = 0; row<5; row++) {
        printf("%s\n", grid[row]);
    }
}
// updating the game after each player turn
void updateGame(char move,char player, char g [6][6]){
    for(int j= 0;j<6;j++){
        for(int i = 0;i<6;i++){
            // checking whether this place is taken or available
            if (move == g[i][j] && (g[i][j] != 'X' ||g[i][j] != 'O') ){
                g[i][j] = player;
                positionFlag = 0;
            }
        }
    }
}

// stating the conditions such that the game ends with one of the two players win.
bool gameEnded(char grid[6][6]){
 //  x x x  *3
 //______________
 //  x
 //  x  *3
 //  x
/* _______________
      x    x
        x
      x    x
   ______________

*/
    bool winFlag = 0;

        for(int i = 0;  i<6; i = i+2)
            if(     // if there where three horizontal 'X's or 'O's.
                    (grid[i][0] == grid[i][2] && grid[i][0] ==grid[i][4]) ||
                    // if there where three vertical 'X's or 'O's.
                    (grid[0][i] == grid[2][i] && grid[0][i] == grid[4][i])||
                    // if there where three 'X's or 'O's on the main diagonal axis.
                    (grid[0][0] == grid[2][2] && grid[0][0] == grid[4][4]) ||
                    // if there where three 'X's or 'O's on the other diagonal axis.
                    (grid[0][4] == grid[2][2] && grid[0][4] == grid[4][0])

            )    winFlag =1;

    return winFlag;
}
