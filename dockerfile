# =======================
# Builder Stage
# =======================
FROM alpine:edge AS builder

# Install build tools and dependencies
RUN apk add --no-cache \
    build-base \
    cmake \
    git \
    zlib-dev \
    curl-dev \
    bash

# -----------------------
# Build AWS Lambda C++ Runtime
# -----------------------
WORKDIR /opt

RUN git clone https://github.com/awslabs/aws-lambda-cpp.git

WORKDIR /opt/aws-lambda-cpp/build

RUN cmake .. \
      -DCMAKE_BUILD_TYPE=Release \
      -DBUILD_SHARED_LIBS=OFF \
    && make -j$(nproc) \
    && make install

# -----------------------
# Build Application
# -----------------------
WORKDIR /app
COPY . .

RUN mkdir -p build
WORKDIR /app/build

RUN cmake .. \
      -DCMAKE_BUILD_TYPE=Release \
    && cmake --build . --target main -- -j$(nproc)

# =======================
# Runtime Stage
# =======================
FROM alpine:edge

# Minimal runtime dependencies
RUN apk add --no-cache \
    libstdc++ \
    libgcc \
    zlib \
    curl

WORKDIR /app

# Copy compiled Lambda binary
COPY --from=builder /app/build/main /app/main
RUN chmod +x /app/main

# Lambda ENTRYPOINT
ENTRYPOINT ["/app/main"]
