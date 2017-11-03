cmake_minimum_required(VERSION 3.8)

project(QuickHull)

find_package(GLUT)
find_package(OpenGL)

include_directories(
${OPENGL_INCLUDE_DIR}
   ${GLUT_INCLUDE_DIR}
	)

add_executable(qhull main.cc qhull.h)
target_link_libraries(qhull ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})
set_property(TARGET qhull PROPERTY CXX_STANDARD 11)