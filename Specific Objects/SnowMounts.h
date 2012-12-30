#pragma	once

#include	<vector>
#include	"..\Object\Object.h"



namespace	Globe
{
	/****************************************************************************************
	*****************************************************************************************
	------------------------------------ Snow Mount Class -----------------------------------
	*****************************************************************************************
	****************************************************************************************/

	// Class responsible for displaying the snowy terrain  and the snow on the roof
	class	SnowMounts
	{
		private:

			Object					_terrain_snow;
			vector<Object>			_roof_mounts;
			vector<Vector3f>		_roof_normals;
			Vector3f				_position;


			static vector<Vertex>	_create_roof_vertices( const vector<Vector3f>& plane , const Colour& colour , vector<Vector3f>& normals );
			static vector<GLuint>	_create_roof_indices();
			static vector<Vertex>	_create_terrain_vertices( const unsigned int stacks , const unsigned int slices , const float radius , const float height , const Vector3f& pool_position , const float a , const float b , const Colour& colour );
			static vector<GLuint>	_create_terrain_indices( const unsigned int stacks , const unsigned int slices ) ;


		public:

			SnowMounts();

			void					position( const Vector3f& position );
			void					use_material( const bool value );
			void					use_textures( const bool value );

			Vector3f				position() const;


			void					create(	const float radius = 1.0f , const float height = 1.0f , const unsigned int stacks = 1 , const unsigned int slices = 2 ,
											const Vector3f& pool_position = Vector3f(0.0f,0.0f,0.0f) , const float a = 2.0f , const float b = 1.0f ,   
											const vector<vector<Vector3f> >& roof_planes = vector<vector<Vector3f> >(0,vector<Vector3f>(3)) , const Colour& colour = Colour::colour_null() , const Material& material = Material() , const string& filename = "" );
			void					draw( const GLfloat terrain_scale = 1.0f , const GLfloat roof_x_scale = 1.0f , const GLfloat roof_y_scale = 1.0f , const GLfloat roof_z_scale = 1.0f, bool ignore_stencil = false );
			void					destroy();
	};

}