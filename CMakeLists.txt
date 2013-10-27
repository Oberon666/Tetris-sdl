project(XO_SDL)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(. SRC_LIST)

# REQUIRED does not work in CMake <=2.4.6 for SDL
Find_Package ( SDL REQUIRED )
Find_Package ( SDL_image REQUIRED ) # if using SDL_image
Find_Package ( SDL_mixer REQUIRED )
Find_Package ( SDL_ttf REQUIRED )

# Workaround for the non-working REQUIRED flag
if ( NOT SDL_FOUND )
   message ( FATAL_ERROR "SDL not found!" )
endif ( NOT SDL_FOUND )

link_libraries (
   ${SDL_LIBRARY}
   ${SDLIMAGE_LIBRARY} # if using SDL_image, obviously
   ${SDLMIXER_LIBRARY}
   ${SDLTTF_LIBRARY}
   SDLmain # Sadly not included in SDL_LIBRARY variable
)
add_executable(${PROJECT_NAME} ${SRC_LIST})

