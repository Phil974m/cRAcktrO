
#include <GL/glut.h>

enum {
    SCROLL_LEFT = 1,
    SCROLL_RIGHT,
    SCROLL_UP,
    SCROLL_DOWN
} type = SCROLL_RIGHT;


typedef struct _star {
    float x, y;
    float vx, vy;
} star;
