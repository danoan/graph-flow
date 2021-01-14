#Use an official Python runtime as a parent image
FROM danoan/graphflow:deps

# Set the working directory to /app
WORKDIR /app

# Copy the current directory contents into the container at /app
COPY . /app

RUN chmod +x /app/scripts/*

RUN bash /app/scripts/install-dgtal.sh
RUN bash /app/scripts/install-lemon.sh
