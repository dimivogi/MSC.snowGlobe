#include	"Matrix4x4f.h"

using		namespace Globe;



Matrix4x4f::Matrix4x4f(	const GLfloat c0 , const GLfloat c4 , const GLfloat c8 , const GLfloat c12 ,
						const GLfloat c1 , const GLfloat c5 , const GLfloat c9 , const GLfloat c13 , 
						const GLfloat c2 , const GLfloat c6 , const GLfloat c10 , const GLfloat c14 ,
						const GLfloat c3 , const GLfloat c7 , const GLfloat c11 , const GLfloat c15 )
{ this->set(c0,c4,c8,c12,c1,c5,c9,c13,c2,c6,c10,c14,c3,c7,c11,c15); };

Matrix4x4f::Matrix4x4f(	const Vector4f& r0 , const Vector4f& r1 , const Vector4f& r2 , const Vector4f& r3 )	
{ this->set(r0,r1,r2,r3); };


GLfloat	Matrix4x4f::determinant() const
{
	GLfloat	sign = -1.0f;
	GLfloat	returnValue = 0.0f;



	for ( unsigned int i = 0;  i < 4;  ++i )
	{
		GLfloat	sign2 = -1.0f;


		sign *= -1.0f;
		this->_data[i*4];
		for ( unsigned int j = 0;  j < 4;  ++j )
		{
			if ( j != i )
			{
				GLfloat	temp[4];
				unsigned int	l = 0;


				this->_data[ 1 + j*4];
				sign2 *= -1.0f;
				for ( unsigned int k = 0;  k < 4;  ++k )
				{
					if ( k != i   &&  k != j )
					{
						temp[l*2] = this->_data[2 + k*4];
						temp[l*2 + 1] = this->_data[3 + k*4];
						++l;
					}
				}

				returnValue += sign * sign2 *this->_data[i*4] * this->_data[1+j*4] * (temp[0]*temp[3] - temp[1]*temp[2]);
			}
		}
	};


	return returnValue;
};

void		Matrix4x4f::add( const Matrix4x4f& matrix )
{
	GLfloat	m[16];



	matrix.get(m[0],m[4],m[8],m[12],m[1],m[5],m[9],m[13],m[2],m[6],m[10],m[14],m[3],m[7],m[11],m[15]);

	for ( unsigned int i = 0;  i < 4;  ++i )
	{
		for ( unsigned int j = 0;  j < 4;  ++j )
			this->_data[i+j*4] += m[i+j*4];
	}
};

void		Matrix4x4f::subtract( const Matrix4x4f& matrix )
{
	GLfloat	m[16];



	matrix.get(m[0],m[4],m[8],m[12],m[1],m[5],m[9],m[13],m[2],m[6],m[10],m[14],m[3],m[7],m[11],m[15]);

	for ( unsigned int i = 0;  i < 4;  ++i )
	{
		for ( unsigned int j = 0;  j < 4;  ++j )
			this->_data[i+j*4] -= m[i+j*4];
	}
};

void		Matrix4x4f::multiply( const GLfloat value )
{
	for ( unsigned int i = 0;  i < 4;  ++i )
	{
		for ( unsigned int j = 0;  j < 4;  ++j )
			this->_data[i+j*4] *= value;
	} 
};

Vector4f	Matrix4x4f::multiply( const Vector4f& vector ) const
{
	GLfloat	m[4];
	GLfloat	temp[4];



	m[0] = vector.x();	m[1] = vector.y();	m[2] = vector.z();	m[3] = vector.w();

	for ( unsigned int i = 0;  i < 4;  ++i )
	{
		temp[i] = 0.0f;

		for ( unsigned int j = 0;  j < 4;  ++j )
			temp[i] += this->_data[i+j*4] * m[j];
	}


	return Vector4f(temp[0],temp[1],temp[2],temp[3]);
};

void		Matrix4x4f::multiply( const Matrix4x4f& matrix )
{
	GLfloat	m[16];
	GLfloat	temp[16];



	matrix.get(m[0],m[4],m[8],m[12],m[1],m[5],m[9],m[13],m[2],m[6],m[10],m[14],m[3],m[7],m[11],m[15]);

	for ( unsigned int i = 0;  i < 4;  ++i )
	{
		for ( unsigned int j = 0;  j < 4;  ++j )
		{
			temp[i+j*4] = 0;

			for ( unsigned int k = 0;  k < 4;  ++k )
				temp[i+j*4] += this->_data[i + k*4] * m[k+j*4];

		}
	}

	this->set(temp[0],temp[4],temp[8],temp[12],
			temp[1],temp[5],temp[9],temp[13],
			temp[2],temp[6],temp[10],temp[14],
			temp[3],temp[7],temp[11],temp[15]);
};


void		Matrix4x4f::identity()
{
	for ( unsigned int i = 0;  i < 4;  ++i )
	{
		for ( unsigned int j = 0;  j < 4;  ++j )
		{
			if ( i == j )
				this->_data[i+j*4] = 1.0f;
			else
				this->_data[i+j*4] = 0.0f;
		}
	}
};