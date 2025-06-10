project(EngineSandbox)

set(SANDBOX_SOURCES
    "main.cpp"
    "SandboxApp.cpp"
    "SandboxApp.hpp"
)

add_executable(EngineSandbox ${SANDBOX_SOURCES})


if(WIN32)

    target_compile_definitions(EngineSandbox PRIVATE 
        UTENGINE_API=__declspec\(dllimport\) 
        REFLECTION_API=__declspec\(dllimport\)
    )

else()
    target_compile_definitions(EngineSandbox PRIVATE 
        UTENGINE_API=
        REFLECTION_API=
    )
endif()

target_include_directories(EngineSandbox PRIVATE
    ${UTENGINE_ROOT_DIR}/Engine/
)

target_link_libraries(EngineSandbox PRIVATE
    UTEngine
)