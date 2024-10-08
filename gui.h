#ifndef gui_H
#define gui_H

#define OGL_GUI_VERSION		1
#define OGL_GUI_SUBVERSION	0

#include <iostream>
#include <vector>
#include <math.h>
#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>

#define PI		3.14159265359
#define PI180	3.14159265359/180

using namespace std;

/*typedef struct ControlHandle
{
	void *p;	//Pointer to control object
	void *t;	//Type of provided control
} ControlHandle;*/

//-----------------------------------------------
// Base control class
//-----------------------------------------------
typedef class Control
{
public:
	//Positioning
	float x,y,z;
	//Size: width, height and border
	float w,h,b;
	//Render control
	bool visible;
	int state;
	GLuint font;
	//Mouse control
	bool mleft,mmiddle,mright;
	//Text
	char *text;
} Control;


//-----------------------------------------------
// STATIC
//-----------------------------------------------
typedef class Static : public Control
{
public:
	//Main functions
	Static(void);
	Static(float xpos, float ypos, float zpos, float width, float height, bool vis, const char *txt);
	void SetText(const char *txt);
	void SetFloat(float value);
	void SetFloat(const char* fmt, float value);
	void Render(void);

	//Events
	int LDown(float xpos, float ypos);
	int LUp(float xpos, float ypos);
	int Over(float xpos, float ypos, bool lmb);
} Static;


//-----------------------------------------------
// BUTTON
//-----------------------------------------------
typedef class Button : public Control
{
public:
	//Main functions
	Button(void);
	Button(float xpos, float ypos, float zpos, float width, float height, bool vis, const char *txt);
	void SetText(const char *txt);
	void Render(void);

	//Events
	int LDown(float xpos, float ypos);
	int LUp(float xpos, float ypos);
	int Over(float xpos, float ypos, bool lmb);
} Button;


//-----------------------------------------------
// FRAME
//-----------------------------------------------
typedef class Frame : public Control
{
public:
	float x,x0,xi,xf,xd;
	float y,y0,yi,yf,yd;
	float hw;
	float hh;
	float b;
	bool movable;

	//Child elements pointers
	//vector<Static*> child_statics;
	//vector<Button*> child_buttons;
	vector<void*> child_controls;

	//Main functions
	Frame(void);
	Frame(float xpos, float ypos, float zpos, float width, float height, bool vis, const char *txt);
	void SetText(const char *txt);
	void AddControl(void *_pcontrol);
	void Show(bool _b);
	void Render(void);

	//Events
	int LDown(float xpos, float ypos);
	int LUp(float xpos, float ypos);
	int Over(float xpos, float ypos, bool lmb);
} Frame;


//-----------------------------------------------
// EDIT
//-----------------------------------------------
typedef class Edit : public Control
{
public:
	//Main functions
	Edit(void);
	Edit(float xpos, float ypos, float zpos, float width, float height, bool vis, const char *txt);
	void SetText(const char *txt);
	void Render(void);

	//Events
	int LDown(float xpos, float ypos);
	int LUp(float xpos, float ypos);
	int Over(float xpos, float ypos, bool lmb);
} Edit;


//-----------------------------------------------
// CHECKBOX
//-----------------------------------------------
typedef class CheckBox : public Control
{
public:
	//Main functions
	CheckBox(void);
	CheckBox(float xpos, float ypos, float zpos, float width, float height, bool vis, const char *txt);
	void SetText(const char *txt);
	void Render(void);

	//Events
	int LDown(float xpos, float ypos);
	int LUp(float xpos, float ypos);
	int Over(float xpos, float ypos, bool lmb);
} CheckBox;


//-----------------------------------------------
// EDITNUMBER
//-----------------------------------------------
typedef class EditNumber : public Control
{
public:
	//Draw control
	int lstate;
	int rstate;

	//Mouse buttons
	bool mleft,mleftl,mleftr;

	//Text
	char rtext[64];

	//Numeric configuration
	int value;
	int min;
	int max;
	int step;

	//Main functions
	EditNumber(void);
	EditNumber(float xpos, float ypos, float zpos, float width, float height, bool vis, int val);
	void SetText(const char *txt);
	void Render(void);

	//Events
	int LDown(float xpos, float ypos);
	int LUp(float xpos, float ypos);
	int Over(float xpos, float ypos, bool lmb);
private:
} EditNumber;

typedef class EditNumberF : public Control
{
public:
	//Draw control
	int lstate;
	int rstate;

	//Mouse buttons
	bool mleft,mleftl,mleftr;

	//Text
	char rtext[64];

	//Numeric configuration
	float value;
	float min;
	float max;
	float step;

	//Main functions
	EditNumberF(void);
	EditNumberF(float xpos, float ypos, float zpos, float width, float height, bool vis, float val, float _min, float _max, float _step);
	void SetText(const char *txt);
	void Render(void);

	//Events
	int LDown(float xpos, float ypos);
	int LUp(float xpos, float ypos);
	int Over(float xpos, float ypos, bool lmb);
private:
} EditNumberF;


//-----------------------------------------------
// SLIDER
//-----------------------------------------------
typedef class Slider : public Control
{
private:
	//sizes
	float x0,y0,z0;
	float px,py,pz,pw,ph,vw;

public:
	//Values
	int value,minv,maxv,step;

	//Main functions
	Slider(void);
	Slider(float xpos, float ypos, float zpos, float width, float height, bool vis, int _val, int _min, int _max, int _step);
	void SetText(const char *txt);
	void Render(void);

	//Events
	int LDown(float xpos, float ypos);
	int LUp(float xpos, float ypos);
	int Over(float xpos, float ypos, bool lmb);
} Slider;

typedef class Wheel : public Control
{
public:
	//Values
	float x0;
	float value,minv,maxv,step;
	float delta;

	//Main functions
	Wheel(void);
	Wheel(float xpos, float ypos, float zpos, float width, float height, bool vis, float _val, float _min, float _max, float _step);
	void SetText(const char *txt);
	void Render(void);

	//Events
	int LDown(float xpos, float ypos);
	int LUp(float xpos, float ypos);
	int Over(float xpos, float ypos, bool lmb);
} Wheel;

typedef class Tabs :  public Control
{
public:
	//Tabs
	vector<char*> TabNames;
	vector<vector<void*>> TabFrameControls;
	int current_tab;
	int mousein;
	//Tab drawing control
	float twidth,theight;

	//Main functions
	Tabs(void);
	Tabs(float xpos, float ypos, float zpos, float width, float height, bool vis, int numtabs);
	void AddTab(const char* tname);
	void AddTabControl(int tab,void *control);
	void SetTabName(int tpos, const char* tname);
	void ShowTabControls(void);
	void Render(void);
	
	//Events
	int LDown(float xpos, float ypos);
	int LUp(float xpos, float ypos);
	int Over(float xpos, float ypos, bool lmb);
} TabsFrame;

typedef class Table : public Control
{
} Table;

typedef class View : public Control
{
} View;

#endif