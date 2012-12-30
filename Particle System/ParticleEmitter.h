#pragma	once

#include	<vector>
#include	<map>
#include	<string>
#include	"Particle.h"
#include	"..\Matrix\Matrix4x4f.h"
#include	"..\Texture\Texture.h"
#include	"..\Object\Object.h"

using		namespace std;



namespace	Globe
{
	/****************************************************************************************
	*****************************************************************************************
	---------------------------------- Particle Emitter Class -------------------------------
	*****************************************************************************************
	****************************************************************************************/

	// class responsible for handling and updating all the particles attached to it
	class	ParticleEmitter
	{
		private:
			
			vector<Particle>			_particles;
			vector<Matrix4x4f>			_starting_positions;
			vector<vector<Vector3f> >	_collision_planes;
			vector<GLfloat>				_delays;
			map<string,Vector3f>		_forces;
			map<unsigned int,Colour>	_colours;
			map<unsigned int,Material>	_materials;
			map<unsigned int,GLfloat>	_scales;
			Object						_display_particle;
			Vector3f					_position;
			Vector3f					_starting_velocity;
			float						_particle_size;
			float						_particle_mass;
			float						_particle_energy;
			float						_particle_delay;
			float						_spread;
			bool						_fixed_positions;
			bool						_fixed_delays;
			bool						_collision_testing;
			bool						_billboards;
			bool						_spherical_billboards;
			bool						_use_material;
			bool						_emit;
			bool						_stop_request;
			bool						_do_not_reset;

	
			vector<Vertex>				_create_vertices() const;
			vector<GLuint>				_create_indices() const;
			void						_reset_particle( const unsigned long particle );
			void						_reset_particles();
			void						_apply_forces();


		public:

			ParticleEmitter();
			~ParticleEmitter();


			void						particle_count( const unsigned long count );
			void						starting_positions( const vector<Matrix4x4f>& positions );
			void						collision_planes( const vector<vector<Vector3f> >& planes );
			void						delays( const vector<GLfloat>& delays );
			void						add_force( const string& name , const Vector3f& value );
			void						remove_force( const string& name );
			void						add_colour( const unsigned int percent , const Colour& value );
			void						remove_colour( const unsigned int percent );
			void						add_material( const unsigned int percent , const Material& value );
			void						remove_material( const unsigned int percent );
			void						add_scale( const unsigned int percent , const GLfloat value );
			void						remove_scale( const unsigned int percent );
			void						position( const Vector3f& position );
			void						starting_velocity( const Vector3f& value );
			void						particle_size( const float value );
			void						particle_mass( const float value );
			void						particle_energy( const float value );
			void						particle_delay( const float value );
			void						spread( const float value );
			void						fixed_starting_positions( const bool value );
			void						fixed_delays( const bool value );
			void						collision( const bool value );
			void						use_material( const bool value );
			void						use_textures( const bool value );
			void						manual_reset( const bool value );
			void						use_billboards( const bool value );
			void						use_spherical_billboards( const bool value );

			unsigned long				particle_count() const;
			vector<Matrix4x4f>			starting_positions() const;
			vector<vector<Vector3f> >	collision_planes() const;
			vector<GLfloat>				delays() const;
			Vector3f					force( const string& name ) const;
			Colour						colour( const unsigned int percent ) const;
			Material					material( const unsigned int percent ) const;
			GLfloat						scale( const unsigned int percent ) const;
			Vector3f					position() const;
			Vector3f					starting_velocity() const;
			float						particle_size() const;
			float						particle_mass() const;
			float						particle_energy() const;
			float						particle_delay() const;
			float						spread() const;
			bool						fixed_starting_positions() const;
			bool						collision() const;
			bool						fixed_delays() const;
			bool						using_material() const;
			bool						using_textures() const;
			bool						manual_reset() const;
			bool						using_billboards() const;
			bool						using_spherical_billboards() const;
			bool						emitting() const;


			void						create( const float size = 1.0f , const float mass = 1.0f , const float energy = 10.0f , const string& filename = "" );
			void						destroy();
			void						start();
			void						stop();
			void						force_stop();
			void						reset();
			void						update( const float time_since_last_update );
			void						draw( const float scale = 1.0f );
	};

};