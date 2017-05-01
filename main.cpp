#include <cmath>
#include <iostream>

#include "proto.h"

enum {
    ICON_NONE = 0,
    ICON_ARROW_UP,
    ICON_ARROW_DOWN,
    ICON_ARROW_LEFT,
    ICON_ARROW_RIGHT,
    ICON_VERTICAL_GRIP,
    ICON_HORIZONTAL_GRIP,
    // large icons
    ICON_FOLDER,
    ICON_FILE,
    ICON_TEXTFILE,
    ICON_AUDIO,
    ICON_PASSWORDS
};

void drawIcon(int icon, float x, float y, int c1, int c2, int c3) {
    fill(c1);
    pushMatrix();
    translate(x, y);
    switch(icon) {
    case ICON_NONE:
	break;
    case ICON_ARROW_UP:
	beginShape();
	vertex(-10, 5);
	vertex(0, -5);
	vertex(10, 5);
	endShape();
	break;
    case ICON_ARROW_DOWN:
	beginShape();
	vertex(-10, -5);
	vertex(0, 5);
	vertex(10, -5);
	endShape();
	break;
    case ICON_ARROW_LEFT:
	beginShape();
	vertex(5, -10);
	vertex(-5, 0);
	vertex(5, 10);
	endShape();
	break;
    case ICON_ARROW_RIGHT:
	beginShape();
	vertex(-5, -10);
	vertex(5, 0);
	vertex(-5, 10);
	endShape();
	break;
    case ICON_VERTICAL_GRIP:
	rect(-10, -10, 20, 2);
	rect(-10, -1, 20, 2);
	rect(-10, 8, 20, 2);
	break;
    case ICON_HORIZONTAL_GRIP:
	rect(-10, -10, 2, 20);
	rect(-1, -10, 2, 20);
	rect(8, -10, 2, 20);
	break;
    case ICON_FOLDER:
	rect(-20, -10, 40, 26);
	beginShape();
	vertex(-20, -10);
	vertex(-20, -14);
	vertex(-6, -14);
	vertex(-2, -10);
	endShape();
	break;
    case ICON_FILE:
	beginShape();
	vertex(-16, -20);
	vertex(-16, 20);
	vertex(16, 20);
	vertex(16, -14);
	vertex(10, -20);
	endShape();
	break;
    case ICON_TEXTFILE: {
	beginShape();
	vertex(-16, -20);
	vertex(-16, 20);
	vertex(16, 20);
	vertex(16, -14);
	vertex(10, -20);
	endShape();
	fill(c2);
	int sizes[6] = {15, 18, 16, 10, 20, 15};
	for(int i = 0; i < 6; i++) {
	    rect(-12, -12 + 4 * i, sizes[i], 2);
	}
	break;
    }
    case ICON_AUDIO: {
	int sizes[14] = {2, 5, 3, 6, 4, 7, 5, 7, 4, 6, 3, 5, 2};
	for(int i = 0; i < 14; i++) {
	    rect(-26 + i * 4, -sizes[i], 2, sizes[i] * 2);
	}
	break;
    }
    case ICON_PASSWORDS:
	strokeCircle(10, 0, 5, 5);
	rect(-20, -3, 25, 6);
	rect(-18, 3, 10, 3);
	break;
    }
    popMatrix();
};

class Element {
public:
    Element() {
    };
    
    ~Element() {
    };
};

Element *hoverElement;

class Button : public Element {
public:
    Button() {
    };

    Button(float _x, float _y, float _w, float _h, int _icon) : x(_x), y(_y), w(_w), h(_h), icon(_icon) {
    };

    ~Button() {
    };

