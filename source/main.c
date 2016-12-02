#include "gpio.h"
#include "system_timer.h"
#include "uart.h"

void blink_once()
{
    // Turn on GPIO 24
    gpio[GPSET0] |= 1 << 24;

    timer_delay_ms(500);

    // Turn off GPIO 24
    gpio[GPCLR0] |= 1 << 24;

    timer_delay_ms(500);
}

void blink_code(uint32_t err)
{
    for(int i = 0; i < err; ++i)
    {
        blink_once();
    }

    // Only delay 4 seconds, since we delay for 1 additional
    // second in blink_once().
    timer_delay_ms(4500);
}

/*
 * Outputs the game board which looks like this:
 *    1 | 2 | 3
 * -+---+---+---
 * A| X | O | X
 * -+---+---+---
 * B| O | X | O
 * -+---+---+---
 * C| X | O | X
 */
void display_game_board()
{
    put_string("   1 | 2 | 3\r\n");
    put_string("-+---+---+---\r\n");
    put_string("A| X | O | X\r\n");
    put_string("-+---+---+---\r\n");
    put_string("B| O | X | O\r\n");
    put_string("-+---+---+---\r\n");
    put_string("C| X | O | X\r\n");
}

int main()
{
    // Initialize uart
    init_uart();

    display_game_board();
    
    return 0;
}
