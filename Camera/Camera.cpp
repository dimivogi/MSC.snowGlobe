#include	"Camera.h"



Globe::Camera::Camera( const Vector3f& position , const Vector3f& lookingAt , const Vector3f& up , const float zoom , const bool free )	:
	_position(position) , _looking_at(lookingAt) , _up(up) , _zoom( ( zoom >= 0.0f  ?  zoom : 0.0f ) ) , _free(free)	{};