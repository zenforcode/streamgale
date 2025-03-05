FROM mcr.microsoft.com/devcontainers/cpp:ubuntu

# Install required dependencies
RUN apt-get update && \
    apt-get install -y \
    libasio-dev \
    cmake \
    ninja-build \
    software-properties-common \
    make \
    libboost-all-dev \
    clang \
    clang-format \
    clang-tidy \
    zlib1g-dev \
    gdb \
    curl \
    zip \
    unzip \
    tar \
    git \
    && rm -rf /var/lib/apt/lists/*
    
RUN add-apt-repository ppa:deadsnakes/ppa -y && \
        apt-get update && \
        apt-get install -y python3.11 python3.11-venv python3.11-dev && \
        rm -rf /var/lib/apt/lists/*
    
RUN update-alternatives --install /usr/bin/python3 python3 /usr/bin/python3.11 1
RUN curl -sS https://bootstrap.pypa.io/get-pip.py | python3.11
# Install vcpkg
RUN git clone https://github.com/microsoft/vcpkg.git /opt/vcpkg && \
    cd /opt/vcpkg && \
    ./bootstrap-vcpkg.sh && \
    ln -s /opt/vcpkg/vcpkg /usr/local/bin/vcpkg
RUN chmod -R o+rwx /opt/vcpkg/


WORKDIR /workspace
