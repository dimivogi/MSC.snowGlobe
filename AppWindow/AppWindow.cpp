#include	<io.h>
#include	<iostream>
#include	<fstream>
#include	<cstdio>
#include	<fcntl.h>
#include	"AppWindow.h"

using		namespace std;
using		namespace Globe;



// function for getting the handle of the newly allocated console
HWND	AppWindow::_find_console_handle()
{
	static const int	BUFF_SIZE	= 1024;
	wchar_t				windowTitle[BUFF_SIZE];
	wchar_t				temp_windowTitle[BUFF_SIZE+5];
	HWND				returnValue;



	GetConsoleTitle(windowTitle,BUFF_SIZE);
	wsprintf(temp_windowTitle,L"%s-temp",windowTitle);
	SetConsoleTitle(temp_windowTitle);
	Sleep(40);
	returnValue = FindWindow(NULL,temp_windowTitle);
	SetConsoleTitle(windowTitle);


	return returnValue;
};

// function responsible for redirecting the output and input streams to a (newly) allocated console
void	AppWindow::_redirect_io()
{
	// allocate a new console window
	if ( !AllocConsole() )	return;



	CONSOLE_SCREEN_BUFFER_INFO	console_info;

	// set the maximum console lines
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&console_info);
	console_info.dwSize.Y = AppWindow::_max_console_lines;
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE),console_info.dwSize);


	// resize the console window
	HWND	console_handle = AppWindow::_find_console_handle();
	RECT	console_size;
	RECT	desktop_size;
	
	GetWindowRect(console_handle,&console_size);
	GetClientRect(GetDesktopWindow(),&desktop_size);
	console_size.bottom = desktop_size.bottom - 100;
	MoveWindow(console_handle,AppWindow::_console_x_offset,AppWindow::_console_y_offset,console_size.right,console_size.bottom,TRUE);




	// get the handles to the input and output streams, and redirect them
	int		stdout_handle = _open_osfhandle((long)GetStdHandle(STD_OUTPUT_HANDLE),_O_TEXT); 
	int		stdin_handle = _open_osfhandle((long)GetStdHandle(STD_INPUT_HANDLE),_O_TEXT);
	int		stderr_handle = _open_osfhandle((long)GetStdHandle(STD_ERROR_HANDLE),_O_TEXT);

	FILE*	stdout_file = _fdopen(stdout_handle,"w");
	FILE*	stdin_file = _fdopen(stdin_handle,"r");
	FILE*	stderr_file = _fdopen(stderr_handle,"w");

	*stdout = *stdout_file;
	*stdin = *stdin_file;
	*stderr = *stderr_file;

	
	ios::sync_with_stdio();
};


AppWindow::AppWindow()	:	
	#ifdef	_DEBUG
		_scene_manager(AppWindow::_window_width_debug,AppWindow::_window_height_debug) , 
	#else
		_scene_manager(AppWindow::_window_width_debug,AppWindow::_window_height_debug) , 
	#endif
	_fullscreen(false)
{	
	#ifdef	_DEBUG
		this->SetSize(AppWindow::_window_width_debug,AppWindow::_window_height_debug);
		this->SetPosition(AppWindow::_window_x_offset_debug,AppWindow::_window_y_offset_debug);
	#else
		this->SetSize(AppWindow::_window_width,AppWindow::_window_height);
		this->SetPosition(AppWindow::_window_x_offset,AppWindow::_window_y_offset);
	#endif

	this->SetDoubleBuffer(true);
	this->SetDepthBits(32);
	this->SetStencilBits(32);
};


void	AppWindow::OnCreate()
{
	#ifdef	_DEBUG
		AppWindow::_redirect_io();
	#endif

	try
	{
		GLWindowEx::OnCreate();

		if ( !this->HasExtension("GL_ARB_vertex_buffer_object") )
			throw(exception("Vertex Buffer not supported!"));

		this->_scene_manager.setup();
	}
	catch ( exception& e )
	{
		string	output = e.what();
		
		
		
		output += "\nThe application will now terminate!\n";
		cerr << output << endl;
		MessageBoxA(0,output.c_str(),"Setup error!",MB_OK);
		PostQuitMessage(1);
	}
};

void	AppWindow::OnDestroy()					{ this->_scene_manager.clean_up(); };
void	AppWindow::OnResize( int w, int h )		{ this->_scene_manager.resize(w,h); };
void	AppWindow::OnMouseMove( int x , int y)	{ this->_scene_manager.mouse_position(x,y); };

void	AppWindow::OnMouseButton( MouseButton button , bool down )
{
	if ( MBLeft == button )
	{
		if ( down )
			this->_scene_manager.left_button_down();
		else
			this->_scene_manager.left_button_up();
	}
	else if ( MBMiddle == button )
	{
		if ( down )
			this->_scene_manager.middle_button_down();
		else
			this->_scene_manager.middle_button_up();
	}
	else
	{
		if ( down )
			this->_scene_manager.right_button_down();
		else
			this->_scene_manager.right_button_up();
	}
};

void	AppWindow::OnKeyboard( int key , bool down )
{
	if ( down )
	{
		this->_scene_manager.key_down(key);
	
		if ( key == VK_ESCAPE  &&  !this->_fullscreen )
			this->Close();
		else if ( key == VK_F11  ||  ( key == VK_ESCAPE  &&  this->_fullscreen ) )
		{
			this->_fullscreen = !this->_fullscreen;
			SetFullscreen(this->_fullscreen);
		}
	}
	else
		this->_scene_manager.key_up(key);
};

void	AppWindow::OnDisplay()					{ this->_scene_manager.update_time(App::GetTime());	this->_scene_manager.draw(); this->SwapBuffers(); };
void	AppWindow::OnIdle()						{ this->Redraw(); };


