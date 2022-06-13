"#version 400\n"
"layout (location = 0) in vec3 inPos;"
""
"uniform mat4 u_projectionMatrix;"
"uniform mat4 u_viewMatrix;"
"uniform mat4 u_modelMatrix;"
""
"void main() {"
"   vec4 pos = vec4( inPos, 1.0 );"
"   vec4 modelPos = u_modelMatrix * pos;\n"
"   vec4 viewPos  = u_viewMatrix * modelPos;"
"   vec4 finalPos = u_projectionMatrix * viewPos;"
"   gl_Position = finalPos;"
"}";