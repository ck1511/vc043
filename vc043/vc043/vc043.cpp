// vc043.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "vc043.h"

#define MAX_LOADSTRING 100

//+++++++++++++++++++++++���³���Ա���+++++++++++++++++++++++//
typedef struct Time
{
	int hour,min,sec;
}TimeStructure;
TimeStructure xclock; //ʱ�ӽṹ��ע�⣺ȫ�ֱ�����Ҫ�õ�����ĸ������
WORD xhour,xmin,xsec;
TCHAR kkk[60]; //������ʾ��ϵͳʱ���ַ���
TCHAR kkk1[60]; //������ʾ���������ֵ(�û���)�ַ���
TCHAR kkk11[60]; //������ʾ���������ֵ����Ļ���꣩�ַ���
TCHAR kkk2[60]; //������ʾ�ļ��������ֵ�ַ���
#define PI 3.1415926

void AdjustTime(TimeStructure *x); //ʱ�ӵ�������

//+++++++++++++++++++++++���ϳ���Ա���+++++++++++++++++++++++//


// ȫ�ֱ���:
HINSTANCE hInst;								// ��ǰʵ��
TCHAR szTitle[MAX_LOADSTRING];					// �������ı�
TCHAR szWindowClass[MAX_LOADSTRING];			// ����������

// �˴���ģ���а����ĺ�����ǰ������:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

// ��ʱ�����á������Ϣ�������
INT_PTR CALLBACK TimerSet(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: �ڴ˷��ô��롣
	MSG msg;
	HACCEL hAccelTable;

	// ��ʼ��ȫ���ַ���
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_VC043, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ִ��Ӧ�ó����ʼ��:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_VC043));

	// ����Ϣѭ��:
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
//  ����: MyRegisterClass()
//
//  Ŀ��: ע�ᴰ���ࡣ
//
//  ע��:
//
//    ����ϣ��
//    �˴�������ӵ� Windows 95 �еġ�RegisterClassEx��
//    ����֮ǰ�� Win32 ϵͳ����ʱ������Ҫ�˺��������÷������ô˺���ʮ����Ҫ��
//    ����Ӧ�ó���Ϳ��Ի�ù�����
//    ����ʽ��ȷ�ġ�Сͼ�ꡣ
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
//   ����: InitInstance(HINSTANCE, int)
//
//   Ŀ��: ����ʵ�����������������
//
//   ע��:
//
//        �ڴ˺����У�������ȫ�ֱ����б���ʵ�������
//        ��������ʾ�����򴰿ڡ�
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����

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

// ��ʱ�����á������Ϣ�������
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
					xhour=_ttoi(str); //tcharת��Ϊ����int
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
//  ����: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  Ŀ��: ���������ڵ���Ϣ��
//
//  WM_COMMAND	- ����Ӧ�ó���˵�
//  WM_PAINT	- ����������
//  WM_DESTROY	- �����˳���Ϣ������
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	//+++++++++++++++++++++++���³���Ա���+++++++++++++++++++++++//
	
	HPEN hpen;
	HBRUSH hbrush;
	RECT clientRect;
	//static TimeStructure x;
	float sita=0;
	int xOrg,yOrg,rSec,rMin,rHour,rClock,xBegin,xEnd,yBegin,yEnd;
	//+++++++++++++++++++++++���ϳ���Ա���+++++++++++++++++++++++//

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// �����˵�ѡ��:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
	//+++++++++++++++++++++++���³���Ա���+++++++++++++++++++++++//
		case IDM_DST:
			KillTimer(hWnd, 9999); //�رն�ʱ��
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, TimerSet);
			SetTimer(hWnd, 9999,1000,NULL); //������ʱ��
			break;
