#include <stdio.h>

typedef enum { false, true } bool; // allow for use of booleans

// Initialize 2D game board with single space strings
const char * board[3][3] = {
    {" ", " ", " "},
    {" ", " ", " "},
    {" ", " ", " "}
};

// Return the value of a single game board space as a string
const char * get_board_value(char x, int y)
{
    int row = 0; // need to convert A/B/C to 0/1/2
    int col = y - 1; // need to convert 1/2/3 to 0/1/2

    if (x == 'B')
    {
        row = 1;
    } else if (x == 'C')
    {
        row = 2;
    }

    return board[row][col];
}

// Record a player move
// Return false if the move is invalid
// Return true if the move is valid and successfully recorded
bool record_player_move(char x, int y, const char * player_symbol)
{
    int row = 0; // need to convert A/B/C to 0/1/2
    int col = y - 1; // need to convert 1/2/3 to 0/1/2

    if (x == 'B')
    {
        row = 1;
    } else if (x == 'C')
    {
        row = 2;
    }

    if (board[row][col] != " ")
    {
        return false;
    }

    board[row][col] = player_symbol;

    return true;
}

// Get the winner of the game
// Work in progress...not fully functional yet..
const char * get_winner()
{
    int i, j;
    const char * current;
    const char * winner = "\0";

    // iterate over rows
    for (i = 0; i < 3; i++)
    {
        current = board[i][0];
        for (j = 0; j < 3; j++)
        {
            if (board[i][j] != current || board[i][j] == " ")
            {
                current = "\0";
            }
        }

        if (current != "\0")
        {
            winner = current;
        }
    }

    // iterate over columns
    for (i = 0; i < 3; i++)
    {
        current = board[0][i];
        for (j = 0; j < 3; j++)
        {
            if (board[j][i] != current || board[i][j] == " ")
            {
                current = "\0";
            }
        }

        if (current != "\0")
        {
            winner = current;
        }
    }

    // iterate over diagonals
    current = board[0][0];
    for (i = 0; i < 3; i++)
    {
        if (board[i][i] != current || board[i][j] == " ")
        {
            current = "\0";
        }
    }

    if (current != "\0")
    {
        winner = current;
    }

    current = board[0][4];
    for (i = 0; i < 3; i++)
    {
        if (board[i][3 - i] != current || board[i][j] == " ")
        {
            current = "\0";
        }
    }

    if (current != "\0")
    {
        winner = current;
    }

    if (winner != " ")
    {
        return winner;
    }

    return "No winner yet";
}

// Output the game board to the console
// Warning: this is ugly
void display_game_board()
{
    printf("   1 | 2 | 3\r\n");
    printf("-+---+---+---\r\n");
    printf("A| ");
    printf(get_board_value('A', 1));
    printf(" | ");
    printf(get_board_value('A', 2));
    printf(" | ");
    printf(get_board_value('A', 3));
    printf("\r\n");
    printf("-+---+---+---\r\n");
    printf("B| ");
    printf(get_board_value('B', 1));
    printf(" | ");
    printf(get_board_value('B', 2));
    printf(" | ");
    printf(get_board_value('B', 3));
    printf("\r\n");
    printf("-+---+---+---\r\n");
    printf("C| ");
    printf(get_board_value('C', 1));
    printf(" | ");
    printf(get_board_value('C', 2));
    printf(" | ");
    printf(get_board_value('C', 3));
    printf("\r\n");
}

int main()
{
    display_game_board();

    printf("\r\n");
    printf("Recording player X move in space A1\r\n\r\n");

    record_player_move('A', 1, "X");

    display_game_board();

    printf("\r\n");
    printf("Recording player X move in space B2\r\n\r\n");

    record_player_move('B', 2, "X");

    display_game_board();

    printf("\r\n");
    printf("Recording player X move in space C3\r\n\r\n");

    record_player_move('C', 3, "X");

    display_game_board();

    printf("\r\n");
    printf(get_winner());
    printf(" is the winner!\r\n");

    return 0;
}
