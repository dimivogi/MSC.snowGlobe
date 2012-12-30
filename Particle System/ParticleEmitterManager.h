#pragma	once

#include	"ParticleEmitter.h"



namespace	Globe
{

	/****************************************************************************************
	*****************************************************************************************
	----------------------------- Particle Emitter Manager Class ----------------------------
	*****************************************************************************************
	****************************************************************************************/

	class	ParticleEmitterManager
	{
		private:

			vector<ParticleEmitter>		_emitters;


		public:

			explicit ParticleEmitterManager( const unsigned int emitter_count = 0 );

			
			void						particle_count( const unsigned int emitter , const unsigned long count );
			void						starting_positions( const unsigned int emitter , const vector<Matrix4x4f>& positions );
			void						collision_planes( const unsigned int emitter , const vector<vector<Vector3f> >& planes );
			void						delays( const unsigned int emitter , const vector<GLfloat>& delays );
			void						add_force( const unsigned int emitter , const string& name , const Vector3f& value );
			void						remove_force( const unsigned int emitter , const string& name );
			void						add_colour( const unsigned int emitter , const unsigned int percent , const Colour& value );
			void						remove_colour( const unsigned int emitter , const unsigned int percent );
			void						add_material( const unsigned int emitter , const unsigned int percent , const Material& value );
			void						remove_material( const unsigned int emitter , const unsigned int percent );
			void						add_scale( const unsigned int emitter , const unsigned int percent , const GLfloat value );
			void						remove_scale( const unsigned int emitter , const unsigned int percent );
			void						position( const unsigned int emitter , const Vector3f& position );
			void						starting_velocity( const unsigned int emitter , const Vector3f& value );
			void						particle_size( const unsigned int emitter , const float value );
			void						particle_mass( const unsigned int emitter , const float value );
			void						particle_energy( const unsigned int emitter , const float value );
			void						particle_delay( const unsigned int emitter , const float value );
			void						spread( const unsigned int emitter , const float value );
			void						fixed_starting_positions( const unsigned int emitter , const bool value );
			void						collision( const unsigned int emitter , const bool value );
			void						fixed_delays( const unsigned int emitter , const bool value );
			void						use_material( const unsigned int emitter , const bool value );
			void						use_textures( const unsigned int emitter , const bool value );
			void						manual_reset( const unsigned int emitter , const bool value );
			void						use_billboards( const unsigned int emitter , const bool value );
			void						use_spherical_billboards( const unsigned int emitter , const bool value );

			unsigned long				particle_count( const unsigned int emitter ) const;
			vector<Matrix4x4f>			starting_positions( const unsigned int emitter ) const;
			vector<vector<Vector3f> >	collision_planes( const unsigned int emitter ) const;
			vector<GLfloat>				delays( const unsigned int emitter ) const;
			Vector3f					force( const unsigned int emitter , const string& name ) const;
			Colour						colour( const unsigned int emitter  , const unsigned int percent ) const;
			Material					material( const unsigned int emitter , const unsigned int percent ) const;
			GLfloat						scale( const unsigned int emitter , const unsigned int percent ) const;
			Vector3f					position( const unsigned int emitter ) const;
			Vector3f					starting_velocity( const unsigned int emitter ) const;
			float						particle_size( const unsigned int emitter ) const;
			float						particle_mass( const unsigned int emitter ) const;
			float						particle_energy( const unsigned int emitter ) const;
			float						particle_delay( const unsigned int emitter ) const;
			float						spread( const unsigned int emitter ) const;
			bool						fixed_starting_positions( const unsigned int emitter ) const;
			bool						collision( const unsigned int emitter ) const;
			bool						fixed_delays( const unsigned int emitter ) const;
			bool						using_material( const unsigned int emitter ) const;
			bool						using_textures( const unsigned int emitter ) const;
			bool						manual_reset( const unsigned int emitter ) const;
			bool						using_billboards( const unsigned int emitter ) const;
			bool						using_spherical_billboards( const unsigned int emitter ) const;
			bool						emitting( const unsigned int emitter ) const;


			void						create(  const unsigned int emitter , const float size = 1.0f , const float mass = 1.0f , const float energy = 10.0f , const string& filename = "" );
			void						destroy( const unsigned int emitter );
			void						start( const unsigned int emitter );
			void						stop( const unsigned int emitter );
			void						force_stop( const unsigned int emitter );
			void						reset( const unsigned int emitter );
			void						update( const unsigned int emitter , const float time_since_last_update );
			void						draw( const unsigned int emitter , const float scale = 1.0f );

