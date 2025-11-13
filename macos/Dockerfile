FROM ubuntu:latest
RUN useradd user
RUN apt -y update && apt -y install\
    make\
    gcc\
    nano\
    iproute2\
    libgtk-4-dev\
    pkg-config\
    xterm
USER user
WORKDIR /home/user
CMD ["bash"]