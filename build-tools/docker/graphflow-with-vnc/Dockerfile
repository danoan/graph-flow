FROM danoan/graphflow:v0.2.8.1

# Set the working directory to /graph-flow
WORKDIR /graph-flow

#Install vnc

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y xfce4 \
xfce4-goodies \
tightvncserver \
--fix-missing

COPY ./scripts/start-vnc.sh /graph-flow/scripts/start-vnc.sh