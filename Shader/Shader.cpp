#include	"Shader.h"
#include	<fstream>
#include	<sstream>

using		namespace Globe;



Shader::Shader()	:	_id(0) , _source("") , _log("") , _attached_to_programs(0) , _init(false)	{};


void	Shader::load( const string& filename )
{
	char*			char_buffer = NULL;



	try
	{
		ifstream		input;
		streamoff		size;



		input.setstate(ifstream::badbit|ifstream::failbit);
		input.open(filename.c_str(),ifstream::in);

		input.seekg(0,ifstream::end);
		size = input.tellg();
		input.seekg(0,ifstream::beg);
		char_buffer = new char[static_cast<unsigned int>(size+1)];
		memset(char_buffer,'\0',static_cast<size_t>(size+1));
		input.read(char_buffer,size);
		this->_source = char_buffer;


		delete[] char_buffer;
	}
	catch( exception& e )
	{
		string	msg("Could not parse the shader file!\n");



		msg += e.what();
		throw( exception(msg.c_str() ));
	}
};

void	Shader::compile( GLenum shader_type )
{
	if ( !this->_init )
	{
		glex::Load();
		this->_init = true;
	}
	

	if ( this->_id == 0  &&  this->_source != "" )
	{
		GLchar**	strings = NULL;



		this->_id = glCreateShader(shader_type);
		if ( this->_id == 0 )
				throw( exception("Shader could not be created!"));


		try
		{
			GLint		size[1];
			
			
			
			strings = new GLchar*[1];
			strings[0] = new GLchar[this->_source.size()];
			size[0] = this->_source.size();
			memcpy(strings[0],this->_source.c_str(),this->_source.size());
			glShaderSource(this->_id,1,(const GLchar**)strings,size);
			delete[] strings[0];

			glCompileShader(this->_id);
			
			glGetShaderiv(this->_id,GL_INFO_LOG_LENGTH,size);
			if ( size[0] > 1 )
			{
				GLsizei	temp;



				strings[0] = new GLchar[ size[0] + 1];
				glGetShaderInfoLog(this->_id,size[0],&temp,strings[0]);
				this->_log = strings[0];
				delete[] strings[0];
			}

			delete[] strings;
			this->_source = "";
		}
		catch( exception& e )
		{
			string	msg("Shader could not be created!\n");



			if ( strings != NULL )
				delete[] strings;

			msg += e.what();
			glDeleteShader(this->_id);
			throw( exception(msg.c_str()));
		}
	}
};