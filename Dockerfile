#Use an official Python runtime as a parent image
FROM danoan/graphflow:dgtal1.1

# Set the working directory to /app
WORKDIR /app

# Copy the current directory contents into the container at /app
COPY . /app

RUN chmod +x /app/scripts/*

#Install lcov

RUN apt-get update && apt-get install -y lcov curl --fix-missing

RUN /app/scripts/build-graph-flow.sh