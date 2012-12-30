#pragma	once

#include	"..\Object\Object.h"



namespace	Globe
{
	/****************************************************************************************
	*****************************************************************************************
	---------------------------------- Pool Class ---------------------------------
	*****************************************************************************************
	****************************************************************************************/

	// Class responsible for drawing the pool, although it supports more that one height stack, 
	// results are not visibly optimal
	class	Pool	:	public Object
	{
		private:


			static vector<Vertex>	_create_vertices( const unsigned int stacks , const unsigned int slices , const unsigned int height_stacks , const float a , const float b , const float height , const Vector3f& position , const Vector3f& terrain_position , const float radius , const Colour& colour );
			static vector<GLuint>	_create_indices( const unsigned int stacks , const unsigned int slices , const unsigned int height_stacks );


		public:

			Pool();

			void					create( const float a , const float b = 1.0f , const float height = 1.0f , 
											const unsigned int stacks = 60 , const unsigned int slices = 60 , const unsigned int height_stacks = 10 , 
											const Vector3f& terrain_position = Vector3f(0.0f,0.0f,0.0f) , const float radius = 50.0f , 
											const Colour& colour = Colour::colour_null() , const Material& material = Material() , 
											const string& filename = "" );
			void					draw();
	};

};