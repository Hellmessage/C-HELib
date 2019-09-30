#include "HEWindow.h"
#include <cstdio>

HEWindow::HEWindow(HINSTANCE hinstance) {
	this->cs = {};
	this->hinstance = hinstance;
}

HEWindow::HEWindow() {
	this->cs = {};
	this->hinstance = nullptr;
}

void HEWindow::SetHinstance(HINSTANCE hinstance) {
	this->hinstance = hinstance;
}

void HEWindow::SetWinProc(WNDPROC proc) {
	this->proc = proc;
}

void HEWindow::SetBackColor(COLORREF color) {
	this->color = color;
}

void HEWindow::SetStyle(UINT style) {
	this->style = style;
}

void HEWindow::SetClassName(LPCSTR class_name) {
	this->class_name = class_name;
}

void HEWindow::SetCursor(HCURSOR cursor) {
	this->cursor = cursor;
}

void HEWindow::SetCursor(LPCSTR cursor) {
	this->cursor = LoadCursor(nullptr, cursor);
}

void HEWindow::SetIcon(HICON icon, HICON icon_small) {
	this->icon = icon;
	this->icon_small = icon_small;
}

void HEWindow::SetIcon(int icon, int icon_small) {
	if (this->hinstance == nullptr) {
		return;
	}
	this->icon = LoadIcon(this->hinstance, MAKEINTRESOURCE(icon));
	this->icon_small = LoadIcon(this->hinstance, MAKEINTRESOURCE(icon_small));
}

void HEWindow::SetMenu(LPCSTR menu_name) {
	this->menu_name = menu_name;
}

void HEWindow::Registry() {
	cs.cbSize = sizeof(WNDCLASSEX);
	cs.style = this->style;
	cs.lpfnWndProc = this->proc;
	cs.hInstance = this->hinstance;
	cs.hbrBackground = static_cast<HBRUSH>(CreateSolidBrush(this->color));
	cs.lpszClassName = this->class_name;
	cs.cbWndExtra = 0;
	cs.cbClsExtra = 0;
	cs.hCursor = this->cursor;
	cs.hIconSm = this->icon_small;
	cs.hIcon = this->icon;
	cs.lpszMenuName = this->menu_name;
	if (!RegisterClassEx(&cs)) {
		MessageBox(nullptr, "注册窗体样式失败", "HEWindow::Registry 错误提示", MB_OK);
		exit(EXIT_FAILURE);
	}
	this->registered = true;
}

void HEWindow::SetSize(SIZE size) {
	this->size = size;
}

void HEWindow::SetSize(int width, int height) {
	this->size = { width, height };
}

void HEWindow::SetPoint(POINT point) {
	this->point = point;
}

void HEWindow::SetPoint(int x, int y) {
	this->point = { x, y };
}

auto HEWindow::Create(LPCSTR title, DWORD style) -> HWND {
	if (!this->registered) {
		MessageBox(nullptr, "请先注册窗体样式", "HEWindow::CreateHWND 错误提示", MB_OK);
		exit(EXIT_FAILURE);
	}
	this->hwnd = CreateWindow(this->class_name, title, style, this->point.x, this->point.y, this->size.cx, this->size.cy, nullptr, nullptr, this->hinstance, nullptr);
	this->created = this->hwnd != nullptr;
	if (!this->created) {
		MessageBox(nullptr, "构建窗体失败", "HEWindow::CreateHWND 错误提示", MB_OK);
		exit(EXIT_FAILURE);
	}
	return this->hwnd;
}

void HEWindow::Show(int cmd) const {
	if (this->created) {
		ShowWindow(hwnd, cmd);
		Update();
	}
}

void HEWindow::Update() const {
	if (this->created) {
		UpdateWindow(hwnd);
	}
}

void HEWindow::SetAlpha(int alpha) const {
	if (this->created) {
		SetWindowAlpha(this->hwnd, alpha);
	}
}

void HEWindow::SetTransparency() const {
	if (this->created) {
		SetWindowTransColor(this->hwnd, this->color);
	}
}

void HEWindow::SetTopMost() const {
	if (this->created) {
		SetWindowPos(this->hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);
	}
}

auto HEWindow::GetHWND() const -> HWND {
	return this->hwnd;
}


void HEWindow::Center() const {
	Center(this->size);
}

void HEWindow::Center(int width, int height) const {
	Center(this->hwnd, width, height);
}

void HEWindow::Center(SIZE size) const {
	Center(size.cx, size.cy);
}

void HEWindow::OpenConsole() {
	AllocConsole();
	freopen("CONOUT$", "w+t", stdout);
	freopen("CONOUT$", "w+t", stderr);
	freopen("CONIN$", "r+t", stdin);
}

void HEWindow::CloseConsole() {
	FreeConsole();
}

void HEWindow::Center(HWND hwnd, int width, int height) {
	RECT rect;
	GetWindowRect(hwnd, &rect);
	const auto win_x = rect.right - rect.left;
	const auto win_y = rect.bottom - rect.top;
	GetClientRect(hwnd, &rect);
	const auto client_x = rect.right - rect.left;
	const auto client_y = rect.bottom - rect.top;
	width += (win_x - client_x);
	height += (win_y - client_y);
	const auto screen = GetFullScreen();
	MoveWindow(hwnd, (screen.cx - width) / 2, (screen.cy - height) / 2, width, height, true);
}

auto HEWindow::GetWorkScreen() -> SIZE {
	return { GetSystemMetrics(SM_CXFULLSCREEN), GetSystemMetrics(SM_CYFULLSCREEN) };
}

auto HEWindow::GetFullScreen() -> SIZE {
	return { GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN) };
}

void HEWindow::SetWindowAlpha(HWND hwnd, int alpha) {
	SetWindowLong(hwnd, GWL_EXSTYLE, GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_LAYERED);
	SetLayeredWindowAttributes(hwnd, 0, static_cast<BYTE>((255 * (alpha * 1.5)) / 150), LWA_ALPHA);
}

void HEWindow::SetWindowTransColor(HWND hwnd, COLORREF color) {
	SetWindowLong(hwnd, GWL_EXSTYLE, GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_LAYERED);
	SetLayeredWindowAttributes(hwnd, color, 0, LWA_COLORKEY);
}