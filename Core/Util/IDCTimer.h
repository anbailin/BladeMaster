#pragma once
class IDCTimer{
public:
	virtual ~IDCTimer(){};
	virtual void Notify()=0;
};