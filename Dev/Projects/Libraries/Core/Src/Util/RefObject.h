#pragma once

class RefObject
{
public:
	RefObject():mReference(0){}
	virtual ~RefObject(){	mReference = 0; }

	void AddRef(){mReference++;}
	void Release()
	{
		if(mReference<=1) 
			delete this; 
		else
			mReference--;
	}
protected:
	unsigned int mReference;
};

