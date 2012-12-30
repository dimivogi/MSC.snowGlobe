#include	"ParticleEmitter.h"
#include	"..\Vector\Vector3f.h"

using		namespace	Globe;



vector<Vertex>	ParticleEmitter::_create_vertices() const
{
	Vertex			vertex;
	vector<Vertex>	returnValue(4);
	

	vertex._position[2] = 0.0f;
	vertex._normal[0] = 0.0f;
	vertex._normal[1] = 0.0f;
	vertex._colour[0] = 1.0f;
	vertex._colour[1] = 1.0f;
	vertex._colour[2] = 1.0f;
	vertex._colour[3] = 1.0f;
	vertex._texture[2] = 0.0f;

	vertex._position[0] = 0.5f;
	vertex._position[1] = -0.5f;
	vertex._normal[2] = 1.0f;
	vertex._texture[0] = 1.0f;
	vertex._texture[1] = 0.0f;
	returnValue[0] = vertex;

	vertex._position[0] = 0.5f;
	vertex._position[1] = 0.5f;
	vertex._normal[2] = 1.0f;
	vertex._texture[0] = 1.0f;
	vertex._texture[1] = 1.0f;
	returnValue[1] = vertex;

	vertex._position[0] = -0.5f;
	vertex._position[1] = 0.5f;
	vertex._normal[2] = 1.0f;
	vertex._texture[0] = 0.0f;
	vertex._texture[1] = 1.0f;
	returnValue[2] = vertex;

	vertex._position[0] = -0.5f;
	vertex._position[1] = -0.5f;
	vertex._normal[2] = 1.0f;
	vertex._texture[0] = 0.0f;
	vertex._texture[1] = 0.0f;
	returnValue[3] = vertex;


	return returnValue;
};

vector<GLuint>	ParticleEmitter::_create_indices() const
{
	vector<GLuint>	returnValue(6);



	returnValue[0] = 0;
	returnValue[1] = 1;
	returnValue[2] = 2;

	returnValue[3] = 2;
	returnValue[4] = 3;
	returnValue[5] = 0;


	return returnValue;
};

void	ParticleEmitter::_reset_particle( const unsigned long particle )
{
	if ( particle < this->_particles.size() )
	{
		if ( this->_fixed_positions  &&  particle < this->_starting_positions.size() )
		{
			this->_particles[particle].starting_position(this->_starting_positions[particle].multiply(Vector3f(0.0f,0.0f,0.0f)));
			this->_particles[particle].starting_velocity(this->_starting_velocity);
		}
		else
		{
			float		angle = (rand()%101)*0.01f*this->_spread;
			Matrix4x4f	temp;
			Vector3f	new_velocity(0.0f,0.0f,0.0f);



			temp.identity();
			temp.rotate(angle,0.0f,1.0f,0.0f);
			new_velocity = 0.5f*temp.multiply(this->_starting_velocity);

			angle = (rand()%101)*0.01f*this->_spread;
			temp.rotate(angle,0.0f,0.0f,1.0f);
			new_velocity += 0.5f*temp.multiply(this->_starting_velocity);


			this->_particles[particle].starting_position(Vector3f(0.0f,0.0f,0.0f));
			this->_particles[particle].starting_velocity(new_velocity);
		}

		if ( this->_fixed_delays  &&  particle < this->_delays.size() )
			this->_particles[particle].delay(this->_delays[particle]);
		else
			this->_particles[particle].delay( (rand()%101)*0.01f*this->_particle_delay);

		this->_particles[particle].position(Vector3f(0.0f,0.0f,0.0f));
		this->_particles[particle].energy(this->_particle_energy);
		this->_particles[particle].visible(true);
	}
};

void	ParticleEmitter::_reset_particles()
{
	for ( unsigned long i = 0;  i < this->_particles.size();  ++i )
		this->_reset_particle(i);
};

