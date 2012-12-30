#include	"Vector4f.h"



const float				Globe::Vector4f::_V4EPSILON = 0.001f;


Globe::Vector4f::Vector4f( const GLfloat x , const GLfloat y , const GLfloat z , const GLfloat w )	{ this->set(x,y,z,w); };