			void						update( const float time_since_last_update );
			void						draw();
			void						destroy();
	};



	/****************************************************************************************
	*****************************************************************************************
	---------------------------------- Function Definitions ---------------------------------
	*****************************************************************************************
	****************************************************************************************/


	inline void						ParticleEmitterManager::particle_count( const unsigned int emitter , const unsigned long count )
	{
		if ( emitter < this->_emitters.size() )
			this->_emitters[emitter].particle_count(count);
	};

	inline void						ParticleEmitterManager::starting_positions( const unsigned int emitter , const vector<Matrix4x4f>& positions )
	{
		if ( emitter < this->_emitters.size() )
			this->_emitters[emitter].starting_positions(positions);
	};

	inline void						ParticleEmitterManager::collision_planes( const unsigned int emitter , const vector<vector<Vector3f> >& planes )
	{
		if ( emitter < this->_emitters.size() )
			this->_emitters[emitter].collision_planes(planes);
	};

	inline void						ParticleEmitterManager::delays( const unsigned int emitter , const vector<GLfloat>& delays )
	{
		if ( emitter < this->_emitters.size() )
			this->_emitters[emitter].delays(delays);
	};

	inline void						ParticleEmitterManager::add_force( const unsigned int emitter , const string& name , const Vector3f& value )
	{
		if ( emitter < this->_emitters.size() )
			this->_emitters[emitter].add_force(name,value);
	};

	inline void						ParticleEmitterManager::remove_force( const unsigned int emitter , const string& name )
	{
		if ( emitter < this->_emitters.size() )
			this->_emitters[emitter].remove_force(name);
	};

	inline void						ParticleEmitterManager::add_colour( const unsigned int emitter , const unsigned int percent , const Colour& value )
	{
		if ( emitter < this->_emitters.size() )
			this->_emitters[emitter].add_colour(percent,value);
	};

	inline void						ParticleEmitterManager::remove_colour( const unsigned int emitter , const unsigned int percent )
	{
		if ( emitter < this->_emitters.size() )
			this->_emitters[emitter].remove_colour(percent);
	};

	inline void						ParticleEmitterManager::add_material( const unsigned int emitter , const unsigned int percent , const Material& value )
	{
		if ( emitter < this->_emitters.size() )
			this->_emitters[emitter].add_material(percent,value);
	};

	inline void						ParticleEmitterManager::remove_material( const unsigned int emitter , const unsigned int percent )
	{
		if ( emitter < this->_emitters.size() )
			this->_emitters[emitter].remove_material(percent);
	};

	inline void						ParticleEmitterManager::add_scale( const unsigned int emitter , const unsigned int percent , const GLfloat value )
	{
		if ( emitter < this->_emitters.size() )
			this->_emitters[emitter].add_scale(percent,value);
	};

	inline void						ParticleEmitterManager::remove_scale( const unsigned int emitter , const unsigned int percent )
	{
		if ( emitter < this->_emitters.size() )
			this->_emitters[emitter].remove_scale(percent);
	};

	inline void						ParticleEmitterManager::position( const unsigned int emitter , const Vector3f& position )
	{
		if ( emitter < this->_emitters.size() )
			this->_emitters[emitter].position(position);
	};

	inline void						ParticleEmitterManager::starting_velocity( const unsigned int emitter , const Vector3f& value )
	{
		if ( emitter < this->_emitters.size() )
			this->_emitters[emitter].starting_velocity(value);
	};

	inline void						ParticleEmitterManager::particle_size( const unsigned int emitter , const float value )
	{
		if ( emitter < this->_emitters.size() )
			this->_emitters[emitter].particle_size(value);
	};

	inline void						ParticleEmitterManager::particle_mass( const unsigned int emitter , const float value )
	{
		if ( emitter < this->_emitters.size() )
			this->_emitters[emitter].particle_mass(value);
	};

	inline void						ParticleEmitterManager::particle_energy( const unsigned int emitter , const float value )
	{
		if ( emitter < this->_emitters.size() )
			this->_emitters[emitter].particle_energy(value);
	};

	inline void						ParticleEmitterManager::particle_delay( const unsigned int emitter , const float value )
	{
		if ( emitter < this->_emitters.size() )
			this->_emitters[emitter].particle_delay(value);
	};

	inline void						ParticleEmitterManager::spread( const unsigned int emitter , const float value )
	{
		if ( emitter < this->_emitters.size() )
			this->_emitters[emitter].spread(value);
	};

