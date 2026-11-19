#include <stdio.h>
#include <math.h>

int main(void) {
    const long students = 150000L, window_sec = 7200L;
    const long total_reqs = students * 6L;
    double avg_rps = (double)total_reqs / (double)window_sec;
    double peak_rps = (0.60 * total_reqs) / 900.0;
    double design_rps = peak_rps * 1.25;
    printf("Total Requests (2h): %ld | Avg RPS: %.1f | Peak RPS: %.1f | Design Target: %.1f\n",
           total_reqs, avg_rps, peak_rps, design_rps);
    printf("Required Pods (Redis Cached @ 188.6 rps/pod): %d (+2 N+1 HA = %d Pods)\n",
           (int)ceil(design_rps / 188.6), (int)ceil(design_rps / 188.6) + 2);
    return 0;
}
