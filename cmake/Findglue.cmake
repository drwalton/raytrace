if(WIN32)
set(glue_DIR "C:/local/SDL/SDL2-2.0.4/")
else(WIN32)
set(glue_DIR ~/glue)
endif(WIN32)

find_path(glue_INCLUDE_DIRS
	NAMES
		glue/VectorTypes.hpp
	PATHS
		"${glue_DIR}/include"
)

find_library(glue_LIBRARIES_RELEASE
	NAMES
		glue
	PATHS
		"${glue_DIR}/lib/x64"
		"${glue_DIR}/lib/Release"
)

find_library(glue_LIBRARIES_DEBUG
	NAMES
		glue
	PATHS
		"${glue_DIR}/lib/x64"
		"${glue_DIR}/lib/Debug"
)

message("glue Library: ${glue_LIBRARIES_RELEASE}")
message("       Debug: ${glue_LIBRARIES_DEBUG}")
message("     Include: ${glue_INCLUDE_DIRS}")

set(GLUE_LIBRARIES_RELEASE ${glue_LIBRARIES_RELEASE})
set(GLUE_LIBRARY_RELEASE ${glue_LIBRARIES_RELEASE})
set(glue_LIBRARY_RELEASE ${glue_LIBRARIES_RELEASE})
set(GLUE_LIBRARIES_DEBUG ${glue_LIBRARIES_DEBUG})
set(GLUE_LIBRARY_DEBUG ${glue_LIBRARIES_DEBUG})
set(glue_LIBRARY_DEBUG ${glue_LIBRARIES_DEBUG})
set(GLUE_INCLUDE_DIRS ${glue_INCLUDE_DIRS})
set(GLUE_INCLUDE_DIR ${glue_INCLUDE_DIRS})
set(glue_INCLUDE_DIR ${glue_INCLUDE_DIRS})
