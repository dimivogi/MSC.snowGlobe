#include	"Tree.h"
#include	<algorithm>

using		namespace std;
using		namespace Globe;



vector<Vertex>	Tree::_create_vertices(  const float width , const float height , const float scale , const Colour& colour )
{
	unsigned int	counter = 0;
	Vertex			vertex;
	unsigned int	stacks = max(static_cast<unsigned int>(scale * this->_branch_stacks),static_cast<unsigned int>(1));
	unsigned int	slices = max(static_cast<unsigned int>(scale * this->_branch_slices),static_cast<unsigned int>(2));
	vector<Vertex>	returnValue( (stacks+1) * (slices+1)  + (slices+1) + 1 );



	vertex._colour[0] = colour.red();
	vertex._colour[1] = colour.green();
	vertex._colour[2] = colour.blue();
	vertex._colour[3] = colour.alpha();
	for ( unsigned int i = 0;  i <= stacks;  ++i )
	{
		float	y = static_cast<float>(i) / static_cast<float>(stacks);
		float	radius = 1.0f - 0.5f*y;



		for ( unsigned int j = 0;  j <= slices;  ++j )
		{
			float		angle = Object::_PI * 2.0f * static_cast<float>(j)/static_cast<float>(slices);
			float		x = cos(angle);
			float		z = sin(angle);
			Vector3f	normal(x,0.0f,z);
			
			

			normal.normalize();
			vertex._position[0] = width*radius*x;
			vertex._position[1] = height*y;
			vertex._position[2] = width*radius*z;
			vertex._normal[0] = normal.x();
			vertex._normal[1] = normal.y();
			vertex._normal[2] = normal.z();
			vertex._texture[0] = static_cast<float>(j)/static_cast<float>(slices);
			vertex._texture[1] = 1.0f - y;
			vertex._texture[2] = 0.0f;
			returnValue[counter++] = vertex;
		}
	}

	vertex._position[0] = 0.0f;
	vertex._position[1] = 1.01f*height;
	vertex._position[2] = 0.0f;
	vertex._normal[0] = 0.0f;
	vertex._normal[1] = 1.0f;
	vertex._normal[2] = 0;
	vertex._texture[0] = 0.0f;
	vertex._texture[1] = 1.0f;
	vertex._texture[2] = 0.0f;
	returnValue[counter++] = vertex;

	for ( unsigned int j  = 0;  j <= slices;  ++j )
	{
		float		angle = Object::_PI * 2.0f * static_cast<float>(j)/static_cast<float>(slices);
		float		x = cos(angle);
		float		z = sin(angle);
		Vector3f	normal(0.0,1.0f,0.0f);
			
			

		normal.normalize();
		vertex._position[0] = width*0.5f*x;
		vertex._position[1] = height;
		vertex._position[2] = width*0.5f*z;
		vertex._normal[0] = normal.x();
		vertex._normal[1] = normal.y();
		vertex._normal[2] = normal.z();
		vertex._texture[0] = static_cast<float>(j)/static_cast<float>(slices);
		vertex._texture[1] = 1.0f;
		vertex._texture[2] = 0.0f;
		returnValue[counter++] = vertex;
	}



	return returnValue;
};

vector<GLuint>	Tree::_create_indices( const float scale )
{
	unsigned int	counter = 0;
	unsigned int	stacks = max(static_cast<unsigned int>(scale * this->_branch_stacks),static_cast<unsigned int>(1));
	unsigned int	slices = max(static_cast<unsigned int>(scale * this->_branch_slices),static_cast<unsigned int>(2));
	vector<GLuint>	returnValue( 3 * 2 * stacks * slices + 3*slices);



	for ( unsigned int i = 0;  i < stacks;  ++i )
	{
		unsigned int	offset = i * (slices+1);



		for ( unsigned int j = 0;  j < slices;  ++j )
		{
			unsigned int	current = offset + j;
			unsigned int	next = offset + j + 1;
			unsigned int	one_stack_up = offset + j + slices + 1;
			unsigned int	next_one_stack_up = offset + j + 1 + slices + 1;



			returnValue[counter++] = current;
			returnValue[counter++] = one_stack_up;
			returnValue[counter++] = next_one_stack_up;

			returnValue[counter++] = current;
			returnValue[counter++] = next_one_stack_up;
			returnValue[counter++] = next;
		}
	}


	unsigned int	top = (stacks+1)*(slices+1);
	unsigned int	offset = top + 1;
	for ( unsigned int j = 0;  j < slices;  ++j )
	{
		unsigned int	current = offset + j;
		unsigned int	next = offset + j + 1;



		returnValue[counter++] = top;
		returnValue[counter++] = current;
		returnValue[counter++] = next;
	}


	return returnValue;
};


