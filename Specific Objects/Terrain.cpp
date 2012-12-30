#include	"Terrain.h"

using		namespace Globe;



vector<Vertex>	Terrain::_create_vertices( const unsigned int stacks , const unsigned int slices , const float radius , const float height , const Vector3f& pool_position , const float a , const float b , const Colour& top_colour , const Colour& bottom_colour )
{
	unsigned int	counter = 0;
	unsigned int	side_offset = 2*(slices+1) + 1;
	Vertex			vertex;
	vector<Vertex>	returnValue( ( (slices+1) * stacks + 1 ) + (slices + 1 + 1) + 4*(slices+1) );
	Vector4f		difference(bottom_colour.red() - top_colour.red(),bottom_colour.green() - top_colour.green(),bottom_colour.blue() - top_colour.blue(),bottom_colour.alpha() - top_colour.alpha());



	vertex._position[0] = 0.0f;
	vertex._position[1] = 0.0f;
	vertex._position[2] = 0.0f;
	vertex._normal[0] = 0.0f;
	vertex._normal[1] = 1.0f;
	vertex._normal[2] = 0.0f;
	vertex._colour[0] = top_colour.red();
	vertex._colour[1] = top_colour.green();
	vertex._colour[2] = top_colour.blue();
	vertex._colour[3] = top_colour.alpha();
	vertex._texture[0] = 0.5f;
	vertex._texture[1] = 0.5f;	
	vertex._texture[2] = 0.0f;
	returnValue[counter] = vertex;

	vertex._position[1] = -height;
	vertex._normal[1] = -1.0f;
	vertex._colour[0] = bottom_colour.red();
	vertex._colour[1] = bottom_colour.green();
	vertex._colour[2] = bottom_colour.blue();
	vertex._colour[3] = bottom_colour.alpha();
	returnValue[(counter++) + stacks*(slices+1) + 1] = vertex;

	for ( unsigned int i = 1;  i <= stacks;  ++i )
	{
		float	temp_radius = radius * static_cast<float>(i)/static_cast<float>(stacks);



		for ( unsigned int j = 0;  j <= slices;  ++j )
		{
			float	angle = Terrain::_PI * 2.0f * static_cast<float>(j)/static_cast<float>(slices);
			float	x = cos(angle);
			float	z = -sin(angle);



			vertex._position[0] = temp_radius*x;
			vertex._position[1] = 0.0f;
			vertex._position[2] = temp_radius*z;
			vertex._normal[0] = 0.0f;
			vertex._normal[1] = 1.0f;
			vertex._normal[2] = 0.0f;
			vertex._colour[0] = top_colour.red();
			vertex._colour[1] = top_colour.green();
			vertex._colour[2] = top_colour.blue();
			vertex._colour[3] = top_colour.alpha();
			vertex._texture[0] = 0.5f * (1 + x*20.0f*static_cast<float>(i)/static_cast<float>(stacks));
			vertex._texture[1] = 0.5f * (1 + z*20.0f*static_cast<float>(i)/static_cast<float>(stacks));
			vertex._texture[2] = 0.0f;
			returnValue[counter] = vertex;


			if ( i == stacks )
			{
				Vector3f	normal(x,0.0f,z);



				normal.normalize();
				vertex._normal[0] = normal.x();
				vertex._normal[1] = normal.y();
				vertex._normal[2] = normal.z();
				vertex._texture[0] = 20.0f*static_cast<float>(j)/static_cast<float>(slices);
				vertex._texture[1] = 0.0f;
				returnValue[counter + side_offset] = vertex;

				vertex._colour[0] = top_colour.red() + difference.r() *0.2f;
				vertex._colour[1] = top_colour.green() + difference.g() *0.2f;
				vertex._colour[2] = top_colour.blue() + difference.b() * 0.2f;
				vertex._colour[3] = top_colour.alpha() + difference.a() * 0.2f;
				vertex._texture[1] = 0.33f;
				vertex._position[1] = -height * 0.33f;
				returnValue[counter + side_offset + (slices+1)] = vertex;

				vertex._colour[0] += difference.r() *0.4f;
				vertex._colour[1] += difference.g() *0.4f;
				vertex._colour[2] += difference.b() * 0.4f;
				vertex._colour[3] += difference.a() * 0.4f;
				vertex._texture[1] = 0.66f;
				vertex._position[1] = -height * 0.66f;
				returnValue[counter + side_offset + 2*(slices+1)] = vertex;

				vertex._colour[0] = bottom_colour.red();
				vertex._colour[1] = bottom_colour.green();
				vertex._colour[2] = bottom_colour.blue();
				vertex._colour[3] = bottom_colour.alpha();
				vertex._texture[1] = 1.0f;
				vertex._position[1] = -height;
				returnValue[counter + side_offset + 3*(slices+1)] = vertex;


				normal.set(0.0f,-1.0f,0.0f);
				normal.normalize();
				vertex._position[1] = -height;
				vertex._normal[0] = normal.x();
				vertex._normal[1] = normal.y();
				vertex._normal[2] = normal.z();
				vertex._colour[0] = bottom_colour.red();
				vertex._colour[1] = bottom_colour.green();
				vertex._colour[2] = bottom_colour.blue();
				vertex._colour[3] = bottom_colour.alpha();
				vertex._texture[0] = 0.5f * (1 + x*20.0f*static_cast<float>(i)/static_cast<float>(stacks));
				vertex._texture[1] = 0.5f * (1 + z*20.0f*static_cast<float>(i)/static_cast<float>(stacks));
				vertex._texture[1] = 1.0f;
				returnValue[counter + slices + 1 + 1] = vertex;
			}


			counter++;
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


			returnValue[j]._position[1] = min((-0.9f*height)*percent,returnValue[j]._position[1]);

			normal.normalize();
			returnValue[j]._normal[0] = normal.x();
			returnValue[j]._normal[1] = normal.y();
			returnValue[j]._normal[2] = normal.z();

			if ( j > (slices*(stacks) + 1) )
			{
				returnValue[j+side_offset]._position[1] = returnValue[j]._position[1];
				returnValue[j+side_offset + slices+1]._position[1] = min((-0.933f*height)*percent,returnValue[j+side_offset + slices+1]._position[1]);
				returnValue[j+side_offset + 2*(slices+1)]._position[1] = min((-0.966f*height)*percent,returnValue[j+side_offset + 2*(slices+1)]._position[1]);
			}
		}
	}


	return returnValue;
};

