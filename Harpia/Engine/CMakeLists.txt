#
# Created by Ricardo Bustamante <ricardo@busta.dev> on 29/05/2022.
#

project(Harpia.Engine)

file(GLOB Harpia.Engine_SRC CONFIGURE_DEPENDS "*.cpp" "*.h")
add_library(${PROJECT_NAME} STATIC ${Harpia.Engine_SRC})