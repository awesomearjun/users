if (NOT ASIO_INCLUDE_DIR)
	if(DEFINED asio_SOURCE_DIR)
		set(ASIO_INCLUDE_DIR "${asio_SOURCE_DIR}/asio/include")
		message("Could find asio header")
	else()
		message(FATAL_ERROR "Couldn't locate asio header files.")
	endif()
endif()

set(ASIO_FOUND TRUE)

if(NOT TARGET asio::asio)
	add_library(asio::asio INTERFACE IMPORTED)
	set_target_properties(asio::asio PROPERTIES
		INTERFACE_INCLUDE_DIRECTORIES "${ASIO_INCLUDE_DIR}"
	)
endif()
