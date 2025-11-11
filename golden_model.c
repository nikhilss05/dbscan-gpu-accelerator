#include <stdio.h>
#include <math.h>

typedef struct {
    float x;
    float y;
} Point;

#define eps2  0.36f 
#define minpt 3     
#define numpt 6

float calc_dist_squ(Point p1, Point p2) {
    float dx = p1.x - p2.x;
    float dy = p1.y - p2.y;
    
    return (dx * dx) + (dy * dy);
}

int main() {
    Point data[numpt] = { 
        {1.0f, 1.0f},
        {1.5f, 1.0f},
        {1.0f, 1.5f},
        {5.0f, 5.0f},
        {5.5f, 5.5f},
        {10.0f, 10.0f}
    };
    printf("--- DBSCAN Golden Model: D^2 and Neighbor Count ---\n");
    printf("Parameters: eps^2 = %.2f, MinPts = %d \n\n", eps2, minpt); 
    for (int i = 0; i < numpt; i++) {
        int neighbour = 0; 
        printf("--- Analyzing P%d (%.1f, %.1f) ---\n", i, data[i].x, data[i].y);
        for (int j = 0; j < numpt; j++) { 
            
            if (i == j) continue;

            float dist_sq = calc_dist_squ(data[i], data[j]);

            if (dist_sq <= eps2) { 
                neighbour++; 
                printf("  -> P%d (%.1f, %.1f): D^2 = %.2f (Neighbor)\n", j, data[j].x, data[j].y, dist_sq);
            } else {
                printf("  -> P%d (%.1f, %.1f): D^2 = %.2f (Too Far)\n", j, data[j].x, data[j].y, dist_sq);
            }
        }
        printf("P%d Final Neighbor Count: %d\n", i, neighbour);
        if (neighbour >= minpt) { 
            printf("P%d is a **CORE POINT**\n\n", i);
        } else {
            printf("P%d is NOT a Core Point (Noise or Border)\n\n", i);
        }
    } 

    return 0;
}
