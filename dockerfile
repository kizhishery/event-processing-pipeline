# ---- Stage 1: Build ----
FROM alpine:edge AS builder

# Install build tools and dependencies
RUN apk add --no-cache \
    build-base \
    cmake \
    zlib-dev \
    curl-dev

# Set working directory
WORKDIR /app

# Copy all source files
COPY . .

# Create build directory
RUN mkdir build
WORKDIR /app/build

# Configure CMake and build the project
RUN cmake .. -DCMAKE_BUILD_TYPE=Release \
    && cmake --build . -- -j$(nproc)

# ---- Stage 2: Runtime ----
FROM alpine:edge AS runtime

# Install only runtime dependencies
RUN apk add --no-cache \
    zlib \
    curl

# Set working directory
WORKDIR /app

# Copy the executable from the builder stage
COPY --from=builder /app/build/main .

# Make executable entrypoint
ENTRYPOINT ["./main"]
