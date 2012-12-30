#include	"SnowMounts.h"
#include	"..\Matrix\Matrix4x4f.h"

using		namespace Globe;



vector<Vertex>		SnowMounts::_create_roof_vertices( const vector<Vector3f>& plane , const Colour& colour , vector<Vector3f>& normals )
{
	Vertex			vertex;
	vector<Vertex>	return_value(6);



	vertex._colour[0] = colour.red();
	vertex._colour[1] = colour.green();
	vertex._colour[2] = colour.blue();
	vertex._colour[3] = colour.alpha();

	if ( plane.size() >= 3 )
	{
		Vector3f	normal(plane[1] - plane[0]);



		normal.dot_product(plane[2] - plane[0]);
		normal.normalize();
		
		if ( normal.y() < 0 )
			normal *= -1.0f;

		normals.push_back(normal);

		for ( unsigned int i = 0;  i < 3;  ++i )
		{
			vertex._position[0] = plane[i].x() + normal.x();
			vertex._position[1] = plane[i].y() + normal.y();
			vertex._position[2] = plane[i].z() + normal.z();
			vertex._normal[0] = normal.x();
			vertex._normal[1] = normal.y();
			vertex._normal[2] = normal.z();
			vertex._texture[0] = 0.0f;
			vertex._texture[1] = 0.0f;
			vertex._texture[2] = 0.0f;
			return_value[i] = vertex;

			vertex._position[0] = plane[i].x();
			vertex._position[1] = plane[i].y();
			vertex._position[2] = plane[i].z();
			vertex._texture[2] = 1.0f;
			return_value[i+3] = vertex;
		}
	}


	return return_value;
};

vector<GLuint>		SnowMounts::_create_roof_indices()
{
	vector<GLuint>	return_value( 2*3 + 3*2*3);



	return_value[0] = 0;
	return_value[1] = 1;
	return_value[2] = 2;

	return_value[3] = 3;
	return_value[4] = 4;
	return_value[5] = 5;

	return_value[6] = 0;
	return_value[7] = 3;
	return_value[8] = 4;

	return_value[9] = 0;
	return_value[10] = 4;
	return_value[11] = 1;

	return_value[12] = 1;
	return_value[13] = 4;
	return_value[14] = 5;

	return_value[15] = 1;
	return_value[16] = 5;
	return_value[17] = 2;

	return_value[18] = 2;
	return_value[19] = 5;
	return_value[20] = 3;

	return_value[21] = 2;
	return_value[22] = 3;
	return_value[23] = 1;


	return return_value;
};


