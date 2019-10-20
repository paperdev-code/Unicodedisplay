#include "./unicodedisplay.h"

#define WIDTH  12
#define HEIGHT 12

int main() {
    /*Creating display buffers*/
    display* canvas = create_display(WIDTH, HEIGHT);
    display* sprite = create_display(10 , 10);

    /*Drawing onto the sprite buffer*/
    set_rect(sprite, 1, 1, 10, 10, 1);
    set_rect(sprite, 2, 2,  8,  8, 0);
    set_line(sprite, 3, 8, 8, 8, 1);
    set_pixel(sprite, 3, 7, 1);
    set_pixel(sprite, 8, 7, 1);
    set_rect(sprite, 3, 3, 2, 2, 1);
    set_rect(sprite, 7, 3, 2, 2, 1);

    /*Drawing the sprite onto the canvas*/
    set_section(canvas, 2, 2, sprite);

    /*Printing and cleaning up*/
    print_display(canvas, 1);
    free_display(canvas);
    free_display(sprite);
    
    return 0;
}
