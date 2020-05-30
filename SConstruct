import os

env = Environment(BINDIR='#bin',
                  LIBS=['SDK', 'EGL', 'GL'],
                  CCFLAGS=['-std=c++11', '-g', '-DGL_GLEXT_PROTOTYPES'])

env.Decider('MD5-timestamp')
Export('env')

# get a list of subdirectories
sub_dirs = os.walk('.', topdown=False)
first = last = next(sub_dirs)
for last in sub_dirs:
    pass

# Do nothing unless a subdirectory contains a build script named SConscript
scons_scripts = [os.path.join(d, 'SConscript') for d in last[1] if os.path.exists(os.path.join(d, 'SConscript'))]

# Hierarchical build
for s in scons_scripts:
    SConscript(s, variant_dir=os.path.join('build', os.path.dirname(s)), duplicate=0)
