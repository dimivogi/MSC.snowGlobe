#pragma	once

#ifndef	NOMINMAX
	#define	NOMINMAX
#endif
#include	"GXBase.h"



namespace	Globe
{
	/****************************************************************************************
	*****************************************************************************************
	------------------------------------- Branch Class --------------------------------------
	*****************************************************************************************
	****************************************************************************************/

	// class used in the construction of the fractal tree
	class	Branch
	{
		private:

			GLfloat			_position[3];
			unsigned int	_level;
			GLfloat			_yaw_angle;
			GLfloat			_pitch_angle;


		public:
		
			Branch();

			void			position( const GLfloat x , const GLfloat y , const GLfloat z );
			void			x( const GLfloat x );
			void			y( const GLfloat y );
			void			z( const GLfloat z );
			void			level( const unsigned int level );
			void			yaw_angle( const GLfloat angle );
			void			pitch_angle( const GLfloat angle );

			GLfloat			x() const;
			GLfloat			y() const;
			GLfloat			z() const;
			unsigned int	level() const;
			GLfloat			yaw_angle() const;
			GLfloat			pitch_angle() const;
	};



	/****************************************************************************************
	*****************************************************************************************
	--------------------------------- Function Definitions ----------------------------------
	*****************************************************************************************
	****************************************************************************************/


	inline void	Branch::position( const GLfloat x , const GLfloat y , const GLfloat z )
	{
		this->x(x);
		this->y(y);
		this->z(z);
	};

	inline void	Branch::x( const GLfloat x )				{ this->_position[0] = x; };
	inline void	Branch::y( const GLfloat y )				{ this->_position[1] = y; };
	inline void	Branch::z( const GLfloat z )				{ this->_position[2] = z; };
	inline void	Branch::level( const unsigned int level )	{ this->_level = level; };
	inline void	Branch::yaw_angle( const GLfloat angle )	{ this->_yaw_angle = angle; };
	inline void Branch::pitch_angle( const GLfloat angle )	{ this->_pitch_angle = angle; };

	inline GLfloat			Branch::x() const				{ return this->_position[0]; };
	inline GLfloat			Branch::y() const				{ return this->_position[1]; };
	inline GLfloat			Branch::z() const				{ return this->_position[2]; };
	inline unsigned int		Branch::level() const			{ return this->_level; };
	inline GLfloat			Branch::yaw_angle() const		{ return this->_yaw_angle; };
	inline GLfloat			Branch::pitch_angle() const		{ return this->_pitch_angle; };

};