#pragma	once

#include	"AppWindow\AppWindow.h"

using		namespace gxbase;



namespace	Globe
{

	// Class responsible for creating the application window
	class	GlobeApplication	:	public App
	{
		private:

			AppWindow	_main_window;


		public:

			GlobeApplication();
	};


	//Constructor declaration since parasoft throws a violation if there is no default constructor
	GlobeApplication::GlobeApplication()	{};



	// creation of one global static instance of our class, in order to generate the window
	static GlobeApplication	globe_application;

};