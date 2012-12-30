#include	"SceneManager.h"
#include	<fstream>
#include	<sstream>
#include	<string>

using		namespace std;
using		namespace Globe;




// function for loading any parameters from the config file. If a specific parameter 
// is not found, the default hard coded values are not changed, enabling a smooth fallback to
// default values.
void	SceneManager::_load_configuration()
{
	ifstream		config_file("Globe.options",ifstream::in);



	if ( config_file.is_open() )
	{
		config_file.seekg(0,ifstream::end);

		unsigned long	size = static_cast<unsigned long>(config_file.tellg());
		char*			file = new char[size];
		stringstream	buffer;
		string			input;
		string			command;
		string			value;
		bool			init_leaf_spring_materials = false;
		bool			init_leaf_autumn_materials = false;
		bool			init_fire_materials = false;
		bool			init_smoke_materials = false;
		bool			init_snow_materials = false;
		bool			init_grass_materials = false;
		bool			init_lightning_materials = false;
		bool			init_storm_materials = false;
		bool			init_rain_materials = false;
		bool			init_leaf_spring_scales = false;
		bool			init_leaf_autumn_scales = false;
		bool			init_fire_scales = false;
		bool			init_smoke_scales = false;
		bool			init_snow_scales = false;
		bool			init_grass_scales = false;
		bool			init_lightning_scales = false;
		bool			init_storm_scales = false;
		bool			init_rain_scales = false;
		bool			init_roof_planes = false;
		bool			init_snow_mount_planes = false;
		unsigned int	temp;
		Vector3f		temp2,temp8,temp9;
		Colour			temp3,temp4,temp5,temp6;
		float			temp7;



		config_file.seekg(0,ifstream::beg);
		config_file.read(file,size);
		config_file.close();
		buffer.write(file,size);
		delete[] file;

		while( !buffer.eof()  &&  !buffer.bad() )
		{
			getline(buffer,input,'\n');

			if ( input.size() > 1 )
			{
				if ( input[0] != '#' )
				{
					size_t position = input.find_first_of('=');



					if ( position != input.npos )
					{
						command = input.substr(0,position);
						value = input.substr(position+1);

						stringstream	command_buffer(value);



						if ( command == "leaf_spring_material" )
						{
							if ( !init_leaf_spring_materials )
							{
								init_leaf_spring_materials = true;
								this->_leaf_spring_materials.clear();
							}


							command_buffer	>> temp >> temp3 >> temp4 >> temp5 >> temp6 >> temp7;
							this->_leaf_spring_materials.insert(pair<unsigned int,Material>(temp,Material(temp3,temp4,temp5,temp6,temp7)));
						}
						else if ( command == "leaf_autumn_material" )
						{
							if ( !init_leaf_autumn_materials )
							{
								init_leaf_autumn_materials = true;
								this->_leaf_autumn_materials.clear();
							}


							command_buffer	>> temp >> temp3 >> temp4 >> temp5 >> temp6 >> temp7;
							this->_leaf_autumn_materials.insert(pair<unsigned int,Material>(temp,Material(temp3,temp4,temp5,temp6,temp7)));
						}
						else if ( command == "fire_material" )
						{
							if ( !init_fire_materials )
							{
								init_fire_materials = true;
								this->_fire_materials.clear();
							}


							command_buffer	>> temp >> temp3 >> temp4 >> temp5 >> temp6 >> temp7;
							this->_fire_materials.insert(pair<unsigned int,Material>(temp,Material(temp3,temp4,temp5,temp6,temp7)));
						}
						else if ( command == "smoke_material" )
						{
							if ( !init_smoke_materials )
							{
								init_smoke_materials = true;
								this->_smoke_materials.clear();
							}


							command_buffer	>> temp >> temp3 >> temp4 >> temp5 >> temp6 >> temp7;
							this->_smoke_materials.insert(pair<unsigned int,Material>(temp,Material(temp3,temp4,temp5,temp6,temp7)));
						}
						else if ( command == "snow_material" )
						{
							if ( !init_snow_materials )
							{
								init_snow_materials = true;
								this->_snow_materials.clear();
							}


							command_buffer	>> temp >> temp3 >> temp4 >> temp5 >> temp6 >> temp7;
							this->_snow_materials.insert(pair<unsigned int,Material>(temp,Material(temp3,temp4,temp5,temp6,temp7)));
						}
						else if ( command == "grass_material" )
						{
							if ( !init_grass_materials )
							{
								init_grass_materials = true;
								this->_grass_materials.clear();
							}


							command_buffer	>> temp >> temp3 >> temp4 >> temp5 >> temp6 >> temp7;
							this->_grass_materials.insert(pair<unsigned int,Material>(temp,Material(temp3,temp4,temp5,temp6,temp7)));
						}
						else if ( command == "lightning_material" )
						{
							if ( !init_lightning_materials )
							{
								init_lightning_materials = true;
								this->_lightning_materials.clear();
							}


							command_buffer	>> temp >> temp3 >> temp4 >> temp5 >> temp6 >> temp7;
							this->_lightning_materials.insert(pair<unsigned int,Material>(temp,Material(temp3,temp4,temp5,temp6,temp7)));
						}
						else if ( command == "storm_material" )
						{
							if ( !init_storm_materials )
							{
								init_storm_materials = true;
								this->_storm_materials.clear();
							}


							command_buffer	>> temp >> temp3 >> temp4 >> temp5 >> temp6 >> temp7;
							this->_storm_materials.insert(pair<unsigned int,Material>(temp,Material(temp3,temp4,temp5,temp6,temp7)));
						}
						else if ( command == "rain_material" )
						{
							if ( !init_rain_materials )
							{
								init_rain_materials = true;
								this->_rain_materials.clear();
							}


							command_buffer	>> temp >> temp3 >> temp4 >> temp5 >> temp6 >> temp7;
							this->_rain_materials.insert(pair<unsigned int,Material>(temp,Material(temp3,temp4,temp5,temp6,temp7)));
						}
						else if ( command == "leaf_spring_scale" )
						{
							if ( !init_leaf_spring_scales )
							{
								init_leaf_spring_scales = true;
								this->_leaf_spring_scales.clear();
							}

							command_buffer >> temp >> temp7;
							this->_leaf_spring_scales.insert(pair<unsigned int,GLfloat>(temp,static_cast<GLfloat>(temp7)));
						}
						else if ( command == "leaf_autumn_scale" )
						{
							if ( !init_leaf_autumn_scales )
							{
								init_leaf_autumn_scales = true;
								this->_leaf_autumn_scales.clear();
							}


							command_buffer >> temp >> temp7;
							this->_leaf_autumn_scales.insert(pair<unsigned int,GLfloat>(temp,static_cast<GLfloat>(temp7)));
						}
						else if ( command == "fire_scale" )
						{
							if ( !init_fire_scales )
							{
								init_fire_scales = true;
								this->_fire_scales.clear();
							}


							command_buffer >> temp >> temp7;
							this->_fire_scales.insert(pair<unsigned int,GLfloat>(temp,static_cast<GLfloat>(temp7)));
						}
						else if ( command == "smoke_scale" )
						{
							if ( !init_smoke_scales )
							{
								init_smoke_scales = true;
								this->_smoke_scales.clear();
							}


							command_buffer >> temp >> temp7;
							this->_smoke_scales.insert(pair<unsigned int,GLfloat>(temp,static_cast<GLfloat>(temp7)));
						}
						else if ( command == "snow_scale" )
						{
							if ( !init_snow_scales )
							{
								init_snow_scales = true;
								this->_snow_scales.clear();
							}


							command_buffer >> temp >> temp7;
							this->_snow_scales.insert(pair<unsigned int,GLfloat>(temp,static_cast<GLfloat>(temp7)));
						}
						else if ( command == "grass_scale" )
						{
							if ( !init_grass_scales )
							{
								init_grass_scales = true;
								this->_grass_scales.clear();
							}


							command_buffer >> temp >> temp7;
							this->_grass_scales.insert(pair<unsigned int,GLfloat>(temp,static_cast<GLfloat>(temp7)));
						}
						else if ( command == "lightning_scale" )
						{
							if ( !init_lightning_scales )
							{
								init_lightning_scales = true;
								this->_lightning_scales.clear();
							}


							command_buffer >> temp >> temp7;
							this->_lightning_scales.insert(pair<unsigned int,GLfloat>(temp,static_cast<GLfloat>(temp7)));
						}
						else if ( command == "storm_scale" )
						{
							if ( !init_storm_scales )
							{
								init_storm_scales = true;
								this->_storm_scales.clear();
							}


							command_buffer >> temp >> temp7;
							this->_storm_scales.insert(pair<unsigned int,GLfloat>(temp,static_cast<GLfloat>(temp7)));
						}
						else if ( command == "rain_scale" )
						{
							if ( !init_rain_scales )
							{
								init_rain_scales = true;
								this->_rain_scales.clear();
							}


							command_buffer >> temp >> temp7;
							this->_rain_scales.insert(pair<unsigned int,GLfloat>(temp,static_cast<GLfloat>(temp7)));
						}
						else if ( command == "roof_plane" )
						{
							if ( !init_roof_planes )
							{
								init_roof_planes = true;
								this->_roof_planes.clear();
							}

							vector<Vector3f>	temp_vector(3);



							command_buffer >> temp_vector[0] >> temp_vector[1] >> temp_vector[2];
							this->_roof_planes.push_back(temp_vector);
						}
						else if ( command == "snow_mount_plane" )
						{
							if ( !init_roof_planes )
							{
								init_snow_mount_planes = true;
								this->_snow_mount_planes.clear();
							}

							vector<Vector3f>	temp_vector(3);



							command_buffer >> temp_vector[0] >> temp_vector[1] >> temp_vector[2];
							this->_snow_mount_planes.push_back(temp_vector);
						}
						else if ( command == "globe_position" )
							command_buffer >> this->_globe_position;
						else if ( command == "terrain_position" )
							command_buffer >> this->_terrain_position;
						else if ( command == "pool_position" )
							command_buffer >> this->_pool_position;
						else if ( command == "tree_position" )
							command_buffer >> this->_tree_position;
						else if ( command == "house_position" )
							command_buffer >> this->_house_position;
						else if ( command == "snow_mounts_position" )
							command_buffer >> this->_snow_mounts_position;
						else if ( command == "fire_position" )
							command_buffer >> this->_fire_position;
						else if ( command == "smoke_position" )
							command_buffer >> this->_smoke_position;
						else if ( command.substr(0,command.length()-1) == "snow_position" )
						{
							unsigned int	i = (command[command.length()-1] - '0');



							if ( i == 0 )
								command_buffer >> this->_snow_position;
							else if ( i == 1 )
								command_buffer >> this->_snow_position2;
							else if ( i == 2 )
								command_buffer >> this->_snow_position3;
							else if ( i == 3 )
								command_buffer >> this->_snow_position4;
							else if ( i == 4 )
								command_buffer >> this->_snow_position5;
							else if ( i == 5 )
								command_buffer >> this->_snow_position6;
							else if ( i == 6 )
								command_buffer >> this->_snow_position7;
							else if ( i == 7 )
								command_buffer >> this->_snow_position8;
						}
						else if ( command == "grass_position" )
							command_buffer >> this->_grass_position;
						else if ( command == "lightning_position" )
							command_buffer >> this->_lightning_position;
						else if ( command == "storm_position" )
							command_buffer >> this->_storm_position;
						else if ( command.substr(0,command.length()-1) == "rain_position" )
						{
							unsigned int	i = (command[command.length()-1] - '0');



							if ( i == 0 )
								command_buffer >> this->_rain_position;
							else if ( i == 1 )
								command_buffer >> this->_rain_position2;
							else if ( i == 2 )
								command_buffer >> this->_rain_position3;
							else if ( i == 3 )
								command_buffer >> this->_rain_position4;
							else if ( i == 4 )
								command_buffer >> this->_rain_position5;
							else if ( i == 5 )
								command_buffer >> this->_rain_position6;
							else if ( i == 6 )
								command_buffer >> this->_rain_position7;
							else if ( i == 7 )
								command_buffer >> this->_rain_position8;
						}
						else if ( command == "fire_speed" )
							command_buffer >> this->_fire_speed;
						else if ( command == "smoke_speed" )
							command_buffer >> this->_smoke_speed;
						else if ( command == "snow_speed" )
							command_buffer >> this->_snow_speed;
						else if ( command == "lightning_speed" )
							command_buffer >> this->_lightning_speed;
						else if ( command == "storm_speed" )
							command_buffer >> this->_storm_speed;
						else if ( command == "rain_speed" )
							command_buffer >> this->_rain_speed;
						else if ( command == "leaf_acceleration" )
							command_buffer >> this->_leaf_acceleration;
						else if ( command == "fire_acceleration" )
							command_buffer >> this->_fire_acceleration;
						else if ( command == "smoke_acceleration" )
							command_buffer >> this->_smoke_acceleration;
						else if ( command == "snow_acceleration" )
							command_buffer >> this->_snow_acceleration;
						else if ( command == "lightning_acceleration" )
							command_buffer >> this->_lightning_acceleration;
						else if ( command == "storm_acceleration" )
							command_buffer >> this->_storm_acceleration;
						else if ( command == "rain_acceleration" )
							command_buffer >> this->_rain_acceleration;
						else if ( command == "globe_material" )
						{
							command_buffer >> temp3 >> temp4 >> temp5 >> temp6 >> temp7;
							this->_globe_material.ambient(temp3);
							this->_globe_material.diffuse(temp4);
							this->_globe_material.specular(temp5);
							this->_globe_material.emission(temp6);
							this->_globe_material.shininess(temp7);
						}
						else if ( command == "terrain_material" )
						{
							command_buffer >> temp3 >> temp4 >> temp5 >> temp6 >> temp7;
							this->_terrain_material.ambient(temp3);
							this->_terrain_material.diffuse(temp4);
							this->_terrain_material.specular(temp5);
							this->_terrain_material.emission(temp6);
							this->_terrain_material.shininess(temp7);
						}
						else if ( command == "pool_material" )
						{
							command_buffer >> temp3 >> temp4 >> temp5 >> temp6 >> temp7;
							this->_pool_material.ambient(temp3);
							this->_pool_material.diffuse(temp4);
							this->_pool_material.specular(temp5);
							this->_pool_material.emission(temp6);
							this->_pool_material.shininess(temp7);
						}
						else if ( command == "tree_material" )
						{
							command_buffer >> temp3 >> temp4 >> temp5 >> temp6 >> temp7;
							this->_tree_material.ambient(temp3);
							this->_tree_material.diffuse(temp4);
							this->_tree_material.specular(temp5);
							this->_tree_material.emission(temp6);
							this->_tree_material.shininess(temp7);
						}
						else if ( command == "snow_mount_material" )
						{
							command_buffer >> temp3 >> temp4 >> temp5 >> temp6 >> temp7;
							this->_snow_mount_material.ambient(temp3);
							this->_snow_mount_material.diffuse(temp4);
							this->_snow_mount_material.specular(temp5);
							this->_snow_mount_material.emission(temp6);
							this->_snow_mount_material.shininess(temp7);
						}
						else if ( command == "globe_colour" )
							command_buffer >> this->_globe_colour;
						else if ( command == "terrain_top_colour" )
							command_buffer >> this->_terrain_top_colour;
						else if ( command == "terrain_bottom_colour" )
							command_buffer >> this->_terrain_bottom_colour;
						else if ( command == "pool_colour" )
							command_buffer >> this->_pool_colour;
						else if ( command == "tree_colour" )
							command_buffer >> this->_tree_colour;
						else if ( command == "snow_mount_colour" )
							command_buffer >> this->_snow_mount_colour;
						else if ( command.substr(0,command.length()-1) == "light_position" )
						{
							unsigned int	i = (command[command.length()-1] - '0');



							if ( i < 4 )
								command_buffer >> this->_lights_position[i];
						}
						else if ( command.substr(0,command.length()-1) == "light_direction" )
						{
							int	i = (command[command.length()-1] - '0');
							


							if ( i < 4 )
								command_buffer >> this->_lights_direction[i];
						}
						else if ( command.substr(0,command.length()-1) == "light_colour" )
						{
							int	i = (command[command.length()-1] - '0');


							


							if ( i < 4 )
							{
								command_buffer >> temp3 >> temp4 >> temp5;
								this->_lights_colour[i].ambient(temp3);
								this->_lights_colour[i].diffuse(temp4);
								this->_lights_colour[i].specular(temp5);
							}
						}
						else if ( command == "sun_colour" )
						{
							command_buffer >> temp3 >> temp4 >> temp5;
							this->_sun_colour.ambient(temp3);
							this->_sun_colour.diffuse(temp4);
							this->_sun_colour.specular(temp5);
						}
						else if ( command == "moon_colour" )
						{
							command_buffer >> temp3 >> temp4 >> temp5;
							this->_moon_colour.ambient(temp3);
							this->_moon_colour.diffuse(temp4);
							this->_moon_colour.specular(temp5);
						}
						else if ( command == "house_model_filename" )
							command_buffer >> this->_house_model_filename;
						else if ( command == "terrain_texture_filename" )
							command_buffer >> this->_terrain_texture_filename;
						else if ( command == "pool_texture_filename" )
							command_buffer >> this->_pool_texture_filename;
						else if ( command == "tree_bark_texture_filename" )
							command_buffer >> this->_tree_bark_texture_filename;
						else if ( command == "tree_leaf_texture_filename" )
							command_buffer >> this->_tree_leaf_texture_filename;
						else if ( command == "snow_mounts_texture_filename" )
							command_buffer >> this->_snow_mounts_texture_filename;
						else if ( command == "smoke_texture_filename" )
							command_buffer >> this->_smoke_texture_filename;
						else if ( command == "snow_texture_filename" )
							command_buffer >> this->_snow_texture_filename;
						else if ( command == "grass_texture_filename" )
							command_buffer >> this->_grass_texture_filename;
						else if ( command == "lightning_texture_filename" )
							command_buffer >> this->_lightning_texture_filename;
						else if ( command == "storm_texture_filename" )
							command_buffer >> this->_storm_texture_filename;
						else if ( command == "rain_texture_filename" )
							command_buffer >> this->_rain_texture_filename;
						else if ( command == "vertex_shader_filename" )
							command_buffer >> this->_vertex_shader_filename;
						else if ( command == "fragment_shader_filename" )
							command_buffer >> this->_fragment_shader_filename;
						else if ( command == "near" )
							command_buffer >> this->_near;
						else if ( command == "far" )
							command_buffer >> this->_far;
						else if ( command == "field_of_view" )
							command_buffer >> this->_field_of_view;
						else if ( command == "camera_step" )
							command_buffer >> this->_camera_step;
						else if ( command == "camera_distance" )
							command_buffer >> this->_camera_distance;
						else if ( command.substr(0,command.length()-1) == "light_cutoff" )
						{
							int	i = (command[command.length()-1] - '0');


							


							if ( i < 4 )
								command_buffer >> this->_lights_cuttoff[i];
						}
						else if ( command.substr(0,command.length()-1) == "light_exponent" )
						{
							int	i = (command[command.length()-1] - '0');


							


							if ( i < 4 )
								command_buffer >> this->_lights_exponent[i];
						}
						else if ( command == "current_season" )
						{
							command_buffer >> this->_current_season;

							if ( this->_current_season > 3 )
								this->_current_season = 0;
						}
						else if ( command == "sun_distance" )
							command_buffer >> this->_sun_distance;
						else if ( command == "day_cycle_time" )
							command_buffer >> this->_day_cycle_time;
						else if ( command == "season_cycle_time" )
						{
							command_buffer >> this->_season_cycle_time;

							if ( this->_season_cycle_time > 100 )
								this->_season_cycle_time = 100;
							else if ( this->_season_cycle_time < 1 )
								this->_season_cycle_time = 1;
						}
						else if ( command == "tree_levels" )
							command_buffer >> this->_tree_levels;
						else if ( command == "tree_branching_factor" )
							command_buffer >> this->_tree_branching_factor;
						else if ( command == "tree_width_radius" )
							command_buffer >> this->_tree_width_radius;
						else if ( command == "tree_height" )
							command_buffer >> this->_tree_height;
						else if ( command == "tree_branch_stacks" )
							command_buffer >> this->_tree_branch_stacks;
						else if ( command == "tree_branch_slices" )
							command_buffer >> this->_tree_branch_slices;
						else if ( command == "tree_leaves_size" )
							command_buffer >> this->_tree_leaves_size;
						else if ( command == "tree_leaves_mass" )
							command_buffer >> this->_tree_leaves_mass;
						else if ( command == "globe_stacks" )
							command_buffer >> this->_globe_stacks;
						else if ( command == "globe_slices" )
							command_buffer >> this->_globe_slices;
						else if ( command == "globe_radius" )
							command_buffer >> this->_globe_radius;
						else if ( command == "terrain_radius" )
							command_buffer >> this->_terrain_radius;
						else if ( command == "terrain_height" )
							command_buffer >> this->_terrain_height;
						else if ( command == "terrain_stacks" )
							command_buffer >> this->_terrain_stacks;
						else if ( command == "terrain_slices" )
							command_buffer >> this->_terrain_slices;
						else if ( command == "pool_a_radius" )
							command_buffer >> this->_pool_a_radius;
						else if ( command == "pool_b_radius" )
							command_buffer >> this->_pool_b_radius;
						else if ( command == "pool_height" )
							command_buffer >> this->_pool_height;
						else if ( command == "pool_stacks" )
							command_buffer >> this->_pool_stacks;
						else if ( command == "pool_slices" )
							command_buffer >> this->_pool_slices;
						else if ( command == "pool_height_stacks" )
							command_buffer >> this->_pool_height_stacks;
						else if ( command == "snow_mount_height" )
							command_buffer >> this->_snow_mount_height;
						else if ( command == "light_sphere_radius" )
							command_buffer >> this->_light_sphere_radius;
						else if ( command == "light_sphere_stacks" )
							command_buffer >> this->_light_sphere_stacks;
						else if ( command == "light_sphere_slices" )
							command_buffer >> this->_light_sphere_slices;
						else if ( command == "fire_density" )
							command_buffer >> this->_fire_density;
						else if ( command == "smoke_density" )
							command_buffer >> this->_smoke_density;
						else if ( command == "snow_density" )
							command_buffer >> this->_snow_density;
						else if ( command == "grass_density" )
							command_buffer >> this->_grass_density;

						if ( command == "lightning_density" )
							command_buffer >> this->_lightning_density;
						else if ( command == "storm_density" )
							command_buffer >> this->_storm_density;
						else if ( command == "rain_density" )
							command_buffer >> this->_rain_density;
						else if ( command == "fire_size" )
							command_buffer >> this->_fire_size;
						else if ( command == "fire_mass" )
							command_buffer >> this->_fire_mass;
						else if ( command == "fire_lifespan" )
							command_buffer >> this->_fire_lifespan;
						else if ( command == "fire_delay" )
							command_buffer >> this->_fire_delay;
						else if ( command == "fire_spread" )
							command_buffer >> this->_fire_spread;
						else if ( command == "smoke_size" )
							command_buffer >> this->_smoke_size;
						else if ( command == "smoke_mass" )
							command_buffer >> this->_smoke_mass;
						else if ( command == "smoke_lifespan" )
							command_buffer >> this->_smoke_lifespan;
						else if ( command == "smoke_delay" )
							command_buffer >> this->_smoke_delay;
						else if ( command == "smoke_spread" )
							command_buffer >> this->_smoke_spread;
						else if ( command == "snow_size" )
							command_buffer >> this->_snow_size;
						else if ( command == "snow_mass" )
							command_buffer >> this->_snow_mass;
						else if ( command == "snow_lifespan" )
							command_buffer >> this->_snow_lifespan;
						else if ( command == "snow_delay" )
							command_buffer >> this->_snow_delay;
						else if ( command == "snow_spread" )
							command_buffer >> this->_snow_spread;
						else if ( command == "grass_size" )
							command_buffer >> this->_grass_size;
						else if ( command == "grass_mass" )
							command_buffer >> this->_grass_mass;
						else if ( command == "grass_delay" )
							command_buffer >> this->_grass_delay;
						else if ( command == "grass_spread" )
							command_buffer >> this->_grass_spread;
						else if ( command == "lightning_size" )
							command_buffer >> this->_lightning_size;
						else if ( command == "lightning_mass" )
							command_buffer >> this->_lightning_mass;
						else if ( command == "lightning_lifespan" )
							command_buffer >> this->_lightning_lifespan;
						else if ( command == "lightning_delay" )
							command_buffer >> this->_lightning_delay;
						else if ( command == "lightning_spread" )
							command_buffer >> this->_lightning_spread;
						else if ( command == "storm_size" )
							command_buffer >> this->_storm_size;
						else if ( command == "storm_mass" )
							command_buffer >> this->_storm_mass;
						else if ( command == "storm_lifespan" )
							command_buffer >> this->_storm_lifespan;
						else if ( command == "storm_delay" )
							command_buffer >> this->_storm_delay;
						else if ( command == "storm_radius" )
							command_buffer >> this->_storm_radius;
						else if ( command == "rain_size" )
							command_buffer >> this->_rain_size;
						else if ( command == "rain_mass" )
							command_buffer >> this->_rain_mass;
						else if ( command == "rain_lifespan" )
							command_buffer >> this->_rain_lifespan;
						else if ( command == "rain_delay" )
							command_buffer >> this->_rain_delay;
						else if ( command == "rain_spread" )
							command_buffer >> this->_rain_spread;
						else if ( command == "house_rotation" )
							command_buffer >> this->_house_rotation;
						else if ( command == "house_scale" )
							command_buffer >> this->_house_scale;
						else if ( command == "render_model" )
						{
							command_buffer >> this->_render_model;

							if ( this->_render_model > 4 )
								this->_render_model = 0;
						}
					}
				}
			}
		}
	}
};

