#pragma	once

#include	"..\Colour\Colour.h"

using		namespace Globe;



namespace	Globe
{
	/****************************************************************************************
	*****************************************************************************************
	-------------------------------------- Light Class --------------------------------------
	*****************************************************************************************
	****************************************************************************************/

	class	Light
	{
		private:

			GLuint		_number;
			Vector3f	_position;
			Vector3f	_direction;
			Colour		_ambient;
			Colour		_diffuse;
			Colour		_specular;
			GLfloat		_cut_off;
			GLfloat		_exponent;
			bool		_spotlight;
			bool		_directional;


			void		_set_position() const;
			void		_set_ambient() const;
			void		_set_diffuse() const;
			void		_set_specular() const;
			void		_set_spot() const;


		public:

			explicit Light( const GLuint number = 1 , const Vector3f& position = Vector3f(0,0,0) , const Colour& ambient = Colour::colour_black() , 
							const Colour& diffuse = Colour::colour_white() , const Colour& specular = Colour::colour_white() , 
							const bool is_directional = false , const Vector3f& direction = Vector3f(0,0,1) , const bool is_spotlight = false , const GLfloat cutoff = 180.0f , const GLfloat exponent = 0.0f );


			void		number( const GLuint number );
			void		position( const Vector3f&	position );
			void		direction( const Vector3f& direction );
			void		ambient( const Colour& colour );
			void		diffuse( const Colour& colour );
			void		specular( const Colour& colour );
			void		cut_off( const GLfloat cutt_off );
			void		exponent( const GLfloat exponent );
			void		spotlight( const bool is_spotlight );
			void		directional( const bool is_directional );

			GLuint		number() const;
			Vector3f	position() const;
			Vector3f	direction() const;
			Colour		diffuse() const;
			Colour		ambient() const;
			Colour		specular() const;
			GLfloat		cut_off() const;
			GLfloat		exponent() const;
			bool		is_spotlight() const;
			bool		is_directional() const;


			void		apply() const;
			void		select() const;
			void		deselect() const;
	};



	/****************************************************************************************
	*****************************************************************************************
	--------------------------------- Function Definitions ----------------------------------
	*****************************************************************************************
	****************************************************************************************/


	inline void		Light::_set_position() const
	{ 
		if ( this->_directional )
			glLightfv(GL_LIGHT0 + this->_number,GL_POSITION,Vector4f(this->_position.x(),this->_position.y(),this->_position.z(),0.0f).get());
		else
			glLightfv(GL_LIGHT0 + this->_number,GL_POSITION,Vector4f(this->_position.x(),this->_position.y(),this->_position.z(),1.0f).get());
	};
	inline void		Light::_set_ambient() const						{ glLightfv(GL_LIGHT0 + this->_number,GL_AMBIENT,this->_ambient.colour().get()); };
	inline void		Light::_set_diffuse() const						{ glLightfv(GL_LIGHT0 + this->_number,GL_DIFFUSE,this->_diffuse.colour().get()); };
	inline void		Light::_set_specular() const					{ glLightfv(GL_LIGHT0 + this->_number,GL_SPECULAR,this->_specular.colour().get()); };
	inline void		Light::_set_spot() const
	{
		glLightfv(GL_LIGHT0 + this->_number,GL_SPOT_DIRECTION, this->_direction.get());
		glLightf(GL_LIGHT0 + this->_number,GL_SPOT_CUTOFF, this->_cut_off);
		glLightf(GL_LIGHT0 + this->_number,GL_SPOT_EXPONENT, this->_exponent); 
	};


	inline void		Light::number( const GLuint number )			{ this->_number = number; };
	inline void		Light::position( const Vector3f& position )		{ this->_position = position; };
	inline void		Light::direction( const Vector3f& direction )	{ this->_direction = direction; };
	inline void		Light::ambient( const Colour& colour )			{ this->_ambient = colour; };
	inline void		Light::diffuse( const Colour& colour )			{ this->_diffuse = colour; };
	inline void		Light::specular( const Colour& colour )			{ this->_specular = colour; };
	inline void		Light::cut_off( const GLfloat cut_off )			{ this->_cut_off = ( cut_off >= 0  ?   ( cut_off <= 90  ?  cut_off : ( abs(cut_off-180.0) < Vector3f::_V3EPSILON  ?  cut_off : 90 ) ) : 0 ); };
	inline void		Light::exponent( const GLfloat exponent )		{ this->_exponent = ( exponent >= 0  ?   ( exponent <= 128  ?  exponent : 128 ) : 0 ); }; 
	inline void		Light::spotlight( const bool is_spotlight )		{ this->_spotlight = is_spotlight; };
	inline void		Light::directional( const bool is_directional )	{ this->_directional = is_directional; };

	inline GLuint	Light::number() const							{ return this->_number; };
	inline Vector3f	Light::position() const							{ return this->_position; };
	inline Vector3f	Light::direction() const						{ return this->_direction; };
	inline Colour	Light::ambient() const							{ return this->_ambient; };
	inline Colour	Light::diffuse() const							{ return this->_diffuse; };
	inline Colour	Light::specular() const							{ return this->_specular; };
	inline GLfloat	Light::cut_off() const							{ return this->_cut_off; };
	inline GLfloat	Light::exponent() const							{ return this->_exponent; };
	inline bool		Light::is_spotlight() const						{ return this->_spotlight; };
	inline bool		Light::is_directional() const					{ return this->_directional; };


	inline void	Light::apply() const
	{
		this->select();
	
		this->_set_position();
		this->_set_ambient();
		this->_set_diffuse();
		this->_set_specular();
	
		if ( this->is_spotlight() )
			this->_set_spot();

		this->deselect();
	};

	inline void		Light::select() const							{ glEnable(GL_LIGHT0 + this->_number); }
	inline void		Light::deselect() const							{ glDisable(GL_LIGHT0 + this->_number); };

};