set(SDL_DIR "C:/local/SDL/SDL2_ttf-2.0.14/")

find_path(SDL_ttf_INCLUDE_DIRS
	NAMES
		SDL_ttf.h
	PATHS
		"${SDL_DIR}/include"
		/opt/local/include/SDL2
		/usr/local/include/SDL2
)

find_library(SDL_ttf_LIBRARIES
	NAMES
		SDL2_ttf
	PATHS
		"${SDL_DIR}/lib/x64"
		/Library/Frameworks
)

message("SDL2 Library: ${SDL_LIBRARIES}")

