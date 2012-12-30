#pragma	once

#ifndef	NOMINMAX
	#define	NOMINMAX
#endif
#include	"GXBase.h"
#include	<iostream>
#include	"..\Vector\Vector3f.h"

using		namespace gxbase;
using		namespace std;



namespace	Globe
{

	/****************************************************************************************
	*****************************************************************************************
	---------------------------------- House Class ---------------------------------
	*****************************************************************************************
	****************************************************************************************/

	class	House
	{
		private:

			Model				_house;
			Vector3f			_position;
			Vector3f			_centre;
			Vector3f			_difference;
			GLfloat				_rotation;


			void				_update_difference();

		public:

			House();


			void				position( const Vector3f& position );
			void				rotation( const GLfloat value );

			Vector3f			position() const;
			GLfloat				rotation() const;


			void				create( const string& filename , const float scale = 1.0f );
			void				destroy();
			void				draw( unsigned int renderMode = 5 );
	};

};