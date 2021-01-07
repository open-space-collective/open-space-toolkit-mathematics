################################################################################################################################################################

# @project        Open Space Toolkit ▸ Mathematics
# @file           docker/development/debian/Dockerfile
# @author         Lucas Brémond <lucas@loftorbital.com>
# @license        Apache License 2.0

################################################################################################################################################################

ARG BASE_IMAGE_VERSION=latest

FROM openspacecollective/open-space-toolkit-base:${BASE_IMAGE_VERSION}-debian

LABEL maintainer="lucas@loftorbital.com"

# Dependencies

## {fmt} [5.2.0]

RUN cd /tmp \
 && git clone --branch 5.2.0 --depth 1 https://github.com/fmtlib/fmt.git \
 && cd fmt \
 && mkdir build \
 && cd build \
 && cmake -DCMAKE_POSITION_INDEPENDENT_CODE=TRUE .. \
 && make --silent -j $(nproc) \
 && make install \
 && rm -rf /tmp/fmt

## Eigen [3.3.7]

RUN mkdir /tmp/eigen \
 && cd /tmp/eigen \
 && wget --quiet https://gitlab.com/libeigen/eigen/-/archive/3.3.7/eigen-3.3.7.tar.gz \
 && tar -xvf eigen-3.3.7.tar.gz \
 && cd eigen-3.3.7 \
 && mkdir build \
 && cd build \
 && cmake .. \
 && make install \
 && rm -rf /tmp/eigen

## Geometric Tools Engine [3.28]

RUN git clone --branch 3.28 --depth 1 https://github.com/lucas-bremond/geometric-tools-engine.git /tmp/geometric-tools-engine \
 && cd /tmp/geometric-tools-engine \
 && cp -r ./Include /usr/local/include/Gte \
 && rm -rf /tmp/geometric-tools-engine

## Open Space Toolkit ▸ Core [0.3.0]

# RUN mkdir -p /tmp/open-space-toolkit-core \
#  && cd /tmp/open-space-toolkit-core \
#  && wget --quiet https://github.com/open-space-collective/open-space-toolkit-core/releases/download/0.3.0/open-space-toolkit-core-0.3.0-1.x86_64-runtime.deb \
#  && wget --quiet https://github.com/open-space-collective/open-space-toolkit-core/releases/download/0.3.0/open-space-toolkit-core-0.3.0-1.x86_64-devel.deb \
#  && apt-get install -y ./*.deb \
#  && rm -rf /tmp/open-space-toolkit-core

# TBR: for assessing cross-use of ostk packages with the use of pybind11
COPY ./assets/cpp ./tmp/open-space-toolkit-core
RUN cd /tmp/open-space-toolkit-core \
 && apt-get install -y ./open-space-toolkit-core-0.3.3.60-1.x86_64-runtime.deb \
 && apt-get install -y ./open-space-toolkit-core-0.3.3.60-1.x86_64-devel.deb \
 && rm -rf /tmp/open-space-toolkit-core

# Labels

ARG VERSION

ENV VERSION ${VERSION}

LABEL VERSION="${VERSION}"

# Execution

CMD ["/bin/bash"]

################################################################################################################################################################
