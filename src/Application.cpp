#include "../include/Application.h"
#include "../include/ApplicationState.h"
#include "../include/ApplicationStateManager.h"
#include "../include/Texture.h"

int currentSprite = 0;
SDL_Window *gWindow;
SDL_Renderer *gRenderer;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 640;
int BUTTON_WIDTH = 0;
int BUTTON_HEIGHT = 0;
int GAMEMODE = 0;

vector<SDL_Rect> spriteClips;
Texture spriteSheetTexture;

//Constructor de la clase
Application::Application(){
    gWindow=NULL;
    gRenderer=NULL;
    // Checks if init was able to excute //
    if(!init()){
        cout<<"Could not load application!"<<endl;
    }
    applicationStateManager = new ApplicationStateManager;
}

Application::~Application(){
    delete applicationStateManager;
    applicationStateManager = NULL;

    SDL_DestroyWindow(gWindow);
    gWindow=NULL;

    SDL_DestroyRenderer(gRenderer);
    gRenderer=NULL;
}

//Método que ejecuta el proceso en ejecución tras la carga del núcleo y el que a su vez genera todos los demás procesos
bool Application::init(){
    bool initSuccessful = true;

    if(SDL_Init(SDL_INIT_VIDEO)>0)
    {
        cout<<"Failed init. SDL_ERROR: %s\n"<<SDL_GetError();
        initSuccessful = false;
    }
    else
    {
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
        {
            cout<<"Warning: Linear texture filtering not enabled!"<<endl;
        }

        gWindow=SDL_CreateWindow("Checkers",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);

        if(gWindow==NULL)
        {
            cout<<"Couldnt make window. SDL_Error: %s\n"<<SDL_GetError()<<endl;
            initSuccessful = false;
        }
        else
        {
            gRenderer=SDL_CreateRenderer(gWindow,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
            if(gRenderer==NULL)
            {
                cout<<"Renderer failed. SDL_Error: %s\n"<<SDL_GetError()<<endl;
                initSuccessful = false;
            }
            else
            {
                SDL_SetRenderDrawColor(gRenderer,0xFF,0xFF,0xFF,0xFF);

                // Init for img loading
                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) )
                {
                    cout<<"Image failed. SDl_image Error: %s\n"<<IMG_GetError()<<endl;
                    initSuccessful = false;
                }
            }
        }
    }
    return initSuccessful;
}

//Método que inicia la aplicación
int Application::startApplication(){

    while (!applicationStateManager->stateExit()) {
        applicationStateManager->stateEvent();
        applicationStateManager->stateRender();
        if (applicationStateManager->stateUpdate() != applicationStateManager->getCurrentStateEnum()) {
            applicationStateManager->setCurrentStateEnum(applicationStateManager->stateUpdate());
            applicationStateManager->changeStates();
        }
        SDL_RenderPresent(gRenderer);
        if (applicationStateManager->getCurrentStateEnum() == MENU_STATE) {
            SDL_Delay(30);
        }
        else {
            SDL_Delay(100);
        }
    }

    closeApplication();

    return (EXIT_SUCCESS);

}

//Método que cierra la aplicación
void Application::closeApplication(){
    IMG_Quit();
    SDL_Quit();
}