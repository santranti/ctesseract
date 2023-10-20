#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>

double A = 0, B = 0, C = 0, D = 0;
char b[1760];
double z[1760];

void sleep_ms(int milliseconds) {
    struct timespec ts;
    ts.tv_sec = milliseconds / 1000;
    ts.tv_nsec = (milliseconds % 1000) * 1000000;
    nanosleep(&ts, NULL);
}

int main() {
    printf("\x1b[H");
    
    int edges[32][2] = {
        {0, 1}, {1, 3}, {3, 2}, {2, 0},
        {4, 5}, {5, 7}, {7, 6}, {6, 4},
        {0, 4}, {1, 5}, {3, 7}, {2, 6},
        {8, 9}, {9, 11}, {11, 10}, {10, 8},
        {12, 13}, {13, 15}, {15, 14}, {14, 12},
        {8, 12}, {9, 13}, {11, 15}, {10, 14},
        {0, 8}, {1, 9}, {3, 11}, {2, 10},
        {4, 12}, {5, 13}, {7, 15}, {6, 14}
    };

    for (;;) {
        memset(b, 32, 1760);
        memset(z, 0, 7040);

        for (int e = 0; e < 32; e++) {
            double x1 = (edges[e][0] & 1) ? 1 : -1;
            double y1 = (edges[e][0] & 2) ? 1 : -1;
            double z1 = (edges[e][0] & 4) ? 1 : -1;
            double w1 = (edges[e][0] & 8) ? 1 : -1;

            double x2 = (edges[e][1] & 1) ? 1 : -1;
            double y2 = (edges[e][1] & 2) ? 1 : -1;
            double z2 = (edges[e][1] & 4) ? 1 : -1;
            double w2 = (edges[e][1] & 8) ? 1 : -1;

            // 4D rotations
            double t;

            // XY plane
            t = x1; x1 = cos(A) * x1 - sin(A) * y1; y1 = sin(A) * t + cos(A) * y1;
            t = x2; x2 = cos(A) * x2 - sin(A) * y2; y2 = sin(A) * t + cos(A) * y2;

            // ZW plane
            t = z1; z1 = cos(B) * z1 - sin(B) * w1; w1 = sin(B) * t + cos(B) * w1;
            t = z2; z2 = cos(B) * z2 - sin(B) * w2; w2 = sin(B) * t + cos(B) * w2;

            // XW plane
            t = x1; x1 = cos(C) * x1 - sin(C) * w1; w1 = sin(C) * t + cos(C) * w1;
            t = x2; x2 = cos(C) * x2 - sin(C) * w2; w2 = sin(C) * t + cos(C) * w2;

            // YZ plane
            t = y1; y1 = cos(D) * y1 - sin(D) * z1; z1 = sin(D) * t + cos(D) * z1;
            t = y2; y2 = cos(D) * y2 - sin(D) * z2; z2 = sin(D) * t + cos(D) * y2;

            // 3D projection
            double fov = 4.0;
            double scale1 = fov / (z1 + 5);
            double px1 = x1 * scale1;
            double py1 = y1 * scale1;
            
            double scale2 = fov / (z2 + 5);
            double px2 = x2 * scale2;
            double py2 = y2 * scale2;

            // Draw the edge
            double dx = px2 - px1;
            double dy = py2 - py1;
            double dist = sqrt(dx*dx + dy*dy);
            for (double i = 0; i <= dist; i += 0.01) {
                double interp = i / dist;
                int screenX = 40 + 15 * (px1 + dx * interp);
                int screenY = 12 + 8 * (py1 + dy * interp);
                int o = screenX + 80 * screenY;
                if (0 <= o && o < 1760) {
                    b[o] = '.';
                }
            }
        }

        printf("\x1b[H");
        for (int k = 0; k < 1760; k++) {
            putchar(k % 80 > 0 ? b[k] : 10);
        }
        
        A += 0.03;
        B += 0.02;
        C += 0.04;
        D += 0.05;
        sleep_ms(30);
    }

    return 0;
}
