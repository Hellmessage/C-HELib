#include "HETimer.h"

using namespace std;

HETimer::HETimer() {
	bus = nullptr;
	InitializeCriticalSection(&critical_section);
}

HETimer::~HETimer() {
	EnterCriticalSection(&critical_section);
	task.clear();
	LeaveCriticalSection(&critical_section);
	if (bus != nullptr) {
		bus->join();
		delete bus;
		bus = nullptr;
	}
}

void HETimer::AddTimer(unsigned int id, unsigned long usec, int param, const char* str_param) {
	if (usec > 0) {
		HETimerInfo info;
		info.id = id;
		info.usec = usec;
		info.param = param;
		info.str_param = str_param;
		info.last_time = GetTickCount64();
		info.del = false;
		EnterCriticalSection(&critical_section);
		task.push_back(info);
		LeaveCriticalSection(&critical_section);
		if (task.size() == 1) {
			if (bus != nullptr) {
				bus->join();
				delete bus;
				bus = nullptr;
			}
			bus = new thread{ &HETimer::OnThread, this };
		}
	}
}

void HETimer::CancelTimer(unsigned int id) {
	EnterCriticalSection(&critical_section);
	for (auto item = task.begin(); item != task.end(); ++item) {
		if (item->id == id) {
			item->del = true;
			LeaveCriticalSection(&critical_section);
			return;
		}
	}
	LeaveCriticalSection(&critical_section);
}

void HETimer::CloseTimer() {
	EnterCriticalSection(&critical_section);
	task.clear();
	LeaveCriticalSection(&critical_section);
}

void HETimer::TimerRun() {
	const auto now = GetTickCount64();
	EnterCriticalSection(&critical_section);
	for (auto item = task.begin(); item != task.end(); ++item) {
		if (now - item->last_time >= item->usec) {
			item->last_time = now;
			if (OnTimer(item->id, item->param, item->str_param) == -1) {
				item->del = true;
			}
		}
	}
	LeaveCriticalSection(&critical_section);
}


void HETimer::TimerDelete() {
	EnterCriticalSection(&critical_section);
	for (auto item = task.begin(); item != task.end();) {
		if (item->del) {
			task.erase(item);
			item = task.begin();
			continue;
		}
		++item;
	}
	LeaveCriticalSection(&critical_section);
}

auto HETimer::ThreadIsClose() const -> bool {
	return task.empty();
}


void HETimer::OnThread() {
	while (true) {
		if (ThreadIsClose()) {
			break;
		}
		TimerDelete();
		TimerRun();
	}
}

