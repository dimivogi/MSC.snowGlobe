#include	"Pool.h"

using		namespace Globe;



const float	_EPSILON = 0.001f;



vector<Vertex>	Pool::_create_vertices(  const unsigned int stacks , const unsigned int slices , const unsigned int height_stacks , const float a , const float b , const float height , const Vector3f& position , const Vector3f& terrain_position , const float radius , const Colour& colour )
{
	unsigned int	counter = 0;
	unsigned int	side_offset = height_stacks*((slices+1)*stacks+1) /*+ 1*/;
	Vertex			vertex;
	vector<Vertex>	returnValue( height_stacks * ((slices+1)*stacks + 1 + (slices+1))/* + 1*/ );



	for ( unsigned int k = 0;  k < height_stacks;  ++k )
	{
		float	angle = Pool::_PI * 0.5f* static_cast<float>(k)/static_cast<float>(height_stacks);
		float	y = sin(angle);
		float	rad = 1.0f - static_cast<float>(k)/static_cast<float>(height_stacks); //cos(angle);




		vertex._position[0] = 0.0f;
		vertex._position[1] = -height * y;
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
		returnValue[counter++] = vertex;


		for ( unsigned int i = 1;  i <= stacks;  ++i )
		{
			float	temp_a = a * static_cast<float>(i) / static_cast<float>(stacks);
			float	temp_b = b * static_cast<float>(i) / static_cast<float>(stacks);



			for( unsigned int j = 0;  j <= slices;  ++j )
			{
				float	angle = Pool::_PI * 2.0f * static_cast<float>(j)/static_cast<float>(slices);
				float	x = cos(angle);
				float	z = -sin(angle);
				float	x_coef = rad*temp_a*x;
				float	z_coef = rad*temp_b*z;



				if ( sqrt( pow( (position.x() + x_coef) - terrain_position.x(),2) + pow( (position.z() + z_coef) - terrain_position.z(),2) ) < (radius+_EPSILON) )
				{
					vertex._position[0] = x_coef;
					vertex._position[2] = z_coef;
				}
				else
				{
					Vector3f	x_axis(radius,0,0);
					Vector3f	temp_position(position.x() + x_coef - terrain_position.x(),0,position.z() + z_coef - terrain_position.z());
					float		dot_product = temp_position * x_axis;



					vertex._position[0] = radius*dot_product;
					vertex._position[2] = radius*(sqrt(1-pow(dot_product,2)));
				}

				
				vertex._position[1] = -height * y;
				vertex._normal[0] = 0.0f;
				vertex._normal[1] = 1.0f;
				vertex._normal[2] = 0.0f;
				vertex._texture[0] = 0.5f * (1 + x*static_cast<float>(i)/static_cast<float>(stacks));
				vertex._texture[1] = 0.5f * (1 + z*static_cast<float>(i)/static_cast<float>(stacks));
				returnValue[counter++] = vertex;

				if ( i == stacks )
				{
					vertex._normal[0] = x;
					vertex._normal[1] = 0.0f;
					vertex._normal[2] = z;
					vertex._texture[0] = static_cast<float>(j)/static_cast<float>(slices);
					vertex._texture[1] = y;
					returnValue[side_offset + k*(slices+1) + j] = vertex;
				}
			}
		}
	}

	/*vertex._position[0] = 0.0f;
	vertex._position[1] = -height;
	vertex._position[2] = 0.0f;
	vertex._normal[0] = 0.0f;
	vertex._normal[1] = -1.0f;
	vertex._normal[2] = 0.0f;
	vertex._texture[0] = 0.5f;
	vertex._texture[1] = 0.5f;
	vertex._texture[2] = 1.0f;
	returnValue[counter] = vertex;*/


	return returnValue;
};

vector<GLuint>	Pool::_create_indices(  const unsigned int stacks , const unsigned int slices , const unsigned int height_stacks )
{
	unsigned int	counter = 0;
	unsigned int	index = 0;
	vector<GLuint>	returnValue( height_stacks*(3 * 2 * slices*(stacks-1) + 3*slices) + (height_stacks-1)*3*2*slices /*+ 3*slices*/ );


	
	for ( unsigned int i = 0;  i < height_stacks;  ++i )
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


	//unsigned int	bottom_index = index;
	--index;
	for ( unsigned int i = 0;  i < (height_stacks-1);  ++i )
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


	/*for ( unsigned int i = 1;  i <= slices;  ++i )
	{
		unsigned int	current = index + i;
		unsigned int	next = index + i + 1;



		returnValue[counter++] = bottom_index;
		returnValue[counter++] = current;
		returnValue[counter++] = next;
	};*/


	return returnValue;
};



Pool::Pool()	{};


void					Pool::create( const float a , const float b , const float height , 
									  const unsigned int stacks , const unsigned int slices , const unsigned  int height_stacks ,
									  const Vector3f& terrain_position , const float radius , 
									  const Colour& colour , const Material& material , const string& filename )
{
	Image	texture;



	this->material(material);
	this->use_textures(true);
	this->use_vertex_buffer(true);
	this->display_data(this->_create_vertices(stacks,slices,height_stacks,abs(a),abs(b),abs(height),this->position(),terrain_position,radius,colour));
	this->indices_data(this->_create_indices(stacks,slices,height_stacks));

	if ( filename != "" )
	{
		texture.Load(filename.c_str());
		this->textures(vector<Texture>(1,Texture(2,texture)));
		texture.Free();
	}


	Object::create();
};

void					Pool::draw()
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
	Object::draw();
	glBlendFunc(src,dst);

	if ( !blend )
		glDisable(GL_BLEND);

	glDepthMask(mask);

	if ( cull )
		glEnable(GL_CULL_FACE);
};