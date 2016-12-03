#include "tic_tac_toe.h"
#include "uart.h"

// Initialize 2D game board with single space strings
char board[3][3];

// Return the value of a single game board space as a string
char get_board_value(char x, int y)
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
// ***After casting input column from char to int, the int is
// always > 2 so y has to be explicitly checked for values
bool record_player_move(char x, char y, char player_symbol)
{
    int row; // need to convert A/B/C to 0/1/2
    int col; // need to convert 1/2/3 to 0/1/2

    if (x == 'A' || x == 'a')
    {
        row = 0;
    } else if (x == 'B' || x == 'b')
    {
        row = 1;
    } else if (x == 'C' || x == 'c')
    {
        row = 2;
    } else
    {
        row = -1;
    }

    if (y == '1')
    {
        col = 0;
    } else if (y == '2')
    {
        col = 1;
    } else if (y == '3')
    {
        col = 2;
    } else
    {
        col = -1;
    }

    // out of bounds
    if (row < 0 || col < 0 ) return false;

    // grid square already filled in
    if (board[row][col] != ' ') return false;

    board[row][col] = player_symbol;

    return true;
}

// Get the winner of the game
char get_winner()
{
    int i, j;
    char current;

    // iterate over rows
    for (i = 0; i < 3; i++)
    {
        current = board[i][0];
        for (j = 0; j < 3; j++)
        {
            if (board[i][j] != current)
            {
                current = '$';
            }
        }

        if (current != '$' && current != ' ') return current;
    }

    // iterate over columns
    for (i = 0; i < 3; i++)
    {
        current = board[0][i];
        for (j = 0; j < 3; j++)
        {
            if (board[j][i] != current)
            {
                current = '$';
            }
        }

        if (current != '$' && current != ' ') return current;
    }

    // iterate over diagonals
    current = board[0][0];
    for (i = 0; i < 3; i++)
    {
        if (board[i][i] != current)
        {
            current = '$';
        }
    }

    if (current != '$' && current != ' ') return current;

    current = board[0][2];
    for (i = 0; i < 3; i++)
    {
        if (board[i][2 - i] != current || board[i][2 - i] == ' ')
        {
            current = '$';
        }
    }

    if (current != '$' && current != ' ') return current;

    return '$';
}

// Returns true if every space of the game board is full
// Returns false otherwise
bool is_game_board_full()
{
    int i, j;

    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            if (board[i][j] == ' ') return false;
        }
    }

    return true;
}

// Output the game board to the console
// Warning: this is ugly
void display_game_board()
{
    put_string("   1 | 2 | 3\r\n");
    put_string("-+---+---+---\r\n");
    put_string("A| ");
    put_char(get_board_value('A', 1));
    put_string(" | ");
    put_char(get_board_value('A', 2));
    put_string(" | ");
    put_char(get_board_value('A', 3));
    put_string("\r\n");
    put_string("-+---+---+---\r\n");
    put_string("B| ");
    put_char(get_board_value('B', 1));
    put_string(" | ");
    put_char(get_board_value('B', 2));
    put_string(" | ");
    put_char(get_board_value('B', 3));
    put_string("\r\n");
    put_string("-+---+---+---\r\n");
    put_string("C| ");
    put_char(get_board_value('C', 1));
    put_string(" | ");
    put_char(get_board_value('C', 2));
    put_string(" | ");
    put_char(get_board_value('C', 3));
    put_string("\r\n\r\n");
}

char play_game(char first_player)
{
    // Initialize the buffer
    const int buffer_size = 50;
    char buffer [buffer_size];

    char active_player = first_player;

    // Initialize/reset game board
    for (int x = 0; x < 3; x++)
    {
        for (int y = 0; y < 3; y++)
        {
            board[x][y] = ' ';
        }
    }

    display_game_board();

    // Keep playing until a result
    while (1)
    {
        // Ask user for input and get what they enter
        put_string("Player ");
        put_char(active_player);
        put_string(" enter your move: ");
        size_t chars_got = get_string(buffer, buffer_size);
        put_string("\r\n");

        // Move is invalid if it's not 2 characters
        if (chars_got != 2)
        {
            put_string("Invalid move!\r\n");
            continue;
        }

        // Validate/record move
        if (!record_player_move(buffer[0], buffer[1], active_player))
        {
            put_string("Invalid move!\r\n");
            continue;
        }

        display_game_board();

        // Check for a winner ($ means no winner)
        char winner = get_winner();

        // End game if a player has won
        // Switch active player if no winner
        if (winner != '$')
        {
            put_string("Player ");
            put_char(winner);
            put_string(" is the winner!\r\n");
            return winner;
        } else if (is_game_board_full()) {
            put_string("Game has ended in a tie!\r\n");
            return '$';
        }

        active_player = active_player == 'X' ? 'O' : 'X';
    }

    // TODO: LED lights
}