vector<Vertex>	SnowMounts::_create_terrain_vertices( const unsigned int stacks , const unsigned int slices , const float radius , const float height , const Vector3f& pool_position , const float a , const float b , const Colour& colour )
{
	unsigned int	counter = 0;
	unsigned int	bottom_offset = (slices+1)*stacks + 1;
	unsigned int	side_offset = bottom_offset + (slices+1);
	Vertex			vertex;
	vector<Vertex>	returnValue( 2*( (slices+1) * stacks + 1 ) + 3*(slices+1) );



	vertex._position[0] = 0.0f;
	vertex._position[1] = 1.0f + 0.1f*(rand()%201 - 100)*0.002f;
	vertex._position[2] = 0.0f;
	vertex._normal[0] = 0.0f;
	vertex._normal[1] = 1.0f;
	vertex._normal[2] = 0.0f;
	vertex._colour[0] = colour.red();
	vertex._colour[1] = colour.green();
	vertex._colour[2] = colour.blue();
	vertex._colour[3] = colour.alpha();
	vertex._texture[0] = 0.5f;
	vertex._texture[1] = 0.5f;	
	vertex._texture[2] = 0.0f;
	returnValue[counter] = vertex;

	vertex._position[1] = 0.0f;
	vertex._normal[1] = -1.0f;
	vertex._texture[2] = 1.0f;
	returnValue[(counter++) + bottom_offset] = vertex;

	for ( unsigned int i = 1;  i <= stacks;  ++i )
	{
		float	temp_radius = radius * static_cast<float>(i)/static_cast<float>(stacks);



		for ( unsigned int j = 0;  j <= slices;  ++j )
		{
			float	angle = Object::_PI * 2.0f * static_cast<float>(j)/static_cast<float>(slices);
			float	x = cos(angle);
			float	z = -sin(angle);



			vertex._position[0] = temp_radius*x;

			if ( j == slices )
				vertex._position[1] = returnValue[counter-slices]._position[1];
			else
				vertex._position[1] = height + 0.1f*(rand()%201 - 100)*0.025f;

			vertex._position[2] = temp_radius*z;
			vertex._normal[0] = 0.0f;
			vertex._normal[1] = 1.0f;
			vertex._normal[2] = 0.0f;
			vertex._texture[0] = 0.5f * (1 + x*20.0f*static_cast<float>(i)/static_cast<float>(stacks));
			vertex._texture[1] = 0.5f * (1 + z*20.0f*static_cast<float>(i)/static_cast<float>(stacks));
			vertex._texture[2] = 0.0f;
			returnValue[counter] = vertex;

			vertex._position[1] = 0.0f;
			vertex._normal[1] = -1.0f;
			vertex._texture[2] = 1.0f;
			returnValue[counter + bottom_offset] = vertex;


			if ( i == stacks )
			{
				vertex._position[1] = returnValue[counter]._position[1];
				vertex._normal[0] = x;
				vertex._normal[1] = 0.0f;
				vertex._normal[2] = z;
				vertex._texture[0] = 20.0f*static_cast<float>(j)/static_cast<float>(slices);
				vertex._texture[1] = 0.0f;
				vertex._texture[2] = 0.0f;
				returnValue[counter + side_offset] = vertex;

				vertex._position[1] = 0.5f;
				vertex._texture[1] = 0.5f;
				returnValue[counter + side_offset + slices + 1] = vertex;

				vertex._position[1] = returnValue[counter + bottom_offset]._position[1];
				vertex._texture[1] = 1.0f;
				returnValue[counter + side_offset + 2*(slices+1) ] = vertex;
			}

			++counter;
		}
	}

	
	float	a_sqr = a*a;
	float	b_sqr = b*b;
	float	ab_sqr = a_sqr*b_sqr;
	for ( unsigned int j = 0;  j <= (slices+1) * stacks;  ++j )
	{
		float	distance = b_sqr*pow(returnValue[j]._position[0] - pool_position.x(),2) + a_sqr*pow(returnValue[j]._position[2]-pool_position.z(),2);
		float	percent = 1.0f  - distance/ab_sqr;



		if (  (distance - ab_sqr) <= Vector3f::_V3EPSILON )
		{
			Vector3f	normal(0.0f,1.0f,0.0f);




			if ( abs(distance) > Vector3f::_V3EPSILON )
				normal.set((pool_position.x() - returnValue[j]._position[0])*ab_sqr/distance,max(percent,1.0f-percent),(pool_position.z() - returnValue[j]._position[2])*ab_sqr/distance);


			returnValue[j]._position[1] = min(1.0f -(0.9f),returnValue[j]._position[1]);
			returnValue[j + bottom_offset]._position[1] = min(-0.9f*percent,returnValue[j+bottom_offset]._position[1]);

			normal.normalize();
			returnValue[j]._normal[0] = normal.x();
			returnValue[j]._normal[1] = normal.y();
			returnValue[j]._normal[2] = normal.z();

			if ( j > (slices*(stacks) + 1) )
			{
				returnValue[j+side_offset]._position[1] = returnValue[j]._position[1];
				returnValue[j+side_offset + slices+1]._position[1] = min((0.5f-0.9f*percent),returnValue[j+side_offset + slices+1]._position[1]);
				returnValue[j+side_offset + 2*(slices+1)]._position[1] = returnValue[j + bottom_offset]._position[1];
			}
		}
	}


	return returnValue;
};

vector<GLuint>	SnowMounts::_create_terrain_indices( const unsigned int stacks , const unsigned int slices )
{
	unsigned int	counter = 0;
	unsigned int	index = 0;
	vector<GLuint>	returnValue( 2*(3 * 2 * slices*(stacks-1) + 3*slices) + 3*2*2*(slices) );



	for ( unsigned int i = 0;  i < 2;  ++i )
	{
		for ( unsigned int j = 1;  j <= slices;  ++j )
		{
			unsigned int	current = index + j;
			unsigned int	next = index + j + 1;



			returnValue[counter++] = index;
			returnValue[counter++] = current;
			returnValue[counter++] = next;
		}

		
		for ( unsigned int j = 0;  j < (stacks-1);  ++j )
		{
			for ( unsigned int k = 1;  k <= slices;  ++k )
			{
				unsigned int	current = index + k;
				unsigned int	next = index + k + 1;
				unsigned int	one_stack_further = index + k + slices + 1;
				unsigned int	next_one_stack_further = index + k + slices + 1 + 1;



				returnValue[counter++] = current;
				returnValue[counter++] = one_stack_further;
				returnValue[counter++] = next_one_stack_further;

				returnValue[counter++] = current;
				returnValue[counter++] = next_one_stack_further;
				returnValue[counter++] = next;
			};


			index += slices + 1;
		}

		index += (slices + 1 + 1);
	};


	--index;
	for ( unsigned int i = 0;  i < 2;  ++i )
	{
		for ( unsigned int j = 1;  j <= slices;  ++j )
		{
			unsigned int	current = index + j;
			unsigned int	next = index + j + 1;
			unsigned int	one_stack_lower = index + j + slices + 1;
			unsigned int	next_one_stack_lower = index + j + slices + 1 + 1;



			returnValue[counter++] = current;
			returnValue[counter++] = one_stack_lower;
			returnValue[counter++] = next_one_stack_lower;

			returnValue[counter++] = current;
			returnValue[counter++] = next_one_stack_lower;
			returnValue[counter++] = next;
		}

		index += slices + 1;
	}


	return returnValue;
};