void	ParticleEmitter::_apply_forces()
{
	Vector3f	final_acceleration(0.0f,0.0f,0.0f);



	for ( map<string,Vector3f>::iterator it = this->_forces.begin();  it != this->_forces.end();  ++it )
		final_acceleration += it->second;
	final_acceleration *= (1.0f/this->_particle_mass);

	for ( unsigned long i = 0;  i < this->_particles.size();  ++i )
	{
		this->_particles[i].acceleration(final_acceleration);
		this->_particles[i].size(this->_particle_size);
		this->_particles[i].mass(this->_particle_mass);
	}
};


ParticleEmitter::ParticleEmitter()	:	
	_particle_size(1.0f) , _particle_mass(1.0f) , _particle_energy(1.0f) , 
	_particle_delay(0.0f) , _spread(0.0f) ,
	_fixed_positions(false) , _fixed_delays(false) , _collision_testing(false) , 
	_billboards(false) , _spherical_billboards(false) , 
	_use_material(true) , 
	_emit(false) , _stop_request(false) , _do_not_reset(false)	{};
ParticleEmitter::~ParticleEmitter()	{};


void	ParticleEmitter::particle_count( const unsigned long count )
{
	if ( this->_particles.size() < count )
	{
		unsigned long						difference = count - this->_particles.size();
		vector<Particle>::reverse_iterator	it;



		this->_particles.resize(count);
		it = this->_particles.rbegin();

		for ( unsigned long i = 0;  i < difference;  ++i )
		{
			this->_reset_particle(i);
			++it;
		};

		this->_apply_forces();
	}
	else
		this->_particles.resize(count);
};

void	ParticleEmitter::starting_positions( const vector<Matrix4x4f>& positions )		{ this->_starting_positions = positions; };
void	ParticleEmitter::collision_planes( const vector<vector<Vector3f> >& planes )	{	this->_collision_planes = planes; };
void	ParticleEmitter::delays( const vector<GLfloat>& delays )						{  this->_delays = delays; };
void	ParticleEmitter::add_force( const string& name , const Vector3f& value )
{
	map<string,Vector3f>::iterator	it = this->_forces.find(name);



	if ( it != this->_forces.end() )
		it->second = value;
	else
		this->_forces.insert(pair<string,Vector3f>(name,value));

	this->_apply_forces();
};

void	ParticleEmitter::remove_force( const string& name )
{
	this->_forces.erase(name);
	this->_apply_forces();
};

void	ParticleEmitter::add_colour( const unsigned int percent , const Colour& value )
{
	map<unsigned int,Colour>::iterator	it = this->_colours.find(percent);



	if ( it != this->_colours.end() )
		it->second = value;
	else
		this->_colours.insert(pair<unsigned int,Colour>(percent,value));
};

void	ParticleEmitter::remove_colour( const unsigned int percent )	{ this->_colours.erase(percent); };
void	ParticleEmitter::add_material( const unsigned int percent , const Material& value )
{
	map<unsigned int,Material>::iterator	it = this->_materials.find(percent);



	if ( it != this->_materials.end() )
		it->second = value;
	else
		this->_materials.insert(pair<unsigned int,Material>(percent,value));
};

void	ParticleEmitter::remove_material( const unsigned int percent )	{ this->_materials.erase(percent); };
void	ParticleEmitter::add_scale( const unsigned int percent , const GLfloat value )
{
	map<unsigned int,GLfloat>::iterator	it = this->_scales.find(percent);



	if ( it != this->_scales.end() )
		it->second = value;
	else
		this->_scales.insert(pair<unsigned int,GLfloat>(percent,value));
};

void	ParticleEmitter::remove_scale( const unsigned int percent )		{ this->_scales.erase(percent); };
void	ParticleEmitter::position( const Vector3f& position )			{ this->_position = position; };
void	ParticleEmitter::starting_velocity( const Vector3f& value )		{ this->_starting_velocity = value; };
void	ParticleEmitter::particle_size( const float value )
{
	this->_particle_size = value;
	this->_apply_forces();
};

