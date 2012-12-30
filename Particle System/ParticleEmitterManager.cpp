#include	"ParticleEmitterManager.h"

using		namespace Globe;



ParticleEmitterManager::ParticleEmitterManager( const unsigned int emitter_count )	: _emitters(emitter_count)	{};


void	ParticleEmitterManager::update( const float time_since_last_update )
{
	for ( unsigned int i = 0;  i < this->_emitters.size();  ++i )
		this->update(i,time_since_last_update);
};

void	ParticleEmitterManager::draw()
{
	for ( unsigned int i = 0;  i < this->_emitters.size();  ++i )
		this->draw(i);
};

void	ParticleEmitterManager::destroy()
{
	for ( unsigned int i = 0;  i < this->_emitters.size();  ++i )
		this->destroy(i);
};