// recursively create the trr
unsigned int	Tree::_create_tree( const unsigned int level , const unsigned long counter , const unsigned int branch_no , const float offset , const float scale , const Matrix4x4f& matrix , unsigned long& leaf_counter)
{
	unsigned long	new_counter = counter;
	unsigned int	children = this->_branching;
	GLfloat			new_offset = static_cast<float>((rand()%360));
	GLfloat			distance = 1.0f;
	GLfloat			yaw_angle;
	GLfloat			pitch_angle;
	GLfloat			y_move;



	// For big branching factors, we reduce the number of leaves per final branch to improve performance
	if ( level > (this->_levels+1) )
		return counter;
	else if ( level == this->_levels )
		children = max(static_cast<unsigned int>(min(4.0f*scale,1.0f)*this->_branching),static_cast<unsigned int>(1));
	else if ( level > this->_levels )
		children = max(static_cast<unsigned int>(min(8.0f*scale,1.0f)*this->_branching),static_cast<unsigned int>(1));
	
	// for each branch and leaf, a y_axis translation
	// a pitch and a yaw angle is calculated
	if ( counter > 0 )
	{
		if ( level <= this->_levels )
		{
			if ( this->_branching > 0 )
				distance = 360.0f / static_cast<float>(this->_branching);
		}
		else
			distance = 360.0f / static_cast<float>(children);


		yaw_angle = branch_no*distance + offset;
		
		if ( yaw_angle > 360.0f )
			yaw_angle -= 360.0f;

		pitch_angle = static_cast<GLfloat>((rand()%61)+10);
		y_move = (2.0f*scale*this->_height - scale*this->_width)*(rand()%56 + 45)*0.01f;
	}
	else
	{
		yaw_angle = 0.0f;
		pitch_angle = 0.0f;
		y_move = 0.0f;
	}

	// then we save the current matrix, for use as a starting position for the leaves
	Matrix4x4f		new_matrix(matrix);
	new_matrix.translate(0.0f,y_move,0.0f);
	new_matrix.rotate(yaw_angle,0.0f,1.0f,0.0f);

	if ( level > this->_levels )
		new_matrix.translate((2.0f*scale*this->_width),0.0f,0.0f);

	new_matrix.rotate(pitch_angle,1.0f,0.0f,0.0f);

	if ( level <= this->_levels )
	{
		this->_tree[counter].yaw_angle(yaw_angle);
		this->_tree[counter].pitch_angle(pitch_angle);
		this->_tree[counter].x(0.0f);
		this->_tree[counter].y(y_move);
		this->_tree[counter].z(0.0f);
		this->_tree[counter].level(level);


		// for each brach create it's children
		++new_counter;
		for ( unsigned int i = 0;  i < children;  ++i )
			new_counter = this->_create_tree((level+1),new_counter,i,new_offset,scale*0.5f,new_matrix,leaf_counter);
	}
	else
		this->_leaves_positions[leaf_counter++] = new_matrix;

	
	return new_counter;
};

unsigned int	Tree::_draw_tree( const unsigned int level , const unsigned long counter , const unsigned int max_level , const GLfloat scale )
{
	unsigned long	new_counter = counter;


	if ( level > this->_levels  ||  counter >= this->_tree.size() )	return counter;


	if ( this->_branch[this->_tree[counter].level()].using_textures() )
	{
		this->_branch[this->_tree[counter].level()].glActiveTexture(GL_TEXTURE0);
		this->_bark.apply();
	}
	
	glPushMatrix();

		if ( level <= (max_level+1) )
		{
			glTranslatef(this->_tree[counter].x(),this->_tree[counter].y(),this->_tree[counter].z());
			glRotatef(this->_tree[counter].yaw_angle(),0.0f,1.0f,0.0f);
			glRotatef(this->_tree[counter].pitch_angle(),1.0f,0.0f,0.0f);
			glScalef(scale,scale,scale);

			this->_branch[this->_tree[counter].level()].draw();
		}
		
		++new_counter;
		for ( unsigned int i = 0;  i < this->_branching;  ++i )
				new_counter = this->_draw_tree((level+1),new_counter,max_level,scale);

	glPopMatrix();

	if ( this->_branch[this->_tree[counter].level()].using_textures() )
	{
		this->_branch[this->_tree[counter].level()].glActiveTexture(GL_TEXTURE0);
		this->_bark.remove();
	}


	return new_counter;
};