	inline void						ParticleEmitterManager::fixed_starting_positions( const unsigned int emitter , const bool value )
	{
		if ( emitter < this->_emitters.size() )
			this->_emitters[emitter].fixed_starting_positions(value);
	};

	inline void						ParticleEmitterManager::collision( const unsigned int emitter , const bool value )
	{
		if ( emitter < this->_emitters.size() )
			this->_emitters[emitter].collision(value);
	};

	inline void						ParticleEmitterManager::fixed_delays( const unsigned int emitter , const bool value )
	{
		if ( emitter < this->_emitters.size() )
			this->_emitters[emitter].fixed_delays(value);
	};

	inline void						ParticleEmitterManager::use_material( const unsigned int emitter , const bool value )
	{
		if ( emitter < this->_emitters.size() )
			this->_emitters[emitter].use_material(value);
	};

	inline void						ParticleEmitterManager::use_textures( const unsigned int emitter , const bool value )
	{
		if ( emitter < this->_emitters.size() )
			this->_emitters[emitter].use_textures(value);
	};

	inline void						ParticleEmitterManager::manual_reset( const unsigned int emitter , const bool value )
	{
		if ( emitter < this->_emitters.size() )
			this->_emitters[emitter].manual_reset(value);
	};

	inline void						ParticleEmitterManager::use_billboards( const unsigned int emitter , const bool value )
	{
		if ( emitter < this->_emitters.size() )
			this->_emitters[emitter].use_billboards(value);
	};

	inline void						ParticleEmitterManager::use_spherical_billboards( const unsigned int emitter , const bool value )
	{
		if ( emitter < this->_emitters.size() )
			this->_emitters[emitter].use_spherical_billboards(value);
	};


	inline unsigned long				ParticleEmitterManager::particle_count( const unsigned int emitter ) const
	{
		if ( emitter < this->_emitters.size() )
			return this->_emitters[emitter].particle_count();
		else
			return 0;
	};

	inline vector<Matrix4x4f>			ParticleEmitterManager::starting_positions( const unsigned int emitter ) const
	{
		if ( emitter < this->_emitters.size() )
			return this->_emitters[emitter].starting_positions();
		else
			return vector<Matrix4x4f>(0);
	};

	inline vector<vector<Vector3f> >	ParticleEmitterManager::collision_planes( const unsigned int emitter ) const
	{
		if ( emitter < this->_emitters.size() )
			return this->_emitters[emitter].collision_planes();
		else
			return vector<vector<Vector3f> >(0);
	};

	inline vector<GLfloat>	ParticleEmitterManager::delays( const unsigned int emitter ) const
	{
		if ( emitter < this->_emitters.size() )
			return this->_emitters[emitter].delays();
		else
			return vector<GLfloat>(0);
	};

	inline Vector3f					ParticleEmitterManager::force( const unsigned int emitter , const string& name ) const
	{
		if ( emitter < this->_emitters.size() )
			return this->_emitters[emitter].force(name);
		else
			return Vector3f(0.0f,0.0f,0.0f);
	};

	inline Colour						ParticleEmitterManager::colour( const unsigned int emitter  , const unsigned int percent ) const
	{
		if ( emitter < this->_emitters.size() )
			return this->_emitters[emitter].colour(percent);
		else
			return Colour(0.0f,0.0f,0.0f);
	};

	inline Material					ParticleEmitterManager::material( const unsigned int emitter , const unsigned int percent ) const
	{
		
		if ( emitter < this->_emitters.size() )
			return this->_emitters[emitter].material(percent);
		else
			return Material();
	};

	inline GLfloat					ParticleEmitterManager::scale( const unsigned int emitter , const unsigned int percent ) const
	{
		if ( emitter < this->_emitters.size() )
			return this->_emitters[emitter].scale(percent);
		else
			return 0.0f;
	};

	inline Vector3f					ParticleEmitterManager::position( const unsigned int emitter ) const
	{
		if ( emitter < this->_emitters.size() )
			return this->_emitters[emitter].position();
		else
			return Vector3f(0.0f,0.0,0.0f);
	};

	inline Vector3f					ParticleEmitterManager::starting_velocity( const unsigned int emitter ) const
	{
		if ( emitter < this->_emitters.size() )
			return this->_emitters[emitter].starting_velocity();
		else
			return Vector3f(0.0f,0.0,0.0f);
	};

	inline float					ParticleEmitterManager::particle_size( const unsigned int emitter ) const
	{
		
		if ( emitter < this->_emitters.size() )
			return this->_emitters[emitter].particle_size();
		else
			return 0.0f;
	};

