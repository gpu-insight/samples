project(
    'Botson Samples',
    ['c', 'cpp'],
    version : '0.1.0',
    default_options : ['c_std=c99', 'cpp_std=c++11']
)

cc = meson.get_compiler('c')
cpp = meson.get_compiler('cpp')

add_project_arguments('-DGL_GLEXT_PROTOTYPES', language : ['c', 'cpp'])
incdir = include_directories('.')

conf = configuration_data()
conf.set_quoted('SAMPLES_DATA_PATH', join_paths(get_option('prefix'), get_option('datadir'), 'sietium'))
configure_file(
    output : 'config.h',
    configuration : conf
)

subdir('data')

# General dependencies
gl_dep = dependency('GL', required : true)
sdk_dep = dependency('botson_sdk', required : true)

# Specific dependencies
glut_dep = dependency('glut', required : false)
if glut_dep.found()
    subdir('samples/glut')
endif

egl_dep = dependency('egl', required : false)
if egl_dep.found()
    subdir('samples/egl')
endif

x11_dep = dependency('X11', required : false)
if x11_dep.found()
    subdir('samples/glx')
endif

