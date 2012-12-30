#pragma	once

#include	"..\Vector\Vector3f.h"
#include	"..\Vector\Vector4f.h"



namespace	Globe
{
	/****************************************************************************************
	*****************************************************************************************
	----------------------------------- Matrix4x4f Class ------------------------------------
	*****************************************************************************************
	****************************************************************************************/

	class	Matrix4x4f
	{
		private:

			GLfloat		_data[16];


		public:

			explicit Matrix4x4f(	const GLfloat c0 = 0.0f , const GLfloat c4 = 0.0f , const GLfloat c8 = 0.0f , const GLfloat c12 = 0.0f ,
								const GLfloat c1 = 0.0f , const GLfloat c5 = 0.0f , const GLfloat c9 = 0.0f , const GLfloat c13 = 0.0f , 
								const GLfloat c2 = 0.0f , const GLfloat c6 = 0.0f , const GLfloat c10 = 0.0f , const GLfloat c14 = 0.0f ,
								const GLfloat c3 = 0.0f , const GLfloat c7 = 0.0f , const GLfloat c11 = 0.0f , const GLfloat c15 = 0.0f );
			explicit Matrix4x4f( const Vector4f& r0 , const Vector4f& r1 = Vector4f(0.0f,0.0f,0.0f,0.0f) , 
								const Vector4f& r2 = Vector4f(0.0f,0.0f,0.0f,0.0f) , const Vector4f& r3 = Vector4f(0.0f,0.0f,0.0f,0.0f) );


			Matrix4x4f		operator+() const;
			Matrix4x4f		operator-() const;
			const GLfloat&	operator[]( const unsigned int index) const;
			Matrix4x4f&		operator+=( const Matrix4x4f& matrix );
			Matrix4x4f&		operator-=( const Matrix4x4f& matrix );
			Matrix4x4f&		operator*=( const GLfloat value );
			Matrix4x4f&		operator*=( const Matrix4x4f& matrix );


			void			set(	const GLfloat c0 , const GLfloat c4 , const GLfloat c8 , const GLfloat c12 ,
									const GLfloat c1 , const GLfloat c5 , const GLfloat c9 , const GLfloat c13 , 
									const GLfloat c2 , const GLfloat c6 , const GLfloat c10 , const GLfloat c14 ,
									const GLfloat c3 , const GLfloat c7 , const GLfloat c11 , const GLfloat c15 );
			void			set( const Vector4f& r0 , const Vector4f& r1 , const Vector4f& r2 , const Vector4f& r3 );
			void			row( const unsigned int row , const Vector4f& value );

			const GLfloat*	get() const;
			void			get(	GLfloat& c0 , GLfloat& c4 , GLfloat& c8 , GLfloat& c12 ,
									GLfloat& c1 , GLfloat& c5 , GLfloat& c9 , GLfloat& c13 , 
									GLfloat& c2 , GLfloat& c6 , GLfloat& c10 , GLfloat& c14 ,
									GLfloat& c3 , GLfloat& c7 , GLfloat& c11 , GLfloat& c15 ) const;
			void			get( Vector4f& r0 , Vector4f& r1 , Vector4f&r2 , Vector4f& r3 ) const;
			Vector4f		row( const unsigned int row ) const;


			GLfloat			determinant() const;
			void			add( const Matrix4x4f& matrix );
			void			subtract( const Matrix4x4f& matrix );
			void			multiply( const GLfloat value );
			Vector3f		multiply( const Vector3f& vector ) const;
			Vector4f		multiply( const Vector4f& vector ) const;
			void			multiply( const Matrix4x4f& matrix );


			void			identity();
			void			inverse();
			void			rotate( const GLfloat angle , const GLfloat x , const GLfloat y , const GLfloat z );
			void			rotate( const GLfloat angle , const Vector3f& axices );
			void			translate( const GLfloat x , const GLfloat y , const GLfloat z );
			void			translate( const Vector3f& translation );
			void			scale( const GLfloat x , const GLfloat y , const GLfloat z );
			void			scale( const Vector3f& axices );

