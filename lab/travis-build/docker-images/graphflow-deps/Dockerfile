#Use an official Python runtime as a parent image
FROM danoan/graphflow:env

# Set the working directory to /app
WORKDIR /app

# Copy the current directory contents into the container at /app
COPY . /app

ENV SCRIPT_DIR="/app/scripts"
ENV SRC_DIR="/app"
ENV BUILD_DIR="/app/build"
ENV DEPS_DIR="/app/deps"
ENV TEMP_DIR="/app/temp"

ENV PATH="/app/deps/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"
ENV CPATH="/app/deps/include:"
ENV CMAKE_PREFIX_PATH="/app/deps:"
ENV LD_LIBRARY_PATH="/app/deps/lib:"

RUN chmod +x /app/scripts/*

RUN bash $SCRIPT_DIR/init.sh

RUN bash $SCRIPT_DIR/install-eigen.sh
RUN bash $SCRIPT_DIR/install-opencv.sh
RUN bash $SCRIPT_DIR/install-boost.sh
