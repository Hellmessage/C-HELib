#ifndef HEWINDOW_H
#define HEWINDOW_H

#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>

class HEWindow {
public:
	explicit HEWindow(HINSTANCE hinstance);
	HEWindow();

	//���þ��
	void SetHinstance(HINSTANCE hinstance);
	//���ý�������
	void SetWinProc(WNDPROC proc);
	//���ñ�����ʽ
	void SetBackColor(COLORREF color);
	//������ʽ
	void SetStyle(UINT style);
	//���ô�������
	void SetClassName(LPCSTR class_name);
	//�������
	void SetCursor(HCURSOR cursor);
	void SetCursor(LPCSTR cursor);
	//����ͼ��
	void SetIcon(HICON icon, HICON icon_small);
	void SetIcon(int icon, int icon_small);
	//���ò˵�
	void SetMenu(LPCSTR menu_name);
	//ע�ᴰ����ʽ
	void Registry();
	//���ô������ɴ�С
	void SetSize(SIZE size);
	void SetSize(int width, int height);
	//���ô�������λ��
	void SetPoint(POINT point);
	void SetPoint(int x, int y);
	//��������
	auto Create(LPCSTR title, DWORD style)->HWND;
	//��ʾ����
	void Show(int cmd) const;
	void Update() const;
	//���ô���͸��
	void SetAlpha(int alpha = 100) const;
	void SetTransparency() const;
	//�����ö�
	void SetTopMost() const;
	//��ȡ������
	auto GetHWND() const->HWND;
	//�Դ������
	void Center() const;
	void Center(int width, int height) const;
	void Center(SIZE size) const;


public:
	//���ô������
	static void Center(HWND hwnd, int width, int height);
	//��ȡ��������
	static auto GetWorkScreen()->SIZE;
	//��ȡ��Ļ��С
	static auto GetFullScreen()->SIZE;
	static void SetWindowAlpha(HWND hwnd, int alpha = 100);
	static void SetWindowTransColor(HWND hwnd, COLORREF color);
	//�򿪿���̨
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