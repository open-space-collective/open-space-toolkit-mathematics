################################################################################################################################################################

# @project        Library/Mathematics
# @file           tools/development/docker/Dockerfile
# @author         Lucas Brémond <lucas@loftorbital.com>
# @license        TBD

################################################################################################################################################################

FROM openspacecollective/library-core:0.1.2

LABEL maintainer="lucas@loftorbital.com"

# Arguments

ARG version
ARG cpu_count=1

# Dependencies

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

## Library :: Core [master]

RUN pushd /tmp > /dev/null \
    && git clone https://github.com/open-space-collective/library-core.git \
    && cd library-core \
    && mkdir build \
    && cd build \
    && cmake -DBUILD_UNIT_TESTS=OFF .. \
    && make -j ${cpu_count} \
    && make install \
    && rm -rf /tmp/library-core \
    && popd > /dev/null

## NumPy

RUN pip install --upgrade pip \
    && pip install numpy

# Labels

ENV version ${version}

LABEL version="${version}"

# Execution

CMD ["/bin/bash"]

################################################################################################################################################################