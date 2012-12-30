#include	"Particle.h"

using		namespace Globe;



Particle::Particle()	:	_energy(1) , _mass(1) , _size(1) , _delay(0) , _visible(true)	{};


void		Particle::_update_position( const float time , const bool collision , const vector<vector<Vector3f> >& planes )
{
	this->_previous_position = this->_current_position;
	this->_current_position += this->_starting_velocity*time + 0.5f*this->_acceleration*time*time;


	if ( collision ) 
	{
		float										intersects = 2.0f;
		Vector3f									plane_point(0.0f,0.0f,0.0f);
		vector<vector<Vector3f> >::const_iterator	plane = planes.begin();
			


		while( abs(intersects) > 1.0f  &&  plane != planes.end() )
		{
			plane_point = this->_test_collision(*plane,intersects);
			++plane;
		}

		if ( abs(intersects) < 1.0f )
			this->_current_position = plane_point;
	}

	this->_starting_velocity += this->acceleration()*time;
	this->energy(this->energy() - time);

	if ( this->energy() < 0 )
		this->visible(false);
};