Tree::Tree()	:	_bark(2) , _branch(NULL) , _levels(2) , _branching(1) , _width(1.0f) , _height(1.0f) , _branch_stacks(1) , _branch_slices(2) , _leaf_size(1.0f)	{};


void		Tree::leaves_spring_colours( const map<unsigned int,Colour>& colours )			{ this->_leaves_spring_colours = colours; };
void		Tree::leaves_autumn_colours( const map<unsigned int,Colour>& colours )			{ this->_leaves_autumn_colours = colours; };
void		Tree::leaves_spring_materials( const map<unsigned int,Material>& materials )	{ this->_leaves_spring_materials = materials; };
void		Tree::leaves_autumn_materials( const map<unsigned int,Material>& materials )	{ this->_leaves_autumn_materials = materials; };
void		Tree::leaves_spring_scales( const map<unsigned int,GLfloat>& scales )			{ this->_leaves_spring_scales = scales; };
void		Tree::leaves_autumn_scales( const map<unsigned int,GLfloat>& scales )			{ this->_leaves_autumn_scales = scales; };
void		Tree::position( const Vector3f& position )										{ this->_position = position;  };
void		Tree::leaves_acceleration( const Vector3f& value )								{ this->_leaves_acceleration = value; };

void		Tree::use_material( const bool value )
{
	for ( unsigned int i = 0;  i < this->_branch.size();  ++i )
		this->_branch[i].use_material(value);

	this->_leaves.use_material(value);
};

void		Tree::use_textures( const bool value )
{
	for ( unsigned int i = 0;  i < this->_branch.size();  ++i )
		this->_branch[i].use_textures(value);

	this->_leaves.use_textures(value);
};

Vector3f	Tree::position() const						{ return this->_position; };
Vector3f	Tree::leaves_acceleration() const			{ return this->_leaves_acceleration; };


void		Tree::create(	const unsigned int levels , const unsigned int branching ,
							const float width , const float height ,
							const unsigned int branch_stacks , const unsigned int branch_slices , 
							const GLfloat leaf_size ,  const GLfloat leaf_mass , 
							const Colour& colour , const Material& material , 
							const string& filename , const string& leaf_filename )
{
	Image			texture;
	unsigned long	total_branches = 1;
	float			scale = 1.0f;
	unsigned int	children = branching;



	this->_levels = levels;
	this->_branching = branching;
	this->_width = abs(width);
	this->_height = abs(height);
	this->_branch_stacks = branch_stacks;
	this->_branch_slices = branch_slices;
	this->_leaf_size = abs(leaf_size);

	if ( filename != "" )
	{
		texture.Load(filename.c_str());
		_bark.image(texture);
		_bark.create();
		texture.Free();
	};
		

	this->_branch.resize(this->_levels+1);
	for ( unsigned int i = 0;  i <= this->_levels;  ++i )
	{
		this->_branch[i].position(Vector3f(0.0f,0.0f,0.0f));
		this->_branch[i].material(material);
		this->_branch[i].use_vertex_buffer(true);
		this->_branch[i].display_data(this->_create_vertices(scale*this->_width,scale*this->_height,scale,colour));
		this->_branch[i].indices_data(this->_create_indices(scale));

		this->_branch[i].create();
		scale *= 0.5f;
	}

	for ( unsigned int i = 1;  i <= this->_levels;  ++i )
		total_branches += static_cast<unsigned long>(pow(static_cast<long double>(this->_branching),static_cast<long double>(i)));
	
	children = max(static_cast<unsigned int>(min(8.0f*scale,1.0f)*this->_branching),static_cast<unsigned int>(1));
	this->_leaves.position(Vector3f(0.0f,0.0f,0.0f));
	this->_leaves.starting_velocity(Vector3f(0.0f,0.0f,0.0f));
	this->_leaves.fixed_starting_positions(true);
	this->_leaves.collision(true);
	this->_leaves_positions.resize(static_cast<unsigned long>(pow(static_cast<long double>(this->_branching),static_cast<long double>(this->_levels))*children));
	this->_leaves.particle_count(static_cast<unsigned long>(pow(static_cast<long double>(this->_branching),static_cast<long double>(this->_levels))*children));
	this->_leaves.manual_reset(true);
	this->_leaves.create(this->_leaf_size,leaf_mass,10.0f,leaf_filename);
	this->_tree.resize(total_branches);
};

