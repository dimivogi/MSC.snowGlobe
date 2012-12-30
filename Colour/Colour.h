#pragma	once

#include	"..\Vector\Vector3f.h"
#include	"..\Vector\Vector4f.h"
#include	<iomanip>



namespace	Globe
{
	/****************************************************************************************
	*****************************************************************************************
	------------------------------------- Colour Class --------------------------------------
	*****************************************************************************************
	****************************************************************************************/

	class	Colour
	{
		private:

			GLfloat					_colour[4];


		public:

			static Colour			colour_null();
			static Colour			colour_black();
			static Colour			colour_red();
			static Colour			colour_green();
			static Colour			colour_blue();
			static Colour			colour_yellow();
			static Colour			colour_purple();
			static Colour			colour_teal();
			static Colour			colour_white();


			explicit Colour( const GLfloat red = 0.0f , const GLfloat green = 0.0f , const GLfloat blue = 0.0f , const GLfloat alpha = 1.0 );
			explicit Colour( const Vector3f& input );
			explicit Colour( const Vector4f& input );


			void					colour( const GLfloat red , const GLfloat green , const GLfloat blue , const GLfloat alpha = 1.0f );
			void					colour( const Vector3f& values );
			void					colour( const Vector4f& values );
			void					red( const GLfloat value );
			void					green( const GLfloat value );
			void					blue( const GLfloat value );
			void					alpha( const GLfloat value );

			Vector3f				colour_only() const;
			Vector4f				colour() const;
			GLfloat					red() const;
			GLfloat					green() const;
			GLfloat					blue() const;
			GLfloat					alpha() const;
			int						hex() const;

			void					set_colour_black();
			void					set_colour_red();
			void					set_colour_green();
			void					set_colour_blue();
			void					set_colour_yellow();
			void					set_colour_purple();
			void					set_colour_teal();
			void					set_colour_white();
			void					set_transparent();
			void					set_visible();


			void					write( ostream& out ) const; 
			void					read( istream& in );
			friend std::ostream&	operator<<( ostream& stream , const Colour& input );
			friend std::istream&	operator>>( istream& stream , Colour& input );
	};



	/****************************************************************************************
	*****************************************************************************************
	--------------------------------- Function Definitions ----------------------------------
	*****************************************************************************************
	****************************************************************************************/


	inline Colour	Colour::colour_null()		{ return Colour(0.0f,0.0f,0.0f,0.0f); };
	inline Colour	Colour::colour_black()		{ return Colour(0.0f,0.0f,0.0f,1.0f); };
	inline Colour	Colour::colour_red()		{ return Colour(1.0f,0.0f,0.0f,1.0f); };
	inline Colour	Colour::colour_green()		{ return Colour(0.0f,1.0f,0.0f,1.0f); };
	inline Colour	Colour::colour_blue()		{ return Colour(0.0f,0.0f,1.0f,1.0f); };
	inline Colour	Colour::colour_yellow()		{ return Colour(1.0f,1.0f,0.0f,1.0f); };
	inline Colour	Colour::colour_purple()		{ return Colour(1.0f,0.0f,1.0f,1.0f); };
	inline Colour	Colour::colour_teal()		{ return Colour(0.0f,1.0f,1.0f,1.0f); };
	inline Colour	Colour::colour_white()		{ return Colour(1.0f,1.0f,1.0f,1.0f); };


	inline void	Colour::colour( const GLfloat red , const GLfloat green , const GLfloat blue , const GLfloat alpha )
	{
		this->red(red);
		this->green(green);
		this->blue(blue);
		this->alpha(alpha);
	};

	inline void	Colour::colour( const Vector3f& values )
	{
		this->red(values.r());
		this->green(values.g());
		this->blue(values.b());
	};

	inline void	Colour::colour( const Vector4f& values ) 
	{
		this->red(values.r());
		this->green(values.g());
		this->blue(values.b());
		this->alpha(values.a());
	};

