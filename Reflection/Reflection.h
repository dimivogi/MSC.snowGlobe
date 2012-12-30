#pragma	once

#ifndef	NOMINMAX
	#define	NOMINMAX
#endif
#include	"..\Vector\Vector3f.h"
#include	"GXBase.h"



namespace	Globe
{
	/****************************************************************************************
	*****************************************************************************************
	---------------------------------- Reflection Class -------------------------------------
	*****************************************************************************************
	****************************************************************************************/


	class	Reflection
	{
		private:

			Vector3f	_plane;
			bool		_depth_test;
			bool		_lighting;
			bool		_textures1D;
			bool		_textures2D;
			bool		_textures3D;
			bool		_normalize;
			bool		_cull_face;
			bool		_cull_face_back;


		public:

			explicit Reflection( const GLfloat x_plane = 1.0f , const GLfloat y_plane = 1.0f , const GLfloat z_plane = 1.0f );

			void	pre_transparent_surface();
			void	post_transparent_surface();
			void	pre_reflection();
			void	post_reflection();
	};



	/****************************************************************************************
	*****************************************************************************************
	---------------------------------- Function Definitions ---------------------------------
	*****************************************************************************************
	****************************************************************************************/


	inline void	Reflection::pre_transparent_surface()
	{
		GLboolean		boolean = GL_FALSE;



		this->_depth_test = false;
		this->_lighting = false;
		this->_textures1D = false;
		this->_textures2D = false;
		this->_textures3D = false;
		this->_normalize = false;
		this->_cull_face = true;
		this->_cull_face_back = false;


		glGetBooleanv(GL_DEPTH_TEST,&boolean);
		if ( boolean )
		{
			this->_depth_test = true;
			glDisable(GL_DEPTH_TEST);
		}

		glColorMask(GL_FALSE,GL_FALSE,GL_FALSE,GL_FALSE);

		glGetBooleanv(GL_LIGHTING,&boolean);
		if ( boolean )
		{
			this->_lighting = true;
			glDisable(GL_LIGHTING);
		}

		glGetBooleanv(GL_TEXTURE_1D,&boolean);
		if ( boolean )
		{
			this->_textures1D = true;
			glDisable(GL_TEXTURE_1D);
		}

		glGetBooleanv(GL_TEXTURE_2D,&boolean);
		if ( boolean )
		{
			this->_textures2D = true;
			glDisable(GL_TEXTURE_2D);
		}

		glGetBooleanv(GL_TEXTURE_3D,&boolean);
		if ( boolean )
		{
			this->_textures3D = true;
			glDisable(GL_TEXTURE_3D);
		}

		glEnable(GL_STENCIL_TEST);
		glStencilFunc(GL_ALWAYS,1,1);
		glStencilOp(GL_REPLACE,GL_REPLACE,GL_REPLACE);
		//glFrontFace(GL_CW);
	};

	inline void	Reflection::post_transparent_surface()
	{
		if ( this->_textures1D )
			glEnable(GL_TEXTURE_1D);

		if ( this->_textures2D )
			glEnable(GL_TEXTURE_2D);

		if ( this->_textures3D )
			glEnable(GL_TEXTURE_3D);

		if ( this->_lighting )
			glEnable(GL_LIGHTING);

		if ( this->_depth_test )
			glEnable(GL_DEPTH_TEST);

		//glFrontFace(GL_CCW);
		glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE);
	};

	inline void	Reflection::pre_reflection()
	{
		GLboolean		boolean = GL_FALSE;
		GLint			cull = GL_BACK;



		glGetBooleanv(GL_NORMALIZE,&boolean);
		if ( !boolean )
		{
			this->_normalize = false;
			glEnable(GL_NORMALIZE);
		}

		glGetBooleanv(GL_CULL_FACE,&boolean);
		if ( !boolean )
		{
			this->_cull_face = false;
			glEnable(GL_CULL_FACE);
		}

		glGetIntegerv(GL_CULL_FACE_MODE,&cull);
		if ( cull == GL_BACK )
		{
			this->_cull_face_back = true;
			glCullFace(GL_FRONT);
		}

		glStencilFunc(GL_EQUAL,1,1);
		glStencilOp(GL_KEEP,GL_KEEP,GL_KEEP);

		glPushMatrix();
			
			glScalef(this->_plane.x(),this->_plane.y(),this->_plane.z());
	};

	inline void	Reflection::post_reflection()
	{
		glPopMatrix();

		if ( !this->_normalize )
			glDisable(GL_NORMALIZE);

		if ( !this->_cull_face )
			glDisable(GL_CULL_FACE);

		if ( this->_cull_face_back )
			glCullFace(GL_BACK);

		glDisable(GL_STENCIL_TEST);
	}; 

}