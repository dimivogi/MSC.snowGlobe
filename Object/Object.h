#pragma	once

#include	<string>
#include	<vector>
#include	"Vertex.h"
#include	"..\Material\Material.h"
#include	"..\Texture\Texture.h"

using		namespace std;



namespace	Globe
{
	/****************************************************************************************
	*****************************************************************************************
	---------------------------------- Object Class ---------------------------------
	*****************************************************************************************
	****************************************************************************************/

	// Generic openGL object class, capable of supporting vertex arrays and vertex buffers
	class	Object	: public glex
	{
		private:

			vector<Vertex>		_display_data;
			vector<GLuint>		_indices;
			GLuint				_display_data_id;
			GLuint				_indices_id;
			bool				_buffer_initialised;
			bool				_update_pending;
			bool				_using_vertex_buffer;

			Vector3f			_position;
			Material			_material;
			vector<Texture>		_textures;
			vector<bool>		_initialised;
			bool				_use_textures;
			bool				_use_material;

			static const int	_maximum_textures = 8;


			void				create_vertex_buffer();
			void				update_vertex_buffer();
			void				destroy_vertex_buffer();
			void				draw_vertex_buffer();
			void				draw_vertex_array();


		public:

			static const float	_PI;
			static const float	_PI_DIV_180;


			explicit Object( const Vector3f& position = Vector3f(0) , const Material& material = Material() , const std::vector<Texture>&  textures = vector<Texture>(0) );
			Object( const Object& obj );
			virtual ~Object();


			Object&	operator=( const Object& obj );


			void				position( const Vector3f& position );
			void				material( const Material& material );
			void				texture( const unsigned int texture_no , const Texture& texture );
			void				textures( const std::vector<Texture>& textures );
			void				use_textures( const bool value );
			void				use_material( const bool value );
			void				use_vertex_buffer( const bool value );
			void				display_data( const std::vector<Vertex>& data );
			void				indices_data( const std::vector<GLuint>& data );

			Vector3f			position() const;
			Material			material() const;
			Texture				texture( unsigned int texture_no ) const;
			vector<Texture>		textures() const;
			bool				using_textures() const;
			bool				using_material() const;
			bool				using_vertex_buffer() const;
			vector<Vertex>		display_data() const;
			vector<GLuint>		indices_data() const;



			void				create_texture( const unsigned int texture_no );
			void				create_textures();
			void				destroy_texture( const unsigned int texture_no );
			void				destroy_textures();

			virtual void		create();
			void				destroy();
			virtual void		draw();
	};

};