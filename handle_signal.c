#include "main.h"

/**
 * handle_signal - Handle the crtl + c call in prompt
 * @sig: Signal handler
 */
void handle_signal(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n#(Simple Shell)$$ ", 19);
}
