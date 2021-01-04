#Use an official Python runtime as a parent image
FROM danoan/graphflow:dgtal

# Set the working directory to /app
WORKDIR /app

# Copy the current directory contents into the container at /app
COPY . /app

RUN chmod +x /app/scripts/*

#Install lcov

RUN apt-get install -y lcov

RUN /app/scripts/build-graph-flow.sh