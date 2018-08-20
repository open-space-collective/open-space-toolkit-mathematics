################################################################################################################################################################

# @project        Library/Mathematics
# @file           tools/development/docker/Dockerfile
# @author         Lucas Brémond <lucas@loftorbital.com>
# @license        TBD

################################################################################################################################################################

FROM openspacecollective/library-core:0.1.6

LABEL maintainer="lucas@loftorbital.com"

# Arguments

ARG cpu_count=1

# Dependencies

## NumPy

RUN pip3 install numpy

## Eigen [3.3.4]

RUN mkdir /tmp/eigen \
    && cd /tmp/eigen \
    && wget --quiet http://bitbucket.org/eigen/eigen/get/3.3.4.tar.gz \
    && tar -xvf 3.3.4.tar.gz \
    && cd eigen-eigen-5a0156e40feb \
    && mkdir build \
    && cd build \
    && cmake .. \
    && make install \
    && rm -rf /tmp/eigen

## Library :: Core [0.1.8]

RUN mkdir -p /tmp/library-core \
    && pushd /tmp/library-core > /dev/null \
    && wget --quiet https://github.com/open-space-collective/library-core/releases/download/0.1.8/library-core-0.1.8-1.x86_64-runtime.rpm \
    && wget --quiet https://github.com/open-space-collective/library-core/releases/download/0.1.8/library-core-0.1.8-1.x86_64-devel.rpm \
    && wget --quiet https://github.com/open-space-collective/library-core/releases/download/0.1.8/library-core-0.1.8-1.x86_64-python.rpm \
    && dnf install -y ./*.rpm \
    && rm -rf /tmp/library-core \
    && popd > /dev/null

# Labels

ARG version

ENV version ${version}

LABEL version="${version}"

# Execution

CMD ["/bin/bash"]

################################################################################################################################################################