	inline float					ParticleEmitterManager::particle_mass( const unsigned int emitter ) const
	{
		if ( emitter < this->_emitters.size() )
			return this->_emitters[emitter].particle_mass();
		else
			return 0.0f;
	};

	inline float					ParticleEmitterManager::particle_energy( const unsigned int emitter ) const
	{
		
		if ( emitter < this->_emitters.size() )
			return this->_emitters[emitter].particle_energy();
		else
			return 0.0f;
	};

	inline float					ParticleEmitterManager::particle_delay( const unsigned int emitter ) const
	{
		if ( emitter < this->_emitters.size() )
			return this->_emitters[emitter].particle_delay();
		else
			return 0.0f;
	};

	inline float					ParticleEmitterManager::spread( const unsigned int emitter ) const
	{
		if ( emitter < this->_emitters.size() )
			return this->_emitters[emitter].spread();
		else
			return 0.0f;
	};

	inline bool						ParticleEmitterManager::fixed_starting_positions( const unsigned int emitter ) const
	{
		if ( emitter < this->_emitters.size() )
			return this->_emitters[emitter].fixed_starting_positions();
		else
			return false;
	};

	inline bool						ParticleEmitterManager::collision( const unsigned int emitter ) const
	{
		if ( emitter < this->_emitters.size() )
			return this->_emitters[emitter].collision();
		else
			return false;
	};

	inline bool						ParticleEmitterManager::fixed_delays( const unsigned int emitter ) const
	{
		if ( emitter < this->_emitters.size() )
			return this->_emitters[emitter].fixed_delays();
		else
			return false;
	};

	inline bool						ParticleEmitterManager::using_material( const unsigned int emitter ) const
	{
		if ( emitter < this->_emitters.size() )
			return this->_emitters[emitter].using_material();
		else
			return false;
	};

	inline bool						ParticleEmitterManager::using_textures( const unsigned int emitter ) const
	{
		if ( emitter < this->_emitters.size() )
			return this->_emitters[emitter].using_textures();
		else
			return false;
	};

	inline bool						ParticleEmitterManager::manual_reset( const unsigned int emitter ) const
	{
		if ( emitter < this->_emitters.size() )
			return this->_emitters[emitter].manual_reset();
		else
			return false;
	};

	inline bool						ParticleEmitterManager::using_billboards( const unsigned int emitter ) const
	{
		if ( emitter < this->_emitters.size() )
			return this->_emitters[emitter].using_billboards();
		else
			return false;
	};

	inline bool						ParticleEmitterManager::using_spherical_billboards( const unsigned int emitter ) const
	{
		if ( emitter < this->_emitters.size() )
			return this->_emitters[emitter].using_spherical_billboards();
		else
			return false;
	};

	inline bool						ParticleEmitterManager::emitting( const unsigned int emitter ) const
	{
		if ( emitter < this->_emitters.size() )
			return this->_emitters[emitter].emitting();
		else
			return false;
	};


	inline void						ParticleEmitterManager::create(  const unsigned int emitter , const float size , const float mass , const float energy , const string& filename )
	{
		if ( emitter < this->_emitters.size() )
			this->_emitters[emitter].create(size,mass,energy,filename);
	};

	inline void						ParticleEmitterManager::destroy( const unsigned int emitter )
	{
		if ( emitter < this->_emitters.size() )
			this->_emitters[emitter].destroy();
	};

	inline void						ParticleEmitterManager::start( const unsigned int emitter )
	{
		if ( emitter < this->_emitters.size() )
			this->_emitters[emitter].start();
	};

	inline void						ParticleEmitterManager::stop( const unsigned int emitter )
	{
		if ( emitter < this->_emitters.size() )
			this->_emitters[emitter].stop();
	};

	inline void						ParticleEmitterManager::force_stop( const unsigned int emitter )
	{
		if ( emitter < this->_emitters.size() )
			this->_emitters[emitter].force_stop();
	};

	inline void						ParticleEmitterManager::reset( const unsigned int emitter )
	{
		if ( emitter < this->_emitters.size() )
			this->_emitters[emitter].reset();
	};

	inline void						ParticleEmitterManager::update( const unsigned int emitter , const float time_since_last_update )
	{
		if ( emitter < this->_emitters.size() )
			this->_emitters[emitter].update(time_since_last_update);
	};

	inline void						ParticleEmitterManager::draw( const unsigned int emitter , const float scale )
	{
		if ( emitter < this->_emitters.size() )
			this->_emitters[emitter].draw(scale);
	};

}