void	ParticleEmitter::particle_mass( const float value )
{
	this->_particle_mass = value;
	this->_apply_forces();
};

void	ParticleEmitter::particle_energy( const float value )
{ 
	if ( this->_emit )
	{
		for ( unsigned int i = 0;  i < this->_particles.size();  ++i )
		{
			if ( this->_particles[i].visible() )
				this->_particles[i].energy(abs(value)*this->_particles[i].energy()/this->_particle_energy);
		}
	}

	this->_particle_energy = abs(value);
};

void	ParticleEmitter::particle_delay( const float value )
{ 
	if ( this->_emit )
	{
		for ( unsigned int i = 0;  i < this->_particles.size();  ++i )
		{
			if ( this->_particles[i].visible() )
			{
				if ( this->_particles[i].delay() > 0 )
					this->_particles[i].delay(abs(value)*this->_particles[i].delay()/this->_particle_delay);
			}
		}
	}
	
	this->_particle_delay = abs(value);
};

void	ParticleEmitter::spread( const float value )
{ 
	if ( abs(value) <= 360.0f )
		this->_spread = value; 
};

void	ParticleEmitter::fixed_starting_positions( const bool value )
{
	this->_fixed_positions = value;
};

void	ParticleEmitter::collision( const bool value )							{ this->_collision_testing = value; };
void	ParticleEmitter::fixed_delays( const bool value )						{ this->_fixed_delays = value; };	
void	ParticleEmitter::use_material( const bool value )						{ this->_use_material = value; };
void	ParticleEmitter::use_textures( const bool value )						{ this->_display_particle.use_textures(value); };
void	ParticleEmitter::manual_reset( const bool value )						{ this->_do_not_reset = value; };
void	ParticleEmitter::use_billboards( const bool value )						{ this->_billboards = value; };
void	ParticleEmitter::use_spherical_billboards( const bool value )			{ this->_spherical_billboards = value; };


unsigned long				ParticleEmitter::particle_count() const				{ return this->_particles.size(); };
vector<Matrix4x4f>			ParticleEmitter::starting_positions() const			{ return this->_starting_positions; };
vector<vector<Vector3f> >	ParticleEmitter::collision_planes() const			{ return this->_collision_planes; };
vector<GLfloat>				ParticleEmitter::delays() const						{ return this->_delays; };
Vector3f	ParticleEmitter::force( const string& name ) const
{
	map<string,Vector3f>::const_iterator	it = this->_forces.find(name);
	Vector3f								returnValue(0.0f,0.0f,0.0f);



	if ( it != this->_forces.end() )
		returnValue = it->second;


	return returnValue;
};

Colour	ParticleEmitter::colour( const unsigned int percent ) const
{
	map<unsigned int,Colour>::const_iterator	it = this->_colours.find(percent);
	Colour										returnValue(Colour::colour_null());



	if ( it != this->_colours.end() )
		returnValue = it->second;


	return returnValue;
};

Material	ParticleEmitter::material( const unsigned int percent ) const
{
	map<unsigned int,Material>::const_iterator	it = this->_materials.find(percent);
	Material									returnValue;



	if ( it != this->_materials.end() )
		returnValue = it->second;


	return returnValue;
};

GLfloat	ParticleEmitter::scale( const unsigned int percent ) const
{
	map<unsigned int,GLfloat>::const_iterator	it = this->_scales.find(percent);
	GLfloat										returnValue = 0.0f;



	if ( it != this->_scales.end() )
		returnValue = it->second;


	return returnValue;
};

