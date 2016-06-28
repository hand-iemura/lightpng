import sys
env = Environment();
Export('env')
AddOption('--enable-debug',
          dest='enabledebug',
          action='store_true',
          default=False,
          help='Debug Build')
AddOption('--mingw32',
          dest='mingw32',
          action='store_true',
          default=False,
          help='Create Windows binary by using MinGW')
AddOption('--no-opensource',
          dest='opensource',
          action='store_false',
          default=True,
          help='Enable Texture Compression format support')

if sys.platform == 'win32':
    default_pvr_path = r'C:\Imagination\PowerVR\GraphicsSDK\PVRTexTool\Library'
elif sys.platform == 'darwin':
    default_pvr_path = r'/Applications/Imagination/PowerVR/GraphicsSDK/PVRTexTool/Library'
#AddOption('--PVRTexLib',
#          dest='pvrtexlib',
#          action='store',
#          metavar='DIR',
#          default=default_pvr_path,
#          help='Enable PVRTC Texture Compression convert/preview feature. Default is "./PVRTexLib".')
#AddOption('--AdrenoSDK',
#          dest='adrenosdk',
#          action='store',
#          metavar='DIR',
#          default='$HOME/.wine/drive_c/AdrenoSDK',
#          help='Enable ATITC Texture Compression convert/preview feature. Default is "~/.wine/drive_c/AdrenoSDK".')

sconscript = ['third_party/zlib', 'third_party/libpng', 'third_party/jpeg', 'third_party/libimagequant_build/', 'third_party/zopfli_build']
sources = ['src/PNGReader.cpp', 'src/JPEGReader.cpp', 'src/PNGWriter.cpp', 'src/MedianCut16bitQuantizer.cpp', 'src/MedianCut32bitQuantizer.cpp', 'src/PaletteOptimizer.cpp']
libs = ['png', 'z', 'jpeg', 'libimagequant', 'zopfli', 'pthread']
libpath = ['third_party/zlib/', 'third_party/libpng/', 'third_party/jpeg/', 'third_party/libimagequant_build/', 'third_party/zopfli_build/']
cpppath = [
    'boost_1_53_0/',
    'src/', 'third_party/zlib/', 'third_party/libpng/', 'third_party/jpeg/', 'third_party/libimagequant/lib/', 'third_party/zopfli/']
ccflags = []
linkflags = []

def fix_path(path):
    import os
    for key, value in os.environ.items():
        envkey = '$' + key
        if envkey in path:
            path = path.replace(envkey, value)
    return path

build_target = "linux"

if GetOption('enabledebug'):
    ccflags.append('-g')
    ccflags.append('-Wall')
else:
    ccflags.append('-O3')


ccflags.append('-m64')
linkflags.append('-m64')

sources.insert(0, 'src/lightpng.cpp')

env.SConscript(dirs=sconscript)
env.Program('lightpng', sources, LIBS=libs, LIBPATH=libpath, CPPPATH=cpppath, CCFLAGS=ccflags, LINKFLAGS=linkflags)