void	SceneManager::_set_viewport()
{
	float		f = tan(Object::_PI*0.5f - SceneManager::_field_of_view*Object::_PI_DIV_180);
	Matrix4x4f	temp(	f / this->_ratio,0.0f,0.0f,0.0f,
						0.0f,f , 0.0f,0.0f,
						0.0f,0.0f,(SceneManager::_far + SceneManager::_near) / (SceneManager::_near - SceneManager::_far) , 2 * SceneManager::_near * SceneManager::_near / (SceneManager::_near - SceneManager::_far),
						0.0f,0.0f,-1.0f,0.0f
					);


	glViewport(0,0,this->_window_width,this->_window_height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMultMatrixf(temp.get());	

	glMatrixMode(GL_MODELVIEW);
};


void	SceneManager::_set_camera_position()
{
	if ( !this->_camera_free )
		this->_camera.position(Vector3f(
									cos(this->_yaw_angle*Object::_PI/180)*this->_camera_distance,
									sin(this->_pitch_angle*Object::_PI/180)*this->_camera_distance , 
									-sin(this->_yaw_angle*Object::_PI/180)*this->_camera_distance 
								));
	else
	{
		this->_camera.looking_at(Vector3f(
									cos(this->_yaw_angle*Object::_PI/180),
									sin(this->_pitch_angle*Object::_PI/180) , 
									-sin(this->_yaw_angle*Object::_PI/180)
								));
	}
};

void	SceneManager::_camera_yaw( const float value )
{
	this->_yaw_angle += value;

	if ( this->_yaw_angle < 0.0f )	this->_yaw_angle += 360.0f;
	else if ( this->_yaw_angle > 360.f )	this->_yaw_angle -= 360.0f;

	this->_set_camera_position();
};

void	SceneManager::_camera_roll( const float value )
{
	this->_pitch_angle += value;
	
	if ( this->_pitch_angle <= 5.0f )	this->_pitch_angle = 5.0f;
	else if ( this->_pitch_angle >= 90.f )	this->_pitch_angle = 90.0f;
	
	this->_set_camera_position();
};

void	SceneManager::_camera_zoom( const float value )
{
	this->_zoom += value;

	if ( this->_zoom > 2.0f )	this->_zoom = 2.0f;
	else if ( this->_zoom < 0.25f ) this->_zoom = 0.25f;

	this->_camera.zoom(this->_zoom);
};

void	SceneManager::_check_key_state( const bool repeat )
{
	for ( unsigned int i = 0;  i < 256;  ++i )
	{
		if ( this->_key_state[i] )
		{
			if ( repeat )
			{
				switch( i )
				{
					case	VK_UP:			this->_camera_roll(20.0f*this->_camera_step);	break;
					case	VK_DOWN:		this->_camera_roll(-20.0f*this->_camera_step);	break;
					case	VK_LEFT:		this->_camera_yaw(20.0f*this->_camera_step);	break;
					case	VK_RIGHT:		this->_camera_yaw(-20.0f*this->_camera_step);	break;
				}
			}
			else
			{
				switch ( i )
				{
					case	VK_ADD:
					case	VK_OEM_PLUS :	
											++this->_season_cycle_time;
										
											if ( this->_season_cycle_time > 100 )
												this->_season_cycle_time = 100;

											if ( this->_current_season == 2 )
												this->_tree.change_fall_time(static_cast<float>(this->_day_cycle_time*this->_season_cycle_time*1.05f),this->_day_cycle_time*this->_season_cycle_time*0.05f);
											else
												this->_tree.change_fall_time(this->_day_cycle_time*this->_season_cycle_time*0.75f,this->_day_cycle_time*this->_season_cycle_time*0.1f);
											
											this->_particle_systems.particle_energy(20,static_cast<float>(this->_day_cycle_time*this->_season_cycle_time*4.0f));
											
											break;
				
					case	VK_SUBTRACT:
					case	VK_OEM_MINUS :	
											--this->_season_cycle_time;

											if ( this->_season_cycle_time < 1 )
												this->_season_cycle_time = 1;


											if ( this->_current_season == 2 )
												this->_tree.change_fall_time(static_cast<float>(this->_day_cycle_time*this->_season_cycle_time*1.05f),this->_day_cycle_time*this->_season_cycle_time*0.05f);
											else
												this->_tree.change_fall_time(this->_day_cycle_time*this->_season_cycle_time*0.75f,this->_day_cycle_time*this->_season_cycle_time*0.1f);
											

											this->_particle_systems.particle_energy(20,static_cast<float>(this->_day_cycle_time*this->_season_cycle_time*4.0f));
											
											break;

					case	'M' :			
											++this->_render_model;	
										
											if ( this->_render_model > 4 )
												this->_render_model = 0;

											this->_update_render_parameters();
											break;
					case	'S':
											this->_toggle_directional_lights = !this->_toggle_directional_lights;
											break;

					case	'P':			
											this->_pause = !this->_pause;
											break;
				};
			}
		}
	}
};

// Choose the appropriate render parameters
void	SceneManager::_update_render_parameters()
{
	bool	materials = true;
	bool	textures = true;



	switch( this->_render_model )
	{
		case	0:	
					glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
					glEnable(GL_CULL_FACE);
					glEnable(GL_LIGHTING);
					glShadeModel(GL_SMOOTH);
					glEnable(GL_TEXTURE_2D);
					//this->_program.apply();
					this->_shader_use_textures = true;
					this->_shader_normal_mapping = true;
					break;
		case	1:	
					glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
					glDisable(GL_LIGHTING);
					glDisable(GL_CULL_FACE);
					glDisable(GL_TEXTURE_2D);
					materials = false;
					textures = false;
					//this->_program.remove();
					this->_shader_use_textures = false;
					this->_shader_normal_mapping = false;
					break;
		case	2: 
					glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
					glEnable(GL_CULL_FACE);
					glEnable(GL_LIGHTING);
					glShadeModel(GL_FLAT);
					glDisable(GL_TEXTURE_2D);
					textures = false;
					//this->_program.remove();
					this->_shader_use_textures = false;
					this->_shader_normal_mapping = false;
					break;
		case	3:	
					glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
					glEnable(GL_CULL_FACE);
					glEnable(GL_LIGHTING);
					glShadeModel(GL_SMOOTH);
					glDisable(GL_TEXTURE_2D);
					textures = false;
					//this->_program.apply();
					this->_shader_use_textures = false;
					this->_shader_normal_mapping = false;
					break;
		case	4:	
					glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
					glEnable(GL_CULL_FACE);
					glEnable(GL_LIGHTING);
					glShadeModel(GL_SMOOTH);
					glEnable(GL_TEXTURE_2D);
					//this->_program.apply();
					this->_shader_use_textures = true;
					this->_shader_normal_mapping = false;
					break;
	};


	this->_globe.use_material(materials);
	this->_terrain.use_material(materials);
	this->_pool.use_material(materials);
	this->_tree.use_material(materials);
	this->_snow_mounts.use_material(materials);
	this->_light_spheres[0].use_material(materials);
	this->_light_spheres[1].use_material(materials);
	this->_light_spheres[2].use_material(materials);
	this->_light_spheres[3].use_material(materials);
	this->_sun_sphere.use_material(materials);
	this->_moon_sphere.use_material(materials);
	this->_particle_systems.use_material(0,materials);
	this->_particle_systems.use_material(1,materials);
	this->_particle_systems.use_material(2,materials);
	this->_particle_systems.use_material(3,materials);
	this->_particle_systems.use_material(4,materials);
	this->_particle_systems.use_material(5,materials);
	this->_particle_systems.use_material(6,materials);
	this->_particle_systems.use_material(7,materials);
	this->_particle_systems.use_material(8,materials);
	this->_particle_systems.use_material(9,materials);
	this->_particle_systems.use_material(10,materials);
	this->_particle_systems.use_material(11,materials);
	this->_particle_systems.use_material(12,materials);
	this->_particle_systems.use_material(13,materials);
	this->_particle_systems.use_material(14,materials);
	this->_particle_systems.use_material(15,materials);
	this->_particle_systems.use_material(16,materials);
	this->_particle_systems.use_material(17,materials);
	this->_particle_systems.use_material(18,materials);
	this->_particle_systems.use_material(19,materials);
	this->_particle_systems.use_material(20,materials);
	this->_globe.use_textures(textures);
	this->_terrain.use_textures(textures);
	this->_pool.use_textures(textures);
	this->_tree.use_textures(textures);
	this->_snow_mounts.use_textures(textures);
	this->_light_spheres[0].use_textures(textures);
	this->_light_spheres[1].use_textures(textures);
	this->_light_spheres[2].use_textures(textures);
	this->_light_spheres[3].use_textures(textures);
	this->_sun_sphere.use_textures(textures);
	this->_moon_sphere.use_textures(textures);
	this->_particle_systems.use_textures(0,textures);
	this->_particle_systems.use_textures(1,textures);
	this->_particle_systems.use_textures(2,textures);
	this->_particle_systems.use_textures(3,textures);
	this->_particle_systems.use_textures(4,textures);
	this->_particle_systems.use_textures(5,textures);
	this->_particle_systems.use_textures(6,textures);
	this->_particle_systems.use_textures(7,textures);
	this->_particle_systems.use_textures(8,textures);
	this->_particle_systems.use_textures(9,textures);
	this->_particle_systems.use_textures(10,textures);
	this->_particle_systems.use_textures(11,textures);
	this->_particle_systems.use_textures(12,textures);
	this->_particle_systems.use_textures(13,textures);
	this->_particle_systems.use_textures(14,textures);
	this->_particle_systems.use_textures(15,textures);
	this->_particle_systems.use_textures(16,textures);
	this->_particle_systems.use_textures(17,textures);
	this->_particle_systems.use_textures(18,textures);
	this->_particle_systems.use_textures(19,textures);
	this->_particle_systems.use_textures(20,textures);
};

// change the position of the sun and moon
void	SceneManager::_update_sun_and_moon()
{
	Colour	temp;
	float	sun_sin = sin(this->_day_light_angle*Object::_PI/180.0f);
	float	sun_cos = cos(this->_day_light_angle*Object::_PI/180.0f);
	float	moon_sin = sin((this->_day_light_angle+180)*Object::_PI/180.0f);
	float	moon_cos = cos((this->_day_light_angle+180)*Object::_PI/180.0f);
	float	abs_sun_sin = abs(sun_sin);
	float	abs_moon_sin = abs(moon_sin);



	this->_sun.position(Vector3f(this->_sun_distance*sun_cos,
								 this->_sun_distance*sun_sin, 
								 0));
	this->_moon.position(Vector3f(this->_sun_distance*moon_cos,
								 this->_sun_distance*moon_sin , 
								 0));

	this->_sun_sphere.position(this->_sun.position());
	this->_moon_sphere.position(this->_moon.position());

	this->_sun.direction(Vector3f(-sun_cos,-sun_sin,0));
	this->_moon.direction(Vector3f(-moon_cos,-moon_sin,0));

	
	temp.colour(this->_sun_colour.ambient().colour()*abs_sun_sin);
	this->_sun.ambient(temp);
	temp.colour(this->_sun_colour.diffuse().colour()*abs_sun_sin);
	this->_sun.diffuse(temp);
	temp.colour(this->_sun_colour.specular().colour()*abs_sun_sin);
	this->_sun.specular(temp);
		

	temp.colour(this->_moon_colour.ambient().colour()*abs_moon_sin);
	this->_moon.ambient(temp);
	temp.colour(this->_moon_colour.diffuse().colour()*abs_moon_sin);
	this->_moon.diffuse(temp);
	temp.colour(this->_moon_colour.specular().colour()*abs_moon_sin);
	this->_moon.specular(temp);
};

// change the angle of the sun and the moon rotation,and indirectly 
// keep track of the time of the day.
void	SceneManager::_update_day_time( const double amount )
{
	this->_day_light_angle += static_cast<const float>(amount);


	if ( this->_day_light_angle >= 360.0f )
	{
		this->_day_light_angle -= 360.0f;
		++this->_days_passed;
	}

	this->_update_sun_and_moon();
};

// function responsible for the management of each season's animation and events
void	SceneManager::_update_season( const double amount )
{
	// the remaining of the current season
	float	remaining = static_cast<float>(this->_season_cycle_time) - (static_cast<float>(this->_days_passed) + this->_day_light_angle*0.00278f);



	// if it's winter
	if ( this->_current_season == 0 )
	{
		// increase the snow level
		if ( remaining <= (0.8f*static_cast<float>(this->_season_cycle_time))  &&  remaining >= 0.5f*static_cast<float>(this->_season_cycle_time) )
		{
			this->_snow_mount_draw_scale = static_cast<GLfloat>((static_cast<float>(this->_season_cycle_time*0.8f)-remaining)/static_cast<float>(this->_season_cycle_time*0.3f));
			this->_snow_mounts.position(this->_snow_mounts_position + Vector3f(0.0f,(-1.0f + this->_snow_mount_draw_scale)*this->_snow_mount_height,0.0f));
		}
		// snow levels static
		else if ( remaining < 0.5f*static_cast<float>(this->_season_cycle_time)  &&  remaining > 0.25f*static_cast<float>(this->_season_cycle_time) )
		{
			this->_snow_mount_draw_scale = 1.0f;
			this->_snow_mounts.position(this->_snow_mounts_position);
		}
		// snow levels falling
		else if ( remaining <= 0.25f*static_cast<float>(this->_season_cycle_time) )
		{
			this->_snow_mount_draw_scale = 1.0f - static_cast<GLfloat>((static_cast<float>(0.25f*this->_season_cycle_time)-remaining)/static_cast<float>(0.25f*this->_season_cycle_time));
			this->_snow_mounts.position(this->_snow_mounts_position + Vector3f(0.0f,(-1.0f + this->_snow_mount_draw_scale)*this->_snow_mount_height,0.0f));
		}

		
		// stop the snow particle systems when we reach either the 75% of the season or the point where the maximum delay of the
		// snow particles exceed the remainder of the season
		if ( remaining <= max(this->_snow_delay/static_cast<GLfloat>(this->_day_cycle_time),(0.25f*static_cast<float>(this->_season_cycle_time))) )
		{
			this->_particle_systems.stop(2);
			this->_particle_systems.stop(3);
			this->_particle_systems.stop(4);
			this->_particle_systems.stop(5);
			this->_particle_systems.stop(6);
			this->_particle_systems.stop(7);
			this->_particle_systems.stop(8);
			this->_particle_systems.stop(9);
		}

		// stop emitting cloud particles 
		if ( remaining <= max(this->_storm_delay/static_cast<GLfloat>(this->_day_cycle_time),0.1f*static_cast<float>(this->_season_cycle_time)) )
			this->_particle_systems.stop(11);

		// stop emitting smoke from the chimney
		if ( remaining <= max(this->_smoke_delay/static_cast<GLfloat>(this->_day_cycle_time),(0.05f*static_cast<float>(this->_season_cycle_time))) )
			this->_particle_systems.stop(1);
	}
	// if it's spring, the tree grows
	else if ( this->_current_season == 1 )
	{
		this->_tree_draw_scale = 1.0f - remaining/static_cast<float>(this->_season_cycle_time);
		this->_tree_max_draw_level = static_cast<unsigned int>((this->_tree_levels+1)*this->_tree_draw_scale);
	}
	// during summer we have nothing to do
	/*else if ( this->_current_season == 2 )
	{
		
	}*/
	// during autumn
	else if ( this->_current_season == 3 )
	{
		// start the rain emitters
		if ( !this->_particle_systems.emitting(11) )
		{
			if ( remaining <= (0.75f*static_cast<float>(this->_season_cycle_time)) )
			{
				this->_particle_systems.start(11);
				this->_particle_systems.start(12);
				this->_particle_systems.start(13);
				this->_particle_systems.start(14);
				this->_particle_systems.start(15);
				this->_particle_systems.start(16);
				this->_particle_systems.start(17);
				this->_particle_systems.start(18);
				this->_particle_systems.start(19);
			}
		}

		// when the timing is right, enable the lightning emitter
		if ( !this->_particle_systems.emitting(10) )
		{
			if ( remaining <= (0.63f*static_cast<float>(this->_season_cycle_time) + this->_lightning_delay/this->_day_cycle_time ) )
					this->_particle_systems.start(10);
		}

		// once the lightning hits, fire breaks out
		if ( !this->_particle_systems.emitting(0) )
		{
			if ( remaining <= (0.63f*static_cast<float>(this->_season_cycle_time)) )
				this->_particle_systems.start(0);
		}

		// and the tree burns
		if ( remaining <= (0.33f*static_cast<float>(this->_season_cycle_time)) )
		{
			this->_tree_draw_scale = remaining/(static_cast<float>(this->_season_cycle_time)*0.33f);
			this->_tree_max_draw_level = static_cast<unsigned int>((this->_tree_levels+1)*this->_tree_draw_scale);
		}
	}


	// update the particle systems
	this->_tree.move_leaves(static_cast<float>(amount));
	this->_particle_systems.update(static_cast<float>(amount));


	// update the season when necessary
	if ( this->_days_passed >= this->_season_cycle_time )
	{
		this->_days_passed = 0;
		++this->_current_season;

		if ( this->_current_season > 3 )
			this->_current_season = 0;

		this->_init_season();
	}
};

// season initialization and reset function
void	SceneManager::_init_season()
{
	if ( this->_current_season == 0 )
	{
		this->_tree_max_draw_level = 0;
		this->_tree_draw_scale = 0.0f;
		this->_snow_mount_draw_scale = 0.0f;
		this->_snow_mounts.position(this->_snow_mounts_position - Vector3f(0.0f,this->_snow_mount_height,0.0f));
		this->_particle_systems.stop(0);
		this->_particle_systems.stop(10);
		this->_particle_systems.stop(12);
		this->_particle_systems.stop(13);
		this->_particle_systems.stop(14);
		this->_particle_systems.stop(15);
		this->_particle_systems.stop(16);
		this->_particle_systems.stop(17);
		this->_particle_systems.stop(18);
		this->_particle_systems.stop(19);

		if ( !this->_particle_systems.emitting(11 ) )
			this->_particle_systems.start(11);

		this->_particle_systems.start(1);
		this->_particle_systems.start(2);
		this->_particle_systems.start(3);
		this->_particle_systems.start(4);
		this->_particle_systems.start(5);
		this->_particle_systems.start(6);
		this->_particle_systems.start(7);
		this->_particle_systems.start(8);
		this->_particle_systems.start(9);
	}
	else if ( this->_current_season == 1 )
	{
		this->_particle_systems.start(20);
		this->_snow_mount_draw_scale = 0.0f;
		this->_snow_mounts.position(this->_snow_mounts_position - Vector3f(0.0f,this->_snow_mount_height,0.0f));
		this->_tree.force_hide_leaves();
		this->_tree.update();
	}
	else if ( this->_current_season == 2 )
	{
		this->_tree_max_draw_level = this->_tree_levels+1;
		this->_tree_draw_scale = 1.0f;
		this->_tree.change_fall_time(static_cast<float>(this->_day_cycle_time*this->_season_cycle_time*1.05f),this->_day_cycle_time*this->_season_cycle_time*0.05f);
		this->_tree.grow_leaves();
	}
	else if ( this->_current_season == 3 )
	{
		this->_particle_systems.reset(10);
		this->_tree.change_fall_time(this->_day_cycle_time*this->_season_cycle_time*0.75f,this->_day_cycle_time*this->_season_cycle_time*0.1f);
		this->_tree.shed_leaves();
		this->_tree.hide_leaves();
	}
};


// function for randomly placing grass on the terrain 
// on a terrain_radius - 5*grass_size circle, excluding the pool position
void	SceneManager::_create_grass()
{
	Matrix4x4f	location;
	float		radius = (this->_terrain_radius-this->_grass_size);
	float		a_sqr = pow(this->_pool_a_radius*1.06f,2.0f);
	float		b_sqr = pow(this->_pool_b_radius*1.06f,2.0f);
	float		ab_sqr = a_sqr*b_sqr + this->_grass_size;



	srand(static_cast<unsigned int>(time(NULL)));
	for ( unsigned int i = 0;  i < this->_grass_density;  ++i )
	{
		Vector3f	position;
		bool		placed = false;
		
		
		
		do
		{
			do
			{
				position.set((rand()%2001-1000)*0.001f*radius,0.0f,(rand()%2001-1000)*0.001f*radius); 
			}while( position.length() > this->_terrain_radius );
		
		
			float		distance = b_sqr*pow(position.x()-this->_pool_position.x(),2) + a_sqr*pow(position.z()-this->_pool_position.z(),2);



			if (  (distance - ab_sqr) > Vector3f::_V3EPSILON )
			{
				position.y(this->_grass_size);
				location.identity();
				location.translate(position);
				this->_grass_positions.push_back(location);
				placed = true;
			}
		}while( !placed );
	}
};


// function for generating the positions of the particles of the lightning emitter
void	SceneManager::_create_lightning()
{
	Matrix4x4f	location;
	float		distance_between_particles = this->_lightning_size*0.5f;
	Vector3f	step((this->_tree_position - this->_lightning_position) *  (1.0f/static_cast<float>(this->_lightning_density)) );
	float		delay_step = this->_lightning_delay/static_cast<float>(this->_lightning_density);
	Vector3f	current_position(0.0f,0.0f,0.0f);
	float		current_delay = 0.0f;

	

	srand(static_cast<unsigned int>(time(NULL)));
	for ( unsigned int i = 0;  i < this->_lightning_density;  ++i )
	{

		location.identity();
		location.translate(current_position + Vector3f((rand()%201-100)*0.01f*distance_between_particles,(rand()%201-100)*0.01f*distance_between_particles,(rand()%201-100)*0.01f*distance_between_particles));
		this->_lightning_positions.push_back(location);
		this->_lightning_delays.push_back(current_delay);


		current_position += step;
		current_delay += delay_step;
	}
};

// function for creating the sotrm particles in a circle with random positions
void	SceneManager::_create_storm()
{
	Matrix4x4f	location;



	srand(static_cast<unsigned int>(time(NULL)));
	for ( unsigned int i = 0;  i < this->_storm_density;  ++i )
	{
		Vector3f	position;
		
		
		
		do
		{
			position.set((rand()%2001-1000)*0.001f*this->_storm_radius,0.0f,(rand()%2001-1000)*0.001f*this->_storm_radius); 
		}while( position.length() > this->_storm_radius );

		location.identity();
		location.translate(position);
		this->_storm_positions.push_back(location);
	};
};


// constructor of the class, used to initialise the variables of the class with their default/ hard coded values, for easy fallback in case of missing
// or incomplete configuration file
SceneManager::SceneManager( const int width , const int height )	:
	_particle_systems(21) , _window_background(0.0f,0.0f,0.0f,1.0f) , _reflection(1.0f,-1.0f,1.0f) , 
	_leaf_planes(2,vector<Vector3f>(3)) , 
	_roof_planes(8,vector<Vector3f>(3)) ,
	_snow_mount_planes(6,vector<Vector3f>(3)) ,
	_globe_position(0.0f,0.0f,0.0f) , _terrain_position(0.0f,0.0f,0.0f), _pool_position(10.0f,-0.2f,30.0f) , 
	_tree_position(20.0f,0.001f,6.0f) , _house_position(-18.0f,0.9f,12.0f) , _snow_mounts_position(0.0f,0.001f,0.0f) , 
	_fire_position(20.0f,0.001f,6.0f) , _smoke_position(-1.15f,28.0f,-24.5f) , _grass_position(0.0f,0.001f,0.0f) , 
	_lightning_position(0.0f,0.0f,0.0f) , _storm_position(0.0f,0.0f,0.0f) ,
	_rain_position(0.0f,0.0f,0.0f) , _rain_position2(0.0f,0.0f,0.0f) , _rain_position3(0.0f,0.0f,0.0f) , _rain_position4(0.0f,0.0f,0.0f) , 
	_rain_position5(0.0f,0.0f,0.0f) , _rain_position6(0.0f,0.0f,0.0f) , _rain_position7(0.0f,0.0f,0.0f) , _rain_position8(0.0f,0.0f,0.0f) , 
	_fire_speed(0.0f,3.5f,0.0f) , _smoke_speed(0.0f,1.3f,0.0f) ,  _snow_speed(0.0f,-2.5f,0.0f) , 
	_lightning_speed(0.0f,0.0f,0.0f) , _storm_speed(0.0f,0.0f,0.0f) , _rain_speed(0.0f,-4.0f,0.0f) , 
	_leaf_acceleration(0.0f,-0.66f,0.0f) , _fire_acceleration(0.0f,0.5f,0.0f) , _smoke_acceleration(0.0f,0.005f,0.0f) , _snow_acceleration(0.0f,-0.01f,0.0f) , 
	_lightning_acceleration(0.0f,0.0f,0.0f) , _storm_acceleration(0.0f,0.0f,0.0f) , _rain_acceleration(0.0f,-0.03f,0.0f) , 
	_globe_material(Colour(0.1f,0.1f,0.1f,0.15f),Colour(0.1f,0.1f,0.1f,0.15f),Colour(1.0f,1.0f,1.0f,1.0f),Colour(0.0f,0.0f,0.0f,0.0f),128.0f) , 
	_terrain_material(Colour(0.1f,0.1f,0.1f,0.25f),Colour(0.075f,0.15f,0.03f,1.0f),Colour(0.0f,0.0f,0.0f,0.0f),Colour(0.0f,0.0f,0.0f,0.0f),0.0f) , 
	_pool_material(Colour(0.1f,0.1f,0.1f,0.25f),Colour(0.2f,0.2f,0.35f,0.25f),Colour(1.0f,1.0f,1.0f,1.0f),Colour(0.0f,0.0f,0.0f,0.0f),128.0f) , 
	_tree_material(Colour(0.1f,0.1f,0.1f,0.25f),Colour(0.35f,0.15f,0.02f,1.0f),Colour(0.0f,0.0f,0.0f,0.0f),Colour(0.0f,0.0f,0.0f,0.0f),0.0f) , 
	_snow_mount_material(Colour(0.35f,0.35f,0.35f,0.35f),Colour(1.0f,1.0f,1.0f,1.0f),Colour(1.0f,1.0f,1.0f,1.0f),Colour(0.0f,0.0f,0.0f,0.0f),32.0f) , 
	_globe_colour(0.15f,0.15f,0.15f,0.2f) , _terrain_top_colour(0.075f,0.15f,0.03f,1.0f) , _terrain_bottom_colour(0.28f,0.11f,0.0f,1.0f) , 
	_pool_colour(0.2f,0.2f,0.35f,0.25f) , _tree_colour(0.35f,0.15f,0.02f,1.0f) , _snow_mount_colour(0.85f,0.85f,0.85f,1.0f) , 
	_sun_colour(Colour(0.75f,0.75f,0.75f,1.0f),Colour(1.0f,1.0f,0.8f,1.0f),Colour(1.0f,1.0f,1.0f,1.0f),Colour::colour_null()) , 
	_moon_colour(Colour(0.30f,0.30f,0.30f,0.40f),Colour(0.50f,0.50f,0.50f,1.0f),Colour(0.80f,0.80f,0.80f,1.0f),Colour::colour_null()) ,  
	_house_model_filename("scheune.3ds") , _terrain_texture_filename("Seamless_grass_texture_by_hhh316.jpg") , _pool_texture_filename("Water_Texture_by_Jshei.jpg") , 
	_tree_bark_texture_filename("Bark_Texture_II_by_Neriah_stock.jpg") , _tree_leaf_texture_filename("Green_Leaf_Texture_by_SpiralGraphic.tga") , 
	_snow_mounts_texture_filename("snow.jpg") , _smoke_texture_filename("Smoke.tga") , _snow_texture_filename("Purple_Snowflake.tga") , _grass_texture_filename("billboard_grass.tga") ,
	_lightning_texture_filename("lightning.tga") , _storm_texture_filename("Smoke.tga") , _rain_texture_filename("blue-water-droplet-icon.tga") , 
	_vertex_shader_filename("main_shader.vert") , _fragment_shader_filename("main_shader.frag") , 
	_window_width( (width >= 1 ? width : 1) ) , _window_height( ( height >= 1 ? height : 1 ) ) ,
	_ratio(static_cast<float>(_window_width) / static_cast<float>(_window_height)) , 
	_current_time(App::GetTime()) ,
	_near(-1.0f) , _far(100.0f) , _field_of_view(45.0f) , 
	_camera_step(0.1f) , _camera_distance(60.0f) , _zoom(1.0f) , _camera_free(false) , _yaw_angle(270.0f) , _pitch_angle(30.0f) , 
	_toggle_directional_lights(false) , _current_season(0) , _days_passed(0) , _day_light_angle(0.0f) , _sun_distance(50.0f) , 
	_day_cycle_time(30) , _season_cycle_time(1) ,  
	_tree_levels(4) , _tree_branching_factor(7) , _tree_width_radius(0.75f) , _tree_height(14.5f) , _tree_branch_stacks(1) , _tree_branch_slices(20) ,
	_tree_max_draw_level(0) , _tree_leaves_size(0.35f) , _tree_leaves_mass(1.0f) , _tree_draw_scale(0.0f) ,
	_globe_stacks(120) , 	_globe_slices(120) , _globe_radius(45.0f) ,
	_terrain_radius(44.75f) , _terrain_height(4.475f) , _terrain_stacks(1200) , _terrain_slices(1200) ,
	_pool_a_radius(17.0f) , _pool_b_radius(12.0f) , _pool_height(3.38f) , _pool_stacks(20) , _pool_slices(60) , _pool_height_stacks(1) , 
	_snow_mount_height(0.5f) , _snow_mount_draw_scale(1.0f) ,
	_light_sphere_radius(2.0f) , _light_sphere_stacks(30) , _light_sphere_slices(30) , 
	_fire_density(500) , _smoke_density(50) , _snow_density(8000) , _grass_density(500) , 
	_lightning_density(500) , _storm_density(200) , _rain_density(8000) , 
	_fire_size(1.0f) , _fire_mass(0.2f) , _fire_lifespan(4.0f) , _fire_delay(5.375f) , _fire_spread(360.0f) , 
	_smoke_size(1.0f) , _smoke_mass(0.2f) , _smoke_lifespan(8.0f) , _smoke_delay(10.75f) , _smoke_spread(45.0f) , 
	_snow_size(0.125f) , _snow_mass(0.2f) , _snow_lifespan(24.0f) , _snow_delay (32.25f) , _snow_spread(360.0f) , 
	_grass_size(1.0f) , _grass_mass(1.0f) , _grass_delay(0.0f) , _grass_spread(0.0f) , 
	_lightning_size(0.25f) , _lightning_mass(0.02f) , _lightning_lifespan(0.75f) , _lightning_delay(0.2f) , _lightning_spread(0.0f) , 
	_storm_size(10.0f) , _storm_mass(0.2f) , _storm_lifespan(10.0f) , _storm_delay(11.34375f) , _storm_radius(_globe_radius*0.3f) , 
	_rain_size(0.0625f) , _rain_mass(0.2f) , _rain_lifespan(15.0f) , _rain_delay(20.15625f) , _rain_spread(360.0f) , 
	_house_rotation(-30.0f) , _house_scale(0.025f) , 
	_render_model(0) , _shader_use_textures(false) , _shader_normal_mapping(false) ,
	_use_textures_loc(0) , _normal_mapping_loc(0) , _directional_lights_loc(0) , _pause(false) 
{
	Vector3f	temp;



	this->_mouse_position[0] = 0;
	this->_mouse_position[1] = 0;

	this->_mouse_down[0] = false;
	this->_mouse_down[1] = false;
	this->_mouse_down[2] = false;

	for ( unsigned int i = 0;  i < 256;  ++i )
		this->_key_state[i] = false;


	this->_lights_position[0].set(45.0f,45.0f,0.0f);
	temp = -this->_lights_position[0];
	temp.normalize();
	this->_lights_direction[0] = temp;

	this->_lights_position[1].set(0.0f,45.0f,-45.0f);
	temp = -this->_lights_position[1];
	temp.normalize();
	this->_lights_direction[1] = temp;

	this->_lights_position[2].set(-45.0f,45.0f,0.0f);
	temp = -this->_lights_position[2];
	temp.normalize();
	this->_lights_direction[2] = temp;

	this->_lights_position[3].set(0.0f,45.0f,45.0f);
	temp = -this->_lights_position[3];
	temp.normalize();
	this->_lights_direction[3] = temp;


	this->_lights_colour[0].ambient(Colour(0.1f,0.1f,0.1f,0.25f));
	this->_lights_colour[1].ambient(Colour(0.1f,0.1f,0.1f,0.25f));
	this->_lights_colour[2].ambient(Colour(0.1f,0.1f,0.1f,0.25f));
	this->_lights_colour[3].ambient(Colour(0.1f,0.1f,0.1f,0.25f));

	this->_lights_colour[0].diffuse(Colour(0.8f,0.2f,0.1f,1.0f));
	this->_lights_colour[1].diffuse(Colour(0.2f,0.8f,0.1f,1.0f));
	this->_lights_colour[2].diffuse(Colour(0.1f,0.3f,0.8f,1.0f));
	this->_lights_colour[3].diffuse(Colour(0.75f,0.75f,0.3f,1.0f));

	this->_lights_colour[0].specular(Colour(1.0f,1.0f,1.0f,1.0f));
	this->_lights_colour[1].specular(Colour(1.0f,1.0f,1.0f,1.0f));
	this->_lights_colour[2].specular(Colour(1.0f,1.0f,1.0f,1.0f));
	this->_lights_colour[3].specular(Colour(1.0f,1.0f,1.0f,1.0f));
	
	this->_lights_colour[0].emission(Colour::colour_null());
	this->_lights_colour[1].emission(Colour::colour_null());
	this->_lights_colour[2].emission(Colour::colour_null());
	this->_lights_colour[3].emission(Colour::colour_null());
	

	this->_lights_cuttoff[0] = 90.0f;
	this->_lights_cuttoff[1] = 90.0f;
	this->_lights_cuttoff[2] = 90.0f;
	this->_lights_cuttoff[3] = 45.0f;
	
	this->_lights_exponent[0] = 0.0f;
	this->_lights_exponent[1] = 0.0f;
	this->_lights_exponent[2] = 0.0f;
	this->_lights_exponent[3] = 15.0f;


	this->_leaf_planes[0][0] = Vector3f(-this->_globe_radius,this->_tree_leaves_size,this->_globe_radius);
	this->_leaf_planes[0][1] = Vector3f(this->_globe_radius,this->_tree_leaves_size,this->_globe_radius);
	this->_leaf_planes[0][2] = Vector3f(this->_globe_radius,this->_tree_leaves_size,-this->_globe_radius);
	this->_leaf_planes[1][0] = this->_leaf_planes[0][2];
	this->_leaf_planes[1][1] = Vector3f(-this->_globe_radius,this->_tree_leaves_size,-this->_globe_radius);
	this->_leaf_planes[1][2] = this->_leaf_planes[0][0];

	this->_leaf_spring_materials.insert(pair<unsigned int,Material>(1100,Material(
			Colour(0.25,0.25,0.25,0.25f) , 
			Colour(0.2f,0.6f,0.1f,1.0f) , 
			Colour(0.0f,0.0f,0.0f,0.0f) , 
			Colour(0.0f,0.0f,0.0f,0.0f) , 
			0.0f
		)));
	for ( unsigned int i = 0;  i <= 20;  ++i )
		this->_leaf_autumn_materials.insert(pair<unsigned int,Material>(200-10*i,Material(
			Colour(0.25f,0.25f,0.25f,0.25f),
			Colour(0.2f + i*0.0225f,0.6f - i*0.0125f,0.1f,1.0f),
			Colour(0.0f,0.0f,0.0f,0.0f),
			Colour(0.0f,0.0f,0.0f,0.0f),
			0.0f
		)));

	this->_leaf_spring_scales.insert(pair<unsigned int,GLfloat>(1100,0.0f));
	for ( unsigned int i = 1;  i <= 50;  ++i )
		this->_leaf_spring_scales.insert(pair<unsigned int,GLfloat>(1000-10*i,min(i*0.02f,1.0f)));


	this->_leaf_autumn_materials.insert(pair<unsigned int,Material>(1100,Material(
			Colour(0.25f,0.25f,0.25f,0.25f) , 
			Colour(0.65f,0.35f,0.1f,1.0f) , 
			Colour(0.0f,0.0f,0.0f,0.0f) , 
			Colour(0.0f,0.0f,0.0f,0.0f) , 
			0.0f
		)));
	
	for ( unsigned int i = 0;  i <= 40;  ++i )
		this->_leaf_autumn_materials.insert(pair<unsigned int,Material>(400-10*i,Material(
			Colour(0.25f,0.25f,0.25f,0.25f - i*0.00625f),
			Colour(0.45f,0.6f,0.1f,1.0f - i*0.025f),
			Colour(0.0f,0.0f,0.0f,0.0f),
			Colour(0.0f,0.0f,0.0f,0.0f),
			0.0f
		)));

	this->_leaf_autumn_scales.insert(pair<unsigned int,GLfloat>(1100,1.0f));


	this->_fire_materials.insert(pair<unsigned int,Material>(1100,Material(
		Colour(0.25f,0.25f,0.25f,0.0f),
		Colour(0.75f,0.65f,0.25f,0.0f),
		Colour(0.0f,0.0f,0.0f,0.0f),
		Colour(0.75f,0.65f,0.25f,0.0f),
		0.0f)));
	this->_fire_materials.insert(pair<unsigned int,Material>(990,Material(
		Colour(0.25f,0.25f,0.25f,0.5f),
		Colour(0.75f,0.60f,0.25f,0.5f),
		Colour(0.0f,0.0f,0.0f,0.0f),
		Colour(0.75f,0.60f,0.25f,0.5f),
		0.0f)));
	for ( unsigned int i = 0;  i < 23;  ++i )
		this->_fire_materials.insert(pair<unsigned int,Material>(980 - 10*i,Material(
										Colour(0.25f,0.25f,0.25f,0.5f - i *0.005f),
										Colour(0.75f,0.60f - i*0.0043478f,0.25f - i*0.010867f,0.5f - i*0.0051f),
										Colour(0.0f,0.0f,0.0f,0.0f),
										Colour(0.75f,0.60f - i*0.0043478f,0.25f - i*0.010867f,0.5f - i*0.0051f),
										0.0f)));
	for ( unsigned int i = 0;  i < 25;  ++i )
		this->_fire_materials.insert(pair<unsigned int,Material>(750 - 10*i,Material(
										Colour(0.25f,0.25f,0.25f,0.3827f - i*0.005f),
										Colour(0.75f,0.5f - i*0.01f,0.0f,0.3827f - i*0.0051f),
										Colour(0.0f,0.0f,0.0f,0.0f),
										Colour(0.75f,0.5f - i*0.01f,0.0f,0.3827f - i*0.0051f),
										0.0f)));

	for ( unsigned int i = 0;  i < 25;  ++i )
		this->_fire_materials.insert(pair<unsigned int,Material>(500 - 10*i,Material(
										Colour(0.25f,0.25f,0.25f,0.2552f - i*0.0051f),
										Colour(0.75f - i*0.02f,0.25f,i*0.01f,0.2552f - i*0.0051f),
										Colour(0.0f,0.0f,0.0f,0.0f),
										Colour(0.75f - i*0.03f,0.25f - i*0.01f,0.0f,0.2552f - i*0.010208f),
										0.0f)));

	for ( unsigned int i = 0;  i <= 25;  ++i )
		this->_fire_materials.insert(pair<unsigned int,Material>(250 - 10*i,Material(
										Colour(0.25f,0.25f,0.25f,0.01277f - i*0.0051f),
										Colour(0.25f,0.25f,0.25f,0.01277f - i*0.0051f),
										Colour(0.0f,0.0f,0.0f,0.0f),
										Colour(0.0f,0.0f,0.0f,0.0f),
										0.0f)));

	this->_fire_scales.insert(pair<unsigned int,GLfloat>(1100,2.0f));
	for ( unsigned int i = 0;  i <= 100;  ++i )
		this->_fire_scales.insert(pair<unsigned int,GLfloat>(1000-10*i,2.0f + i*0.05f));


	this->_smoke_materials.insert(pair<unsigned int,Material>(1100,Material(
		Colour(0.25f,0.25f,0.25f,0.25f),
		Colour(0.25f,0.25f,0.25f,1.0f),
		Colour(0.0f,0.0f,0.0f,0.0f),
		Colour(0.0f,0.0f,0.0f,0.0f),
		0.0f)));
	for ( unsigned int i = 0;  i <= 100;  ++i )
		this->_smoke_materials.insert(pair<unsigned int,Material>(1000-10*i,Material(
										Colour(0.25f,0.25f,0.25f,1.0f - i*0.01f),
										Colour(0.25f,0.25f,0.25f,1.0f - i*0.01f),
										Colour(0.0f,0.0f,0.0f,0.0f),
										Colour(0.0f,0.0f,0.0f,0.0f),
										0.0f)));

	this->_smoke_scales.insert(pair<unsigned int,GLfloat>(1100,2.0f));
	for ( unsigned int i = 0;  i <= 100;  ++i )
		this->_smoke_scales.insert(pair<unsigned int,GLfloat>(1000-10*i,2.0f + i*0.06f));


	this->_roof_planes[0][0] = Vector3f(-2.0f*this->_globe_radius,0.0f,2.0f*this->_globe_radius);
	this->_roof_planes[0][1] = Vector3f(2.0f*this->_globe_radius,0.0f,2.0f*this->_globe_radius);
	this->_roof_planes[0][2] = Vector3f(2.0f*this->_globe_radius,0.0f,-2.0f*this->_globe_radius);
	this->_roof_planes[1][0] = this->_roof_planes[0][2];
	this->_roof_planes[1][1] = Vector3f(-2.0f*this->_globe_radius,0.0f,-2.0f*this->_globe_radius);
	this->_roof_planes[1][2] = this->_roof_planes[0][0];

	this->_roof_planes[2][0] = Vector3f(-7.2f,27.85f,4.65f) * this->_house_scale *40.0f;
	this->_roof_planes[2][1] = Vector3f(5.2f,9.5f,4.65f) * this->_house_scale *40.0f;
	this->_roof_planes[2][2] = Vector3f(5.2f,9.5f,-31.5f) * this->_house_scale *40.0f;
	this->_roof_planes[3][0] = this->_roof_planes[2][2];
	this->_roof_planes[3][1] = Vector3f(-7.2f,27.85f,-31.5f) * this->_house_scale *40.0f;
	this->_roof_planes[3][2] = this->_roof_planes[2][0];

	this->_roof_planes[4][0] = Vector3f(-7.85f,27.85f,4.65f) * this->_house_scale *40.0f;
	this->_roof_planes[4][1] = Vector3f(-7.2f,27.85f,4.65f) * this->_house_scale *40.0f;
	this->_roof_planes[4][2] = Vector3f(-7.2f,27.85f,-31.5f) * this->_house_scale *40.0f;
	this->_roof_planes[5][0] = this->_roof_planes[4][2];
	this->_roof_planes[5][1] = Vector3f(-7.85f,27.85f,-31.5f) * this->_house_scale *40.0f;
	this->_roof_planes[5][2] = this->_roof_planes[4][0];

	this->_roof_planes[6][0] = Vector3f(-7.85f,27.85f,4.65f) * this->_house_scale *40.0f;
	this->_roof_planes[6][1] = Vector3f(-7.85f,27.85f,-31.5f) * this->_house_scale *40.0f;
	this->_roof_planes[6][2] = Vector3f(-20.25f,9.5f,-31.5f) * this->_house_scale *40.0f;
	this->_roof_planes[7][0] = this->_roof_planes[6][2];
	this->_roof_planes[7][1] = Vector3f(-20.25f,9.5f,4.65f) * this->_house_scale *40.0f;
	this->_roof_planes[7][2] = this->_roof_planes[6][0];

	
	this->_snow_position.set(_globe_radius*0.3f*cos(45.0f*Object::_PI_DIV_180),this->_globe_radius*0.95f,_globe_radius*0.3f*-sin(45.0f*Object::_PI_DIV_180));
	this->_snow_position2.set(_globe_radius*0.3f*cos(90.0f*Object::_PI_DIV_180),this->_globe_radius*0.95f,_globe_radius*0.3f*-sin(90.0f*Object::_PI_DIV_180));
	this->_snow_position3.set(_globe_radius*0.3f*cos(135.0f*Object::_PI_DIV_180),this->_globe_radius*0.95f,_globe_radius*0.3f*-sin(135.0f*Object::_PI_DIV_180));
	this->_snow_position4.set(_globe_radius*0.3f*cos(180.0f*Object::_PI_DIV_180),this->_globe_radius*0.95f,_globe_radius*0.3f*-sin(180.0f*Object::_PI_DIV_180));
	this->_snow_position5.set(_globe_radius*0.3f*cos(225.0f*Object::_PI_DIV_180),this->_globe_radius*0.95f,_globe_radius*0.3f*-sin(225.0f*Object::_PI_DIV_180));
	this->_snow_position6.set(_globe_radius*0.3f*cos(270.0f*Object::_PI_DIV_180),this->_globe_radius*0.95f,_globe_radius*0.3f*-sin(270.0f*Object::_PI_DIV_180));
	this->_snow_position7.set(_globe_radius*0.3f*cos(315.0f*Object::_PI_DIV_180),this->_globe_radius*0.95f,_globe_radius*0.3f*-sin(315.0f*Object::_PI_DIV_180));
	this->_snow_position8.set(_globe_radius*0.3f*cos(360.0f*Object::_PI_DIV_180),this->_globe_radius*0.95f,_globe_radius*0.3f*-sin(360.0f*Object::_PI_DIV_180));
	
	this->_snow_materials.insert(pair<unsigned int,Material>(1100,Material(
		Colour(0.75f,0.75f,0.75f,0.0f),
		Colour(0.75f,0.75f,0.75f,0.0f),
		Colour(0.0f,0.0f,0.0f,0.0f),
		Colour(0.0f,0.0f,0.0f,0.0f),
		32.0f)));
	for ( unsigned int i = 0;  i <= 20;  ++i )
		this->_snow_materials.insert(pair<unsigned int,Material>(850-10*i,Material(
										Colour(0.75f,0.75f,0.75f,i*0.0175f),
										Colour(0.75f,0.75f,0.75f,i*0.05f),
										Colour(0.75f,0.75f,0.75f,i*0.05f),
										Colour(0.0f,0.0f,0.0f,0.0f),
										32.0f)));
	for ( unsigned int i = 0;  i <= 20;  ++i )
		this->_snow_materials.insert(pair<unsigned int,Material>(200-10*i,Material(
										Colour(0.75f,0.75f,0.75f,0.25f - i*0.0175f),
										Colour(0.75f,0.75f,0.75f,1.0f - i*0.05f),
										Colour(0.75f,0.75f,0.75f,1.0f - i*0.05f),
										Colour(0.0f,0.0f,0.0f,0.0f),
										32.0f)));


	this->_snow_mount_planes[0] = this->_roof_planes[2];
	this->_snow_mount_planes[1] = this->_roof_planes[3];
	this->_snow_mount_planes[2] = this->_roof_planes[4];
	this->_snow_mount_planes[3] = this->_roof_planes[5];
	this->_snow_mount_planes[4] = this->_roof_planes[6];
	this->_snow_mount_planes[5] = this->_roof_planes[7];


	this->_lightning_position.set(0.0f,this->_globe_radius*0.9f,0.0f);
	this->_lightning_materials.insert(pair<unsigned int,Material>(1100,Material(
		Colour(0.75f,0.75f,0.75f,0.0f),
		Colour(0.75f,0.75f,0.75f,0.0f),
		Colour(0.0f,0.0f,0.0f,0.0f),
		Colour(0.0f,0.0f,0.0f,0.0f),
		0.0f)));
	for ( unsigned int i = 0;  i <= 20;  ++i )
		this->_lightning_materials.insert(pair<unsigned int,Material>(1000-10*i,Material(
										Colour(0.75f,0.75f,0.75f,i*0.0125f),
										Colour(0.75f,0.75f,0.75f,i*0.0375f),
										Colour(0.0f,0.0f,0.0f,0.0f),
										Colour(0.75f,0.75f,0.75f,i*0.0375f),
										0.0f)));
	for ( unsigned int i = 0;  i <= 20;  ++i )
		this->_lightning_materials.insert(pair<unsigned int,Material>(200-10*i,Material(
										Colour(0.75f,0.75f,0.75f,0.25f - i*0.0125f),
										Colour(0.75f,0.75f,0.75f,0.75f - i*0.0375f),
										Colour(0.0f,0.0f,0.0f,0.0f),
										Colour(0.75f,0.75f,0.75f,0.75f - i*0.0375f),
										0.0f)));

	this->_lightning_scales.insert(pair<unsigned int,GLfloat>(1100,1.0f));
	for ( unsigned int i = 0;  i <= 99;  ++i )
		this->_lightning_scales.insert(pair<unsigned int,GLfloat>(1000-10*i,i*0.0404f));


	this->_storm_position.set(0.0f,this->_globe_radius*0.9f,0.0f);
	this->_storm_materials.insert(pair<unsigned int,Material>(1100,Material(
		Colour(0.25f,0.25f,0.25f,0.0f),
		Colour(0.25f,0.25f,0.25f,0.0f),
		Colour(0.0f,0.0f,0.0f,0.0f),
		Colour(0.0f,0.0f,0.0f,0.0f),
		0.0f)));
	for ( unsigned int i = 0;  i <= 20;  ++i )
		this->_storm_materials.insert(pair<unsigned int,Material>(1000-10*i,Material(
										Colour(0.25f,0.25f,0.25f,i*0.025f),
										Colour(0.25f,0.25f,0.25f,i*0.025f),
										Colour(0.0f,0.0f,0.0f,0.0f),
										Colour(0.0f,0.0f,0.0f,0.0f),
										0.0f)));
	for ( unsigned int i = 0;  i <= 20;  ++i )
		this->_storm_materials.insert(pair<unsigned int,Material>(200-10*i,Material(
										Colour(0.25f,0.25f,0.25f,0.5f - i*0.025f),
										Colour(0.25f,0.25f,0.25f,0.5f - i*0.025f),
										Colour(0.0f,0.0f,0.0f,0.0f),
										Colour(0.0f,0.0f,0.0f,0.0f),
										0.0f)));

	this->_storm_scales.insert(pair<unsigned int,GLfloat>(1100,0.0f));
	for ( unsigned int i = 0;  i < 100;  i++ )
		this->_storm_scales.insert(pair<unsigned int,GLfloat>(1000 - i,i*0.01f));


	this->_rain_position = this->_snow_position;
	this->_rain_position2 = this->_snow_position2;
	this->_rain_position3 = this->_snow_position3;
	this->_rain_position4 = this->_snow_position4;
	this->_rain_position5 = this->_snow_position5;
	this->_rain_position6 = this->_snow_position6;
	this->_rain_position7 = this->_snow_position7;
	this->_rain_position8 = this->_snow_position8;
	this->_rain_materials.insert(pair<unsigned int,Material>(1100,Material(
		Colour(0.25f,0.25f,0.25f,0.0f),
		Colour(0.25f,0.25f,0.25f,0.0f),
		Colour(0.0f,0.0f,0.0f,0.0f),
		Colour(0.0f,0.0f,0.0f,0.0f),
		0.0f)));
	for ( unsigned int i = 0;  i <= 20;  ++i )
		this->_rain_materials.insert(pair<unsigned int,Material>(950-10*i,Material(
										Colour(0.25f,0.25f,0.25f,i*0.025f),
										Colour(0.25f,0.25f,0.25f,i*0.025f),
										Colour(0.0f,0.0f,0.0f,0.0f),
										Colour(0.0f,0.0f,0.0f,0.0f),
										0.0f)));
	for ( unsigned int i = 0;  i <= 20;  ++i )
		this->_rain_materials.insert(pair<unsigned int,Material>(200-10*i,Material(
										Colour(0.25f,0.25f,0.25f,0.5f - i*0.025f),
										Colour(0.25f,0.25f,0.25f,0.5f - i*0.025f),
										Colour(0.0f,0.0f,0.0f,0.0f),
										Colour(0.0f,0.0f,0.0f,0.0f),
										0.0f)));


	this->_grass_materials.insert(pair<unsigned int,Material>(1100,Material(
										Colour(0.25f,0.25f,0.25f,1.0f),
										Colour(0.15f,0.55f,0.02f,1.0f),
										Colour(0.0f,0.0f,0.0f,0.0f),
										Colour(0.0f,0.0f,0.0f,0.0f),
										0.0f)));

	this->_grass_scales.insert(pair<unsigned int,GLfloat>(1100,0.0f));
	for ( unsigned int i = 0;  i <= 50;  ++i )
		this->_grass_scales.insert(pair<unsigned int,GLfloat>(1000 - i,i*0.02f));

	for ( unsigned int i = 0;  i <= 250;  ++i )
		this->_grass_scales.insert(pair<unsigned int,GLfloat>(500 - i,1.0f - i*0.004f));
};


// update the mouse position, and pitch yaw or zoom accordinglhy
void	SceneManager::mouse_position( int x , int y )
{ 
	if ( this->_mouse_down[0] )
	{
		int	diffX = this->_mouse_position[0] - x;
		int	diffY = y - this->_mouse_position[1];

		if ( abs(diffX) > abs(diffY) )
			this->_camera_yaw(diffX*this->_camera_step);
		else
			this->_camera_roll(diffY*this->_camera_step);
	}
	else if ( this->_mouse_down[2] )
	{
		this->_camera_zoom((this->_mouse_position[0] - x + this->_mouse_position[1] - y )*this->_camera_step*0.1f);
	}

	this->_mouse_position[0] = x;	this->_mouse_position[1] = y;
};

void	SceneManager::left_button_down()				{ this->_mouse_down[0] = true; };
void	SceneManager::left_button_up()					{ this->_mouse_down[0] = false; };
void	SceneManager::middle_button_down()				{ this->_mouse_down[1] = true; };
void	SceneManager::middle_button_up()				{ this->_mouse_down[1] = false; };
void	SceneManager::right_button_down()				{ this->_mouse_down[2] = true; };
void	SceneManager::right_button_up()					{ this->_mouse_down[2] = false; };
void	SceneManager::key_down( int key )
{
	if ( key > 0  &&  key < 256 )
		this->_key_state[key] = true;

	this->_check_key_state(false);
};

void	SceneManager::key_up( int key)
{
	if ( key > 0  &&  key < 256 )
		this->_key_state[key] = false;
};

// setup the scene
void	SceneManager::setup()
{
	this->_load_configuration();

	this->_vertex_shader.load(this->_vertex_shader_filename);
	this->_vertex_shader.compile(GL_VERTEX_SHADER);
	cout << "\n****************\tVertex Shader Log\t***************\n\n" << this->_vertex_shader << endl;
	this->_program.attachShader(this->_vertex_shader);
	this->_fragment_shader.load(this->_fragment_shader_filename);
	this->_fragment_shader.compile(GL_FRAGMENT_SHADER);
	cout << "\n***************\tFragment Shader Log\t**************\n\n" << this->_fragment_shader << endl;
	this->_program.attachShader(this->_fragment_shader);
	this->_program.create();
	cout << "\n*******************\tProgram Log\t******************\n\n" << this->_program << endl;


	this->_use_textures_loc = this->_program.glGetUniformLocation(this->_program.id(),"use_textures");
	this->_normal_mapping_loc = this->_program.glGetUniformLocation(this->_program.id(),"normal_mapping");
	this->_directional_lights_loc = this->_program.glGetUniformLocation(this->_program.id(),"directional_lights");


	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
	glClearColor(	this->_window_background.colour().r(),this->_window_background.colour().g(),
					this->_window_background.colour().b(),this->_window_background.colour().a());


	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
	glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);
	glHint(GL_POLYGON_SMOOTH_HINT,GL_NICEST);
	glHint(GL_LINE_SMOOTH_HINT,GL_NICEST);
	glHint(GL_FRAGMENT_SHADER_DERIVATIVE_HINT,GL_NICEST);


	glEnable(GL_NORMALIZE);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,Colour(0.5f,0.5f,0.5f,0.3f).colour().get());//Colour::colour_null().colour().get());
	
	this->_lights[0].number(1);
	this->_lights[0].position(this->_lights_position[0]);
	this->_lights[0].direction(this->_lights_direction[0]);
	this->_lights[0].ambient(this->_lights_colour[0].ambient());
	this->_lights[0].diffuse(this->_lights_colour[0].diffuse());
	this->_lights[0].specular(this->_lights_colour[0].specular());
	this->_lights[0].spotlight(true);
	this->_lights[0].cut_off(this->_lights_cuttoff[0]);
	this->_lights[0].exponent(this->_lights_exponent[0]);
	this->_lights[0].apply();

	this->_lights[1].number(2);
	this->_lights[1].position(this->_lights_position[1]);
	this->_lights[1].direction(this->_lights_direction[1]);
	this->_lights[1].ambient(this->_lights_colour[1].ambient());
	this->_lights[1].diffuse(this->_lights_colour[1].diffuse());
	this->_lights[1].specular(this->_lights_colour[1].specular());
	this->_lights[1].spotlight(true);
	this->_lights[1].cut_off(this->_lights_cuttoff[1]);
	this->_lights[1].exponent(this->_lights_exponent[1]);
	this->_lights[1].apply();

	this->_lights[2].number(3);
	this->_lights[2].position(this->_lights_position[2]);
	this->_lights[2].direction(this->_lights_direction[2]);
	this->_lights[2].ambient(this->_lights_colour[2].ambient());
	this->_lights[2].diffuse(this->_lights_colour[2].diffuse());
	this->_lights[2].specular(this->_lights_colour[2].specular());
	this->_lights[2].spotlight(true);
	this->_lights[2].cut_off(this->_lights_cuttoff[2]);
	this->_lights[2].exponent(this->_lights_exponent[2]);
	this->_lights[2].apply();

	this->_lights[3].number(4);
	this->_lights[3].position(this->_lights_position[3]);
	this->_lights[3].direction(this->_lights_direction[3]);
	this->_lights[3].ambient(this->_lights_colour[3].ambient());
	this->_lights[3].diffuse(this->_lights_colour[3].diffuse());
	this->_lights[3].specular(this->_lights_colour[3].specular());
	this->_lights[3].spotlight(true);
	this->_lights[3].cut_off(this->_lights_cuttoff[3]);
	this->_lights[3].exponent(this->_lights_exponent[3]);
	this->_lights[3].apply();

	this->_sun.number(5);
	this->_sun.directional(true);

	this->_moon.number(6);
	this->_moon.directional(true);
	this->_update_sun_and_moon();

	this->_light_spheres[0].position(this->_lights_position[0]);
	this->_light_spheres[0].create(	this->_light_sphere_radius,this->_light_sphere_stacks,this->_light_sphere_slices,
									this->_lights_colour[0].diffuse(),Material(this->_lights_colour[0].ambient(),this->_lights_colour[0].diffuse(),Colour::colour_null(),this->_lights_colour[0].diffuse(),0.0f));
	this->_light_spheres[1].position(this->_lights_position[1]);
	this->_light_spheres[1].create(	this->_light_sphere_radius,this->_light_sphere_stacks,this->_light_sphere_slices,
									this->_lights_colour[1].diffuse(),Material(this->_lights_colour[1].ambient(),this->_lights_colour[1].diffuse(),Colour::colour_null(),this->_lights_colour[1].diffuse(),0.0f));
	this->_light_spheres[2].position(this->_lights_position[2]);
	this->_light_spheres[2].create(	this->_light_sphere_radius,this->_light_sphere_stacks,this->_light_sphere_slices,
									this->_lights_colour[2].diffuse(),Material(this->_lights_colour[2].ambient(),this->_lights_colour[2].diffuse(),Colour::colour_null(),this->_lights_colour[2].diffuse(),0.0f));
	this->_light_spheres[3].position(this->_lights_position[3]);
	this->_light_spheres[3].create(	this->_light_sphere_radius,this->_light_sphere_stacks,this->_light_sphere_slices,
									this->_lights_colour[3].diffuse(),Material(this->_lights_colour[3].ambient(),this->_lights_colour[3].diffuse(),Colour::colour_null(),this->_lights_colour[3].diffuse(),0.0f));

	this->_sun_sphere.create(	this->_light_sphere_radius,this->_light_sphere_stacks,this->_light_sphere_slices,
								this->_sun_colour.diffuse(),Material(this->_sun_colour.ambient(),this->_sun_colour.diffuse(),this->_sun_colour.specular(),this->_sun_colour.diffuse(),0.0f));
	this->_moon_sphere.create(	this->_light_sphere_radius,this->_light_sphere_stacks,this->_light_sphere_slices,
								this->_moon_colour.diffuse(),Material(this->_moon_colour.ambient(),this->_moon_colour.diffuse(),this->_moon_colour.specular(),this->_moon_colour.diffuse(),0.0f));


	this->_camera.position(Vector3f(0.0f,0.0f,this->_camera_distance));
	this->_camera.looking_at(Vector3f(0.0f,0.0f,0.0f));
	this->_camera.up(Vector3f(0.0f,1.0f,0.0f));
	this->_camera.zoom(this->_zoom);
	this->_camera.free(this->_camera_free);
	this->_set_camera_position();
	this->_camera.apply();


	this->_globe.position(this->_globe_position);
	this->_globe.create(this->_globe_radius,this->_globe_stacks,this->_globe_slices,this->_globe_colour,this->_globe_material);


	this->_terrain.position(this->_terrain_position);
	this->_terrain.create(this->_terrain_radius,this->_terrain_height,this->_terrain_stacks,this->_terrain_slices,this->_pool_position,this->_pool_a_radius*1.05f,this->_pool_b_radius*1.05f,this->_terrain_top_colour,this->_terrain_bottom_colour,this->_terrain_material,this->_terrain_texture_filename);

	this->_pool.position(this->_pool_position);
	this->_pool.create(this->_pool_a_radius,this->_pool_b_radius,this->_pool_height,this->_pool_stacks,this->_pool_slices,this->_pool_height_stacks,this->_terrain_position,this->_terrain_radius,this->_pool_colour,this->_pool_material,this->_pool_texture_filename);

	this->_house.position(this->_house_position);
	this->_house.rotation(this->_house_rotation);
	this->_house.create(this->_house_model_filename,this->_house_scale);

	this->_tree.position(this->_tree_position);
	this->_tree.set_planes(this->_leaf_planes);
	this->_tree.leaves_acceleration(this->_leaf_acceleration);
	this->_tree.leaves_spring_materials(this->_leaf_spring_materials);
	this->_tree.leaves_spring_scales(this->_leaf_spring_scales);
	this->_tree.leaves_autumn_materials(this->_leaf_autumn_materials);
	this->_tree.leaves_autumn_scales(this->_leaf_autumn_scales);
	this->_tree.create(this->_tree_levels,this->_tree_branching_factor,this->_tree_width_radius,this->_tree_height,this->_tree_branch_stacks,this->_tree_branch_slices,this->_tree_leaves_size,this->_tree_leaves_mass,this->_tree_colour,this->_tree_material,this->_tree_bark_texture_filename,this->_tree_leaf_texture_filename);
	this->_leaf_spring_materials.clear();
	this->_leaf_spring_scales.clear();
	this->_leaf_autumn_materials.clear();
	this->_leaf_autumn_scales.clear();

	this->_particle_systems.position(0,this->_fire_position);
	this->_particle_systems.starting_velocity(0,this->_fire_speed);
	this->_particle_systems.spread(0,this->_fire_spread);
	this->_particle_systems.add_force(0,"BurnReaction",this->_fire_acceleration);
	this->_particle_systems.use_billboards(0,true);
	this->_particle_systems.use_spherical_billboards(0,true);

	for ( map<unsigned int,Material>::const_iterator it = this->_fire_materials.begin();  it != this->_fire_materials.end();  ++it )
		this->_particle_systems.add_material(0,it->first,it->second);

	for ( map<unsigned int,GLfloat>::const_iterator it = this->_fire_scales.begin();  it != this->_fire_scales.end();  ++it )
		this->_particle_systems.add_scale(0,it->first,it->second);

	this->_particle_systems.particle_count(0,this->_fire_density);
	this->_particle_systems.particle_delay(0,this->_fire_delay);
	this->_particle_systems.create(0,this->_fire_size,this->_fire_mass,this->_fire_lifespan,this->_smoke_texture_filename);
	this->_fire_materials.clear();
	this->_fire_scales.clear();


	Matrix4x4f	rotation;
	rotation.identity();
	rotation.translate(this->_house.position());
	rotation.rotate(this->_house.rotation(),0.0f,1.0f,0.0f);

	this->_particle_systems.position(1,rotation.multiply(this->_smoke_position));
	this->_particle_systems.starting_velocity(1,this->_smoke_speed);
	this->_particle_systems.spread(1,this->_smoke_spread);
	this->_particle_systems.add_force(1,"BurnReaction",this->_smoke_acceleration);
	this->_particle_systems.use_billboards(1,true);
	this->_particle_systems.use_spherical_billboards(1,true);

	for ( map<unsigned int,Material>::const_iterator it = this->_smoke_materials.begin();  it != this->_smoke_materials.end();  ++it )
		this->_particle_systems.add_material(1,it->first,it->second);

	for ( map<unsigned int,GLfloat>::const_iterator it = this->_smoke_scales.begin();  it != this->_smoke_scales.end();  ++it )
		this->_particle_systems.add_scale(1,it->first,it->second);
	
	this->_particle_systems.particle_count(1,this->_smoke_density);
	this->_particle_systems.particle_delay(1,this->_smoke_delay);
	this->_particle_systems.create(1,this->_smoke_size,this->_smoke_mass,this->_smoke_lifespan,this->_smoke_texture_filename);
	this->_smoke_materials.clear();
	this->_smoke_scales.clear();



	for ( unsigned int i = 0;  i < this->_roof_planes.size();  ++i )
	{
		for ( unsigned int j = 0;  j < this->_roof_planes[i].size();  ++j )
			this->_roof_planes[i][j] = rotation.multiply(this->_roof_planes[i][j]);
	}

	for ( unsigned int i = 2;  i < 10;  ++i )
	{
		vector<vector<Vector3f> >	planes(this->_roof_planes);
		Vector3f					temp(this->_snow_position);




		if ( i == 3 )
			temp = this->_snow_position2;
		else if ( i == 4 )
			temp = this->_snow_position3;
		else if ( i == 5 )
			temp = this->_snow_position4;
		else if ( i == 6 )
			temp = this->_snow_position5;
		else if ( i == 7 )
			temp = this->_snow_position6;
		else if ( i == 8 )
			temp = this->_snow_position7;
		else if ( i == 9 )
			temp = this->_snow_position8;


		for ( unsigned int j = 0;  j < planes.size();  ++j )
		{	
			for ( unsigned int k = 0;  k < planes[j].size();  ++k )
			{
				if ( j == 0  ||  j == 1 )
					planes[j][k] -= Vector3f(0.0f,this->_snow_size,0.0f);

				planes[j][k] -= temp;
			}
		}


		this->_particle_systems.position(i,temp);
		this->_particle_systems.starting_velocity(i,this->_snow_speed);
		this->_particle_systems.add_force(i,"Gravity",this->_snow_acceleration);
		this->_particle_systems.spread(i,this->_snow_spread);
		this->_particle_systems.collision(i,true);
		this->_particle_systems.collision_planes(i,planes);
		this->_particle_systems.use_billboards(i,true);
		this->_particle_systems.use_spherical_billboards(i,true);

		for ( map<unsigned int,Material>::const_iterator it = this->_snow_materials.begin();  it != this->_snow_materials.end();  ++it )
			this->_particle_systems.add_material(i,it->first,it->second);

		for ( map<unsigned int,GLfloat>::const_iterator it = this->_snow_scales.begin();  it != this->_snow_scales.end();  ++it )
			this->_particle_systems.add_scale(i,it->first,it->second);

		this->_particle_systems.particle_count(i,static_cast<unsigned int>(this->_snow_density*0.125f));
		this->_particle_systems.particle_delay(i,this->_snow_delay);
		this->_particle_systems.create(i,this->_snow_size,this->_snow_mass,this->_snow_lifespan,this->_snow_texture_filename);
	}
	this->_snow_materials.clear();
	this->_snow_scales.clear();


	for ( unsigned int i = 0;  i < this->_snow_mount_planes.size();  ++i )
	{
		for ( unsigned int j = 0;  j < this->_snow_mount_planes[i].size();  ++j )
			this->_snow_mount_planes[i][j] = rotation.multiply(this->_snow_mount_planes[i][j]);
	}

	this->_snow_mounts.position(this->_snow_mounts_position);
	this->_snow_mounts.create(this->_terrain_radius*0.99985f,this->_snow_mount_height,this->_terrain_stacks,this->_terrain_slices,this->_pool_position,this->_pool_a_radius*1.05f,this->_pool_b_radius*1.05f,this->_snow_mount_planes,this->_snow_mount_colour,this->_snow_mount_material,this->_snow_mounts_texture_filename);
	this->_snow_mount_planes.clear();

	
	this->_create_lightning();
	this->_particle_systems.position(10,this->_lightning_position);
	this->_particle_systems.starting_velocity(10,this->_lightning_speed);
	this->_particle_systems.fixed_delays(10,true);
	this->_particle_systems.delays(10,this->_lightning_delays);
	this->_particle_systems.fixed_starting_positions(10,true);
	this->_particle_systems.starting_positions(10,this->_lightning_positions);
	this->_particle_systems.spread(10,this->_lightning_spread);
	this->_particle_systems.collision(10,false);
	this->_particle_systems.use_billboards(10,true);
		
	for ( map<unsigned int,Material>::const_iterator it = this->_lightning_materials.begin();  it != this->_lightning_materials.end();  ++it )
		this->_particle_systems.add_material(10,it->first,it->second);

	for ( map<unsigned int,GLfloat>::const_iterator it = this->_lightning_scales.begin();  it != this->_lightning_scales.end();  ++it )
		this->_particle_systems.add_scale(10,it->first,it->second);

	this->_particle_systems.particle_count(10,this->_lightning_density);
	this->_particle_systems.manual_reset(10,true);
	this->_particle_systems.create(10,this->_lightning_size,this->_lightning_mass,this->_lightning_lifespan,this->_lightning_texture_filename);
	this->_lightning_materials.clear();
	this->_lightning_scales.clear();


	this->_create_storm();
	this->_particle_systems.position(11,this->_storm_position);
	this->_particle_systems.starting_velocity(11,this->_storm_speed);
	this->_particle_systems.fixed_starting_positions(11,true);
	this->_particle_systems.starting_positions(11,this->_storm_positions);
	this->_particle_systems.collision(11,false);
	this->_particle_systems.use_billboards(11,true);
	this->_particle_systems.use_spherical_billboards(11,true);
		
	for ( map<unsigned int,Material>::const_iterator it = this->_storm_materials.begin();  it != this->_storm_materials.end();  ++it )
		this->_particle_systems.add_material(11,it->first,it->second);

	for ( map<unsigned int,GLfloat>::const_iterator it = this->_storm_scales.begin();  it != this->_storm_scales.end();  ++it )
		this->_particle_systems.add_scale(11,it->first,it->second);

	this->_particle_systems.particle_count(11,this->_storm_density);
	this->_particle_systems.particle_delay(11,this->_storm_delay);
	this->_particle_systems.create(11,this->_storm_size,this->_storm_mass,this->_storm_lifespan,this->_storm_texture_filename);
	this->_storm_materials.clear();
	this->_storm_scales.clear();


	for ( unsigned int i = 12;  i < 20;  ++i )
	{
		vector<vector<Vector3f> >	planes(this->_roof_planes);
		Vector3f					temp(this->_rain_position);




		if ( i == 13 )
			temp = this->_rain_position2;
		else if ( i == 14 )
			temp = this->_rain_position3;
		else if ( i == 15 )
			temp = this->_rain_position4;
		else if ( i == 16 )
			temp = this->_rain_position5;
		else if ( i == 17 )
			temp = this->_rain_position6;
		else if ( i == 18 )
			temp = this->_rain_position7;
		else if ( i == 19 )
			temp = this->_rain_position8;


		for ( unsigned int j = 0;  j < planes.size();  ++j )
		{	
			for ( unsigned int k = 0;  k < planes[j].size();  ++k )
			{
				if ( j == 0  ||  j == 1 )
					planes[j][k] -= Vector3f(0.0f,this->_rain_size,0.0f);

				planes[j][k] -= temp;
			}
		}


		this->_particle_systems.position(i,temp);
		this->_particle_systems.starting_velocity(i,this->_rain_speed);
		this->_particle_systems.add_force(i,"Gravity",this->_rain_acceleration);
		this->_particle_systems.spread(i,this->_rain_spread);
		this->_particle_systems.collision(i,true);
		this->_particle_systems.collision_planes(i,planes);
		this->_particle_systems.use_billboards(i,true);
		this->_particle_systems.use_spherical_billboards(i,true);
		
		for ( map<unsigned int,Material>::const_iterator it = this->_rain_materials.begin();  it != this->_rain_materials.end();  ++it )
			this->_particle_systems.add_material(i,it->first,it->second);

		for ( map<unsigned int,GLfloat>::const_iterator it = this->_rain_scales.begin();  it != this->_rain_scales.end();  ++it )
			this->_particle_systems.add_scale(i,it->first,it->second);

		this->_particle_systems.particle_count(i,static_cast<unsigned int>(this->_rain_density*0.125f));
		this->_particle_systems.particle_delay(i,this->_rain_delay);
		this->_particle_systems.create(i,this->_rain_size,this->_rain_mass,this->_rain_lifespan,this->_rain_texture_filename);
	}
	this->_rain_materials.clear();
	this->_rain_scales.clear();
	this->_roof_planes.clear();


	this->_create_grass();
	this->_particle_systems.position(20,this->_grass_position);
	this->_particle_systems.fixed_starting_positions(20,true);
	this->_particle_systems.starting_positions(20,this->_grass_positions);
	this->_particle_systems.use_billboards(20,true);
		
	for ( map<unsigned int,Material>::const_iterator it = this->_grass_materials.begin();  it != this->_grass_materials.end();  ++it )
		this->_particle_systems.add_material(20,it->first,it->second);

	for ( map<unsigned int,GLfloat>::const_iterator it = this->_grass_scales.begin();  it != this->_grass_scales.end();  ++it )
		this->_particle_systems.add_scale(20,it->first,it->second);

	this->_particle_systems.particle_count(20,this->_grass_density);
	this->_particle_systems.particle_delay(20,this->_grass_delay);
	this->_particle_systems.create(20,this->_grass_size,this->_grass_mass,1.0f,this->_grass_texture_filename);
	this->_particle_systems.particle_energy(20,static_cast<float>(this->_day_cycle_time*this->_season_cycle_time*4.0f));
	this->_grass_materials.clear();
	this->_grass_scales.clear();


	this->_init_season();
	this->_update_render_parameters();
	this->_current_time = App::GetTime();
};

