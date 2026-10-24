
cmake_minimum_required(VERSION 3.20)

project(MoveOn LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT WIN32)
    message(FATAL_ERROR
        "Cette configuration supporte Windows x64 uniquement.")
endif()

set(OPENGL_DIR "${CMAKE_SOURCE_DIR}/OpenGL")

# Tous les fichiers sources de MoveOn
file(GLOB SOURCES CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
)

add_executable(MoveOn ${SOURCES})

# Conserver les chemins #include actuels
target_include_directories(MoveOn PRIVATE
    "${CMAKE_SOURCE_DIR}"
    "${CMAKE_SOURCE_DIR}/include"
)

# Bibliothèques locales
if(MINGW)
    set(GLFW_LIB
        "${OPENGL_DIR}/lib/mingw/libglfw3dll.a")
    set(GLEW_LIB
        "${OPENGL_DIR}/lib/mingw/glew32.lib")
elseif(MSVC)
    set(GLFW_LIB
        "${OPENGL_DIR}/lib/msvc/glfw3dll.lib")
    set(GLEW_LIB
        "${OPENGL_DIR}/lib/msvc/glew32.lib")
else()
    message(FATAL_ERROR
        "Compilateur non configure pour les bibliotheques locales.")
endif()

foreach(LIB IN ITEMS "${GLFW_LIB}" "${GLEW_LIB}")
    if(NOT EXISTS "${LIB}")
        message(FATAL_ERROR "Bibliotheque absente : ${LIB}")
    endif()
endforeach()

target_link_libraries(MoveOn PRIVATE
    "${GLFW_LIB}"
    "${GLEW_LIB}"
    opengl32
    gdi32
)

# Copier les DLL locales après compilation
foreach(DLL IN ITEMS glew32.dll glfw3.dll)
    if(NOT EXISTS "${OPENGL_DIR}/bin/${DLL}")
        message(FATAL_ERROR "DLL absente : ${DLL}")
    endif()

    add_custom_command(TARGET MoveOn POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${OPENGL_DIR}/bin/${DLL}"
            "$<TARGET_FILE_DIR:MoveOn>"
        VERBATIM
    )
endforeach()

# Copier les shaders pour conserver les chemins relatifs
if(EXISTS "${CMAKE_SOURCE_DIR}/shaders")
    add_custom_command(TARGET MoveOn POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_SOURCE_DIR}/shaders"
            "$<TARGET_FILE_DIR:MoveOn>/shaders"
        VERBATIM
    )
endif()
