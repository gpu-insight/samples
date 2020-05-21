import os

env = Environment(CCFLAGS=['-std=c++11', '-g'])

Export('env')

# get a list of subdirectories
sub_dirs = os.walk('.', topdown=False)
first = last = next(sub_dirs)
for last in sub_dirs:
    pass

# Do nothing unless a subdirectory contains a build script named SConscript
sub_scripts = [(os.path.join(d, 'SConscript'), d) for d in last[1] if os.path.exists(os.path.join(d, 'SConscript'))]

# Hierarchical build
for sub_script, dirname in sub_scripts:
    SConscript(sub_script, variant_dir=os.path.join('build', dirname), duplicate=0)
