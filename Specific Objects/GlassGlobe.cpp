#include	<cmath>
#include	"GlassGlobe.h"

using		namespace Globe;



std::vector<Vertex>	GlassGlobe::_create_vertices( const float radius , const unsigned int slices , const unsigned int stacks , const Colour& colour )
{
	unsigned int	counter = 0;
	Vertex			vertex;
	vector<Vertex>	returnValue( (slices+1) * (stacks+1) + 1 );
	

	
	vertex._position[0] = 0.0f;
	vertex._position[1] = radius;
	vertex._position[2] = 0.0f;
	vertex._normal[0] = 0.0f;
	vertex._normal[1] = 1.0f;
	vertex._normal[2] = 0.0f;
	vertex._colour[0] = colour.red();
	vertex._colour[1] = colour.green();
	vertex._colour[2] = colour.blue();
	vertex._colour[3] = colour.alpha();
	vertex._texture[0] = 0.0f;
	vertex._texture[1] = 1.0f;
	vertex._texture[2] = 0.0f;
	returnValue[counter++] = vertex;

	
	for ( unsigned int i = 1;  i <= (stacks);  ++i )
	{
		float	angle = GlassGlobe::_PI * 0.5f* (1.0f - static_cast<float>(i)/static_cast<float>(stacks));
		float	y = sin(angle);
		float	rad = cos(angle);
		float	tex = 1.0f - static_cast<float>(i)/static_cast<float>(stacks+1);



		for ( unsigned int j = 0;  j <= slices;  ++j )
		{
			float		ang =  GlassGlobe::_PI * 2.0f * static_cast<float>(j) / static_cast<float>(slices);
			float		x  = cos(ang);
			float		z = -sin(ang);
			Vector3f	normal(rad*x,y,rad*z);



			
			vertex._position[0] = radius*normal.x();
			vertex._position[1] = radius*normal.y();
			vertex._position[2] = radius*normal.z();
			normal.normalize();
			vertex._normal[0] = normal.x();
			vertex._normal[1] = normal.y();
			vertex._normal[2] = normal.z();
			vertex._texture[0] = static_cast<float>(j) / static_cast<float>(slices);
			vertex._texture[1] = tex;
			vertex._texture[2] = 0.0f;
			returnValue[counter++] = vertex;
		}
	}
	
	for ( unsigned int j = 0;  j <= slices;  ++j )
	{
		float		ang =  GlassGlobe::_PI * 2.0f * static_cast<float>(j) / static_cast<float>(slices);
		float		x  = cos(ang);
		float		z = -sin(ang);
		Vector3f	normal(x,0.0f,z);



		normal.normalize();
		vertex._position[0] = radius*x;
		vertex._position[1] = -radius*0.1f;
		vertex._position[2] = radius*z;
		vertex._normal[0] = normal.x();
		vertex._normal[1] = normal.y();
		vertex._normal[2] = normal.z();
		vertex._texture[0] = static_cast<float>(j) / static_cast<float>(slices);
		vertex._texture[1] = 0.0f;
		vertex._texture[2] = 0.0f;
		returnValue[counter++] = vertex;
	}


	return returnValue;
};

std::vector<GLuint>	GlassGlobe::_create_indices( const unsigned int stacks , const unsigned int slices )
{
	unsigned int	counter = 0;
	vector<GLuint>	returnValue(3*2*slices*(stacks) + 3 *slices);



	
	for ( unsigned int i = 1;  i <= slices;  ++i )
	{
		returnValue[counter++] = 0;
		returnValue[counter++] = i;
		returnValue[counter++] = i + 1;
	};

	for ( unsigned int i = 0;  i < stacks;  ++i )
	{
		for ( unsigned int j = 1;  j <= slices;  ++j )
		{
			unsigned int	current = i*(slices+1) + j;
			unsigned int	next = current + 1;
			unsigned int	one_stack_lower = current + slices + 1;
			unsigned int	next_one_stack_lower = one_stack_lower + 1;



			returnValue[counter++] = current;
			returnValue[counter++] = one_stack_lower;
			returnValue[counter++] = next_one_stack_lower;

			returnValue[counter++] = current;
			returnValue[counter++] = next_one_stack_lower;
			returnValue[counter++] = next;
		}
	}


	return returnValue;
};


GlassGlobe::GlassGlobe()	{};


void	GlassGlobe::create(  const float radius , const unsigned int stacks , const unsigned int slices , const Colour& colour , const Material& material )
{
	this->use_material(true);
	this->material(material);
	this->use_textures(true);
	this->use_vertex_buffer(true);
	this->display_data(this->_create_vertices(radius,stacks,slices,colour));
	this->indices_data(this->_create_indices(stacks,slices));

	Object::create();
}

void	GlassGlobe::draw()
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
}