	inline void	Colour::red( const GLfloat value )
	{
		if ( value < 0 )
			this->_colour[0] = 0.0f;
		else if ( value > 1.0f )
			this->_colour[0] = 1.0f;
		else
			this->_colour[0] = value;
	};


	inline void	Colour::green( const GLfloat value )
	{
		if ( value < 0 )
			this->_colour[1] = 0.0f;
		else if ( value > 1.0f )
			this->_colour[1] = 1.0f;
		else
			this->_colour[1] = value;
	};

	inline void	Colour::blue( const GLfloat value )
	{
		if ( value < 0 )
			this->_colour[2] = 0.0f;
		else if ( value > 1.0f )
			this->_colour[2] = 1.0f;
		else
			this->_colour[2] = value;
	};

	inline void	Colour::alpha( const GLfloat value )
	{
		if ( value < 0 )
			this->_colour[3] = 0.0f;
		else if ( value > 1.0f )
			this->_colour[3] = 1.0f;
		else
			this->_colour[3] = value;
	};


	inline Vector3f	Colour::colour_only() const																	{ return Vector3f(this->red(),this->green(),this->blue()); };
	inline Vector4f	Colour::colour() const																		{ return Vector4f(this->red(),this->green(),this->blue(),this->alpha()); };
	inline GLfloat	Colour::red() const																			{ return this->_colour[0]; };
	inline GLfloat	Colour::green() const																		{ return this->_colour[1]; };
	inline GLfloat	Colour::blue() const																		{ return this->_colour[2]; };
	inline GLfloat	Colour::alpha() const																		{ return this->_colour[3]; };
	inline int		Colour::hex() const
	{
		int		colour = 0;



		colour = ( static_cast<int>(ceil((this->red()*255))) << 24 );
		colour |= ( static_cast<int>(ceil((this->green()*255))) << 16 );
		colour |= ( static_cast<int>(ceil((this->blue()*255))) << 8 );
		colour |= static_cast<int>(ceil((this->alpha()*255)));


		return colour;
	};


	inline void	Colour::set_colour_black()																		{ this->colour(0.0f,0.0f,0.0f); };
	inline void	Colour::set_colour_red()																		{ this->colour(1.0f,0.0f,0.0f); };
	inline void	Colour::set_colour_green()																		{ this->colour(0.0f,1.0f,0.0f); };
	inline void	Colour::set_colour_blue()																		{ this->colour(0.0f,0.0f,1.0f); };
	inline void	Colour::set_colour_yellow()																		{ this->colour(1.0f,1.0f,0.0f); };
	inline void	Colour::set_colour_purple()																		{ this->colour(1.0f,0.0f,1.0f); };
	inline void	Colour::set_colour_teal()																		{ this->colour(0.0f,1.0f,1.0f); };
	inline void	Colour::set_colour_white()																		{ this->colour(1.0f,1.0f,1.0f); };
	inline void	Colour::set_transparent()																		{ this->alpha(0.0f); };
	inline void	Colour::set_visible()																			{ this->alpha(1.0f); };


	inline void	Colour::write( ostream& out ) const
	{
		if ( out.flags() & ostream::hex )
		{
			streamsize	width = out.width();
			char		fill = out.fill();



			out	<< "0x" << std::setfill('0') << std::setw(8) <<  this->hex() << std::setw(width) << std::setfill(fill);
		}
		else
			out	<< "(" << this->red() << "," << this->green() << "," << this->blue() << "," << this->alpha() << ")";
	};

	inline void	Colour::read( istream& in )
	{
		char	temp;
		GLfloat	temp1 , temp2 , temp3 , temp4;



		// read in a (r,g,b,a) format
		in	>> temp >> temp1 >> temp >> temp2 >> temp >> temp3 >> temp >> temp4 >> temp;
		this->colour(temp1,temp2,temp3,temp4);
	};

	inline std::ostream&	operator<<( std::ostream& stream , const Colour& input )							{ input.write(stream);	return stream; };
	inline std::istream&	operator>>( std::istream& stream , Colour& input )									{ input.read(stream);	return stream; };

};