SnowMounts::SnowMounts()	{};


void				SnowMounts::position( const Vector3f& position )
{
	this->_position = position;
};


void				SnowMounts::use_material( const bool value )
{
	for ( unsigned int i = 0;  i < this->_roof_mounts.size();  ++i )
		this->_roof_mounts[i].use_material(value);

	this->_terrain_snow.use_material(value);
};

void				SnowMounts::use_textures( const bool value )
{
	for ( unsigned int i = 0;  i < this->_roof_mounts.size();  ++i )
		this->_roof_mounts[i].use_textures(value);

	this->_terrain_snow.use_textures(value);
};

Vector3f			SnowMounts::position() const
{
	return this->_position;
};


void				SnowMounts::create(	const float radius , const float height , const unsigned int stacks , const unsigned int slices , 
										const Vector3f& pool_position , const float a , const float b , 
										const vector<vector<Vector3f> >& roof_planes , 
										const Colour& colour , const Material& material , const string& filename )
{
	Image			image;
	Texture			texture(2);
	vector<Texture>	textures;
	Vector3f		position(0.0f,0.0f,0.0f);



	srand(static_cast<unsigned int>(time(NULL)));

	if ( filename != "" )
	{
		image.Load(filename.c_str());
		texture.image(image);
		textures.push_back(texture);
	}


	if ( roof_planes.size() > 0 )
	{
		this->_roof_mounts.resize(roof_planes.size());

		for ( unsigned int i = 0;  i < roof_planes.size();  ++i )
		{
			this->_roof_mounts[i].position(position);
			this->_roof_mounts[i].material(material);
			this->_roof_mounts[i].textures(textures);
			this->_roof_mounts[i].use_vertex_buffer(true);
			this->_roof_mounts[i].display_data(this->_create_roof_vertices(roof_planes[i],colour,this->_roof_normals));
			this->_roof_mounts[i].indices_data(this->_create_roof_indices());

			this->_roof_mounts[i].create();
		}
	}

	this->_terrain_snow.position(position);
	this->_terrain_snow.material();
	this->_terrain_snow.textures(textures);
	this->_terrain_snow.use_vertex_buffer(true);
	this->_terrain_snow.display_data(this->_create_terrain_vertices(stacks,slices,abs(radius),abs(height),pool_position,a,b,colour));
	this->_terrain_snow.indices_data(this->_create_terrain_indices(stacks,slices));
	this->_terrain_snow.create();


	if ( !image.IsEmpty() )
	{
		image.Free();
		texture.free();
	}
};

void				SnowMounts::draw( const GLfloat terrain_scale , const GLfloat roof_x_scale , const GLfloat roof_y_scale , const GLfloat roof_z_scale , bool ignore_stencil )
{
	Matrix4x4f	matrix;
	Vector3f	roof_scale;



	glPushMatrix();
		glTranslatef(this->_position.x(),this->_position.y(),this->_position.z());

		glPushMatrix();
			glTranslatef(this->_position.x(),this->_position.y(),this->_position.z());
			glScalef(1.0f,terrain_scale,1.0f);

			this->_terrain_snow.draw();

		glPopMatrix();

	
		GLboolean	stencil = GL_FALSE;



		if ( ignore_stencil )
		{
			glGetBooleanv(GL_STENCIL_TEST,&stencil);
			if ( stencil )
				glDisable(GL_STENCIL_TEST);
		}

		for ( unsigned int i = 0;  i < this->_roof_mounts.size();  ++i )
		{
			float	dot_product = this->_roof_normals[i] * Vector3f(0.0f,1.0f,0.0f);



			matrix.identity();
			matrix.rotate(dot_product,this->_roof_normals[i].x(),this->_roof_normals[i].y(),this->_roof_normals[i].z());
			roof_scale = matrix.multiply(Vector3f(roof_x_scale,roof_y_scale,roof_z_scale));

			glPushMatrix();

				glScalef(roof_scale.x(),roof_scale.y(),roof_scale.z());

				this->_roof_mounts[i].draw();

			glPopMatrix();
		};

		
		if ( ignore_stencil )
		{
			if ( stencil )
				glEnable(GL_STENCIL_TEST);
		}

	glPopMatrix();
};

void				SnowMounts::destroy()
{	
	for ( unsigned int i = 0;  i < this->_roof_mounts.size();  ++i )
		this->_roof_mounts[i].destroy();

	this->_terrain_snow.destroy();
};