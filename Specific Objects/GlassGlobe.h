#pragma	once

#include	"..\Object\Object.h"



namespace	Globe
{
	/****************************************************************************************
	*****************************************************************************************
	---------------------------------- Glass Globe Classs ---------------------------------
	*****************************************************************************************
	****************************************************************************************/

	class	GlassGlobe	:	public Object
	{
		private:

			static vector<Vertex>	_create_vertices( const float radius , const unsigned int slices , const unsigned int stacks , const Colour& colour );
			static vector<GLuint>	_create_indices( const unsigned int stacks , const unsigned int slices );


		public:

			GlassGlobe(); 


			void					create( const float radius = 1.0f , const unsigned int stacks = 60 , const unsigned int slices = 60 , const Colour& colour = Colour::colour_null() , const Material& material = Material() );
			void					draw();
	};

};