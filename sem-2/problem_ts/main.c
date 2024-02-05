#include <stdio.h>

struct point_t {
  int x, y;
};

struct triangle_t {
  struct point_t pts[3];
};

int double_area(struct triangle_t tr) {
    int d1 = (tr.pts[0].x - tr.pts[2].x) * (tr.pts[1].y - tr.pts[2].y);
    int d2 = (tr.pts[1].x - tr.pts[2].x) * (tr.pts[0].y - tr.pts[2].y);
    int sum = d1 - d2;
    return (sum >= 0) ? sum : -sum;
}


int main() {
    struct point_t p1 = {-1, -1};
    struct point_t p2 = {2, -3};
    struct point_t p3 = {3, -2};
    struct triangle_t tr;
    tr.pts[0] = p1;
    tr.pts[1] = p2;
    tr.pts[2] = p3;
    
    printf("%d\n", double_area(tr));
}