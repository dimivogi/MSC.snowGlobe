#pragma	once

#include	"..\Object\Object.h"



namespace	Globe
{
	/****************************************************************************************
	*****************************************************************************************
	-------------------------------------- Sphere Class -------------------------------------
	*****************************************************************************************
	****************************************************************************************/

	class	Sphere	:	public Object
	{
		private:

			static vector<Vertex>	_create_vertices( const float radius , const unsigned int stacks , const unsigned int slices , const Colour& colour );
			static vector<GLuint>	_create_indices( const unsigned int stacks , const unsigned int slices );


		public:

			Sphere();


			void	create( const float radius = 1.0f , const unsigned int stacks = 20 , const unsigned int slices = 20 , const Colour& colour = Colour::colour_null() , const Material& material = Material() , const string& filename = "" );

	};

};