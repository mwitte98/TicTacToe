#include "gpio.h"
#include "uart.h"
#include "tic_tac_toe.h"

int main()
{
    // Init GPIO select for external LED
    gpio[GPFSEL1] = 0x40000;
    gpio[GPFSEL2] = 0x1000;

    // Initialize uart
    init_uart();

    // Initialize the buffer
    const int buffer_size = 50;
    char buffer [buffer_size];

    put_string("Welcome to Tic-Tac-Toe!\r\n");
    put_string("Enter a grid space (A1, A2, A3, B1, B2, B3, C1, C2, C3) to play\r\n\r\n");

    char first_move = 'X';
    bool wants_to_play = true;

    int x_wins = 0;
    int o_wins = 0;
    int ties = 0;

    while (wants_to_play)
    {
        char winner = play_game(first_move);

        // Game stats
        if (winner == 'X')
        {
            x_wins++;
        } else if (winner == 'O')
        {
            o_wins++;
        } else
        {
            ties++;
        }
        put_string("X wins: ");
        put_char(x_wins | 0x30);
        put_string("\r\nO wins: ");
        put_char(o_wins | 0x30);
        put_string("\r\nTies: ");
        put_char(ties | 0x30);
        put_string("\r\n\r\n");

        // Change who goes first in the next game
        first_move = first_move == 'X' ? 'O' : 'X';

        // Prompt users for another game
        put_string("Do you want to play another game? [YN]: ");
        size_t chars_got = get_string(buffer, buffer_size);
        put_string("\r\n\r\n");
        if (chars_got < 1 || (buffer[0] != 'Y' && buffer[0] != 'y'))
        {
            wants_to_play = false;
            put_string("Thanks for playing!");
        }
    }
    
    return 0;
}
