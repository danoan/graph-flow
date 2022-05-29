FROM danoan/graphflow:env

# Set the working directory to /graph-flow
WORKDIR /graph-flow

# Copy the current directory contents into the container at /graph-flow
COPY . /graph-flow

ENV SCRIPT_DIR="/graph-flow/scripts"
ENV SRC_DIR="/graph-flow"
ENV BUILD_DIR="/graph-flow/build"
ENV DEPS_DIR="/graph-flow/deps"
ENV TEMP_DIR="/graph-flow/temp"

ENV PATH="/graph-flow/deps/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"
ENV CPATH="/graph-flow/deps/include:"
ENV CMAKE_PREFIX_PATH="/graph-flow/deps:"
ENV LD_LIBRARY_PATH="/graph-flow/deps/lib:"

RUN chmod +x /graph-flow/scripts/*

RUN bash $SCRIPT_DIR/init.sh

RUN bash $SCRIPT_DIR/install-eigen.sh
RUN bash $SCRIPT_DIR/install-opencv.sh
RUN bash $SCRIPT_DIR/install-boost.sh
