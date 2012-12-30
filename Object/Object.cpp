#include	<fstream>
#include	"Object.h"

using		namespace std;
using		namespace Globe;



const float	Object::_PI = 3.1416f;
const float	Object::_PI_DIV_180 = 0.0174532925f;


Object::Object( const Vector3f& position , const Material& material , const vector<Texture>&  textures )	:
	_display_data() , _indices() , _display_data_id(0) , _indices_id(0) , 
	_buffer_initialised(false) ,  _update_pending(false) ,_using_vertex_buffer(true) , 
	_position(position) , _material(material) , _use_textures(false) , _use_material(true)
{
	this->textures(textures);
};

Object::Object( const Object& object )	: _display_data_id(0) , _indices_id(0) , _buffer_initialised(false)
{
	this->position(object.position());
	this->material(object.material());
	this->textures(object.textures());
	this->use_textures(object.using_textures());
	this->use_material(object.using_material());
	this->use_vertex_buffer(object.using_vertex_buffer());
	this->display_data(object.display_data());
	this->indices_data(object.indices_data());
};

Object::~Object()	{};


Object&	Object::operator=( const Object& object )
{
	if ( &object != this )
	{
		this->position(object.position());
		this->material(object.material());
		this->textures(object.textures());
		this->use_textures(object.using_textures());
		this->use_material(object.using_material());
		this->use_vertex_buffer(object.using_vertex_buffer());
		this->_display_data_id = 0;
		this->display_data(object.display_data());
		this->_indices_id = 0;
		this->indices_data(object.indices_data());
		this->_buffer_initialised = false;
	}


	return *this;
}


void	Object::position( const Vector3f& position )	{ this->_position = position; };
void	Object::material( const Material& material )	{ this->_material = material; };
void	Object::texture( const unsigned int texture_no , const Texture& texture )
{
	this->destroy_texture(texture_no);

	if ( texture_no < this->_textures.size() )
		this->_textures[texture_no] = texture;

	this->create_texture(texture_no);
};

void	Object::textures( const vector<Texture>& textures )
{
	this->destroy_textures();

	this->_textures.resize(textures.size());
	this->_initialised.resize(textures.size());

	for ( unsigned long i = 0;  i < this->_textures.size();  ++i )
	{
		this->_initialised[i] = false;
		this->texture(i,textures[i]);
	}
};

void	Object::use_textures( const bool value )		{ this->_use_textures = value; };
void	Object::use_material( const bool value )		{ this->_use_material = value; };

void	Object::use_vertex_buffer( const bool value )
{ 
	if ( value != this->using_vertex_buffer() )
	{	
		if ( !value )
			this->_update_pending = false;
		else
			this->_update_pending = true;

		this->_using_vertex_buffer = value; 
	}
};

void	Object::display_data( const vector<Vertex>& data )
{
	if ( this->using_vertex_buffer() )
		this->_update_pending = true;
	else
		this->_update_pending = false;

	this->_display_data = data;
};
void	Object::indices_data( const vector<GLuint>& data )
{
	if ( this->using_vertex_buffer() )
		this->_update_pending = true;
	else
		this->_update_pending = false;

	this->_indices = data;
};


Vector3f	Object::position() const					{ return this->_position; };
Material	Object::material() const					{ return this->_material; };
Texture		Object::texture( unsigned int texture_no ) const
{
	if ( texture_no < this->_textures.size() )
		return this->_textures[texture_no];
	else
		return Texture();
};

vector<Texture>		Object::textures() const			{ return this->_textures; };
bool				Object::using_textures() const		{ return this->_use_textures; };
bool				Object::using_material() const		{ return this->_use_material; };
bool				Object::using_vertex_buffer() const	{ return this->_using_vertex_buffer; };
vector<Vertex>		Object::display_data() const		{ return this->_display_data; };
vector<GLuint>		Object::indices_data() const		{ return this->_indices; };



void	Object::create_texture( const unsigned int texture_no )
{
	if ( texture_no < this->_textures.size() )
	{
		if ( !this->_initialised[texture_no] )
		{
			this->_textures[texture_no].create();
			this->_initialised[texture_no] = true;
		}
	}
};

void	Object::create_textures()
{
	for ( unsigned int i = 0;  i < this->_textures.size();  ++i )
		this->create_texture(i);
};

void	Object::destroy_texture( const unsigned int texture_no )
{
	if ( texture_no < this->_textures.size() )
		this->_textures[texture_no].free();
};

void	Object::destroy_textures()
{
	for ( unsigned int i = 0;  i < this->_textures.size();  ++i )
		this->destroy_texture(i);
}


void	Object::create_vertex_buffer()
{
	if ( this->using_vertex_buffer() )
	{
		if ( !this->_buffer_initialised )
		{
			glGenBuffersARB(1,&(this->_display_data_id));
			glGenBuffersARB(1,&(this->_indices_id));

			this->_buffer_initialised = true;
			this->_update_pending = true;
			this->update_vertex_buffer();
		}
	}
};

