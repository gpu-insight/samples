project(
    'Botson Samples',
    ['c', 'cpp'],
    version : '0.1.0',
    default_options : ['c_std=c99', 'cpp_std=c++11']
)

cc = meson.get_compiler('c')
cpp = meson.get_compiler('cpp')

add_project_arguments('-DGL_GLEXT_PROTOTYPES', language : ['c', 'cpp'])

# General dependencies
gl_dep = dependency('GL', required : true)
sdk_dep = dependency('botson_sdk', required : false)

# Specific dependencies
glut_dep = cc.find_library('glut', required : false)
if glut_dep.found()
    subdir('samples/glut')
endif

egl_dep = dependency('egl', required : false)
if egl_dep.found()
    subdir('samples/egl')
endif

