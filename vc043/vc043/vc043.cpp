// vc043.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "vc043.h"

#define MAX_LOADSTRING 100

//+++++++++++++++++++++++以下程序员添加+++++++++++++++++++++++//
typedef struct Time
{
	int hour,min,sec;
}TimeStructure;
TimeStructure xclock; //时钟结构。注意：全局变量不要用单个字母！！！
WORD xhour,xmin,xsec;
TCHAR kkk[60]; //界面显示的系统时钟字符串
TCHAR kkk1[60]; //界面显示的鼠标坐标值(用户区)字符串
TCHAR kkk11[60]; //界面显示的鼠标坐标值（屏幕坐标）字符串
TCHAR kkk2[60]; //界面显示的键盘输入键值字符串
#define PI 3.1415926

void AdjustTime(TimeStructure *x); //时钟调整函数

//+++++++++++++++++++++++以上程序员添加+++++++++++++++++++++++//


// 全局变量:
HINSTANCE hInst;								// 当前实例
TCHAR szTitle[MAX_LOADSTRING];					// 标题栏文本
TCHAR szWindowClass[MAX_LOADSTRING];			// 主窗口类名

// 此代码模块中包含的函数的前向声明:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

// “时间设置”框的消息处理程序。
INT_PTR CALLBACK TimerSet(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: 在此放置代码。
	MSG msg;
	HACCEL hAccelTable;

	// 初始化全局字符串
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_VC043, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 执行应用程序初始化:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_VC043));

	// 主消息循环:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目的: 注册窗口类。
//
//  注释:
//
//    仅当希望
//    此代码与添加到 Windows 95 中的“RegisterClassEx”
//    函数之前的 Win32 系统兼容时，才需要此函数及其用法。调用此函数十分重要，
//    这样应用程序就可以获得关联的
//    “格式正确的”小图标。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_VC043));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_VC043);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目的: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // 将实例句柄存储在全局变量中

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

// “时间设置”框的消息处理程序。
INT_PTR CALLBACK TimerSet(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL || LOWORD(wParam) == 2)
		{
			if (LOWORD(wParam) == IDOK)// || LOWORD(wParam) == IDCANCEL )//|| LOWORD(wParam) == 2)
			{
				TCHAR str[50];
				GetDlgItemText(hDlg,IDC_HOUR,str,10); 
				if(_tcscmp(str, _T("")))
				{
					xhour=_ttoi(str); //tchar转换为整形int
					if((xhour>=0)&&(xhour<24))
					{
						if((xhour>=0)&&(xhour<12))
							xclock.hour=xhour;
						else
							xclock.hour=xhour-12;
					}
				}

				GetDlgItemText(hDlg,IDC_MIN,str,10); 
				if(_tcscmp(str, _T("")))
				{
					xmin=_ttoi(str);
					if((xmin>=0)&&(xmin<60))
						xclock.min=xmin;
				}

				GetDlgItemText(hDlg,IDC_SEC,str,10); 
				if(_tcscmp(str, _T("")))
				{
					xsec=_ttoi(str);
					if((xsec>=0)&&(xsec<60))
						xclock.sec=xsec;
				}			

			}
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}


//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的: 处理主窗口的消息。
//
//  WM_COMMAND	- 处理应用程序菜单
//  WM_PAINT	- 绘制主窗口
//  WM_DESTROY	- 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	//+++++++++++++++++++++++以下程序员添加+++++++++++++++++++++++//
	
	HPEN hpen;
	HBRUSH hbrush;
	RECT clientRect;
	//static TimeStructure x;
	float sita=0;
	int xOrg,yOrg,rSec,rMin,rHour,rClock,xBegin,xEnd,yBegin,yEnd;
	//+++++++++++++++++++++++以上程序员添加+++++++++++++++++++++++//

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// 分析菜单选择:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
	//+++++++++++++++++++++++以下程序员添加+++++++++++++++++++++++//
		case IDM_DST:
			KillTimer(hWnd, 9999); //关闭定时器
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, TimerSet);
			SetTimer(hWnd, 9999,1000,NULL); //开启定时器
			break;
