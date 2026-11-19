#include <stdio.h>
#include <math.h>

int main(void) {
    const int n = 6; const double c = 4.0; const double p = 0.001;
    printf("RAID 0 : %.1f TB | 0 failures\n", n * c);
    printf("RAID 1 : %.1f TB | 1/pair | P_loss=%.6f\n", (n / 2) * c, p);
    printf("RAID 5 : %.1f TB | 1 disk | P_loss=%.6f\n", (n - 1) * c, 1.0 - pow(1.0 - p, n - 1));
    printf("RAID 6 : %.1f TB | 2 disks| P_loss=%.8f\n", (n - 2) * c, 10.0 * p * p);
    printf("RAID 10: %.1f TB | 1/pair | P_loss=%.6f (RECOMMENDED)\n", (n / 2) * c, p);
    return 0;
}
