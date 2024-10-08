#ifndef main_H
#define main_H

#include "gui.h"

typedef unsigned char uchar;
typedef unsigned int uint;

#define IDC_GRX_OPENGL 600
#define IDC_GRX_TIMER 608

HWND GraphicsOpengl;
HDC hdc;
HGLRC hrc;
int PixelFormat;

GLuint base;
char glinfo[256];
bool mleft = false;

Button mybutton;
Button mybutton2;
Button mybutton3;
Button mybutton4;
Frame myframe1;
Button framebutton1;
Edit myedit1;
Static mystatic1;
Static mystatic2;
Static mystatic3;
CheckBox mycheckbox1;
CheckBox mycheckbox2;
EditNumber mynumber1;
Slider mysliders[5];
EditNumberF myfloat1;
Wheel mywheel1;
Wheel mywheel2;
Tabs mytabs1;
Button tab1button1;
Button tab2button1;
Button tab3button1;
Static tab4statics[5];
Wheel tab4wheels[5];

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine,
                   int nShowCmd);
LRESULT CALLBACK WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
void CreateGraphicsPanel(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
void OpenglDraw(void);
GLvoid glPrint(float x, float y, float z, const char *fmt, ...);

/*typedef class CoreControl
{
public:
        int value;
        CoreControl(void){
                value = 0;
        }
} CoreControl;

typedef class DerivedControl : public CoreControl
{
public:
        DerivedControl(void){
                value = 1;
        }
} DerivedControl;


DerivedControl mycontrol;*/
#endif