vector<GLuint>	Terrain::_create_indices( const unsigned int stacks , const unsigned int slices )
{
	unsigned int	counter = 0;
	unsigned int	index = 0;
	vector<GLuint>	returnValue( (3 * 2 * slices*(stacks-1) + 3*slices) + 3*slices + 3*2*3*slices );



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


	for ( unsigned int j = 1;  j <= slices;  ++j )
	{
		unsigned int	current = index + j;
		unsigned int	next = index + j + 1;



		returnValue[counter++] = index;
		returnValue[counter++] = current;
		returnValue[counter++] = next;
	}
	index += slices + 1;


	for ( unsigned int i = 0;  i < 3;  ++i )
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


Terrain::Terrain()	{};


void	Terrain::create( const float radius , const float height , const unsigned int stacks , const unsigned int slices ,
						 const Vector3f& pool_position , const float a , const float b , 
						 const Colour& top_colour , const Colour& bottom_colour , const Material& material , const string& filename )
{
	Image	texture;



	this->use_material(true);
	this->material(material);
	this->use_textures(true);
	this->use_vertex_buffer(true);
	this->display_data(this->_create_vertices(stacks,slices,abs(radius),abs(height),pool_position,a,b,top_colour,bottom_colour));
	this->indices_data(this->_create_indices(stacks,slices));

	if ( filename != "" )
	{
		texture.Load(filename.c_str());
		this->textures(vector<Texture>(1,Texture(2,texture)));
		texture.Free();
	}

	Object::create();
};

void	Terrain::draw( const float scale )
{
	glPushMatrix();
		glScalef(1.0f,scale,1.0f);
		Object::draw();
	glPopMatrix();
}