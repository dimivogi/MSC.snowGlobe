#include	"ShaderProgram.h"

using		namespace Globe;



ShaderProgram::ShaderProgram()	:	_id(0) , _log("") , _init(false)	{};


void			ShaderProgram::attachShader( Shader& shader )
{
	bool			found = false;
	unsigned int	key = 0;



	for ( map<unsigned int,Shader&>::iterator it = this->_shaders.begin();  it != this->_shaders.end();  ++it )
	{
		if ( &(it->second) == &shader )
		{
			found = true;
			break;
		}
		else
			++key;
	}

	if ( !found )
	{
		this->_shaders.insert(pair<unsigned int,Shader&>(key,shader));


		if ( this->_id > 0  )
		{
			if (shader.id() > 0 )
			{
				glAttachShader(this->_id,shader.id());
				shader.attach_to_program();
				glLinkProgram(this->_id);
			}
		}
	}
};

void			ShaderProgram::detachShader( const Shader& shader )
{
	for ( map<unsigned int,Shader&>::iterator it = this->_shaders.begin();  it != this->_shaders.end();  ++it )
	{
		if ( &(it->second) == &shader )
		{
			this->_shaders.erase(it);

			if ( this->_id > 0 )
			{
				if ( (it->second).id() > 0 )
				{
					glDetachShader(this->_id,(it->second).id());
					(it->second).detach_from_program();
					(it->second).destroy();
					glLinkProgram(this->_id);
				}
			}

			break;
		}
	}
}

void			ShaderProgram::create()
{
	if ( !this->_init )
	{
		glex::Load();
		this->_init = true;
	}


	if ( this->_id == 0 )
	{
		GLint		size[1];
		GLchar**	strings = NULL;



		this->_id = glCreateProgram();

		if ( this->_shaders.size() > 0 )
		{
			for ( map<unsigned int,Shader&>::iterator it = this->_shaders.begin();  it != this->_shaders.end();  ++it )
			{
				(it->second).attach_to_program();
				glAttachShader(this->_id,(it->second).id());
			};


			glLinkProgram(this->_id);
		}
		
			
		try
		{
			glGetProgramiv(this->_id,GL_INFO_LOG_LENGTH,size);
			if ( size[0] > 1 )
			{
				GLsizei	temp;



				strings = new GLchar*[1];
				strings[0] = new GLchar[ size[0] + 1];
				glGetProgramInfoLog(this->_id,size[0],&temp,strings[0]);
				this->_log = strings[0];
				delete[] strings[0];
			}

			delete[] strings;
		}
		catch( exception& e )
		{
			string	msg("Shader Program could not be created!\n");



			if ( strings != NULL )
				delete[] strings;
			
			for ( map<unsigned int,Shader&>::iterator it = this->_shaders.begin();  it != this->_shaders.end();  ++it )
			{
				(it->second).detach_from_program();
				glDetachShader(this->_id,(it->second).id());
			};

			glDeleteProgram(this->_id);
			this->_id = 0;

			msg += e.what();
			throw( exception(msg.c_str() ));
		}
	}
};

void			ShaderProgram::destroy()
{
	if ( this->_id )
	{
		for ( map<unsigned int,Shader&>::iterator it = this->_shaders.begin();  it != this->_shaders.end();  ++it )
		{
			glDetachShader(this->_id,(it->second).id());
			(it->second).detach_from_program();
			(it->second).destroy();
		}

		glDeleteProgram(this->_id);
	}
};