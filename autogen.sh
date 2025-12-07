# Предполагается, что у вас уже установлены GNU Autotools. В случае, если они у вас не установлены,
# пожалуйста, установите ;->

autoreconf --install && echo "done." || echo "Error: GNU autotools is not installed. Please install them for your distribution or try using configure without this script. (Not recommended)" 
