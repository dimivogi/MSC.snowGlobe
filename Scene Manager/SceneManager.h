#pragma	once

#include	"..\Camera\Camera.h"
#include	"..\Light\Light.h"
#include	"..\Specific Objects\GlassGlobe.h"
#include	"..\Specific Objects\Terrain.h"
#include	"..\Specific Objects\House.h"
#include	"..\Specific Objects\Pool.h"
#include	"..\Specific Objects\Tree.h"
#include	"..\Specific Objects\SnowMounts.h"
#include	"..\Specific Objects\Sphere.h"
#include	"..\Particle System\ParticleEmitterManager.h"
#include	"..\Reflection\Reflection.h"
#include	"..\Shader\ShaderProgram.h"



namespace	Globe
{
	//	Class responsible of handling the content which is displayed on screen
	class	SceneManager
	{
		private:

			GlassGlobe					_globe;
			Terrain						_terrain;
			House						_house;
			Tree						_tree;
			Pool						_pool;
			//Pool						_frozen_pool;
			ParticleEmitterManager		_particle_systems;
			Colour						_window_background;
			SnowMounts					_snow_mounts;
			Sphere						_light_spheres[4];
			Sphere						_sun_sphere;
			Sphere						_moon_sphere;
			Reflection					_reflection;
			ShaderProgram				_program;
			Shader						_vertex_shader;
			Shader						_fragment_shader;

			/*map<unsigned int,Colour>	_leaf_spring_colours;
			map<unsigned int,Colour>	_leaf_autumn_colours;
			map<unsigned int,Colour>	_fire_colours;
			map<unsigned int,Colour>	_smoke_colours;
			map<unsigned int,Colour>	_snow_colours;*/
			//map<unsigned int,Colour>	_lightning_colours;
			//map<unsigned int,Colour>	_storm_colours;
			//map<unsigned int,Colour>	_colour_colours;

			map<unsigned int,Material>	_leaf_spring_materials;
			map<unsigned int,Material>	_leaf_autumn_materials;
			map<unsigned int,Material>	_fire_materials;
			map<unsigned int,Material>	_smoke_materials;
			map<unsigned int,Material>	_snow_materials;
			map<unsigned int,Material>	_grass_materials;
			map<unsigned int,Material>	_lightning_materials;
			map<unsigned int,Material>	_storm_materials;
			map<unsigned int,Material>	_rain_materials;

			map<unsigned int,GLfloat>	_leaf_spring_scales;
			map<unsigned int,GLfloat>	_leaf_autumn_scales;
			map<unsigned int,GLfloat>	_fire_scales;
			map<unsigned int,GLfloat>	_smoke_scales;
			map<unsigned int,GLfloat>	_snow_scales;
			map<unsigned int,GLfloat>	_grass_scales;
			map<unsigned int,GLfloat>	_lightning_scales;
			map<unsigned int,GLfloat>	_storm_scales;
			map<unsigned int,GLfloat>	_rain_scales;

			vector<Matrix4x4f>			_grass_positions;
			vector<Matrix4x4f>			_lightning_positions;
			vector<Matrix4x4f>			_storm_positions;

			vector<vector<Vector3f> >	_leaf_planes;
			vector<vector<Vector3f> >	_roof_planes;
			vector<vector<Vector3f> >	_snow_mount_planes;

			vector<GLfloat>				_lightning_delays;

			Vector3f					_globe_position;
			Vector3f					_terrain_position;
			Vector3f					_pool_position;
			Vector3f					_tree_position;
			Vector3f					_house_position;
			Vector3f					_snow_mounts_position;
			Vector3f					_fire_position;
			Vector3f					_smoke_position;
			Vector3f					_snow_position;
			Vector3f					_snow_position2;
			Vector3f					_snow_position3;
			Vector3f					_snow_position4;
			Vector3f					_snow_position5;
			Vector3f					_snow_position6;
			Vector3f					_snow_position7;
			Vector3f					_snow_position8;
			Vector3f					_grass_position;
			Vector3f					_lightning_position;
			Vector3f					_storm_position;
			Vector3f					_rain_position;
			Vector3f					_rain_position2;
			Vector3f					_rain_position3;
			Vector3f					_rain_position4;
			Vector3f					_rain_position5;
			Vector3f					_rain_position6;
			Vector3f					_rain_position7;
			Vector3f					_rain_position8;

			Vector3f					_fire_speed;
			Vector3f					_smoke_speed;
			Vector3f					_snow_speed;
			Vector3f					_lightning_speed;
			Vector3f					_storm_speed;
			Vector3f					_rain_speed;
			Vector3f					_leaf_acceleration;
			Vector3f					_fire_acceleration;
			Vector3f					_smoke_acceleration;
			Vector3f					_snow_acceleration;
			Vector3f					_lightning_acceleration;
			Vector3f					_storm_acceleration;
			Vector3f					_rain_acceleration;

			Material					_globe_material;
			Material					_terrain_material;
			Material					_pool_material;
			Material					_tree_material;
			Material					_snow_mount_material;

			Colour						_globe_colour;
			Colour						_terrain_top_colour;
			Colour						_terrain_bottom_colour;
			Colour						_pool_colour;
			Colour						_tree_colour;
			Colour						_snow_mount_colour;

			Light						_lights[4];
			Vector3f					_lights_position[4];
			Vector3f					_lights_direction[4];
			Material					_lights_colour[4];
			Light						_sun;
			Light						_moon;
			Material					_sun_colour;
			Material					_moon_colour;
			Camera						_camera;

