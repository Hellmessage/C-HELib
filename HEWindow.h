#ifndef HEWINDOW_H
#define HEWINDOW_H

#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>

class HEWindow {
public:
	explicit HEWindow(HINSTANCE hinstance);
	HEWindow();

	//设置句柄
	void SetHinstance(HINSTANCE hinstance);
	//设置解析函数
	void SetWinProc(WNDPROC proc);
	//设置背景样式
	void SetBackColor(COLORREF color);
	//设置样式
	void SetStyle(UINT style);
	//设置窗口类名
	void SetClassName(LPCSTR class_name);
	//设置鼠标
	void SetCursor(HCURSOR cursor);
	void SetCursor(LPCSTR cursor);
	//设置图标
	void SetIcon(HICON icon, HICON icon_small);
	void SetIcon(int icon, int icon_small);
	//设置菜单
	void SetMenu(LPCSTR menu_name);
	//注册窗体样式
	void Registry();
	//设置窗体生成大小
	void SetSize(SIZE size);
	void SetSize(int width, int height);
	//设置窗体生成位置
	void SetPoint(POINT point);
	void SetPoint(int x, int y);
	//构建窗体
	auto Create(LPCSTR title, DWORD style)->HWND;
	//显示窗体
	void Show(int cmd) const;
	void Update() const;
	//设置窗体透明
	void SetAlpha(int alpha = 100) const;
	void SetTransparency() const;
	//窗体置顶
	void SetTopMost() const;
	//获取窗体句柄
	auto GetHWND() const->HWND;
	//对窗体居中
	void Center() const;
	void Center(int width, int height) const;
	void Center(SIZE size) const;


public:
	//设置窗体居中
	static void Center(HWND hwnd, int width, int height);
	//获取工作区域
	static auto GetWorkScreen()->SIZE;
	//获取屏幕大小
	static auto GetFullScreen()->SIZE;
	static void SetWindowAlpha(HWND hwnd, int alpha = 100);
	static void SetWindowTransColor(HWND hwnd, COLORREF color);
	//打开控制台
	static void OpenConsole();
	static void CloseConsole();

private:
	HWND hwnd = nullptr;
	WNDCLASSEX cs;
	bool registered = false;
	bool created = false;
	HINSTANCE hinstance = nullptr;
	UINT style = CS_HREDRAW | CS_VREDRAW;
	WNDPROC proc = nullptr;
	COLORREF color = WHITE_BRUSH;
	LPCSTR class_name = nullptr;
	LPCSTR menu_name = nullptr;
	HCURSOR cursor = LoadCursor(nullptr, IDC_ARROW);
	HICON icon = nullptr;
	HICON icon_small = nullptr;
	SIZE size = { 0, 0 };
	POINT point = { 0, 0 };
};
#endif