Vector3f	ParticleEmitter::position() const					{ return this->_position; };
Vector3f	ParticleEmitter::starting_velocity() const			{ return this->_starting_velocity; };
float		ParticleEmitter::particle_size() const				{ return this->_particle_size; };
float		ParticleEmitter::particle_mass() const				{ return this->_particle_mass; };
float		ParticleEmitter::particle_energy() const			{ return this->_particle_energy; };
float		ParticleEmitter::particle_delay() const				{ return this->_particle_delay; };
bool		ParticleEmitter::fixed_starting_positions() const	{ return this->_fixed_positions; };
bool		ParticleEmitter::collision() const					{ return this->_collision_testing; };
bool		ParticleEmitter::fixed_delays() const				{ return this->_fixed_delays; };
bool		ParticleEmitter::using_material() const				{ return this->_use_material; };
bool		ParticleEmitter::using_textures() const				{ return this->_display_particle.using_textures(); };
bool		ParticleEmitter::manual_reset() const				{ return this->_do_not_reset; };
bool		ParticleEmitter::using_billboards() const			{ return this->_billboards; };
bool		ParticleEmitter::using_spherical_billboards() const	{ return this->_spherical_billboards; };
bool		ParticleEmitter::emitting() const					{ return this->_emit; };


void	ParticleEmitter::create( const float size , const float mass , const float max_energy , const string& filename )
{
	Image	texture;



	this->_particle_size = size;
	this->_particle_mass = mass;
	this->particle_energy(max_energy);
	this->_reset_particles();
	this->_apply_forces();

	if ( filename != "" )
	{
		vector<Texture>	textures(1);

		texture.Load(filename.c_str());
		textures[0] = Texture(2,texture);
		this->_display_particle.textures(textures);
		texture.Free();
	}

	this->_display_particle.position(Vector3f(0.0f,0.0f,0.0f));
	this->_display_particle.use_material(false);
	this->_display_particle.use_vertex_buffer(true);
	this->_display_particle.display_data(this->_create_vertices());
	this->_display_particle.indices_data(this->_create_indices());
	this->_display_particle.create();
};

void	ParticleEmitter::destroy()
{
	this->_display_particle.destroy();
};

void	ParticleEmitter::start()
{
	this->_emit = true;
	this->_stop_request = false;

	if ( !this->manual_reset() )
		this->reset();
};

void	ParticleEmitter::stop()
{
	this->_stop_request = true;
};

void	ParticleEmitter::force_stop()
{
	this->_emit = false;
};

void	ParticleEmitter::reset()
{
	srand(static_cast<unsigned int>(time(NULL)));
	this->_reset_particles();
}

void	ParticleEmitter::update( const float time_since_last_update )
{
	if ( this->_emit )
	{
		unsigned long	counter = 0;



		for ( unsigned long i = 0;  i < this->_particles.size();  ++i )
		{
			if ( this->_particles[i].visible() )
			{
				this->_particles[i].move(time_since_last_update,this->_collision_testing,this->_collision_planes);

				if ( !this->_stop_request )
				{
					if ( !this->manual_reset() )
					{
						if ( !this->_particles[i].visible() )
							this->_reset_particle(i);
					}
				}
				else
				{
					if ( !this->_particles[i].visible() )
						++counter;
				}
			}
			else
				++counter;
		}

		if ( counter == this->_particles.size() )
			this->_emit = false;
	}
};

