# Unicodedisplay
A unicode character based method of displaying pixels in the console, for C.

## How to add to your project
Simply include the "unicodedisplay.h" header file into your project.

## How to use
So here is a quick overview:
> ```c create_display(int width, int height) ```

Allocates memory for a buffer. Returns a ```c display* ```
The display struct contains it's width, height and an unsigned char buffer.
The values can be modified to be set to either 1 or 0. Other values won't be appreciated...


> ```c free_display(display* display_ptr) ```

Free memory and delete the display 'object'.


> ```c set_pixel(display* display_ptr, int x, int y, unsigned char state) ```

Set a single 'pixel' on the display buffer to a state (either 1 or 0).


> ```c set_rect(display* display_ptr, int x, int y, int width, int height, unsigned char state) ```

Set a rectangle from the top left down to the bottom right to a state.


> ```c set_line(display* display_ptr, int x1, int y1, int x2, int y2, unsigned char state) ```

Set a line to a state.


> ```c set_section(display* dst, int x_offset, int y_offset, display* src) ```

Set values from the src display into the dst display with an offset.


> ```c merge_display(display* dst, display* src) ```

Merge two displays together using bitwise OR operation


> ```c print_display(display* display_ptr, int no_clear) ```

Prints the display using ```c wprintf()``` for unicode.
When ```c no_clear == 1 ``` the function won't use ```system("clear")```


> ```c print_buffer(display*) ```
Prints the buffer in 1s and 0s.

(*I decided not to make a seperate code and seperate header file due to the simplicity of the code.*)
