if(WIN32)
	set(FLANN_DIR "C:/Program Files/flann")
else(WIN32)
	set(FLANN_DIR "TODO")
endif(WIN32)


find_library(FLANN_LIBRARY_RELEASE
	NAMES
		flann
	PATHS
		${FLANN_DIR}/lib
)

find_library(FLANN_LIBRARY_DEBUG
	NAMES
		flann-gd
	PATHS
		${FLANN_DIR}/lib
)

find_path(FLANN_INCLUDE_DIR
	NAMES
		flann/flann.h
	PATHS
		${FLANN_DIR}/include
		/usr/local/include
		/opt/local/include
)

set(FLANN_LIBRARIES_RELEASE ${FLANN_LIBRARY_RELEASE})
set(FLANN_LIBRARIES_DEBUG ${FLANN_LIBRARY_DEBUG})

set(FLANN_INCLUDE_DIRS ${FLANN_INCLUDE_DIR})
