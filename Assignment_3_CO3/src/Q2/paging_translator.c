#include <stdio.h>
#ifndef PAGE_SIZE
#define PAGE_SIZE 1024
#endif
#define PAGES 8

int page_table[PAGES] = {5, 2, -1, 7, 0, -1, 3, -1};

int main(void)
{
    unsigned logical[] = {0, 1500, 3100, 6200, 9000, 2049};
    for (int i = 0; i < 6; i++) {
        unsigned a = logical[i];
        unsigned p = a / PAGE_SIZE;
        unsigned d = a % PAGE_SIZE;
        if (p >= PAGES) {
            printf("%4u -> page %u offset %4u : invalid address\n", a, p, d);
        } else if (page_table[p] == -1) {
            printf("%4u -> page %u offset %4u : page fault\n", a, p, d);
        } else {
            unsigned physical = (unsigned)page_table[p] * PAGE_SIZE + d;
            printf("%4u -> page %u offset %4u : physical %u\n", a, p, d, physical);
        }
    }
    return 0;
}
