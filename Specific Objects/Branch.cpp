#include	"Branch.h"

using		namespace Globe;



Branch::Branch()	:	_level(0) , _yaw_angle(0) , _pitch_angle(0)
{
	this->_position[0] = 0.0f;
	this->_position[1] = 0.0f;
	this->_position[2] = 0.0f;
};