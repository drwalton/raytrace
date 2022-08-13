set(ASSIMP_DIR "C:/Program Files/Assimp/")

find_path(ASSIMP_INCLUDE_DIRS
	NAMES
		assimp/Importer.hpp
	PATHS
		"${ASSIMP_DIR}/include"
)

find_library(ASSIMP_LIBRARIES
	NAMES
		assimp
	PATHS
	"${ASSIMP_DIR}/lib/x64"
)

message("Found ASSIMP: LIB: ${ASSIMP_LIBRARIES} INCLUDE: ${ASSIMP_INCLUDE_DIRS}")