void	ParticleEmitter::draw( const float scale )
{
	if ( this->_emit )
	{
		GLboolean	cull;
		GLboolean	blend;
		GLboolean	mask;
		GLint		src,dst;



		glGetBooleanv(GL_CULL_FACE,&cull);
		glDisable(GL_CULL_FACE);

		glGetBooleanv(GL_DEPTH_WRITEMASK,&mask);
		glDepthMask(GL_FALSE);

		glGetBooleanv(GL_BLEND,&blend);
		glEnable(GL_BLEND);


		glGetIntegerv(GL_BLEND_SRC_ALPHA,&src);
		glGetIntegerv(GL_BLEND_DST_ALPHA,&dst);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

		glPushMatrix();


			glTranslatef(this->_position.x(),this->_position.y(),this->_position.z());

			for ( unsigned long i = 0;  i < this->_particles.size();  ++i )
			{
				GLfloat		size = static_cast<GLfloat>(this->_particles[i].size());
				Vector3f	position = this->_particles[i].position();


				if ( this->_particles[i].visible() )
				{
					unsigned int								percent = static_cast<unsigned int>(1000*(this->_particles[i].energy() / this->_particle_energy));
					bool										fixed_position = ( this->_fixed_positions  &&  ( i < this->_starting_positions.size()  ) );
					bool										colour_found = false;
					bool										material_found = false;
					bool										scale_found = false;
					map<unsigned int,Colour>::const_iterator	colour_it;
					map<unsigned int,Material>::const_iterator	material_it;
					map<unsigned int,GLfloat>::const_iterator	scale_it;	



					for ( map<unsigned int,Colour>::const_iterator it = this->_colours.begin();  it != this->_colours.end();  ++it )
					{
						if ( percent <= it->first )
						{
							colour_found = true;
							colour_it = it;
							break;
						}
					};

					if ( this->_use_material )
					{
						for ( map<unsigned int,Material>::const_iterator it = this->_materials.begin();  it != this->_materials.end();  ++it )
						{
							if ( percent <= it->first )
							{
								material_found = true;
								material_it = it;
								break;
							}
						}
					}

					for ( map<unsigned int,GLfloat>::const_iterator it = this->_scales.begin();  it != this->_scales.end();  ++it )
					{
						if ( percent <= it->first )
						{
							scale_found = true;
							scale_it = it;
							break;
						}
					}


					glPushMatrix();

						if ( colour_found )
							glColor4f(colour_it->second.red(),colour_it->second.green(),colour_it->second.blue(),colour_it->second.alpha());

						if ( material_found )
							material_it->second.apply();

						if ( fixed_position )
						{
							glTranslatef(position.x(),position.y(),position.z());
							glMultMatrixf(this->_starting_positions[i].get());
						}
						else
						{
							glScalef(scale,scale,scale);
							glTranslatef(position.x(),position.y(),position.z());
						}

						if ( this->_billboards )
						{
							Matrix4x4f	matrix;



							matrix.loadGL(GL_MODELVIEW_MATRIX);
							Vector4f	translation(matrix.row(0).w(),matrix.row(1).w(),matrix.row(2).w(),matrix.row(3).w());

							if ( this->_spherical_billboards )
							{
								matrix.set(	1.0f,0.0f,0.0f,translation.x(),
											0.0f,1.0f,0.0f,translation.y(),
											0.0f,0.0f,1.0f,translation.z(),
											0.0f,0.0f,0.0f,translation.w());
							}
							else
							{
								GLfloat	y = matrix.row(1).y();



								
								matrix.set(	1.0f,0.0f,0.0f,translation.x(),
											0.0f,y,0.0f,translation.y(),
											0.0f,0.0f,1.0f,translation.z(),
											0.0f,0.0f,0.0f,translation.w());
							}

							glLoadMatrixf(matrix.get());
						}

						if ( fixed_position )
						{
							if ( scale_found )
								glScalef(size*scale*scale_it->second,size*scale*scale_it->second,size*scale*scale_it->second);
							else
								glScalef(size*scale,size*scale,size*scale);
						}
						else
						{
							if ( this->_billboards )
							{
								if ( scale_found )
									glScalef(size*scale*scale_it->second,size*scale*scale_it->second,size*scale*scale_it->second);
								else
									glScalef(size*scale,size*scale,size*scale);
							}
							else
							{
								if ( scale_found )
									glScalef(size*scale_it->second,size*scale_it->second,size*scale_it->second);
								else
									glScalef(size,size,size);
							}
						}

						this->_display_particle.draw();


						if ( material_found )
							material_it->second.remove();

						if ( colour_found )
							glColor4f(1.0f,1.0f,1.0f,1.0f);
					
					glPopMatrix();
				}
			}


		glPopMatrix();

		
		glBlendFunc(src,dst);

		if ( !blend )
			glDisable(GL_BLEND);

		glDepthMask(mask);

		if ( cull )
			glEnable(GL_CULL_FACE);
	}
};