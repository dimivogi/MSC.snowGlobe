#pragma	once

#ifndef	NOMINMAX
	#define	NOMINMAX
#endif
#include	<iostream>
#include	<string>
#include	"GXBase.h"

using		namespace std;



namespace	Globe
{

	/****************************************************************************************
	*****************************************************************************************
	------------------------------------ Shader Class -------------------------------------
	*****************************************************************************************
	****************************************************************************************/

	// class responsible for managing GLSL shaders
	class	Shader	:	public glex
	{
		private:

			GLuint			_id;
			string			_source;
			string			_log;
			unsigned int	_attached_to_programs;
			bool			_init;


		public:

			Shader();


			GLuint	id() const;


			void	load( const string& filename );
			void	compile( GLenum shader_type );
			void	attach_to_program();
			void	detach_from_program();
			void	destroy();

			void	error_log( ostream& stream ) const;
	};

	ostream&	operator<<( ostream& stream, const Shader& shader );



	/****************************************************************************************
	*****************************************************************************************
	---------------------------------- Function Definitions ---------------------------------
	*****************************************************************************************
	****************************************************************************************/

	
	inline GLuint	Shader::id() const	{ return this->_id; };

	inline void	Shader::attach_to_program()
	{
		if ( this->_id > 0 )
			++this->_attached_to_programs;
	};

	inline void	Shader::detach_from_program()
	{
		if ( this->_id > 0 )
			--this->_attached_to_programs;
	};

	inline void	Shader::destroy()
	{
		if ( this->_attached_to_programs == 0 )
			glDeleteShader(this->_id);
	};


	inline void	Shader::error_log( ostream& stream ) const	{ stream << this->_log; };
	inline ostream&	operator<<( ostream& stream, const Shader& shader )
	{
		shader.error_log(stream);


		return stream;
	};

};