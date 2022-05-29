FROM danoan/graphflow:dgtal1.1

# Set the working directory to /graph-flow
WORKDIR /graph-flow

# Copy the current directory contents into the container at /graph-flow
COPY . /graph-flow

RUN chmod +x /graph-flow/scripts/*

#Install lcov
RUN apt-get update && apt-get install -y lcov curl --fix-missing

#Build and Install graph-flow
RUN /graph-flow/build-tools/scripts/build-graph-flow.sh