//+++++++++++++++++++++++以上程序员添加+++++++++++++++++++++++//
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
		//+++++++++++++++++++++++以下程序员添加+++++++++++++++++++++++//
	case WM_LBUTTONDOWN:		
		POINT p;
		GetCursorPos(&p);
		//将lParam转换为TCHAR字符串
		wsprintf(kkk1,L"鼠标按下坐标为:用户区坐标（%d，%d），屏幕坐标（%d，%d）",LOWORD(lParam),HIWORD(lParam),p.x,p.y);
		InvalidateRect(hWnd,NULL,TRUE); //发出重绘消息
		break;
	case WM_CHAR :
		//将 LOWORD(wParam)转换为TCHAR字符串
		wsprintf(kkk2,_T("键盘字符: %c"),LOWORD(wParam));
		InvalidateRect(hWnd,NULL,TRUE); //发出重绘消息
		break;
	case WM_CREATE:   //创建窗口时产生的消息
		SetTimer(hWnd, 9999,1000,NULL); //开启定时器
		SYSTEMTIME systm1;
		GetLocalTime(&systm1);//读取系统本地时钟，赋值给systm结构体
		xclock.hour=systm1.wHour;
		xclock.min=systm1.wMinute;
		xclock.sec=systm1.wSecond;
		break;
	case WM_TIMER:     //定时器事件产生的消息
		if(wParam==9999)
		{
			xclock.sec++;
			AdjustTime(&xclock);
			InvalidateRect(hWnd,NULL,FALSE); //发出重绘消息，背景不擦除（防止闪烁）。
		}
		break;
		//+++++++++++++++++++++++以上程序员添加+++++++++++++++++++++++//
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: 在此添加任意绘图代码...
		//+++++++++++++++++++++++以下程序员添加+++++++++++++++++++++++//
		SYSTEMTIME systm;
		GetLocalTime(&systm);//读取系统本地时钟，赋值给systm结构体
		//将systm结构体转换为TCHAR字符串
		wsprintf(kkk,L"系统时钟:%d年%02d月%02d日 星期%d  %02d:%02d:%02d",systm.wYear,systm.wMonth,systm.wDay,systm.wDayOfWeek,systm.wHour,systm.wMinute,systm.wSecond);
		
		//设置字体等
		HFONT hFont;
		hFont=CreateFont(18,18,0,0,FW_THIN,0,false,false,
			GB2312_CHARSET,OUT_CHARACTER_PRECIS,
			CLIP_CHARACTER_PRECIS,DEFAULT_QUALITY,
			FF_MODERN,L"隶书");
		SelectObject(hdc,hFont);	 //选择字体
		SetTextColor(hdc,RGB(255,100,0)); //设置颜色
		TextOut( hdc,0,0,kkk,_tcslen(kkk)); //_tcslen计算的是字符数，不是字节数，一个汉字也是一个字符长度
		TextOut( hdc,0,25,kkk1,_tcslen(kkk1)); 
		TextOut( hdc,0,50,kkk2,_tcslen(kkk2)); 
		//xclock.sec++;
		//AdjustTime(&xclock);
		GetClientRect(hWnd,&clientRect);
		hpen=(HPEN)GetStockObject(BLACK_PEN);
		hbrush=CreateSolidBrush(RGB(255,220,220));
		SelectObject(hdc,hpen);
		SelectObject(hdc,hbrush);
		xOrg=(clientRect.left+clientRect.right)/2;
		yOrg=(clientRect.top+clientRect.bottom)/2;
		rClock=min(xOrg,yOrg)-50;
		rSec=rClock*6/7;
		rMin=rClock*5/6;
		rHour=rClock*2/3;
		Ellipse(hdc,xOrg-rClock,yOrg-rClock,xOrg+rClock,yOrg+rClock); //////////////////////////此位置绘制出表盘圆形

		DeleteObject(hpen);
		DeleteObject(hbrush);

		for(int i=0; i<60;i++) ////////////画刻度
		{
			if(i%5)
			{
				hpen=CreatePen(PS_SOLID,2,RGB(255,0,0));
				SelectObject(hdc,hpen);
				xBegin=(int)(xOrg+rClock*sin(2*PI*i/60));
				yBegin=yOrg+rClock*cos(2*PI*i/60);
				MoveToEx(hdc,xBegin,yBegin,NULL);
				xEnd=xOrg+(rClock-20)*sin(2*PI*i/60);
				yEnd=yOrg+(rClock-20)*cos(2*PI*i/60);
			
			}
			else
			{
				hpen=CreatePen(PS_SOLID,5,RGB(255,0,0));
				SelectObject(hdc,hpen);
				xBegin=xOrg+rClock*sin(2*PI*i/60);
				yBegin=yOrg+rClock*cos(2*PI*i/60);
				MoveToEx(hdc,xBegin,yBegin,NULL);
				xEnd=xOrg+(rClock-25)*sin(2*PI*i/60);
				yEnd=yOrg+(rClock-25)*cos(2*PI*i/60);
				
			}

			LineTo(hdc,xEnd,yEnd);
			DeleteObject(hpen);
		}

		hpen=CreatePen(PS_SOLID,2,RGB(255,0,0));
		SelectObject(hdc,hpen);
		sita=2*PI*xclock.sec/60;
		xBegin=xOrg+(int)(rSec*sin(sita));
		yBegin=yOrg-(int)(rSec*cos(sita));
		xEnd=xOrg+(int)(rClock*sin(sita+PI)/8);
		yEnd=yOrg-(int)(rClock*cos(sita+PI)/8);
		MoveToEx(hdc,xBegin,yBegin,NULL);
		LineTo(hdc,xEnd,yEnd); ///////////////绘制秒针//////////////////////
		DeleteObject(hpen);

		hpen=CreatePen(PS_SOLID,5,RGB(0,0,0));
		SelectObject(hdc,hpen);
		sita=2*PI*xclock.min/60;
		xBegin=xOrg+(int)(rMin*sin(sita));
		yBegin=yOrg-(int)(rMin*cos(sita));
		xEnd=xOrg+(int)(rClock*sin(sita+PI)/8);
		yEnd=yOrg-(int)(rClock*cos(sita+PI)/8);
		MoveToEx(hdc,xBegin,yBegin,NULL);
		LineTo(hdc,xEnd,yEnd); ///////////////绘制分针//////////////////////
		DeleteObject(hpen);

		hpen=CreatePen(PS_SOLID,10,RGB(0,0,0));
		SelectObject(hdc,hpen);
		sita=2*PI*xclock.hour/12;
		xBegin=xOrg+(int)(rHour*sin(sita));
		yBegin=yOrg-(int)(rHour*cos(sita));
		xEnd=xOrg+(int)(rClock*sin(sita+PI)/8);
		yEnd=yOrg-(int)(rClock*cos(sita+PI)/8);
		MoveToEx(hdc,xBegin,yBegin,NULL);
		LineTo(hdc,xEnd,yEnd); ///////////////绘制时针//////////////////////

		DeleteObject(hpen);
		//DeleteObject(hbrush);
		//+++++++++++++++++++++++以上程序员添加+++++++++++++++++++++++//


		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

void AdjustTime(TimeStructure *x) //时钟调整函数
{
	if(x->sec==60)
	{
		x->sec=0;
		x->min++;
		if(x->min==60)
		{
			x->min=0;
			x->hour++;
			if(x->hour==12)
				x->hour=0;
		}
	}
}
