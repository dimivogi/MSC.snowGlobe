#pragma	once

#include	<vector>
#include	"..\Vector\Vector3f.h"



namespace	Globe
{
	/****************************************************************************************
	*****************************************************************************************
	------------------------------------- Particle Class ------------------------------------
	*****************************************************************************************
	****************************************************************************************/

	class	Particle
	{
		private:
	
			Vector3f	_previous_position;
			Vector3f	_current_position;
			Vector3f	_starting_position;
			Vector3f	_acceleration;
			Vector3f	_starting_velocity;
			float		_energy;
			float		_mass;
			float		_size;
			float		_delay;
			bool		_visible;

			
			void		_update_position( const float time , const bool collision , const vector<vector<Vector3f> >& planes );
			Vector3f	_test_collision( const vector<Vector3f>& plane , float& intersects );


		public:

			Particle();


			void		position( const Vector3f& position );
			void		starting_position( const Vector3f& position );
			void		acceleration( const Vector3f& direction );
			void		starting_velocity( const Vector3f& velocity );
			void		energy( const float energy );
			void		mass( const float mass );
			void		size( const float size );
			void		delay( const float delay );
			void		visible( const bool visible );

			Vector3f	position() const;
			Vector3f	starting_position() const;
			Vector3f	acceleration() const;
			Vector3f	starting_velocity() const;
			float		energy() const;
			float		mass() const;
			float		size() const;
			float		delay() const;
			bool		visible() const;

			void		move( const float time , const bool collision , const vector<vector<Vector3f> >& planes );
	};



	/****************************************************************************************
	*****************************************************************************************
	---------------------------------- Function Definitions ---------------------------------
	*****************************************************************************************
	****************************************************************************************/


	inline Vector3f		Particle::_test_collision( const vector<Vector3f>& plane , float& intersects )
	{
		float		f = 2.0f;
		Vector3f	return_value(0.0f,0.0f,0.0f);



		if ( plane.size() < 3 )
			intersects = f;
		else
		{
			Vector3f	v1(plane[1] - plane[0]);
			Vector3f	v2(plane[2] - plane[0]);
			Vector3f	normal(v1);
			Vector3f	speed(this->_current_position - this->_previous_position);
			Vector3f	global_position(this->_starting_position + this->_previous_position);
			float		denominator = 2.0f;



			normal.cross_product(v2);
			normal.normalize();
			denominator = normal.dot_product(speed);

			if ( abs(denominator) <= Vector3f::_V3EPSILON )
				intersects = f;
			else
			{
				f = (normal*plane[0] - normal*global_position)/denominator;
				
				if ( f >= -Vector3f::_V3EPSILON  &&  f <= (1.0f+Vector3f::_V3EPSILON) )
				{
					float		v = 0.0f;
					float		u = 0.0f;
					float		w = 0.0f;



					v1 = global_position - plane[0];
					v2 = global_position - plane[1];
					Vector3f	cross(v1);
					cross.cross_product(v2);
					v = speed.dot_product(cross);

					v1 = global_position - plane[1];
					v2 = global_position - plane[2];
					cross = v1;
					cross.cross_product(v2);
					u = speed.dot_product(cross);
					
					v1 = global_position - plane[2];
					v2 = global_position - plane[0];
					cross = v1;
					cross.cross_product(v2);
					w = speed.dot_product(cross);

					if ( ( v >= 0.0f  &&  u >= 0.0f  &&  w >= 0.0f )  ||  ( v <= 0.0f  &&  u <= 0.0f  &&  w <= 0.0f ) )
					{
						intersects = f;
						return_value = f*speed + this->_previous_position;
					}
					else
						intersects = 2.0f;
				}
				else
					intersects = 2.0f;
			}
		}


		return return_value;
	};

	
	inline void		Particle::position( const Vector3f& position )			{ this->_current_position = position; };
	inline void		Particle::starting_position( const Vector3f& position )	{ this->_starting_position = position; };
	inline void		Particle::acceleration( const Vector3f& direction )		{ this->_acceleration = direction; };
	inline void		Particle::starting_velocity( const Vector3f& velocity )	{ this->_starting_velocity = velocity; };
	inline void		Particle::energy( const float energy )					{ this->_energy = energy; };
	inline void		Particle::mass( const float mass )						{ this->_mass = mass; };
	inline void		Particle::size( const float size )						{ this->_size = size; };
	inline void		Particle::delay( const float delay )					{ this->_delay = delay; };
	inline void		Particle::visible( const bool visible )					{ this->_visible = visible; };

	inline Vector3f	Particle::position() const								{ return this->_current_position; };
	inline Vector3f	Particle::starting_position() const						{ return this->_starting_position; };
	inline Vector3f	Particle::acceleration() const							{ return this->_acceleration; };
	inline Vector3f	Particle::starting_velocity() const						{ return this->_starting_velocity; };
	inline float	Particle::energy() const								{ return this->_energy; };
	inline float	Particle::mass() const									{ return this->_mass; };
	inline float	Particle::size() const									{ return this->_size; };
	inline float	Particle::delay() const									{ return this->_delay; };
	inline bool		Particle::visible() const								{ return this->_visible; };

	inline void		Particle::move( const float time , const bool collision , const vector<vector<Vector3f> >& planes )
	{
		if ( this->delay() <= 0.0f )
			this->_update_position(abs(time),collision,planes);
		else
		{
			this->delay(this->delay()-time);
			
			if ( this->delay() < 0 )
				this->_update_position(abs(this->delay()),collision,planes);
		}
	}
};