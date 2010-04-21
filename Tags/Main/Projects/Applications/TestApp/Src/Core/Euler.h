#pragma once

class DCEuler
{
public:
	float roll;//x axis
	float pitch; //y axis
	float yaw; //z axis

	float GetXRotate()const	{ return roll;	}
	float GetYRotate()const { return pitch;	}
	float GetZRotate()const { return yaw;	}
};