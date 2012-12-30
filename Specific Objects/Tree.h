#pragma	once

#include	"..\Object\Object.h"
#include	"..\Particle System\ParticleEmitter.h"
#include	"Branch.h"



namespace	Globe
{
	/****************************************************************************************
	*****************************************************************************************
	---------------------------------- Tree Class ---------------------------------
	*****************************************************************************************
	****************************************************************************************/

	// Fractal Tree Class
	class	Tree
	{
		private :

			ParticleEmitter				_leaves;
			Texture						_bark;
			vector<Object>				_branch;
			vector<Branch>				_tree;
			vector<Matrix4x4f>			_leaves_positions;
			map<unsigned int,Colour>	_leaves_spring_colours;
			map<unsigned int,Colour>	_leaves_autumn_colours;
			map<unsigned int,Material>	_leaves_spring_materials;
			map<unsigned int,Material>	_leaves_autumn_materials;
			map<unsigned int,GLfloat>	_leaves_spring_scales;
			map<unsigned int,GLfloat>	_leaves_autumn_scales;
			Vector3f					_position;
			Vector3f					_leaves_acceleration;
			unsigned int				_levels;
			unsigned int				_branching;
			float						_width;
			float						_height;
			unsigned int				_branch_stacks;
			unsigned int				_branch_slices;
			GLfloat						_leaf_size;


			vector<Vertex>				_create_vertices( const float width , const float height , const float scale , const Colour& colour );
			vector<GLuint>				_create_indices( const float scale );
			unsigned int				_create_tree( const unsigned int level , const unsigned long counter , const unsigned int branch_no , const float offset , const float scale , const Matrix4x4f& matrix , unsigned long& leaf_counter );
			unsigned int				_draw_tree( const unsigned int level , const unsigned long counter , const unsigned int max_level , const GLfloat scale );


		public :

			Tree();


			void						leaves_spring_colours( const map<unsigned int,Colour>& colours );
			void						leaves_autumn_colours( const map<unsigned int,Colour>& colours );
			void						leaves_spring_materials( const map<unsigned int,Material>& materials );
			void						leaves_autumn_materials( const map<unsigned int,Material>& materials );
			void						leaves_spring_scales( const map<unsigned int,GLfloat>& scales );
			void						leaves_autumn_scales( const map<unsigned int,GLfloat>& scales );
			void						position( const Vector3f& position );
			void						leaves_acceleration( const Vector3f& value );
			void						use_material( const bool value );
			void						use_textures( const bool value );

			Vector3f					position() const;
			Vector3f					leaves_acceleration() const;


			void						create( const unsigned int levels = 3 , const unsigned int branching = 3 , 
											const float width = 1.0f , const float height = 1.0f ,
											const unsigned int branch_stacks = 60 , const unsigned int branch_slices = 60 , 
											const GLfloat leaf_size = 1.0f , const GLfloat leaf_mass = 1.0f , 
											const Colour& colour = Colour::colour_null() , const Material& material = Material() , 
											const string& filename = "" , const string& leaf_filename = "" );
			void						update();
			void						grow_leaves();
			void						shed_leaves();
			void						hide_leaves();
			void						force_hide_leaves();
			void						change_fall_time( const float time , const float delay );
			void						move_leaves( const float time = 0.0f);
			void						set_planes( const vector<vector<Vector3f> >& planes );
			void						destroy();
			void						draw( const unsigned int max_level = -1  , const float scale = 1.0f );
	};

};