#include	"Texture.h"

using		namespace Globe;



Texture::Texture( const unsigned int dimension )	:
	_image() , _init(false) , _id(0) , _dimension( ( dimension >= 3 ? GL_TEXTURE_3D : ( dimension >= 2 ? GL_TEXTURE_2D : GL_TEXTURE_1D) ) )	{};
Texture::Texture( const unsigned int dimension , const Image& image )	:
	_image(image) , _init(false) , _id(0) , _dimension( ( dimension >= 3 ? GL_TEXTURE_3D : ( dimension >= 2 ? GL_TEXTURE_2D : GL_TEXTURE_1D) ) )	{};
Texture::Texture( const Texture& texture )	:
	_image(texture.image()) , _init(false) , _id(0) , _dimension( ( texture.dimension() >= 3 ? GL_TEXTURE_3D : ( texture.dimension() >= 2 ? GL_TEXTURE_2D : GL_TEXTURE_1D) ) )	{};
