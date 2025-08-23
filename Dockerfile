FROM ubuntu:22.04

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    libspdlog-dev \
    nlohmann-json3-dev

WORKDIR /app

COPY CMakeLists.txt .
COPY src/server src

RUN cmake -S . -B build -DCMAKE_BUILD_TYPE=Release && cmake --build build

ENTRYPOINT ["/app/build/server"]