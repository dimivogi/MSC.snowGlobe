#include	"Vector3f.h"



const float				Globe::Vector3f::_V3EPSILON = 0.001f;


Globe::Vector3f::Vector3f( const GLfloat x , const GLfloat y , const GLfloat z )	{ this->set(x,y,z); };