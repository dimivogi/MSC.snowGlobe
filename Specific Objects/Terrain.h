#pragma	once

#include	"..\Object\Object.h"



namespace	Globe
{

	/****************************************************************************************
	*****************************************************************************************
	---------------------------------- Terrain Class ---------------------------------
	*****************************************************************************************
	****************************************************************************************/

	// For optimal collision detection with the pool, a lot of stacks and slices are required
	class	Terrain	:	public Object
	{
		private:

			static vector<Vertex>	_create_vertices( const unsigned int stacks , const unsigned int slices , const float radius , const float height , const Vector3f& pool_position , const float a , const float b , const Colour& top_colour , const Colour& bottom_colour );
			static vector<GLuint>	_create_indices( const unsigned int stacks , const unsigned int slices );


		public:

			Terrain();


			void					create( const float radius , const float height = 5 , const unsigned int stacks = 60 , const unsigned int slices = 60 ,
											const Vector3f& pool_position = Vector3f(0.0f,0.0f,0.0f) , const float a = 2.0f , const float b = 1.0f , 
											const Colour& top_colour = Colour::colour_null() , const Colour& bottom_colour = Colour::colour_null() , const Material& material = Material() , const string& filename = "" );
			void					draw( const float scale = 1.0f );
	};

};