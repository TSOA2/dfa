#include <stdio.h>
#include <stdlib.h>


typedef size_t state;

void usage(char *prg_name)
{
    fprintf(stderr,
        "usage: %s [text_for_dfa]\n",
        prg_name
    );

    exit(EXIT_FAILURE);
}

int state_in(state needle, state *stack, size_t stack_size)
{
    for (size_t i = 0; i < stack_size; i++) {
        if (stack[i] == needle) {
            return 1;
        }
    }

    return 0;
}

int run_dfa(char *buf, state start_state, state (*trans)(char, state), state *accept, size_t accept_size)
{
    state current_state = start_state;
    while (*buf != '\0') {
        current_state = trans(*buf++, current_state);
    }

    return state_in(current_state, accept, accept_size);
}

state example_dfa(char c, state s)
{
    if (s == 0) {
        if (c == '0') {
            return 1;
        } else if (c == '1') {
            return 0;
        }
    } else if (s == 1) {
        if (c == '0') {
            return 0;
        } else if (c == '1') {
            return 1;
        }
    }

    return 1;
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        usage(argv[0]);
    }

    state accept_state = 0;
    int dfa_output = run_dfa(argv[1], 0, example_dfa, &accept_state, 1);

    printf("Input %s contain even number of 0's\n", dfa_output ? "does" : "doesn't");
}