void	Object::update_vertex_buffer()
{
	if ( this->using_vertex_buffer() )
	{
		if ( this->_update_pending )
		{
			if ( this->_buffer_initialised )
			{
				glBindBufferARB(GL_ARRAY_BUFFER_ARB,this->_display_data_id);
				glBufferDataARB(GL_ARRAY_BUFFER_ARB,sizeof(Vertex)*this->_display_data.size(),0,GL_STATIC_DRAW_ARB);
				glBufferSubDataARB(GL_ARRAY_BUFFER_ARB,0,sizeof(Vertex)*this->_display_data.size(),this->_display_data.data());
				glVertexPointer(3,GL_FLOAT,sizeof(Vertex),(char*)NULL + 0);
				glNormalPointer(GL_FLOAT,sizeof(Vertex),(char*)NULL + (sizeof(GLfloat)*3));
				glColorPointer(4,GL_FLOAT,sizeof(Vertex),(char*)NULL + (sizeof(GLfloat)*6));

				if ( this->using_textures() )
					glTexCoordPointer(3,GL_FLOAT,sizeof(Vertex),(char*)NULL + (sizeof(GLfloat)*10));

				glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB,this->_indices_id);
				glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER_ARB,sizeof(GLuint)*this->_indices.size(),this->_indices.data(),GL_STATIC_DRAW);


				glBindBufferARB(GL_ARRAY_BUFFER_ARB,0);
				glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER,0);

				this->_update_pending = false;
			}
		}
	}
};

void	Object::destroy_vertex_buffer()
{
	if ( this->_buffer_initialised )
	{
		glDeleteBuffersARB(1,&(this->_display_data_id));
		glDeleteBuffersARB(1,&(this->_indices_id));
		this->_buffer_initialised = false;
	}
};

void	Object::draw_vertex_buffer()
{
	glBindBufferARB(GL_ARRAY_BUFFER_ARB,this->_display_data_id);
	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER,this->_indices_id);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glVertexPointer(3,GL_FLOAT,sizeof(Vertex),(char*)NULL + 0);
	glNormalPointer(GL_FLOAT,sizeof(Vertex),(char*)NULL + (sizeof(GLfloat)*3));
	glColorPointer(4,GL_FLOAT,sizeof(Vertex),(char*)NULL + (sizeof(GLfloat)*6));
	
	if ( this->using_textures() )
		glTexCoordPointer(3,GL_FLOAT,sizeof(Vertex),(char*)NULL + (sizeof(GLfloat)*10));
	
	glDrawElements(GL_TRIANGLES,this->_indices.size(),GL_UNSIGNED_INT,(char*)NULL + 0);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	glBindBufferARB(GL_ARRAY_BUFFER_ARB,0);
	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER,0);
};

void	Object::draw_vertex_array()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glVertexPointer(3,GL_FLOAT,sizeof(Vertex),(char*)this->_display_data.data() + 0);
	glNormalPointer(GL_FLOAT,sizeof(Vertex),(char*)this->_display_data.data() + (sizeof(GLfloat)*3));
	glColorPointer(4,GL_FLOAT,sizeof(Vertex),(char*)this->_display_data.data() + (sizeof(GLfloat)*6));
	glTexCoordPointer(3,GL_FLOAT,sizeof(Vertex),(char*)this->_display_data.data() + (sizeof(GLfloat)*10));
	glDrawElements(GL_TRIANGLES,this->_indices.size(),GL_UNSIGNED_INT,(char*)this->_indices.data() + 0);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
};


void	Object::create()
{
	glex::Load();


	this->create_textures();
	
	if ( this->using_vertex_buffer() )
		this->create_vertex_buffer();
};

void	Object::destroy()
{
	this->destroy_textures();

	if ( this->_display_data_id > 0  )
		this->destroy_vertex_buffer();
};

void	Object::draw()
{
	glPushMatrix();


	glTranslatef(this->_position.x(),this->_position.y(),this->_position.z());

	if ( this->using_material() )
		this->_material.apply();

	if ( this->using_textures() )
	{
		for ( unsigned int i = 0;  i < _textures.size();  ++i )
		{		
			glActiveTextureARB(GL_TEXTURE0 + i );
			this->_textures[i].apply();
		}
	}

	if ( this->using_vertex_buffer() )
	{
		if ( this->_buffer_initialised )
		{
			if ( this->_update_pending )
				this->update_vertex_buffer();

			this->draw_vertex_buffer();
		}
	}
	else
		this->draw_vertex_array();

	if ( this->using_textures() )
	{
		for ( unsigned int i = 0;  i < _textures.size();  ++i )
		{
			glActiveTextureARB(GL_TEXTURE0 + i );
			this->_textures[i].remove();
		}
	}

	if ( this->using_material() )
		this->_material.remove();


	glPopMatrix();
};