// clean up the structures we used
void	SceneManager::clean_up()
{
	this->_globe.destroy();
	this->_terrain.destroy();
	this->_pool.destroy();
	this->_house.destroy();
	this->_tree.destroy();
	this->_snow_mounts.destroy();
	this->_particle_systems.destroy();
	this->_program.destroy();
};

// resize the window and the viewport
void	SceneManager::resize( int width , int height )
{
	if ( width > 1 )
		this->_window_width = width;
	else
		this->_window_width = 1;

	if ( height > 1 )
		this->_window_height = height;
	else
		this->_window_height = 1;

	this->_ratio = static_cast<float>(this->_window_width)/static_cast<float>(this->_window_height);
	this->_set_viewport();
};

// draw the scene content
void	SceneManager::draw()
{
	this->_check_key_state(true);


	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);

	this->_camera.apply();


	if ( this->_toggle_directional_lights )
	{
		this->_sun.apply();
		this->_moon.apply();

		if ( this->_day_light_angle > 180.0f )
			this->_moon.select();
		else
			this->_sun.select();
	}
	else
	{
		this->_lights[0].apply();
		this->_lights[1].apply();
		this->_lights[2].apply();
		this->_lights[3].apply();
		this->_lights[0].select();
		this->_lights[1].select();
		this->_lights[2].select();
		this->_lights[3].select();
	}
	

	this->_reflection.pre_transparent_surface();
	this->_pool.draw();
	this->_reflection.post_transparent_surface();
	glStencilFunc(GL_EQUAL,1,1);
	glStencilOp(GL_KEEP,GL_KEEP,GL_KEEP);
	this->_terrain.draw();
	glClear(GL_DEPTH_BUFFER_BIT);
	this->_reflection.pre_reflection();
	this->_house.draw(this->_render_model);
	this->_particle_systems.draw(20);
	this->_tree.draw(this->_tree_max_draw_level,this->_tree_draw_scale);
	this->_particle_systems.draw(0,this->_tree_draw_scale);
	this->_particle_systems.draw(1);
	this->_particle_systems.draw(2);
	this->_particle_systems.draw(11);
	this->_particle_systems.draw(3);
	this->_particle_systems.draw(4);
	this->_particle_systems.draw(5);
	this->_particle_systems.draw(6);
	this->_particle_systems.draw(7);
	this->_particle_systems.draw(8);
	this->_particle_systems.draw(9);
	this->_particle_systems.draw(12);
	this->_particle_systems.draw(13);
	this->_particle_systems.draw(14);
	this->_particle_systems.draw(15);
	this->_particle_systems.draw(16);
	this->_particle_systems.draw(17);
	this->_particle_systems.draw(18);
	this->_particle_systems.draw(19);
	this->_particle_systems.draw(10);


	if ( this->_toggle_directional_lights )
	{
		if ( this->_day_light_angle > 180.0f )
			this->_moon_sphere.draw();
		else
			this->_sun_sphere.draw();
	}
	else
	{
		this->_light_spheres[0].draw();
		this->_light_spheres[1].draw();
		this->_light_spheres[2].draw();
		this->_light_spheres[3].draw();
	}


	if ( this->_snow_mount_draw_scale >= 0.53f )
		this->_snow_mounts.draw(this->_snow_mount_height,1.0f,1.0f,1.0f);

	this->_globe.draw();
	this->_reflection.post_reflection();


	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_NOTEQUAL,1,1);
	glStencilOp(GL_KEEP,GL_KEEP,GL_KEEP);
	this->_terrain.draw();
	if ( this->_snow_mount_draw_scale >= 0.53f )
		this->_snow_mounts.draw(this->_snow_mount_height,1.0f,1.0f,1.0f,true);
	glDisable(GL_STENCIL_TEST);
	this->_pool.draw();
	this->_house.draw(this->_render_model);
	this->_particle_systems.draw(20);
	this->_tree.draw(this->_tree_max_draw_level,this->_tree_draw_scale);
	this->_particle_systems.draw(0,this->_tree_draw_scale);
	this->_particle_systems.draw(1);
	this->_particle_systems.draw(2);
	this->_particle_systems.draw(11);
	this->_particle_systems.draw(3);
	this->_particle_systems.draw(4);
	this->_particle_systems.draw(5);
	this->_particle_systems.draw(6);
	this->_particle_systems.draw(7);
	this->_particle_systems.draw(8);
	this->_particle_systems.draw(9);
	this->_particle_systems.draw(12);
	this->_particle_systems.draw(13);
	this->_particle_systems.draw(14);
	this->_particle_systems.draw(15);
	this->_particle_systems.draw(16);
	this->_particle_systems.draw(17);
	this->_particle_systems.draw(18);
	this->_particle_systems.draw(19);
	this->_particle_systems.draw(10);
	this->_globe.draw();

	if ( this->_toggle_directional_lights )
	{
		if ( this->_day_light_angle > 180.0f )
			this->_moon_sphere.draw();
		else
			this->_sun_sphere.draw();
	}
	else
	{
		this->_light_spheres[0].draw();
		this->_light_spheres[1].draw();
		this->_light_spheres[2].draw();
		this->_light_spheres[3].draw();
	}


	this->_sun.deselect();
	this->_moon.deselect();
	this->_lights[0].deselect();
	this->_lights[1].deselect();
	this->_lights[2].deselect();
	this->_lights[3].deselect();
};

// update the current time
void	SceneManager::update_time( double time )
{ 
	double	difference = time - this->_current_time;
	
	
	
	this->_current_time = time;
	if ( !this->_pause )
	{
		this->_update_day_time((difference*360.0)/this->_day_cycle_time);
		this->_update_season(difference);
	}
};



