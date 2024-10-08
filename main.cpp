#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <math.h>
#include <Windowsx.h>
#include <gl/glut.h>
#include "main.h"
#include "gui.h"

#pragma comment(lib,"user32.lib")
#pragma comment(lib,"gdi32.lib")
#pragma comment(lib,"winspool.lib")
#pragma comment(lib,"comdlg32.lib")
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")

#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nShowCmd)
{
	WNDCLASSEX wClass;
	memset(&wClass,0,sizeof(WNDCLASSEX));
	wClass.cbClsExtra=NULL;
	wClass.cbSize=sizeof(WNDCLASSEX);
	wClass.cbWndExtra=NULL;
	wClass.hbrBackground=(HBRUSH)COLOR_WINDOW;
	wClass.hCursor=LoadCursor(NULL,IDC_ARROW);
	wClass.hIcon=NULL;
	wClass.hIconSm=NULL;
	wClass.hInstance=hInst;
	wClass.lpfnWndProc=(WNDPROC)WinProc;
	wClass.lpszClassName="WinGL Class";
	wClass.lpszMenuName=NULL;
	wClass.style=CS_HREDRAW|CS_VREDRAW;

	if(!RegisterClassEx(&wClass))
	{
		int nResult=GetLastError();
		MessageBox(NULL,
			"WinGL Class creation failed\r\n",
			"WinGL Class Failed",
			MB_ICONERROR);
	}

	HWND hWnd=CreateWindowEx(NULL,
			"WinGL Class",
			"OpenGL GUI",
			WS_OVERLAPPEDWINDOW,
			0,
			0,
			1024+16,
			720+38,
			NULL,
			NULL,
			hInst,
			NULL);

	if(!hWnd)
	{
		int nResult=GetLastError();

		MessageBox(NULL,
			"Window creation failed\r\n",
			"Window Creation Failed",
			MB_ICONERROR);
	}

    ShowWindow(hWnd,nShowCmd);

	MSG msg;
	ZeroMemory(&msg,sizeof(MSG));

	while(GetMessage(&msg,NULL,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

char aux[512];
LRESULT CALLBACK WinProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	//wchar_t dmsg[128];
	switch(msg)
	{
		case WM_TIMER:
			switch (wParam) 
			{ 
			case IDC_GRX_OPENGL: 
				OpenglDraw();
				return 0;
				break;
			}
		break;

		case WM_CREATE:
		{
			CreateGraphicsPanel(hWnd,msg,wParam,lParam);
			SetTimer(hWnd,IDC_GRX_OPENGL,10,(TIMERPROC) NULL);
		}
		break;

		case WM_COMMAND:
			/*switch(LOWORD(wParam))
            {
			}*/
			break;

		case WM_MOUSEMOVE:
			{
				const int mx = (int)GET_X_LPARAM(lParam);
				const int my = (int)GET_Y_LPARAM(lParam);
				mybutton.Over(mx,my,mleft);
				mybutton2.Over(mx,my,mleft);
				mybutton3.Over(mx,my,mleft);
				mybutton4.Over(mx,my,mleft);
				myframe1.Over(mx,my,mleft);
				framebutton1.Over(mx,my,mleft);
				mynumber1.Over(mx,my,mleft);
				myfloat1.Over(mx,my,mleft);
				for(uint i=0;i<5;i++) mysliders[i].Over(mx,my,mleft);
				if(mywheel1.Over(mx,my,mleft)==1){
					mystatic2.SetFloat("%.3f",mywheel1.value);
				}
				if(mywheel2.Over(mx,my,mleft)==1){
					mystatic3.SetFloat("ResX: %.0f",mywheel2.value);
				}
				mytabs1.Over(mx,my,mleft);
				tab1button1.Over(mx,my,mleft);
				tab2button1.Over(mx,my,mleft);
				tab3button1.Over(mx,my,mleft);
				for(uint i=0;i<5;i++){
					if(tab4wheels[i].Over(mx,my,mleft)==1){
						tab4statics[i].SetFloat("%.0f",tab4wheels[i].value);
					}
				}
			}
			break;

		case WM_LBUTTONDOWN:
			{
				SetCapture(hWnd);
				mleft = true;
				const int mx = (int)GET_X_LPARAM(lParam);
				const int my = (int)GET_Y_LPARAM(lParam);
				mybutton.LDown(mx,my);
				mybutton2.LDown(mx,my);
				mybutton3.LDown(mx,my);
				mybutton4.LDown(mx,my);
				myframe1.LDown(mx,my);
				framebutton1.LDown(mx,my);
				myedit1.LDown(mx,my);
				mycheckbox1.LDown(mx,my);
				mycheckbox2.LDown(mx,my);
				mynumber1.LDown(mx,my);
				myfloat1.LDown(mx,my);
				for(uint i=0;i<5;i++) mysliders[i].LDown(mx,my);
				mywheel1.LDown(mx,my);
				mywheel2.LDown(mx,my);
				mytabs1.LDown(mx,my);
				tab1button1.LDown(mx,my);
				tab2button1.LDown(mx,my);
				tab3button1.LDown(mx,my);
				for(uint i=0;i<5;i++) tab4wheels[i].LDown(mx,my);
			}
			break;

		case WM_LBUTTONUP:
			{
				mleft = false;
				const int mx = (int)GET_X_LPARAM(lParam);
				const int my = (int)GET_Y_LPARAM(lParam);
				if(mybutton.LUp(mx,my)==1){
					MessageBox(hWnd,"New world","WWM beta",MB_OK);
				}
				if(mybutton2.LUp(mx,my)==1){
					MessageBox(hWnd,"Save current world","WWM beta",MB_OK);
				}
				if(mybutton3.LUp(mx,my)==1){
					if(MessageBox(hWnd,"Do you want to exit?","WWM info",MB_YESNO)==IDYES){
						exit(0);
					}
				}
				if(mybutton4.LUp(mx,my)==1){
					myframe1.Show(!myframe1.visible);
				}
				if(myframe1.LUp(mx,my)==1){
					//MessageBox(hWnd,"LButtonUp in myframe","WWM beta",MB_OK);
				}
				if(framebutton1.LUp(mx,my)==1){
					MessageBox(hWnd,"Opening file dialog...","WWM beta",MB_OK);
				}
				mycheckbox1.LUp(mx,my);
				mycheckbox2.LUp(mx,my);
				mynumber1.LUp(mx,my);
				myfloat1.LUp(mx,my);
				for(uint i=0;i<5;i++) 
				{
					mysliders[i].LUp(mx,my);
				}
				mywheel1.LUp(mx,my);
				mywheel2.LUp(mx,my);
				ReleaseCapture();
				mytabs1.LUp(mx,my);
				tab1button1.LUp(mx,my);
				tab2button1.LUp(mx,my);
				tab3button1.LUp(mx,my);
				for(uint i=0;i<5;i++) tab4wheels[i].LUp(mx,my);
			}
			break;

		case WM_RBUTTONDOWN:
			{
			}
			break;

		case WM_KEYDOWN:
			{
				/*swprintf_s(dmsg, L"WM_KEYDOWN: 0x%x\n", wParam);
				OutputDebugStringW(dmsg);*/	
			}
			break;

		case WM_CHAR:
			{
				//char amsg[2048];
				if(myedit1.state==1)
				{
					if(wParam!=VK_BACK){
						sprintf(aux,"%s%c",myedit1.text,wParam);
						myedit1.SetText((const char*)aux);
					}else{
						if(strlen(myedit1.text)>0){
							sprintf(aux,"%s",myedit1.text);
							aux[strlen(aux)-1]='\0';
							myedit1.SetText((const char*)aux);
						}
					}
				}
				//sprintf_s(amsg, "WM_CHAR: 0x%x [%s]\n", wParam, aux);
				//OutputDebugString(amsg);
			}
			break;

		case WM_KEYUP:
			{
				/*swprintf_s(dmsg, L"WM_KEYUP: 0x%x\n", wParam);
				OutputDebugStringW(dmsg);*/	
			}
			break;
		

		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
		break;
	}

	return DefWindowProc(hWnd,msg,wParam,lParam);
}

void CreateGraphicsPanel(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	GraphicsOpengl = CreateWindowEx(0, "STATIC","", WS_CHILD |WS_VISIBLE,0,0,1024,720,hWnd,(HMENU)IDC_GRX_OPENGL,NULL,NULL);
	hdc = GetDC(GraphicsOpengl);
    PIXELFORMATDESCRIPTOR pfd = {
        sizeof(PIXELFORMATDESCRIPTOR),
        1,
        PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, 
        PFD_TYPE_RGBA,
        24,
        0,0,0,0,0,0,
        0,0,
        0,0,0,0,0,
        32,
        0,
        0,
        PFD_MAIN_PLANE,
        0,
        0,0,0
    };
	PixelFormat = ChoosePixelFormat(hdc, &pfd);
    SetPixelFormat(hdc,PixelFormat, &pfd);
    hrc = wglCreateContext(hdc);
    wglMakeCurrent(hdc, hrc);
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
    glFlush();
	glViewport(0, 0, 1024, 720);     
	glMatrixMode(GL_PROJECTION);   
    glLoadIdentity();
    glOrtho(0, 1024, 720, 0, -10, 10);
    glMatrixMode(GL_MODELVIEW);
    glDepthMask(GL_TRUE);    
    glEnable(GL_DEPTH_TEST);

	HFONT font1;
	base = glGenLists(96);
	font1 = CreateFont(	16,
						0,
						0,
						0,
						FW_NORMAL,
						FALSE,
						FALSE,
						FALSE,
						ANSI_CHARSET,
						OUT_TT_PRECIS,
						CLIP_DEFAULT_PRECIS,
						ANTIALIASED_QUALITY,
						FF_DONTCARE|DEFAULT_PITCH,
						"Console");
	SelectObject(hdc, font1);
	wglUseFontBitmaps(hdc, 32, 96, base);
	DeleteObject(font1);

	mybutton = Button(5,5,0,100,20,true,"New");
	mybutton2 = Button(5,30,0,100,20,true,"Save");
	mybutton4 = Button(5,55,0,100,20,true,"Menu");
	mybutton3 = Button(5,80,0,100,20,true,"Exit");
	myframe1 = Frame(121,6,1,150,180,false,"Menu");
	framebutton1 = Button(126,31,1.01,140,20,false,"Open");
	myedit1 = Edit(5,105,0,100,20,true,"text");
	mystatic1 = Static(5,130,0,100,20,true,"Some text");
	mycheckbox1 = CheckBox(5,155,0,20,20,true,"");
	mycheckbox2 = CheckBox(30,155,0,20,20,true,"");
	mynumber1 = EditNumber(5,180,0,100,20,true,3);
	mynumber1.min = 0;
	mynumber1.step = 2;
	mysliders[0] = Slider(5,205,0,200,20,true,1,1,4,1);
	mysliders[1] = Slider(5,230,0,200,20,true,2,1,10,1);
	mysliders[2] = Slider(5,255,0,200,20,true,3,1,10,1);
	mysliders[3] = Slider(5,280,0,200,20,true,4,1,30,1);
	mysliders[4] = Slider(5,305,0,200,20,true,1,1,100,1);
	myfloat1 = EditNumberF(5,330,0,100,20,true,0.8,0.1,1.0,0.05);
	mywheel1 = Wheel(5,355,0,200,20,true,0.2,0.1,2.0,0.001);
	mywheel2 = Wheel(90,380,0,115,20,true,40,10,400,1);
	mystatic2 = Static(210,355,0,100,20,true,"0.200");
	mystatic3 = Static(5,380,0,80,20,true,"ResX: 40");
	mytabs1 = Tabs(225,5,0,300,300,true,0);
	mytabs1.AddTab("Tab 1");
	mytabs1.AddTab("Tab 2");
	mytabs1.AddTab("Tab 3");
	mytabs1.AddTab("Tab 4");
	mytabs1.AddTab("Tab 5");
	mytabs1.current_tab = 2;
	tab1button1 = Button(235,50,0,100,20,false,"tab1button1");
	tab2button1 = Button(235,70,0,100,20,false,"tab2button1");
	tab3button1 = Button(235,90,0,100,20,true,"tab3button1");
	tab4statics[0] = Static(235,50,0.05,30,20,false,"40");
	tab4statics[1] = Static(235,75,0.05,30,20,false,"40");
	tab4statics[2] = Static(235,100,0.05,30,20,false,"40");
	tab4statics[3] = Static(235,125,0.05,30,20,false,"40");
	tab4statics[4] = Static(235,150,0.05,30,20,false,"40");
	tab4wheels[0] =  Wheel(290,50,0.05,200,20,false,40,10,400,1);
	tab4wheels[1] =  Wheel(290,75,0.05,200,20,false,40,10,400,1);
	tab4wheels[2] =  Wheel(290,100,0.05,200,20,false,40,10,400,1);
	tab4wheels[3] =  Wheel(290,125,0.05,200,20,false,40,10,400,1);
	tab4wheels[4] =  Wheel(290,150,0.05,200,20,false,40,10,400,1);
	mytabs1.AddTabControl(0,&tab1button1);
	mytabs1.AddTabControl(1,&tab2button1);
	mytabs1.AddTabControl(2,&tab3button1);
	for(uint i=0;i<5;i++) mytabs1.AddTabControl(3,&tab4statics[i]);
	for(uint i=0;i<5;i++) mytabs1.AddTabControl(3,&tab4wheels[i]);

	mycheckbox2.state = 1;
	mybutton.font = base;
	mybutton2.font = base;
	mybutton3.font = base;
	mybutton4.font = base;
	myframe1.font = base;
	framebutton1.font = base;
	myedit1.font = base;
	mystatic1.font = base;
	mystatic2.font = base;
	mystatic3.font = base;
	mycheckbox1.font = base;
	mycheckbox2.font = base;
	myframe1.AddControl(&framebutton1);
	mynumber1.font = base;
	myfloat1.font = base;
	for(uint i=0;i<5;i++) mysliders[i].font = base;
	mywheel1.font = base;
	mywheel2.font = base;
	mytabs1.font = base;
	tab1button1.font = base;
	tab2button1.font = base;
	tab3button1.font = base;
	for(uint i=0;i<5;i++) tab4statics[i].font = base;
	for(uint i=0;i<5;i++) tab4wheels[i].font = base;
}

void OpenglDraw(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	mybutton.Render();
	mybutton2.Render();
	mybutton3.Render();
	mybutton4.Render();
	myframe1.Render();
	framebutton1.Render();
	myedit1.Render();
	mystatic1.Render();
	mystatic2.Render();
	mystatic3.Render();
	mycheckbox1.Render();
	mycheckbox2.Render();
	mynumber1.Render();
	myfloat1.Render();
	for(uint i=0;i<5;i++) mysliders[i].Render();
	mywheel1.Render();
	mywheel2.Render();
	mytabs1.Render();
	tab1button1.Render();
	tab2button1.Render();
	tab3button1.Render();
	for(uint i=0;i<5;i++) tab4statics[i].Render();
	for(uint i=0;i<5;i++) tab4wheels[i].Render();
	SwapBuffers(hdc);
}

GLvoid glPrint(float x, float y, float z, const char *fmt, ...)
{
	char text[256];
	va_list ap;

	if(fmt == NULL)
		return;

	va_start(ap,fmt);
	vsprintf(text,fmt,ap);
	va_end(ap);

	glRasterPos3f(x,y,z);
	glPushAttrib(GL_LIST_BIT);
	glListBase(base-32);
	glCallLists((GLsizei)strlen(text),GL_UNSIGNED_BYTE, text);
	glPopAttrib();
}