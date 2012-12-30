#pragma	once

#include	"..\Colour\Colour.h"



namespace	Globe
{
	/****************************************************************************************
	*****************************************************************************************
	------------------------------------ Material Class -------------------------------------
	*****************************************************************************************
	****************************************************************************************/

	class	Material
	{
		private:

			Colour	_ambient;
			Colour	_diffuse;
			Colour	_specular;
			Colour	_emission;
			float	_shininess;


		public:
		
			explicit Material(	const Colour& ambient = Colour(0.2f,0.2f,0.2f,1.0f) , const Colour& diffuse = Colour(0.8f,0.8f,0.8f,1.0f) , 
								const Colour& specular = Colour(0.0f,0.0f,0.0f,1.0f) , const Colour& emission = Colour(0.0f,0.0f,0.0f,0.0f), 
								const float shininess = 0.0f );


			void	ambient( const Colour& colour );
			void	diffuse( const Colour& colour );
			void	specular( const Colour& colour );
			void	emission( const Colour& colour );
			void	shininess( const float value );

			Colour	ambient() const;
			Colour	diffuse() const;
			Colour	specular() const;
			Colour	emission() const;
			float	shininess() const;


			void	apply() const;
			void	remove() const;
	};



	/****************************************************************************************
	*****************************************************************************************
	--------------------------------- Function Definitions ----------------------------------
	*****************************************************************************************
	****************************************************************************************/



	inline void	Material::ambient( const Colour& colour )		{ this->_ambient = colour; };
	inline void	Material::diffuse( const Colour& colour )		{ this->_diffuse = colour; };
	inline void	Material::specular( const Colour& colour )		{ this->_specular = colour; };
	inline void	Material::emission( const Colour& colour )		{ this->_emission = colour; };
	inline void	Material::shininess( const float value )		{ this->_shininess = ( value >= 0  ?  ( value <= 128  ?  value : 128 ) : 0 ); };

	inline Colour	Material::ambient() const					{ return this->_ambient; };
	inline Colour	Material::diffuse() const					{ return this->_diffuse; };
	inline Colour	Material::specular() const					{ return this->_specular; };
	inline Colour	Material::emission() const					{ return this->_emission; };
	inline float	Material::shininess() const					{ return this->_shininess; };


	inline void	Material::apply() const
	{
		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,this->_ambient.colour().get());
		glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,this->_diffuse.colour().get());
		glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,this->_specular.colour().get());
		glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,this->_emission.colour().get());
		glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,this->_shininess);
	};

	inline void	Material::remove() const
	{
		GLfloat	temp[4];



		temp[0] = temp[1] = temp[2] = 0.2f;	temp[3] = 1.0f;
		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,temp);
	
		temp[0] = temp[1] = temp[2] = 0.8f;	temp[3] = 1.0f;
		glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,temp);

		temp[0] = temp[1] = temp[2] = 0.0f;	temp[3] = 1.0f;
		glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,temp);
		glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,temp);
		glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,0.0f);
	};

};