			string						_house_model_filename;
			string						_terrain_texture_filename;
			string						_pool_texture_filename;
			//string					_frozen_pool_filename;
			string						_tree_bark_texture_filename;
			string						_tree_leaf_texture_filename;
			string						_snow_mounts_texture_filename;
			string						_smoke_texture_filename;
			string						_snow_texture_filename;
			string						_grass_texture_filename;
			string						_lightning_texture_filename;
			string						_storm_texture_filename;
			string						_rain_texture_filename;
			string						_vertex_shader_filename;
			string						_fragment_shader_filename;

			int							_window_width;
			int							_window_height;
			float						_ratio;

			double						_current_time;
			int							_mouse_position[2];
			bool						_mouse_down[3];
			bool						_key_state[256];
			GLfloat						_near;
			GLfloat						_far;
			GLfloat						_field_of_view;
			GLfloat						_camera_step;
			GLfloat						_camera_distance;
			GLfloat						_zoom;
			bool						_camera_free;
			GLfloat						_yaw_angle;
			GLfloat						_pitch_angle;
			GLfloat						_lights_cuttoff[4];
			GLfloat						_lights_exponent[4];
			bool						_toggle_directional_lights;
			unsigned int				_current_season;
			unsigned int				_days_passed;
			float						_day_light_angle;
			float						_sun_distance;
			unsigned int				_day_cycle_time;
			unsigned int				_season_cycle_time;
			unsigned int				_tree_levels;
			unsigned int				_tree_branching_factor;
			GLfloat						_tree_width_radius;
			GLfloat						_tree_height;
			unsigned int				_tree_branch_stacks;
			unsigned int				_tree_branch_slices;
			unsigned int				_tree_max_draw_level;
			GLfloat						_tree_leaves_size;
			GLfloat						_tree_leaves_mass;
			GLfloat						_tree_draw_scale;
			unsigned int				_globe_stacks;
			unsigned int				_globe_slices;
			GLfloat						_globe_radius;
			GLfloat						_terrain_radius;
			GLfloat						_terrain_height;
			unsigned int				_terrain_stacks;
			unsigned int				_terrain_slices;
			GLfloat						_pool_a_radius;
			GLfloat						_pool_b_radius;
			GLfloat						_pool_height;
			unsigned int				_pool_stacks;
			unsigned int				_pool_slices;
			unsigned int				_pool_height_stacks;
			GLfloat						_snow_mount_height;
			GLfloat						_snow_mount_draw_scale;
			GLfloat						_light_sphere_radius;
			unsigned int				_light_sphere_stacks;
			unsigned int				_light_sphere_slices;
			unsigned int				_fire_density;
			unsigned int				_smoke_density;
			unsigned int				_snow_density;
			unsigned int				_grass_density;
			unsigned int				_lightning_density;
			unsigned int				_storm_density;
			unsigned int				_rain_density;
			GLfloat						_fire_size;
			GLfloat						_fire_mass;
			GLfloat						_fire_lifespan;
			GLfloat						_fire_delay;
			GLfloat						_fire_spread;
			GLfloat						_smoke_size;
			GLfloat						_smoke_mass;
			GLfloat						_smoke_lifespan;
			GLfloat						_smoke_delay;
			GLfloat						_smoke_spread;
			GLfloat						_snow_size;
			GLfloat						_snow_mass;
			GLfloat						_snow_lifespan;
			GLfloat						_snow_delay;
			GLfloat						_snow_spread;
			GLfloat						_grass_size;
			GLfloat						_grass_mass;
			GLfloat						_grass_delay;
			GLfloat						_grass_spread;
			GLfloat						_lightning_size;
			GLfloat						_lightning_mass;
			GLfloat						_lightning_lifespan;
			GLfloat						_lightning_delay;
			GLfloat						_lightning_spread;
			GLfloat						_storm_size;
			GLfloat						_storm_mass;
			GLfloat						_storm_lifespan;
			GLfloat						_storm_delay;
			GLfloat						_storm_radius;
			GLfloat						_rain_size;
			GLfloat						_rain_mass;
			GLfloat						_rain_lifespan;
			GLfloat						_rain_delay;
			GLfloat						_rain_spread;
			GLfloat						_house_rotation;
			GLfloat						_house_scale;
			unsigned int				_render_model;
			bool						_shader_use_textures;
			bool						_shader_normal_mapping;
			GLuint						_use_textures_loc;
			GLuint						_normal_mapping_loc;
			GLuint						_directional_lights_loc;
			bool						_pause;


			void						_load_configuration();
			void						_set_viewport();
			void						_set_camera_position();
			void						_camera_yaw( const float value );
			void						_camera_roll( const float value );
			void						_camera_zoom( const float value );
			void						_check_key_state( const bool repeat );
			void						_update_render_parameters();
			void						_update_sun_and_moon();
			void						_update_day_time( const double amount );
			void						_update_season( const double amount );
			void						_init_season();
			void						_create_grass();
			void						_create_lightning();
			void						_create_storm();


		public:
	
			explicit SceneManager( const int window_width = 100 , const int window_height = 100 );

			void						mouse_position( int x , int y );
			void						left_button_down();
			void						left_button_up();
			void						middle_button_down();
			void						middle_button_up();
			void						right_button_down();
			void						right_button_up();
			void						key_down( int key );
			void						key_up( int key);
				
			void						setup();
			void						clean_up();
			void						resize( int width , int height );
			void						draw();
			void						update_time( double time );
	};

};