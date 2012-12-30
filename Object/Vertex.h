#pragma once

#ifndef	NOMINMAX
	#define	NOMINMAX
#endif
#include	"GXBase.h"



namespace	Globe
{
	// Struct used in the Vertex Buffer Objects
	struct	Vertex
	{
		GLfloat	_position[3];
		GLfloat	_normal[3];
		GLfloat	_colour[4];
		GLfloat	_texture[3];
		GLubyte	_padding[12];
	};

};
