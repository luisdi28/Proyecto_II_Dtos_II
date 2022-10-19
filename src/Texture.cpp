#include "../include/Texture.h"

Texture::Texture(){
    currentTexture = NULL;
    width = 0;
    height = 0;
}

//Constructor de la clase
Texture::~Texture(){
    free();
}

//Método que carga los datos del archivo
bool Texture::loadFromFile(std::string path){

    // Frees current texture //
    free();

    SDL_Texture *newTexture;
    // Load image from path //
    SDL_Surface *loadedSurface = IMG_Load(path.c_str());

    if(loadedSurface == NULL){
        printf("Unable to load img from %s! SDL Error: %s\n",path.c_str(),IMG_GetError());
    }
    else{
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if (newTexture == NULL) {
            printf("Unable to create texture from %s! SDL Error: %s\n",path.c_str(), SDL_GetError());
        }
        else{
            // Gets image dimensions //
            width = loadedSurface->w;
            height = loadedSurface->h;
        }
        SDL_FreeSurface(loadedSurface);
    }
        currentTexture = newTexture;
        return currentTexture != NULL;
}

//Método que renderiza los elementos
void Texture::render(int x, int y, SDL_Rect *clip){

    // Sets place to render on screen //
    SDL_Rect renderSpace = {x, y, width, height};

    // Sets rendering space dimensions from clip dimensions //
    if(clip != NULL){
        renderSpace.w = clip->w;
        renderSpace.h = clip->h;
    }

    // Render to screen //
    SDL_RenderCopy(gRenderer, currentTexture, clip, &renderSpace);
}

//Método que --
void Texture::free(){
    if(currentTexture!=NULL){
        SDL_DestroyTexture(currentTexture);
        currentTexture = NULL;
        width = 0;
        height = 0;
    }
}

//Método que obtiene el ancho
int Texture::getWidth(){
    return width;
}

//Método que obtiene la altura
int Texture::getHeight(){
    return height;
}