			void			loadGL( const GLenum& matrix );
	};

	Matrix4x4f	operator+( const Matrix4x4f& matrix1 , const Matrix4x4f& matrix2 ); 
	Matrix4x4f	operator-( const Matrix4x4f& matrix1 , const Matrix4x4f& matrix2 );
	Matrix4x4f	operator*( const Matrix4x4f& matrix , const GLfloat value );
	Matrix4x4f	operator*( const GLfloat value , const Matrix4x4f& matrix );
	Vector4f	operator*( const Matrix4x4f& matrix , const Vector4f& vector );
	Vector4f	operator*( const Vector4f& vector , const Matrix4x4f& matrix );
	Vector3f	operator*( const Matrix4x4f& matrix , const Vector3f& vector );
	Vector3f	operator*( const Vector3f& vector , const Matrix4x4f& matrix );
	Matrix4x4f	operator*( const Matrix4x4f& matrix1 , const Matrix4x4f& matrix2 );



	/****************************************************************************************
	*****************************************************************************************
	--------------------------------- Function Definitions ----------------------------------
	*****************************************************************************************
	****************************************************************************************/


	inline Matrix4x4f	Matrix4x4f::operator+() const										{ return *this; };
	inline Matrix4x4f	Matrix4x4f::operator-() const
	{
		Vector4f	r0 , r1 , r2 , r3;



		this->get(r0,r1,r2,r3);


		return Matrix4x4f(-r0,-r1,-r2,-r3);
	};

	inline const GLfloat&	Matrix4x4f::operator[]( const unsigned int index) const			{ return this->_data[index]; };

	inline Matrix4x4f&	Matrix4x4f::operator+=( const Matrix4x4f& matrix )					{ this->add(matrix);	return *this; };
	inline Matrix4x4f&	Matrix4x4f::operator-=( const Matrix4x4f& matrix )					{ this->subtract(matrix);	return *this; };
	inline Matrix4x4f&	Matrix4x4f::operator*=( const Matrix4x4f& matrix )					{ this->multiply(matrix);	return *this; };
	inline Matrix4x4f&	Matrix4x4f::operator*=( const GLfloat value )						{ this->multiply(value);	return *this; };

	inline Matrix4x4f	operator+( const Matrix4x4f& matrix1 , const Matrix4x4f& matrix2 )	{ return Matrix4x4f(matrix1) += matrix2; };
	inline Matrix4x4f	operator-( const Matrix4x4f& matrix1 , const Matrix4x4f& matrix2 )	{ return Matrix4x4f(matrix1) -= matrix2; };
	inline Matrix4x4f	operator*( const Matrix4x4f& matrix , const GLfloat value )			{ return Matrix4x4f(matrix) *= value; };
	inline Matrix4x4f	operator*( const GLfloat value , const Matrix4x4f& matrix )			{ return Matrix4x4f(matrix) *= value; };
	inline Vector4f		operator*( const Matrix4x4f& matrix , const Vector4f& vector )		{ return matrix.multiply(vector); };
	inline Vector4f		operator*( const Vector4f& vector , const Matrix4x4f& matrix )		{ return matrix.multiply(vector); };
	inline Vector3f		operator*( const Matrix4x4f& matrix , const Vector3f& vector )		{ return matrix.multiply(vector); };
	inline Vector3f		operator*( const Vector3f& vector , const Matrix4x4f& matrix )		{ return matrix.multiply(vector); };
	inline Matrix4x4f	operator*( const Matrix4x4f& matrix1 , const Matrix4x4f& matrix2 )	{ return Matrix4x4f(matrix1) *= matrix2; };


