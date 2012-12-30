#pragma	once

#ifndef	NOMINMAX
	#define	NOMINMAX
#endif
#include	"GXBase.h"

using		namespace gxbase;



namespace	Globe
{
	/****************************************************************************************
	*****************************************************************************************
	------------------------------------ Texture Class -------------------------------------
	*****************************************************************************************
	****************************************************************************************/

	class	Texture
	{
		private:

			Image			_image;
			bool			_init;
			GLuint			_id;
			GLenum			_dimension;

			void			create_texture();


		public:

			explicit Texture(  const unsigned int texture_dimension = 1 );
			Texture( const unsigned int texture_dimension , const Image& image );
			Texture( const Texture& texture );


			Texture&		operator=( const Texture& texture );


			void			image( const Image& image );

			Image			image() const;
			bool			is_initialised() const;
			GLuint			id() const;
			unsigned int	dimension() const;


			void			create();
			void			apply() const;
			void			remove() const;
			void			free();
	};



	/****************************************************************************************
	*****************************************************************************************
	--------------------------------- Function Definitions ----------------------------------
	*****************************************************************************************
	****************************************************************************************/


	inline void				Texture::create_texture()
	{
		if ( !(this->_init) )
		{
			glGenTextures(1,&(this->_id));
			this->_init = true;
		}


		this->apply();
		glTexParameteri(this->_dimension,GL_TEXTURE_WRAP_S,GL_REPEAT);
		glTexParameteri(this->_dimension,GL_TEXTURE_WRAP_T,GL_REPEAT);
		glTexParameteri(this->_dimension,GL_TEXTURE_WRAP_R,GL_REPEAT);
		glTexParameteri(this->_dimension,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(this->_dimension,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	};

	inline Texture&		Texture::operator= ( const Texture& texture )
	{
		if ( this != &texture )
		{
			this->image(texture.image());
			this->_init = false;
			this->_dimension = ( texture.dimension() >= 3 ? GL_TEXTURE_3D : ( texture.dimension() >= 2 ? GL_TEXTURE_2D : GL_TEXTURE_1D) );
			this->_id = 0;
		}


		return *this;
	}


	inline void			Texture::image( const Image& image )	{ this->_image = image; };

	inline Image		Texture::image() const					{ return this->_image; };
	inline bool			Texture::is_initialised() const			{ return this->_init; };
	inline GLuint		Texture::id() const						{ return this->_id; };
	inline unsigned int	Texture::dimension() const
	{ 
		unsigned int	return_value;



		switch ( this->_dimension )
		{
			case	GL_TEXTURE_3D :	return_value = 3; break;
			case	GL_TEXTURE_2D :	return_value = 2; break;
			case	GL_TEXTURE_1D :
			default :				return_value = 1; break;
		};


		return return_value;
	};


	inline void			Texture::create()
	{
		this->create_texture();

		if	( this->_dimension == GL_TEXTURE_3D )
			this->_image.gluBuild2DMipmaps();		// missing a builtin 3D texture creator, can be implemented manually though, leave for later
		else if ( this->_dimension == GL_TEXTURE_2D )
			this->_image.gluBuild2DMipmaps();
		else
			this->_image.gluBuild1DMipmaps();
	};

	inline void			Texture::apply() const	{ glBindTexture(this->_dimension,this->_id); };
	inline void			Texture::remove() const	{ glBindTexture(this->_dimension,0); };

	inline void			Texture::free()	
	{
		if ( this->_init )
			glDeleteTextures(1,&(this->_id));

		this->_image.Free();
	};
};