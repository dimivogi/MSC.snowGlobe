#include	"Colour.h"



Globe::Colour::Colour( const GLfloat red , const GLfloat green , const GLfloat blue , const GLfloat alpha )	{ this->colour(red,green,blue,alpha); };
Globe::Colour::Colour( const Vector3f& input )																{ this->colour(input); this->alpha(1.0f); };
Globe::Colour::Colour( const Vector4f& input )																{ this->colour(input); };