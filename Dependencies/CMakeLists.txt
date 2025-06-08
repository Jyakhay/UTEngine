#glfw
set(GLFW_INSTALL Off)
add_subdirectory(glfw)
set_target_properties(glfw PROPERTIES FOLDER "Dependencies/GLFW")
set_target_properties(update_mappings PROPERTIES FOLDER "Dependencies/GLFW")

#glad
add_subdirectory(glad)
set_target_properties(glad PROPERTIES FOLDER "Dependencies")