#include "Sprite.h"
#include <SDL2/SDL_image.h>


Sprite::Sprite(){

}

Sprite::Sprite(std::string path, SDL_Renderer* _renderer, Vec2 _position){
	texture = 0;
	renderer = _renderer;
	width = 0;
	height = 0;
	position.x = _position.x;
	position.y = _position.y;
	scale = 1.0f;
	angle = 0.0f;
	if(!loadTexture(path)){
		printf("Texture could not be created.\n");
	}
}

Sprite::Sprite(const Sprite &copy){
	//texture = copy.texture;
}

Sprite::~Sprite(){
	free();
	printf("Sprite Destructor called\n");
}

void Sprite::free(){
	if(texture != 0){
		SDL_DestroyTexture(texture);
	}
}

bool Sprite::loadTexture(std::string path){
	free();

	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if(loadedSurface == NULL ){
		printf("Unable to load image: %s. SDL_Image error: %s\n. ", path.c_str(), IMG_GetError());
	}else{
		//Color key image
		//SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) ); //SDL_MapRGB(format,R,G,B)
		texture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
		if(texture == NULL){
			printf("Unable to create texture from: %s. SDL_Error: %s.\n", path.c_str(), SDL_GetError());
		}else{
			width = loadedSurface->w;
			height = loadedSurface->h;
		}
		SDL_FreeSurface( loadedSurface );
	}

	return texture != NULL;
}

void Sprite::draw(){
	SDL_RenderCopyEx(renderer, texture, NULL, &destination, angle, NULL, flip);
	//SDL_RenderCopy(renderer, texture, NULL, &destination);
}

void Sprite::changeAlpha(int alpha){
	SDL_SetTextureAlphaMod(texture, alpha);
}

void Sprite::update(){
	destination.w = width;
	destination.h = height;
	if(scale != 1.0f){
		destination.w *= scale;
		destination.y *= scale;
	}
	destination.x = position.x;
	destination.y = position.y;
}