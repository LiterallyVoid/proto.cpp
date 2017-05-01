#pragma once

extern int width, height;
extern double pmouseX, pmouseY;
extern double mouseX, mouseY;
extern double seconds;
extern double delta;
extern bool mouseIsPressed;

int color(int r, int g, int b, int a);
int red(int c);
int green(int c);
int blue(int c);
int alpha(int c);
void size(int x, int y);
void background(int c);
void fill(int c);
void rect(float x, float y, float w, float h);
void circle(float x, float y, float s);
void strokeCircle(float x, float y, float s, float w);

void beginShape();
void vertex(float x, float y);
void endShape();

void pushMatrix();
void popMatrix();
void translate(float x, float y);
void rotate(float r);