void		Tree::update()
{
	unsigned long	counter = 0;
	Matrix4x4f		matrix;



	srand(static_cast<unsigned int>(time(NULL)));
	matrix.identity();
	this->_create_tree(0,0,0,0,1.0f,matrix,counter);
	this->_leaves.starting_positions(this->_leaves_positions);
};

void		Tree::grow_leaves()
{
	this->_leaves.reset();
	this->_leaves.remove_force("Gravity");

	for ( map<unsigned int,Colour>::const_iterator it = this->_leaves_autumn_colours.begin();  it != this->_leaves_autumn_colours.end();  ++it )
		this->_leaves.remove_colour(it->first);

	for ( map<unsigned int,Material>::const_iterator it = this->_leaves_autumn_materials.begin();  it != this->_leaves_autumn_materials.end();  ++it )
		this->_leaves.remove_material(it->first);

	for ( map<unsigned int,GLfloat>::const_iterator it = this->_leaves_autumn_scales.begin();  it != this->_leaves_autumn_scales.end();  ++it )
		this->_leaves.remove_scale(it->first);

	for ( map<unsigned int,Colour>::const_iterator it = this->_leaves_spring_colours.begin();  it != this->_leaves_spring_colours.end();  ++it )
		this->_leaves.add_colour(it->first,it->second);

	for ( map<unsigned int,Material>::const_iterator it = this->_leaves_spring_materials.begin();  it != this->_leaves_spring_materials.end();  ++it )
		this->_leaves.add_material(it->first,it->second);

	for ( map<unsigned int,GLfloat>::const_iterator it = this->_leaves_spring_scales.begin();  it != this->_leaves_spring_scales.end();  ++it )
		this->_leaves.add_scale(it->first,it->second);

	this->_leaves.start();
};

void		Tree::shed_leaves()
{
	this->_leaves.reset();
	this->_leaves.add_force("Gravity",this->_leaves_acceleration);


	for ( map<unsigned int,Colour>::const_iterator it = this->_leaves_spring_colours.begin();  it != this->_leaves_spring_colours.end();  ++it )
		this->_leaves.remove_colour(it->first);

	for ( map<unsigned int,Material>::const_iterator it = this->_leaves_spring_materials.begin();  it != this->_leaves_spring_materials.end();  ++it )
		this->_leaves.remove_material(it->first);

	for ( map<unsigned int,GLfloat>::const_iterator it = this->_leaves_spring_scales.begin();  it != this->_leaves_spring_scales.end();  ++it )
		this->_leaves.remove_scale(it->first);

	for ( map<unsigned int,Colour>::const_iterator it = this->_leaves_autumn_colours.begin();  it != this->_leaves_autumn_colours.end();  ++it )
		this->_leaves.add_colour(it->first,it->second);

	for ( map<unsigned int,Material>::const_iterator it = this->_leaves_autumn_materials.begin();  it != this->_leaves_autumn_materials.end();  ++it )
		this->_leaves.add_material(it->first,it->second);

	for ( map<unsigned int,GLfloat>::const_iterator it = this->_leaves_autumn_scales.begin();  it != this->_leaves_autumn_scales.end();  ++it )
		this->_leaves.add_scale(it->first,it->second);

	this->_leaves.start();
};

void		Tree::hide_leaves()											{ this->_leaves.stop(); };
void		Tree::force_hide_leaves()									{ this->_leaves.force_stop(); };
void		Tree::change_fall_time( const float time , const float delay)
{
	this->_leaves.particle_energy(time);
	this->_leaves.particle_delay(delay);
};

void		Tree::move_leaves( const float time )						{ this->_leaves.update(time); };
void		Tree::set_planes( const vector<vector<Vector3f> >& planes )	{ this->_leaves.collision_planes(planes); };
void		Tree::destroy()
{
	for ( unsigned long i = 0;  i <= this->_levels;  ++i )
		this->_branch[i].destroy();

	this->_leaves.destroy();
};

void		Tree::draw( const unsigned int max_level , const float scale )
{
	GLboolean	boolean = GL_FALSE;



	glGetBooleanv(GL_CULL_FACE,&boolean);
	if ( boolean )
		glDisable(GL_CULL_FACE);


	glPushMatrix();
		glTranslatef(this->_position.x(),this->_position.y(),this->_position.z());
		this->_draw_tree(0,0,max_level,scale);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(this->_position.x(),this->_position.y(),this->_position.z());
		this->_leaves.draw();
	glPopMatrix();


	if ( boolean )
		glEnable(GL_CULL_FACE);
};