//+++++++++++++++++++++++���ϳ���Ա���+++++++++++++++++++++++//
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
		//+++++++++++++++++++++++���³���Ա���+++++++++++++++++++++++//
	case WM_LBUTTONDOWN:		
		POINT p;
		GetCursorPos(&p);
		//��lParamת��ΪTCHAR�ַ���
		wsprintf(kkk1,L"��갴������Ϊ:�û������꣨%d��%d������Ļ���꣨%d��%d��",LOWORD(lParam),HIWORD(lParam),p.x,p.y);
		InvalidateRect(hWnd,NULL,TRUE); //�����ػ���Ϣ
		break;
	case WM_CHAR :
		//�� LOWORD(wParam)ת��ΪTCHAR�ַ���
		wsprintf(kkk2,_T("�����ַ�: %c"),LOWORD(wParam));
		InvalidateRect(hWnd,NULL,TRUE); //�����ػ���Ϣ
		break;
	case WM_CREATE:   //��������ʱ��������Ϣ
		SetTimer(hWnd, 9999,1000,NULL); //������ʱ��
		SYSTEMTIME systm1;
		GetLocalTime(&systm1);//��ȡϵͳ����ʱ�ӣ���ֵ��systm�ṹ��
		xclock.hour=systm1.wHour;
		xclock.min=systm1.wMinute;
		xclock.sec=systm1.wSecond;
		break;
	case WM_TIMER:     //��ʱ���¼���������Ϣ
		if(wParam==9999)
		{
			xclock.sec++;
			AdjustTime(&xclock);
			InvalidateRect(hWnd,NULL,FALSE); //�����ػ���Ϣ����������������ֹ��˸����
		}
		break;
		//+++++++++++++++++++++++���ϳ���Ա���+++++++++++++++++++++++//
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: �ڴ���������ͼ����...
		//+++++++++++++++++++++++���³���Ա���+++++++++++++++++++++++//
		SYSTEMTIME systm;
		GetLocalTime(&systm);//��ȡϵͳ����ʱ�ӣ���ֵ��systm�ṹ��
		//��systm�ṹ��ת��ΪTCHAR�ַ���
		wsprintf(kkk,L"ϵͳʱ��:%d��%02d��%02d�� ����%d  %02d:%02d:%02d",systm.wYear,systm.wMonth,systm.wDay,systm.wDayOfWeek,systm.wHour,systm.wMinute,systm.wSecond);
		
		//���������
		HFONT hFont;
		hFont=CreateFont(18,18,0,0,FW_THIN,0,false,false,
			GB2312_CHARSET,OUT_CHARACTER_PRECIS,
			CLIP_CHARACTER_PRECIS,DEFAULT_QUALITY,
			FF_MODERN,L"����");
		SelectObject(hdc,hFont);	 //ѡ������
		SetTextColor(hdc,RGB(255,100,0)); //������ɫ
		TextOut( hdc,0,0,kkk,_tcslen(kkk)); //_tcslen��������ַ����������ֽ�����һ������Ҳ��һ���ַ�����
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
		Ellipse(hdc,xOrg-rClock,yOrg-rClock,xOrg+rClock,yOrg+rClock); //////////////////////////��λ�û��Ƴ�����Բ��

		DeleteObject(hpen);
		DeleteObject(hbrush);

		for(int i=0; i<60;i++) ////////////���̶�
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
		LineTo(hdc,xEnd,yEnd); ///////////////��������//////////////////////
		DeleteObject(hpen);

		hpen=CreatePen(PS_SOLID,5,RGB(0,0,0));
		SelectObject(hdc,hpen);
		sita=2*PI*xclock.min/60;
		xBegin=xOrg+(int)(rMin*sin(sita));
		yBegin=yOrg-(int)(rMin*cos(sita));
		xEnd=xOrg+(int)(rClock*sin(sita+PI)/8);
		yEnd=yOrg-(int)(rClock*cos(sita+PI)/8);
		MoveToEx(hdc,xBegin,yBegin,NULL);
		LineTo(hdc,xEnd,yEnd); ///////////////���Ʒ���//////////////////////
		DeleteObject(hpen);

		hpen=CreatePen(PS_SOLID,10,RGB(0,0,0));
		SelectObject(hdc,hpen);
		sita=2*PI*xclock.hour/12;
		xBegin=xOrg+(int)(rHour*sin(sita));
		yBegin=yOrg-(int)(rHour*cos(sita));
		xEnd=xOrg+(int)(rClock*sin(sita+PI)/8);
		yEnd=yOrg-(int)(rClock*cos(sita+PI)/8);
		MoveToEx(hdc,xBegin,yBegin,NULL);
		LineTo(hdc,xEnd,yEnd); ///////////////����ʱ��//////////////////////

		DeleteObject(hpen);
		//DeleteObject(hbrush);
		//+++++++++++++++++++++++���ϳ���Ա���+++++++++++++++++++++++//


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

// �����ڡ������Ϣ�������
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

void AdjustTime(TimeStructure *x) //ʱ�ӵ�������
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
