#include	"Light.h"



Globe::Light::Light(	const GLuint number , const Vector3f& position , 
						const Colour& ambient , const Colour& diffuse , const Colour& specular ,
						bool is_directional , const Vector3f& direction , const bool is_spotlight , const GLfloat cutoff , const GLfloat exponent )	:
	_number(number) , _position(position) , _direction(direction) ,
	_ambient(ambient) , _diffuse(diffuse) , _specular(specular) ,
	_cut_off(cutoff) , _exponent(exponent) , _spotlight(is_spotlight) , _directional(is_directional)	{};