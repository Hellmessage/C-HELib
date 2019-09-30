#ifndef HETIMER_H
#define HETIMER_H

#include <Windows.h>
#include <list>
#include <thread>

struct HETimerInfo {
	unsigned int id;
	ULONGLONG usec;
	ULONGLONG last_time;
	int param;
	const char* str_param;
	bool del;
	HETimerInfo() {
		id = 0;
		usec = 0;
		last_time = 0;
		param = 0;
		str_param = nullptr;
		del = false;
	}
};

typedef std::list<HETimerInfo> TimerList;
typedef std::list<HETimerInfo>::iterator TimerListItem;





class HETimer {
public:
	HETimer();
	virtual ~HETimer();
	
	//添加一个定时任务
	void AddTimer(unsigned int id, unsigned long usec, int param = 0, const char* str_param = nullptr);
	//关闭一个定时任务
	void CancelTimer(unsigned int id);

public:
	virtual int OnTimer(int id, int param, const char *str_param) = 0;
	
protected:
	void CloseTimer();

private:
	auto ThreadIsClose() const -> bool;
	void TimerDelete();
	void TimerRun();
	void OnThread();
	
private:
	std::thread *bus;
	bool is_close = false;
	TimerList task;
	CRITICAL_SECTION critical_section;
};



#endif
