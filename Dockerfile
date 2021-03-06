FROM akospasztor/docker-python:3.7-linux-1.0.1

# Suppress user dialogs (and selects the default answer) during apt-get install
ARG DEBIAN_FRONTEND=noninteractive

# Install required packages
RUN apt-get update && apt-get -y -q --no-install-recommends install \
  clang-format-11 \
  doxygen \
  cmake \
  make \
  ninja-build \
  wget \
  && rm -rf /var/lib/apt/lists/*

# Install GCC for ARM
ENV GCC_VERSION=10-2020-q4
ENV GCC_DIR=$HOME/gcc/$GCC_VERSION

RUN wget --progress=dot:mega -O /tmp/$GCC_VERSION.tar.bz2 \
  https://developer.arm.com/-/media/Files/downloads/gnu-rm/10-2020q4/gcc-arm-none-eabi-10-2020-q4-major-x86_64-linux.tar.bz2

RUN mkdir -p $GCC_DIR
RUN tar xjf /tmp/$GCC_VERSION.tar.bz2 -C $GCC_DIR --strip-components=1
RUN rm -f /tmp/$GCC_VERSION.tar.bz2

ENV GCC_PATH=$GCC_DIR/bin
ENV PATH=$GCC_PATH:$PATH

WORKDIR /usr/project

