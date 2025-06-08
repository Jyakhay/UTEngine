project(UTEngine)

set(UTENGINE_SOURCES_CORE
    "Core/DependencyManager.cpp"
    "Core/DependencyManager.hpp"
    "Core/EngineDependency.cpp"
    "Core/EngineDependency.hpp"
)

set(UTENGINE_SOURCES_DEBUG
    "Debug/DebugLog.cpp"
    "Debug/DebugLog.hpp"
    "Debug/Assert.hpp"
)

set(UTENGINE_SOURCES_DEPENDENCIES
    "Dependencies/GLFWDependency.cpp"
    "Dependencies/GLFWDependency.hpp"
)

set(UTENGINE_SOURCES_MATH
    "Math/TimeSpan.hpp"
)

set(UTENGINE_SOURCES_PLATFORM
    "Platform/Executable.cpp"
    "Platform/Executable.hpp"
    "Platform/FileSystem.cpp"
    "Platform/FileSystem.hpp"
)

set(UTENGINE_SOURCES
    "Engine.cpp"
    "Engine.hpp"
    ${UTENGINE_SOURCES_CORE}
    ${UTENGINE_SOURCES_DEBUG}
    ${UTENGINE_SOURCES_DEPENDENCIES}
    ${UTENGINE_SOURCES_MATH}
    ${UTENGINE_SOURCES_PLATFORM}
)

add_library(UTEngine SHARED ${UTENGINE_SOURCES})

if(WIN32)

    target_compile_definitions(UTEngine PRIVATE 

        UTENGINE_API=__declspec\(dllexport\) 
        REFLECTION_API=__declspec\(dllexport\)

    )

else()

    target_compile_definitions(UTEngine PRIVATE 

        UTENGINE_API=
        REFLECTION_API=

    )

endif()

target_include_directories(UTEngine PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(UTEngine PRIVATE
    glfw
    glad
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${UTENGINE_SOURCES})