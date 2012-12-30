#include	"Material.h"



Globe::Material::Material(	const Colour& ambient , const Colour& diffuse , const Colour& specular , 
							const Colour& emission , const float shininess )	:
	_ambient(ambient) , _diffuse(diffuse) , _specular(specular), _emission(emission) , 
	_shininess((shininess<0?0:shininess))	{};