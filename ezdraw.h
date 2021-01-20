#ifndef EZ_DRAW_H
#define EZ_DRAW_H

#include <SDL2/SDL.h>

typedef SDL_Point EZ_Point;
typedef SDL_Rect EZ_Rect;
typedef SDL_Color EZ_Color;
typedef SDL_Surface EZ_Image;

void EZ_SetColor(unsigned char r, unsigned char g, unsigned char b);
void EZ_SetColorRGBA(unsigned char r, unsigned char g, unsigned char b,
                     unsigned char a);

void EZ_SetBackColor(unsigned char r, unsigned char g, unsigned char b);
void EZ_SetBackColorRGBA(unsigned char r, unsigned char g, unsigned char b,
                         unsigned char a);

void EZ_DrawPoint(int x, int y);

void EZ_DrawLine(int x0, int y0, int x1, int y1);
void EZ_DrawLineStrip(EZ_Point *points, int npoints);
void EZ_DrawLineLoop(EZ_Point *points, int npoints);

void EZ_FillRect(int xll, int yll, int w, int h);
void EZ_FillRects(EZ_Rect *rects, int nrects);
void EZ_OutlineRect(int xll, int yll, int w, int h);
void EZ_OutlineRects(EZ_Rect *rects, int nrects);

void EZ_FillTriangle(EZ_Point p0, EZ_Point p1, EZ_Point p2);
void EZ_OutlineTriangle(EZ_Point p0, EZ_Point p1, EZ_Point p2);

void EZ_FillCircle(int cx, int cy, int radius);
void EZ_OutlineCircle(int cx, int cy, int radius);

EZ_Image *EZ_CreateBlankImage(int width, int height);
EZ_Image *EZ_LoadBMPImage(const char *bmpfilename);

int EZ_CreateTexture(EZ_Image *image);
void EZ_DestroyTexture(int texture);
void EZ_DrawTexture(int texture, EZ_Rect *texture_rect, EZ_Rect *drawing_rect);

// start up SDL. Returns non-zero if failure
int EZ_Init(int width, int height, const char *title);

void EZ_ClearDrawing();
void EZ_DisplayDrawing();

void EZ_WaitForQuit();

int EZ_HandleEvents(void (*updateDisplay)(),
                    void (*handleKey)(unsigned char),
                    void (*handleButton)(int, int, int),
                    void (*handleMouseMotion)(int, int, int, int));

void EZ_Quit();

#endif
