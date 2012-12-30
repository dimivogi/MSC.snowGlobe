#pragma	once

#ifndef	NOMINMAX
	#define	NOMINMAX
#endif
#include	<iostream>
#include	"GXBase.h"

using		namespace std;



namespace	Globe
{
	/****************************************************************************************
	*****************************************************************************************
	------------------------------------ Vector3f Class -------------------------------------
	*****************************************************************************************
	****************************************************************************************/

	class	Vector4f
	{
		private:

			GLfloat				_data[4];


		public:

			static const float	_V4EPSILON;


			explicit Vector4f( const GLfloat x = 0.0f , const GLfloat y = 0.0f , const GLfloat z = 0.0f , const GLfloat w = 0.0f );


			void				set( const GLfloat x , const GLfloat y , const GLfloat z , const GLfloat w );
			void				x( const GLfloat value );
			void				y( const GLfloat value );
			void				z( const GLfloat value );
			void				w( const GLfloat value );
			void				r( const GLfloat value );
			void				g( const GLfloat value );
			void				b( const GLfloat value );
			void				a( const GLfloat value );
			void				s( const GLfloat value );
			void				t( const GLfloat value );
			void				p( const GLfloat value );
			void				q( const GLfloat value );

			const GLfloat*		get() const;
			GLfloat				x() const;
			GLfloat				y() const;
			GLfloat				z() const;
			GLfloat				w() const;
			GLfloat				r() const;
			GLfloat				g() const;
			GLfloat				b() const;
			GLfloat				a() const;
			GLfloat				s() const;
			GLfloat				t() const;
			GLfloat				p() const;
			GLfloat				q() const;

		
			Vector4f&			operator+= ( const Vector4f& input );
			Vector4f&			operator-= ( const Vector4f& input );
			Vector4f&			operator*= ( const GLfloat& input );	// scale
			Vector4f			operator+ () const;	// unary
			Vector4f			operator- () const;


			void				add( const Vector4f& input );
			void				sub( const Vector4f& input );
			void				scale( const GLfloat value );
			GLfloat				dot_product( const Vector4f&	input ) const;
			GLfloat				length() const;
			void				normalize();


			void				write( ostream& out ) const;
			void				read( istream& in );
	};


	Vector4f	operator+ ( const Vector4f& input , const Vector4f& input2 );
	Vector4f	operator- ( const Vector4f& input , const Vector4f& input2 );
	GLfloat		operator* ( const Vector4f& input , const Vector4f& input2 );	// dot product
	Vector4f	operator* ( const Vector4f& input , const GLfloat& input2 );
	Vector4f	operator* ( const GLfloat& input , const Vector4f& input2 );
	bool		operator== ( const Vector4f& input , const Vector4f& input2 );	// boolean
	bool		operator!= ( const Vector4f& input , const Vector4f& input2);

	ostream&	operator<< ( ostream& stream , const Vector4f& output );
	istream&	operator>> ( istream& stream , Vector4f& input );




	/****************************************************************************************
	*****************************************************************************************
	--------------------------------- Function Definitions ----------------------------------
	*****************************************************************************************
	****************************************************************************************/



	inline void				Vector4f::set( const GLfloat x , const GLfloat y , const GLfloat z , const GLfloat w )	{ this->x(x); this->y(y); this->z(z); this->w(w); };
	inline void				Vector4f::x( const GLfloat value )														{ this->_data[0] = value; };
	inline void				Vector4f::y( const GLfloat value )														{ this->_data[1] = value; };
	inline void				Vector4f::z( const GLfloat value )														{ this->_data[2] = value; };
	inline void				Vector4f::w( const GLfloat value )														{ this->_data[3] = value; };
	inline void				Vector4f::r( const GLfloat value )														{ this->x(value); };
	inline void				Vector4f::g( const GLfloat value )														{ this->y(value); };
	inline void				Vector4f::b( const GLfloat value )														{ this->z(value); };
	inline void				Vector4f::a( const GLfloat value )														{ this->w(value); };
	inline void				Vector4f::s( const GLfloat value )														{ this->x(value); };
	inline void				Vector4f::t( const GLfloat value )														{ this->y(value); };
	inline void				Vector4f::p( const GLfloat value )														{ this->z(value); };
	inline void				Vector4f::q( const GLfloat value )														{ this->w(value); };