	inline void		Matrix4x4f::set(	const GLfloat c0 , const GLfloat c4 , const GLfloat c8 , const GLfloat c12 ,
						const GLfloat c1 , const GLfloat c5 , const GLfloat c9 , const GLfloat c13 , 
						const GLfloat c2 , const GLfloat c6 , const GLfloat c10 , const GLfloat c14 ,
						const GLfloat c3 , const GLfloat c7 , const GLfloat c11 , const GLfloat c15 )
	{
		this->_data[0] = c0;	this->_data[4] = c4;	this->_data[8] = c8;	this->_data[12] = c12;
		this->_data[1] = c1;	this->_data[5] = c5;	this->_data[9] = c9;	this->_data[13] = c13;
		this->_data[2] = c2;	this->_data[6] = c6;	this->_data[10] = c10;	this->_data[14] = c14;
		this->_data[3] = c3;	this->_data[7] = c7;	this->_data[11] = c11;	this->_data[15] = c15;
	};
	inline void		Matrix4x4f::set( const Vector4f& r0 , const Vector4f& r1 , const Vector4f& r2 , const Vector4f& r3 )
	{
		this->set(	r0.x(),r0.y(),r0.z(),r0.w(),
					r1.x(),r1.y(),r1.z(),r1.w(),
					r2.x(),r2.y(),r2.z(),r2.w(),
					r3.x(),r3.y(),r3.z(),r3.w());
	}
	inline void		Matrix4x4f::row( const unsigned int row , const Vector4f& value )
	{
		if ( row == 0 )
		{
			this->_data[0] = value.x();	this->_data[4] = value.y();	this->_data[8] = value.z();	this->_data[12] = value.w();
		}
		else if ( row == 1 )
		{
			this->_data[1] = value.x();	this->_data[5] = value.y();	this->_data[9] = value.z();	this->_data[13] = value.w();
		}
		else if ( row == 2 )
		{
			this->_data[2] = value.x();	this->_data[6] = value.y();	this->_data[10] = value.z();	this->_data[14] = value.w();
		}
		else if ( row == 3 )
		{
			this->_data[3] = value.x();	this->_data[7] = value.y();	this->_data[11] = value.z();	this->_data[15] = value.w();
		}
	}

	inline const GLfloat*	Matrix4x4f::get() const	{ return this->_data; };
	inline void		Matrix4x4f::get(	GLfloat& c0 , GLfloat& c4 , GLfloat& c8 , GLfloat& c12 ,
						GLfloat& c1 , GLfloat& c5 , GLfloat& c9 , GLfloat& c13 , 
						GLfloat& c2 , GLfloat& c6 , GLfloat& c10 , GLfloat& c14 ,
						GLfloat& c3 , GLfloat& c7 , GLfloat& c11 , GLfloat& c15 ) const
	{
		c0 = this->_data[0];	c4 = this->_data[4];	c8 = this->_data[8];	c12 = this->_data[12];
		c1 = this->_data[1];	c5 = this->_data[5];	c9 = this->_data[9];	c13 = this->_data[13];
		c2 = this->_data[2];	c6 = this->_data[6];	c10 = this->_data[10];	c14 = this->_data[14];
		c3 = this->_data[3];	c7 = this->_data[7];	c11 = this->_data[11];	c15 = this->_data[15];
	};
	inline void		Matrix4x4f::get( Vector4f& r0 , Vector4f& r1 , Vector4f&r2 , Vector4f& r3 ) const
	{
		r0.set(this->_data[0],this->_data[4],this->_data[8],this->_data[12]);
		r1.set(this->_data[1],this->_data[5],this->_data[9],this->_data[13]);
		r2.set(this->_data[2],this->_data[6],this->_data[10],this->_data[14]);
		r3.set(this->_data[3],this->_data[7],this->_data[11],this->_data[15]);
	};
	inline Vector4f	Matrix4x4f::row( const unsigned int row ) const
	{
		if ( row == 0 )
			return Vector4f(this->_data[0],this->_data[4],this->_data[8],this->_data[12]);
		else if ( row == 1 )
			return Vector4f(this->_data[1],this->_data[5],this->_data[9],this->_data[13]);
		else if ( row == 2 )
			return Vector4f(this->_data[2],this->_data[6],this->_data[10],this->_data[14]);
		else if ( row == 3 )
			return Vector4f(this->_data[3],this->_data[7],this->_data[11],this->_data[15]);
		else
			return Vector4f(0.0f,0.0f,0.0f,0.0f);
	}


	

