#Use an official Python runtime as a parent image
FROM danoan/dipacus:lemon

# Set the working directory to /app
WORKDIR /app

# Copy the current directory contents into the container at /app
COPY . /app

RUN chmod +x /app/scripts/*
RUN /app/scripts/build-graph-flow.sh
