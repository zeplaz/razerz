
//engine_MCP.cpp

#include "engine_MCP.hpp"
 const constexpr double DELTA_TIME_STEP = 1.0f / 60.0f; // 60hz

void Engine::configure(int argc, char* argv[])
{
  
  std::cout << "##->> ENGINE CONFIGURING:";
  std::cout << "num of lineargs::"<< argc <<'\n';
  for(int i =0; i<argc; i++)
  {
    std::cout << argv[i]<< '\n';
    std::string comd = argv[i];  
    if(comd== "w_num")
    {
       comd = argv[i+1];  
      std::cout << "command entierd::" << comd <<'\n'; 
     renderer.number_of_windows =  std::stoi(comd);
    }
    if(comd == "r_api")
    {
      comd = argv[i+1]; 
      if(comd == "vulkan")
      {
        renderer.set_render_api(RENDER_API::VULKAN);     
      }

        if(comd == "opengl")
      {
        renderer.set_render_api(RENDER_API::OPENGL);     
      }
    }
  }
  if(argc ==1)
  {
    std::cout << "setting defult\n";
    renderer.number_of_windows = 1; 
   renderer.set_render_api(RENDER_API::DEBUG_OPENGL);
  }
engine_status = Engine_State::CONFIGURED;
}



void Engine::ignition()
{
  std::cout << "engine is inialzing. sdl.. et all\n";
    
     if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
      {
        std::cerr << "Error: " << SDL_GetError() << '\n';
        engine_status = Engine_State::FAILURE;
        return;
      }
    renderer.setup();
    engine_status = Engine_State::IGNITION;
 }



void Engine::shutdown()
{
  std::cout << "engineshutdown; SHUTDOWN TYPE::" << (int)engine_status <<'\n';
    if(syms_array.at(SYM_SDL))
    {
      SDL_Quit();
    }
}

Windows_sdl::Windows_sdl()
{
  {
    //Initialize non-existant window
    mWindow = NULL;
    
    mMouseFocus = false;
    mKeyboardFocus = false;
    mFullScreen = false;
    mMinimized = false;
    mShown = false;
   	mwindowID = -1;
  	mwindow_displayID = -1;
    mWidth = 0;
    mHeight = 0;
}
}
bool Windows_sdl::init()
{
  bool success = true;
  mWindow = SDL_CreateWindow( "MAIN", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH_DEFULT, SCREEN_HEIGHT_DEFULT, SDL_WINDOW_OPENGL| SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE );
  
  if( mWindow == NULL )
	{
    std::cerr << "widnow context could not be created! SDL Error:" << SDL_GetError() << '\n';
  	success = false;
	}
  else 
  {
		mMouseFocus = true;
		mKeyboardFocus = true;
		mWidth = SCREEN_WIDTH_DEFULT;
		mHeight = SCREEN_HEIGHT_DEFULT;

    gContext = SDL_GL_CreateContext( mWindow );

    if( gContext == NULL )
			{
			std::cerr << "OpenGL context could not be created! SDL Error:" << SDL_GetError() << '\n';
			success = false;
      }
      else
      {
            gl_configure();
			mwindowID = SDL_GetWindowID( mWindow );
			mwindow_displayID = SDL_GetWindowDisplayIndex( mWindow );

			//Flag as opened
			mShown = true;
  }}
  	return success;
}



void Windows_sdl::handle_event(SDL_Event& e)
{
 if( e.type == SDL_WINDOWEVENT && e.window.windowID == mwindowID )
	{
		switch( e.window.event )
		{
			//Window moved
			case SDL_WINDOWEVENT_MOVED:
			mwindow_displayID = SDL_GetWindowDisplayIndex( mWindow );
		
			break;

			//Window appeared
			case SDL_WINDOWEVENT_SHOWN:
			mShown = true;
			break;

			//Window disappeared
			case SDL_WINDOWEVENT_HIDDEN:
			mShown = false;
			break;

			//Get new dimensions and repaint
			case SDL_WINDOWEVENT_SIZE_CHANGED:
			mWidth = e.window.data1;
			mHeight = e.window.data2;
            resizeWindow(mWidth,mHeight);
		///	SDL_RenderPresent( mRenderer );
      //  Renderer.
			break;

			//Repaint on expose
			case SDL_WINDOWEVENT_EXPOSED:
		//	SDL_RenderPresent( mRenderer );

			break;

			//Mouse enter
			case SDL_WINDOWEVENT_ENTER:
			mMouseFocus = true;
		
			break;
			
			//Mouse exit
			case SDL_WINDOWEVENT_LEAVE:
			mMouseFocus = false;
		
			break;

			//Keyboard focus gained
			case SDL_WINDOWEVENT_FOCUS_GAINED:
			mKeyboardFocus = true;
	
			break;
			
			//Keyboard focus lost
			case SDL_WINDOWEVENT_FOCUS_LOST:
			mKeyboardFocus = false;
	
			break;

			//Window minimized
			case SDL_WINDOWEVENT_MINIMIZED:
            mMinimized = true;
            break;

			//Window maxized
			case SDL_WINDOWEVENT_MAXIMIZED:
			mMinimized = false;
            break;
			
			//Window restored
			case SDL_WINDOWEVENT_RESTORED:
			mMinimized = false;
            break;

			//Hide on close
			case SDL_WINDOWEVENT_CLOSE:
			SDL_HideWindow( mWindow );
			break;
		}
	}
}