# Use ARM-compatible Ubuntu base image
FROM ubuntu:22.04

# Avoid interaction during install
ENV DEBIAN_FRONTEND=noninteractive

# Install build tools
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    gdb \
    git \
    vim \
    curl \
    && apt-get clean

# Set working directory
WORKDIR /app

# Default shell
CMD ["/bin/bash"]
