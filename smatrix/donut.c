#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

int k;
double A = 0, B = 0, i, j;
double sinA, cosA, sinB, cosB;
double z[1760];
char b[1760];

int main() {
    printf("\x1b[H");
    for (;;) {
        memset(b, 32, 1760);
        memset(z, 0, 7040);
        for (j = 0; 6.28 > j; j += 0.07)
            for (i = 0; 6.28 > i; i += 0.02) {
                double c = sin(i),
                       d = cos(j),
                       e = sin(A),
                       f = sin(j),
                       g = cos(A),
                       h = d + 2,
                       D = 1 / (c * h * e + f * g + 5),
                       l = cos(i),
                       m = cos(B),
                       n = sin(B),
                       t = c * h * g - f * e;
                int x = 40 + 30 * D * (l * h * m - t * n),
                    y = 12 + 15 * D * (l * h * n + t * m),
                    o = x + 80 * y,
                    N = (int)(8 * ((f * e - c * d * g) * m - c * d * e - f * g - l * d * n));
                if (1760 > o && o > 0 && D > z[o]) {
                    z[o] = D;
                    b[o] = ".,-~:;=!*#$@"[N];
                }
            }
        printf("\x1b[H");
        for (k = 0; 1761 > k; k++)
            putchar(k % 80 > 0 ? b[k] : 10);
        A += 0.04;
        B += 0.03;
        usleep(30000);
    }
}
