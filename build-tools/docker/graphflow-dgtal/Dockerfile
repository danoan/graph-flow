FROM danoan/graphflow:deps

# Set the working directory to /graph-flow
WORKDIR /graph-flow

# Copy the current directory contents into the container at /graph-flow
COPY . /graph-flow

RUN chmod +x /graph-flow/scripts/*

RUN bash /graph-flow/scripts/install-dgtal.sh
RUN bash /graph-flow/scripts/install-lemon.sh
