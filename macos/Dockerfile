FROM ubuntu:latest
ENV DISPLAY=host.docker.internal:0
RUN useradd user
RUN apt -y update && apt -y install\
    locales\
    make\
    gcc\
    vim\
    iproute2\
    libgtk-4-dev\
    pkg-config
RUN locale-gen ru_RU.UTF-8
ENV LANG=ru_RU.UTF-8
ENV LANGUAGE=ru_RU:ru
ENV LC_LANG=ru_RU.UTF-8
ENV LC_ALL=ru_RU.UTF-8
USER user
WORKDIR /home/user
CMD ["bash"]
