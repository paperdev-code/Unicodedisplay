#ifndef UNICODEDISPLAY_H
#define UNICODEDISPLAY_H

#include <math.h>
#include <wchar.h>
#include <locale.h>
#include <stdlib.h>

typedef struct {
    int width, height;
    unsigned char * buffer;
} display;

const wchar_t pixel_type[16] = {
    L' ', /*0000*/
    L'▘', /*0001*/
    L'▝', /*0010*/
    L'▀', /*0011*/
    L'▖', /*0100*/
    L'▌', /*0101*/
    L'▞', /*0110*/
    L'▛', /*0111*/
    L'▗', /*1000*/
    L'▚', /*1001*/
    L'▐', /*1010*/
    L'▜', /*1011*/
    L'▄', /*1100*/
    L'▙', /*1101*/
    L'▟', /*1110*/
    L'█'  /*1111*/
};

display* create_display(int width, int height);
void free_display(display*);

void set_pixel(display*, int x, int y, unsigned char state);
void set_rect(display*, int x, int y, int width, int height, unsigned char state);
void set_line(display*, int x1, int y1, int x2, int y2, unsigned char state);
void set_section(display* dst, int x_offset, int y_offset, display* src);
void print_display(display*, int no_clear);
void print_buffer(display*);
void merge_display(display* dst, display* src);

display* create_display(int width, int height) {
    display* display_ptr;
    display_ptr = (display*)malloc(sizeof(display));
    display_ptr->width = width;
    display_ptr->height = height;
    display_ptr->buffer = (unsigned char*)malloc((size_t)(width * height));
    return display_ptr;
}

void free_display(display* display_ptr) {
    free(display_ptr->buffer);
    free(display_ptr);
}

void set_pixel(display* display_ptr, int x, int y, unsigned char state) {
    int width = display_ptr->width, height = display_ptr->height;
    x--; y--;
    if (x >= 0 && x < width && y >= 0 && y < height) {
        display_ptr->buffer[y * width + x] = state;
    }
}

void set_rect(display* display_ptr, int x, int y, int width, int height, unsigned char state) {
    int _y, _x;
    for(_y = y; _y < height + y; _y++) {
        for(_x = x; _x < width + x; _x++) {
            set_pixel(display_ptr, _x, _y, state);
        }
    }
}

void set_line(display* display_ptr, int x1, int y1, int x2, int y2, unsigned char state) {
   float x, y, dx, dy, step;

    int i;
    dx = (float)(x2 - x1);
    dy = (float)(y2 - y1);
    step = (abs((int)dx) >= abs((int)dy))? (float)abs((int)dx) : (float)abs((int)dy);
    dx = dx / step;
    dy = dy / step;
    x = (float)x1;
    y = (float)y1;
    for(i = 0; i <= step; i++) {
        set_pixel(display_ptr, (int)x, (int)y, state);
        x += dx;
        y += dy;
    }
}

void set_section(display* dst, int x_offset, int y_offset,  display* src) {
    int y, x;
    for (y = 0; y < src->height; y++) {
        for(x = 0; x < src->width; x++) {
            set_pixel(dst, x + x_offset, y + y_offset, src->buffer[y * src->width + x]);
        }
    }
}

void print_display(display* display_ptr, int no_clear) {
    int width = display_ptr->width, height = display_ptr->height;
    int y, x, pixel_index;
    wchar_t pixel;
    if (no_clear == 0) {
        system("clear");
    }
    setlocale(LC_ALL, "");
    for (y = 0; y < height; y += 2) {
        for (x = 0; x < width; x += 2) {
            pixel_index = 0b0000;
            pixel_index |= display_ptr->buffer[y * width + x] * 0b0001;
            pixel_index |= display_ptr->buffer[y * width + (x + 1)] * 0b0010;
            pixel_index |= display_ptr->buffer[(y + 1) * width + x] * 0b0100;
            pixel_index |= display_ptr->buffer[(y + 1) * width + (x + 1)] * 0b1000;
            pixel = pixel_type[pixel_index];
            wprintf(L"%lc",pixel);
        }
        wprintf(L"\n");
    }
}

void print_buffer(display* display_ptr) {
    int width = display_ptr->height;
    int height = display_ptr->width;
    int y, x;
    for(y = 0; y < height; y++) {
        for(x = 0; x < width; x++) {
            wprintf(L"%d",display_ptr->buffer[y * width + x]);
        }
        wprintf(L"\n");
    }
}

void merge_display(display* dst, display* src) {
    int y, x, index;
    for(y = 0; y < dst->height; y++) {
        for(x = 0; x < dst->width; x++) {
            index = y * dst->width + x;
            dst->buffer[index] = (src->buffer[index] || dst->buffer[index]);
        }
    }
}

#endif