    void draw() {
	float l = 1.0 - pow(0.1, delta * 10.0);
	pressed = false;
	if(hoverElement == this) {
	    if(mouseX > x && mouseY > y && mouseX < x + w && mouseY < y + h) {
		if(mouseIsPressed) {
		    r -= (r - 224) * l;
		    g -= (g - 160) * l;
		    b -= (b - 32) * l;
		    pressed = true;
		} else {
		    r -= (r - 255) * l;
		    g -= (g - 192) * l;
		    b -= (b - 64) * l;
		}
	    } else {
		hoverElement = NULL;
	    }
	}
	if(mouseX > x && mouseY > y && mouseX < x + w && mouseY < y + h) {
	    hoverElement = this;
	} else {
	    r -= (r - 224) * l;
	    g -= (g - 224) * l;
	    b -= (b - 224) * l;
	}
	fill(color(r, g, b, 255));
	rect(x, y, w, h);

	drawIcon(icon, x + (w * 0.5), y + (h * 0.5),
		 color(r * 0.9, g * 0.9, b * 0.9, 255),
		 color(r * 0.8, g * 0.8, b * 0.8, 255),
		 color(r * 0.7, g * 0.7, b * 0.7, 255));
    };

    void set_rect(float _x, float _y, float _w, float _h) {
	x = _x;
	y = _y;
	w = _w;
	h = _h;
    };

    float x, y, w, h;
    float r, g, b;
    int icon;

    bool pressed;
};

class Scrollbar : public Element {
public:
    Scrollbar() {
    };

    Scrollbar(float _x, float _y, bool _vertical, float _size) : x(_x), y(_y), vertical(_vertical), size(_size) {
	buttons[0] = Button(x, y, width, width, vertical ? ICON_ARROW_UP : ICON_ARROW_LEFT);
	buttons[1] = Button(x + (vertical ? 0 : size - width), y + (vertical ? size - width : 0), width, width, vertical ? ICON_ARROW_DOWN : ICON_ARROW_RIGHT);
	buttons[2] = Button(x + (vertical ? 0 : width), y + (vertical ? width : 0), vertical ? width : size - (width * 2) - 100, vertical ? size - (width * 2) - 100 : width, vertical ? ICON_VERTICAL_GRIP : ICON_HORIZONTAL_GRIP);
    };

    ~Scrollbar() {
    };

    void draw() {
	fill(color(192, 192, 192, 255));
	rect(x, y, vertical ? width : size, vertical ? size : width);
	for(int i = 0; i < 3; i++) {
	    buttons[i].draw();
	}

	if(buttons[2].pressed) {
	    if(vertical) {
		buttons[2].y += (mouseY - pmouseY);
	    } else {
		buttons[2].x += (mouseX - pmouseX);
	    }
	}
    };

    const static float width = 30;
    float x;
    float y;
    bool vertical;
    float size;
    Button buttons[3];
};

Button buttons[5];
Scrollbar scrollbar;

void setup() {
    size(1366, 768);
    float margin = 30.0;
    float iconSize = 60.0;
    float w = width - (margin + 30);
    buttons[0] = Button(margin, margin, iconSize, iconSize, ICON_FOLDER);
    buttons[1] = Button(margin * 2 + iconSize, margin, iconSize, iconSize, ICON_FILE);
    buttons[2] = Button(margin * 3 + iconSize * 2, margin, iconSize, iconSize, ICON_TEXTFILE);
    buttons[3] = Button(margin * 4 + iconSize * 3, margin, iconSize, iconSize, ICON_AUDIO);
    buttons[4] = Button(margin * 5 + iconSize * 4, margin, iconSize, iconSize, ICON_PASSWORDS);
    scrollbar = Scrollbar(width - 30, 0, true, height - 30);
};

void rectLine(float x1, float y1, float x2, float y2, float w) {
    float s = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
    pushMatrix();
    translate(x1, y1);
    rotate(atan2(y2 - y1, x2 - x1));
    rect(0, -w, s, w * 2);
    popMatrix();
};

void loading(float x, float y) {
    fill(color(0, 0, 0, 255));
    float rt = 50.0;
    float o = seconds * 3.0;
    for(float i = 0; i < M_PI * 2; i += M_PI / 3) {
	float r = i - o;
	float szr = r - o;
	float sz = (sin(szr)) * 4.0 + 7.0;
	circle(x + cos(r) * rt, y + sin(r) * rt, sz);
    }
};

void draw() {
    background(color(240, 240, 240, 255));
    for(int i = 0; i < 5; i++) {
	buttons[i].draw();
    }
    scrollbar.draw();
};
