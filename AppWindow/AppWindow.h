#pragma once

#ifndef	NOMINMAX
	#define	NOMINMAX
#endif
#include	"GXBase.h"
#include	"..\Scene Manager\SceneManager.h"

using		namespace gxbase;



namespace	Globe
{

	//	Class responsible for handling the message functions and passing the relevant information to the scene_manager class
	class	AppWindow	:	public GLWindowEx
	{
		private:

			SceneManager				_scene_manager;
			bool						_fullscreen;


			static const unsigned int	_window_width = 1280;
			static const unsigned int	_window_height = 800;
			static const unsigned int	_window_width_debug = 1024;
			static const unsigned int	_window_height_debug = 768;
			static const unsigned int	_window_x_offset = 10;
			static const unsigned int	_window_y_offset = 10;
			static const unsigned int	_window_x_offset_debug = 700;
			static const unsigned int	_window_y_offset_debug = 10;

			static const unsigned int	_max_console_lines = 999;
			static const unsigned int	_console_x_offset = 10;
			static const unsigned int	_console_y_offset = 10;


			static HWND					_find_console_handle();
			static void					_redirect_io();


		public:

			AppWindow();


			void	OnCreate();
			void	OnDestroy();
			void	OnResize( int w , int h );

			void	OnMouseMove( int x , int y);
			void	OnMouseButton( MouseButton button , bool down );
			void	OnKeyboard( int key , bool down );

			void	OnDisplay();
			void	OnIdle();
	};

}