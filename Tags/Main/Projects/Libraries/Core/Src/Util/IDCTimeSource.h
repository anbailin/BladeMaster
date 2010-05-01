#pragma once

class IDCTimeSource{
public:
	virtual ~IDCTimeSource(){}
	virtual double GetTime() const=0;
};