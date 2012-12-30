#include	"House.h"

using		namespace Globe;



void		House::_update_difference()
{
	this->_difference.set(	this->_position.x()-this->_centre.x(),
							this->_position.y()-this->_centre.y(),
							this->_position.z()-this->_centre.z()
						);
};


House::House()	:	_rotation(0.0f)	{};


void		House::position( const Vector3f& position )	{ this->_position = position;	this->_update_difference(); };
void		House::rotation( const GLfloat value )		{ this->_rotation = value; };

Vector3f	House::position() const						{ return this->_position; };
GLfloat		House::rotation() const						{ return this->_rotation; };


void	House::create( const string& filename , const float scale )
{
	if ( !this->_house.Load(filename.c_str()) )
		throw(exception("The house model file could not be loaded!"));

	this->_house.SetScale(scale);

	Model::Vector3f	centre = this->_house.GetBoxCentre();
	this->_centre.set(centre.x,centre.y,centre.z);
	this->_update_difference();
};

void	House::destroy()
{
	this->_house.FreeGL();
	this->_house.Free();
};

void	House::draw( unsigned int renderMode )
{
	glPushMatrix();
		glTranslatef(this->_difference.x(),this->_difference.y(),this->_difference.z());
		glRotatef(this->_rotation,0.0f,1.0f,0.0f);
		glRotatef(270.0f,1.0f,0.0f,0.0f);

		if ( renderMode == 1 )
			this->_house.DrawGL(DSWire|DSNoBindTexture);
		else if ( renderMode == 2 )
			this->_house.DrawGL(DSFlat|DSNoBindTexture);
		else if ( renderMode == 3 )
			this->_house.DrawGL(DSSmooth|DSNoBindTexture);
		else
			this->_house.DrawGL(DSMaterial);
	glPopMatrix();
};