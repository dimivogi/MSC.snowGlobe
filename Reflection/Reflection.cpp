#include	"Reflection.h"

using		namespace Globe;


Reflection::Reflection( const GLfloat x_plane , const GLfloat y_plane , const GLfloat z_plane )	:
	_plane(x_plane,y_plane,z_plane) , 
	_depth_test(false) , _lighting(false) , 
	_textures1D(false) , _textures2D(false) , _textures3D(false) , 
	_normalize(true) , _cull_face(true) , _cull_face_back(false)	{};