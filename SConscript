from building import *
Import('rtconfig')

src   = []
cwd   = GetCurrentDir()

src += Glob('sensor_st_sths34pf80.c.c')
src += Glob('libraries/sths34pf80_reg.c')
src += Glob('libraries/sths34pf80.c')

# add sths34pf80 include path.
path  = [cwd, cwd + '/libraries']

# add src and include to group.
group = DefineGroup('sths34pf80', src, depend = ['PKG_USING_STHS34PF80'], CPPPATH = path)

Return('group')
