#include <stdio.h>
#include <math.h>

int main(void) {
    const double usable_tb = 100.0, p_fail = 0.01;
    printf("Single NFS      : Raw=%.1f TB | Unavail=%.4f%%\n", usable_tb, p_fail * 100.0);
    printf("Distributed 3x  : Raw=%.1f TB | Unavail=%.6f%%\n", usable_tb * 3.0, pow(p_fail, 3) * 100.0);
    printf("Erasure EC (4+2): Raw=%.1f TB | Unavail=%.6f%%\n", usable_tb * 1.5, 15.0 * pow(p_fail, 3) * 100.0);
    return 0;
}