	inline const GLfloat*	Vector4f::get() const																	{ return this->_data; };
	inline GLfloat			Vector4f::x()  const																	{ return this->_data[0]; };
	inline GLfloat			Vector4f::y() const																		{ return this->_data[1]; };
	inline GLfloat			Vector4f::z() const																		{ return this->_data[2]; };
	inline GLfloat			Vector4f::w() const																		{ return this->_data[3]; };
	inline GLfloat			Vector4f::r() const																		{ return this->x(); };
	inline GLfloat			Vector4f::g() const																		{ return this->y(); };
	inline GLfloat			Vector4f::b() const																		{ return this->z(); };
	inline GLfloat			Vector4f::a() const																		{ return this->w(); };
	inline GLfloat			Vector4f::s() const																		{ return this->x(); };
	inline GLfloat			Vector4f::t() const																		{ return this->y(); };
	inline GLfloat			Vector4f::p() const																		{ return this->z(); };
	inline GLfloat			Vector4f::q() const																		{ return this->w(); };


	inline Vector4f&		Vector4f::operator+= ( const Vector4f& input )											{ this->add(input);	return *this; };
	inline Vector4f&		Vector4f::operator-= ( const Vector4f& input )											{ this->sub(input);	return *this; };
	inline Vector4f&		Vector4f::operator*= ( const GLfloat& input )											{ this->scale(input);	return *this; };
	inline Vector4f			Vector4f::operator+ () const															{ return *this; };
	inline Vector4f			Vector4f::operator- () const															{ return Vector4f(-this->x(),-this->y(),-this->z(),-this->w()); };
	inline Vector4f			operator+ ( const Vector4f& input , const Vector4f& input2 )							{ return Vector4f(input) += input2; };
	inline Vector4f			operator- ( const Vector4f& input , const Vector4f& input2 )							{ return Vector4f(input) -= input2; };
	inline GLfloat			operator* ( const Vector4f& input , const Vector4f& input2 )							{ return input.dot_product(input2); };
	inline Vector4f			operator* ( const Vector4f& input , const GLfloat& input2 )								{ return Vector4f(input) *= input2; };
	inline Vector4f			operator* ( const GLfloat& input , const Vector4f& input2 )								{ return Vector4f(input2) *= input; };
	inline bool				operator== ( const Vector4f& input , const Vector4f& input2 )							{ return ( abs(input.x()-input2.x()) < Vector4f::_V4EPSILON  &&  abs(input.y()-input2.y()) < Vector4f::_V4EPSILON  &&  abs(input.z()-input2.z()) < Vector4f::_V4EPSILON  &&  abs(input.w()-input2.w()) < Vector4f::_V4EPSILON); };
	inline bool				operator!= ( const Vector4f& input , const Vector4f& input2)							{ return ( abs(input.x()-input2.x()) > Vector4f::_V4EPSILON  ||  abs(input.y()-input2.y()) > Vector4f::_V4EPSILON  ||  abs(input.z()-input2.z()) > Vector4f::_V4EPSILON  ||  abs(input.w()-input2.w()) > Vector4f::_V4EPSILON); };


	inline void				Vector4f::add( const Vector4f& input )
	{
		this->x(this->x() + input.x());
		this->y(this->y() + input.y());
		this->z(this->z() + input.z());
		this->w(this->w() + input.w());
	};

	inline void				Vector4f::sub( const Vector4f& input )
	{
		this->x(this->x() - input.x());
		this->y(this->y() - input.y());
		this->z(this->z() - input.z());
		this->w(this->w() - input.w());
	};

	inline void				Vector4f::scale( const GLfloat value )
	{
		this->x(this->x() * value);
		this->y(this->y() * value);
		this->z(this->z() * value);
		this->w(this->w() * value);
	};

	inline GLfloat			Vector4f::dot_product( const Vector4f&	input ) const									{ return ( this->x()*input.x() + this->y()*input.y() + this->z()*input.z() + this->w()*input.w() ); };

	inline GLfloat			Vector4f::length() const																{ return sqrt(this->dot_product(*this)); };
	inline void				Vector4f::normalize()
	{
		GLfloat			length = this->length();



		if ( length > 0 )
			this->scale(1.0f/length);
	}


	inline void					Vector4f::write( ostream& out ) const												{ out	<< "(" << this->x() << "," << this->y() << "," << this->z() << "," << this->w() << ")"; };
	inline void					Vector4f::read( istream& in )
	{
		char	temp;
		GLfloat	temp1 , temp2 , temp3 , temp4;



		in	>> temp >> temp1 >> temp >> temp2 >> temp >> temp3 >> temp >> temp4 >> temp;
		this->x(temp1);
		this->y(temp2);
		this->z(temp3);
		this->w(temp4);
	}

	inline ostream&		operator<< ( ostream& stream , const Vector4f& output )										{ output.write(stream);	return stream; };
	inline istream&		operator>> ( istream& stream , Vector4f& input )											{ input.read(stream);	return stream; };

};