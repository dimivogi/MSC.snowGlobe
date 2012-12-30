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

	class	Vector3f
	{
		private:

			GLfloat				_data[3];


		public:

			static const float	_V3EPSILON;

			explicit Vector3f( const GLfloat x = 0.0f , const GLfloat y = 0.0f , const GLfloat z = 0.0f );


			void				set( const GLfloat x , const GLfloat y , const GLfloat z );
			void				x( const GLfloat value );
			void				y( const GLfloat value );
			void				z( const GLfloat value );
			void				r( const GLfloat value );
			void				g( const GLfloat value );
			void				b( const GLfloat value );
			void				s( const GLfloat value );
			void				t( const GLfloat value );
			void				p( const GLfloat value );

			const GLfloat*		get() const;
			GLfloat				x() const;
			GLfloat				y() const;
			GLfloat				z() const;
			GLfloat				r() const;
			GLfloat				g() const;
			GLfloat				b() const;
			GLfloat				s() const;
			GLfloat				t() const;
			GLfloat				p() const;

		
			Vector3f&			operator+= ( const Vector3f& input );
			Vector3f&			operator-= ( const Vector3f& input );
			Vector3f&			operator*= ( const GLfloat& input );	// scale
			Vector3f&			operator^= ( const Vector3f& input );	// cross product
			Vector3f			operator+ () const;	// unary
			Vector3f			operator- () const;


			void				add( const Vector3f& input );
			void				sub( const Vector3f& input );
			void				scale( const GLfloat value );
			GLfloat				dot_product( const Vector3f&	input ) const;
			void				cross_product( const Vector3f&  input );
			GLfloat				length() const;
			void				normalize();


			void				write( ostream& out ) const;
			void				read( istream& in );
	};


	Vector3f	operator+ ( const Vector3f& input , const Vector3f& input2 );
	Vector3f	operator- ( const Vector3f& input , const Vector3f& input2 );
	Vector3f	operator^ ( const Vector3f& input , const Vector3f& input2 );	// cross product
	GLfloat		operator* ( const Vector3f& input , const Vector3f& input2 );	// dot product
	Vector3f	operator* ( const Vector3f& input , const GLfloat& input2 );
	Vector3f	operator* ( const GLfloat& input , const Vector3f& input2 );
	bool		operator== ( const Vector3f& input , const Vector3f& input2 );	// boolean
	bool		operator!= ( const Vector3f& input , const Vector3f& input2);

	ostream&	operator<< ( ostream& stream , const Vector3f& output );
	istream&	operator>> ( istream& stream , Vector3f& input );




	/****************************************************************************************
	*****************************************************************************************
	--------------------------------- Function Definitions ----------------------------------
	*****************************************************************************************
	****************************************************************************************/



	inline void				Vector3f::set( const GLfloat x , const GLfloat y , const GLfloat z )	{ this->x(x); this->y(y); this->z(z); };
	inline void				Vector3f::x( const GLfloat value )										{ this->_data[0] = value; };
	inline void				Vector3f::y( const GLfloat value )										{ this->_data[1] = value; };
	inline void				Vector3f::z( const GLfloat value )										{ this->_data[2] = value; };
	inline void				Vector3f::r( const GLfloat value )										{ this->x(value); };
	inline void				Vector3f::g( const GLfloat value )										{ this->y(value); };
	inline void				Vector3f::b( const GLfloat value )										{ this->z(value); };
	inline void				Vector3f::s( const GLfloat value )										{ this->x(value); };
	inline void				Vector3f::t( const GLfloat value )										{ this->y(value); };
	inline void				Vector3f::p( const GLfloat value )										{ this->z(value); };


	inline const GLfloat*	Vector3f::get() const													{ return this->_data; };
	inline GLfloat			Vector3f::x()  const													{ return this->_data[0]; };
	inline GLfloat			Vector3f::y() const														{ return this->_data[1]; };
	inline GLfloat			Vector3f::z() const														{ return this->_data[2]; };
	inline GLfloat			Vector3f::r() const														{ return this->x(); };
	inline GLfloat			Vector3f::g() const														{ return this->y(); };
	inline GLfloat			Vector3f::b() const														{ return this->z(); };
	inline GLfloat			Vector3f::s() const														{ return this->x(); };
	inline GLfloat			Vector3f::t() const														{ return this->y(); };
	inline GLfloat			Vector3f::p() const														{ return this->z(); };


	inline Vector3f&		Vector3f::operator+= ( const Vector3f& input )							{ this->add(input);	return *this; };
	inline Vector3f&		Vector3f::operator-= ( const Vector3f& input )							{ this->sub(input);	return *this; };
	inline Vector3f&		Vector3f::operator*= ( const GLfloat& input )							{ this->scale(input);	return *this; };
	inline Vector3f&		Vector3f::operator^= ( const Vector3f& input )							{ this->cross_product(input);	return *this; };
	inline Vector3f			Vector3f::operator+ () const											{ return *this; };
	inline Vector3f			Vector3f::operator- () const											{ return Vector3f(-this->x(),-this->y(),-this->z()); };
	inline Vector3f			operator+ ( const Vector3f& input , const Vector3f& input2 )			{ return Vector3f(input) += input2; };
	inline Vector3f			operator- ( const Vector3f& input , const Vector3f& input2 )			{ return Vector3f(input) -= input2; };
	inline Vector3f			operator^ ( const Vector3f& input , const Vector3f& input2 )			{ return Vector3f(input) ^= input2; };
	inline GLfloat			operator* ( const Vector3f& input , const Vector3f& input2 )			{ return input.dot_product(input2); };
	inline Vector3f			operator* ( const Vector3f& input , const GLfloat& input2 )				{ return Vector3f(input) *= input2; };
	inline Vector3f			operator* ( const GLfloat& input , const Vector3f& input2 )				{ return Vector3f(input2) *= input; };
	inline bool				operator== ( const Vector3f& input , const Vector3f& input2 )			{ return ( abs(input.x()-input2.x()) < Vector3f::_V3EPSILON  &&  abs(input.y()-input2.y()) < Vector3f::_V3EPSILON  &&  abs(input.z()-input2.z()) < Vector3f::_V3EPSILON ); };
	inline bool				operator!= ( const Vector3f& input , const Vector3f& input2)			{ return ( abs(input.x()-input2.x()) > Vector3f::_V3EPSILON  ||  abs(input.y()-input2.y()) > Vector3f::_V3EPSILON  ||  abs(input.z()-input2.z()) > Vector3f::_V3EPSILON ); };


	inline void				Vector3f::add( const Vector3f& input )
	{
		this->x(this->x() + input.x());
		this->y(this->y() + input.y());
		this->z(this->z() + input.z());
	};

	inline void				Vector3f::sub( const Vector3f& input )
	{
		this->x(this->x() - input.x());
		this->y(this->y() - input.y());
		this->z(this->z() - input.z());
	};

	inline void				Vector3f::scale( const GLfloat value )
	{
		this->x(this->x() * value);
		this->y(this->y() * value);
		this->z(this->z() * value);
	};

	inline GLfloat			Vector3f::dot_product( const Vector3f&	input ) const					{ return ( this->x()*input.x() + this->y()*input.y() + this->z()*input.z() ); };
	inline void				Vector3f::cross_product( const Vector3f& input )
	{
		GLfloat	x;
		GLfloat	y;
		GLfloat	z;



		x = this->y()*input.z() - this->z()*input.y();
		y = this->z()*input.x() - this->x()*input.z();
		z = this->x()*input.y() - this->y()*input.x();

		this->x(x);
		this->y(y);
		this->z(z);
	};

	inline GLfloat			Vector3f::length() const												{ return sqrt(this->dot_product(*this)); };
	inline void				Vector3f::normalize()
	{
		GLfloat			length = this->length();



		if ( length > 0 )
			this->scale(1.0f/length);
	}


	inline void					Vector3f::write( ostream& out ) const								{ out	<< "(" << this->x() << "," << this->y() << "," << this->z() << ")"; };
	inline void					Vector3f::read( istream& in )
	{
		char	temp;
		GLfloat	temp1 , temp2 , temp3;



		in	>> temp >> temp1 >> temp >> temp2 >> temp >> temp3 >> temp;
		this->x(temp1);
		this->y(temp2);
		this->z(temp3);
	}

	inline ostream&		operator<< ( ostream& stream , const Vector3f& output )						{ output.write(stream);	return stream; };
	inline istream&		operator>> ( istream& stream , Vector3f& input )							{ input.read(stream);	return stream; };

};