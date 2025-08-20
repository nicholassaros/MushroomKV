FROM alpine:latest

# Install all required build tools and spdlog
RUN apk add --no-cache \
    cmake \
    g++ \
    make \
    spdlog-dev \
    libstdc++ \
    musl-dev

WORKDIR /app

# Copy source code and CMake config
COPY CMakeLists.txt .
COPY src/server src

# Build project
RUN cmake -S . -B build -DCMAKE_BUILD_TYPE=Release && cmake --build build

# Change entrypoint to your binary
ENTRYPOINT ["/app/build/server"]
