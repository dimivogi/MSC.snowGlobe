#pragma	once

#ifndef	NOMINMAX
	#define	NOMINMAX
#endif
#include	<map>
#include	"Shader.h"
#include	"GXBase.h"

using		namespace std;



namespace	Globe
{
	
	/****************************************************************************************
	*****************************************************************************************
	--------------------------------- Shader Program Class ----------------------------------
	*****************************************************************************************
	****************************************************************************************/

	// class responsible for managin shader programs
	class	ShaderProgram	:	public	glex
	{
		private:
		
			map<unsigned int,Shader&>	_shaders;
			GLuint						_id;
			string						_log;
			bool						_init;
	

		public:

			ShaderProgram();


			void						attachShader( Shader& shader );
			void						detachShader( const Shader& shader );

			GLuint						id() const;
			const Shader*				shader( const unsigned int index ) const;

			void						create();
			void						destroy();
			void						apply();
			void						remove();

			void						error_log( ostream& stream ) const;
	};

	ostream&	operator<<( ostream& stream, const ShaderProgram& program );



	/****************************************************************************************
	*****************************************************************************************
	------------------------------------ Function Definitions -------------------------------
	*****************************************************************************************
	****************************************************************************************/


	inline GLuint			ShaderProgram::id() const	{ return this->_id; };
	inline const Shader*	ShaderProgram::shader( const unsigned int index ) const
	{
		if ( index < this->_shaders.size() )
		{
			map<unsigned int,Shader&>::const_iterator	it = this->_shaders.find(index);


			
			if ( it != this->_shaders.end() )
				return &(it->second);
			else
				return NULL;
		}
		else
			return NULL;
	};


	inline void			ShaderProgram::apply()								{ glUseProgram(this->_id); };
	inline void			ShaderProgram::remove()								{ glUseProgram(0); };

	inline void			ShaderProgram::error_log( ostream& stream ) const	{ stream << this->_log; };
	inline ostream&	operator<<( ostream& stream, const ShaderProgram& program )
	{
		program.error_log(stream);


		return stream;
	};

};