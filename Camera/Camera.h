#pragma	once

#include	"..\Vector\Vector3f.h"



namespace	Globe
{
	/****************************************************************************************
	*****************************************************************************************
	------------------------------------- Camera Class --------------------------------------
	*****************************************************************************************
	****************************************************************************************/

	class	Camera
	{
		private:

			Vector3f	_position;
			Vector3f	_looking_at;
			Vector3f	_up;
			float		_zoom;
			bool		_free;


		public:

			explicit Camera(	const Vector3f& position = Vector3f(0,0,0) , const Vector3f& lookingAt = Vector3f(0,0,1) ,
					const Vector3f& up = Vector3f(0,1,0) , const float zoom = 1.0f , bool free = false);


			void		position( const Vector3f& value );
			void		looking_at( const Vector3f& value );
			void		up( const Vector3f& value );
			void		zoom( const float value );
			void		free( const bool value );

			Vector3f	position() const;
			Vector3f	looking_at() const;
			Vector3f	up() const;
			float		zoom() const;
			bool		free() const;


			void		apply();
	};



	/****************************************************************************************
	*****************************************************************************************
	--------------------------------- Function Definitions ----------------------------------
	*****************************************************************************************
	****************************************************************************************/



	inline void		Camera::position( const Vector3f& value )	{ this->_position = value; };
	inline void		Camera::looking_at( const Vector3f& value )	{ this->_looking_at = value; };
	inline void		Camera::up( const Vector3f& value )			{ this->_up = value; };
	inline void		Camera::zoom( const float value )			{ if ( value >= 0 )	this->_zoom = value; };
	inline void		Camera::free( const bool value )			{ this->_free = value; };

	inline Vector3f	Camera::position() const					{ return this->_position; };
	inline Vector3f	Camera::looking_at() const					{ return this->_looking_at; };
	inline Vector3f	Camera::up() const							{ return this->_up; };
	inline float	Camera::zoom() const						{ return this->_zoom; };
	inline bool		Camera::free() const						{ return this->_free; };


	inline void		Camera::apply()
	{
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		if ( !this->_free )
			gluLookAt(	this->_looking_at.x() + this->_zoom*this->_position.x(),this->_looking_at.y() + this->_zoom*this->_position.y(),this->_looking_at.z() + this->_zoom*this->_position.z(),
						this->_looking_at.x(),this->_looking_at.y(),this->_looking_at.z(),
						this->_up.x(),this->_up.y(),this->_up.z());
		else
			gluLookAt(	this->_position.x(),this->_position.y(),this->_position.z(),
						this->_position.x() + this->_looking_at.x() , this->_position.y() + this->_looking_at.y() , this->_position.z() + this->_looking_at.z() , 
						this->_up.x(),this->_up.y(),this->_up.z() );
	};

};