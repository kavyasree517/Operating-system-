#define _DEFAULT_SOURCE
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <setjmp.h>

typedef struct { int seg_id; const char *name; unsigned base; unsigned limit; const char *perms; } seg_entry_t;

static const seg_entry_t seg_table[4] = {
    {0, "Code (.text)",   4096, 2500, "R-X"},
    {1, "Data (.data)",   8192, 1200, "RW-"},
    {2, "Heap (dynamic)",12288, 3000, "RW-"},
    {3, "Stack (frames)",20480, 2048, "RW-"}
};

int main(void) {
    struct { int s; unsigned d; char op; } queries[8] = {
        {0, 0, 'X'}, {0, 1850, 'R'}, {0, 2500, 'R'}, {0, 500, 'W'},
        {1, 900, 'W'}, {2, 2999, 'W'}, {3, 2200, 'R'}, {4, 100, 'R'}
    };
    for (int i = 0; i < 8; i++) {
        int s = queries[i].s; unsigned d = queries[i].d; char op = queries[i].op;
        if (s < 0 || s >= 4) printf("Q%d: TRAP Invalid Segment %d\n", i+1, s);
        else if (d >= seg_table[s].limit) printf("Q%d: TRAP Limit Violation (d=%u >= %u)\n", i+1, d, seg_table[s].limit);
        else if (op == 'W' && seg_table[s].perms[1] != 'W') printf("Q%d: TRAP Protection Fault (Write on %s)\n", i+1, seg_table[s].perms);
        else printf("Q%d: VALID Physical = %u [%s]\n", i+1, seg_table[s].base + d, seg_table[s].name);
    }
    return 0;
}