	inline Vector3f	Matrix4x4f::multiply( const Vector3f& vector ) const
	{
		Vector4f	temp(this->multiply(Vector4f(vector.x(),vector.y(),vector.z(),1.0f)));



		return Vector3f(temp.x()/temp.w(),temp.y()/temp.w(),temp.z()/temp.w());
	};

	

	inline void		Matrix4x4f::inverse()
	{
		GLfloat	determinant = this->determinant();



		this->set(	this->_data[0] , this->_data[1] , this->_data[2],this->_data[3],
					this->_data[4] , this->_data[5] , this->_data[6],this->_data[7],
					this->_data[8] , this->_data[9] , this->_data[10],this->_data[11],
					this->_data[12] , this->_data[13] , this->_data[14],this->_data[15] );
		this->multiply(determinant);
	};

	inline void		Matrix4x4f::rotate( const GLfloat angle , const GLfloat x , const GLfloat y , const GLfloat z )
	{
		this->rotate(angle,Vector3f(x,y,z));
	};

	inline void		Matrix4x4f::rotate( const GLfloat angle , const Vector3f& axices )
	{
		Vector3f	v(axices);
		GLfloat		rad_angle = 0.0174532925f * angle;
		GLfloat		rot_cos = cos(rad_angle);
		GLfloat		rot_sin = sin(rad_angle);



		if ( v.length() > 1.0f )
			v.normalize();
	
		this->multiply(Matrix4x4f(	v.x()*v.x()*(1-rot_cos) + rot_cos , v.x()*v.y()*(1-rot_cos) - v.z()*rot_sin , v.x()*v.z()*(1-rot_cos) + v.y()*rot_sin , 0.0f ,
							v.y()*v.x()*(1-rot_cos) + v.z()*rot_sin , v.y()*v.y()*(1-rot_cos) + rot_cos , v.y()*v.z()*(1-rot_cos) - v.x()*rot_sin , 0.0f , 
							v.x()*v.z()*(1-rot_cos) - v.y()*rot_sin , v.y()*v.z()*(1-rot_cos) + v.x()*rot_sin , v.z()*v.z()*(1-rot_cos) + rot_cos , 0.0f , 
							0.0f , 0.0f , 0.0f , 1.0f ));
	};

	inline void		Matrix4x4f::translate( const GLfloat x , const GLfloat y , const GLfloat z )
	{
		this->multiply(Matrix4x4f(	1.0f,0.0f,0.0f,x,
							0.0f,1.0f,0.0f,y,
							0.0f,0.0f,1.0f,z,
							0.0f,0.0f,0.0f,1.0f));
	};

	inline void		Matrix4x4f::translate( const Vector3f& translation )
	{
		this->translate(translation.x(),translation.y(),translation.z());
	}
	inline void		Matrix4x4f::scale( const GLfloat x , const GLfloat y , const GLfloat z )
	{
		this->multiply(Matrix4x4f(	x,0.0f,0.0f,0.0f,
							0.0f,y,0.0f,0.0f,
							0.0f,0.0f,z,0.0f,
							0.0f,0.0f,0.0f,1.0f));
	};

	inline void		Matrix4x4f::scale( const Vector3f& axices )
	{
		this->scale(axices.x(),axices.y(),axices.z());
	};

	inline void		Matrix4x4f::loadGL( const GLenum& matrix )
	{
		glGetFloatv(matrix,this->_data);
	};
};