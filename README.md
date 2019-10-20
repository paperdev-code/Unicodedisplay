# Unicodedisplay
A unicode character based method of displaying pixels in the console, for C.

## How to add to your project
Simply include the "unicodedisplay.h" header file into your project.

## How to use
So here is a quick overview:

``` create_display(int width, int height) ```

> Allocates memory for a buffer. Returns a ```display*```
The display struct contains it's width, height and an unsigned char buffer.
The values can be modified to be set to either 1 or 0. Other values won't be appreciated...


``` free_display(display* display_ptr) ```

> Free memory and delete the display 'object'.


``` set_pixel(display* display_ptr, int x, int y, unsigned char state) ```

> Set a single 'pixel' on the display buffer to a state (either 1 or 0).


``` set_rect(display* display_ptr, int x, int y, int width, int height, unsigned char state) ```

> Set a rectangle from the top left down to the bottom right to a state.


``` set_line(display* display_ptr, int x1, int y1, int x2, int y2, unsigned char state) ```

> Set a line to a state.


``` set_section(display* dst, int x_offset, int y_offset, display* src) ```

> Set values from the src display into the dst display with an offset.


``` merge_display(display* dst, display* src) ```

> Merge two displays together using bitwise OR operation


``` print_display(display* display_ptr, int no_clear) ```

> Prints the display using ```wprintf()``` for unicode.
When ```no_clear == 1``` the function won't use ```system("clear")```


```c print_buffer(display*) ```

> Prints the buffer in 1s and 0s.

(*I decided not to make a seperate code and seperate header file due to the simplicity of the code.*)
