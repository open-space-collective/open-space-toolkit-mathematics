################################################################################################################################################################

# @project        Library ▸ Mathematics
# @file           docker/development/fedora/Dockerfile
# @author         Lucas Brémond <lucas@loftorbital.com>
# @license        Apache License 2.0

################################################################################################################################################################

ARG BASE_IMAGE_VERSION=latest
ARG BASE_IMAGE_SYSTEM=debian

FROM openspacecollective/library-base:${BASE_IMAGE_VERSION}-${BASE_IMAGE_SYSTEM} as development-base

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
 && wget --quiet http://bitbucket.org/eigen/eigen/get/3.3.7.tar.gz \
 && tar -xvf 3.3.7.tar.gz \
 && cd eigen-eigen-323c052e1731 \
 && mkdir build \
 && cd build \
 && cmake .. \
 && make install \
 && rm -rf /tmp/eigen

## Geometric Tools Engine [3.25]

RUN mkdir /tmp/geometric-tools-engine \
 && cd /tmp/geometric-tools-engine \
 && wget --quiet https://www.geometrictools.com/Downloads/GeometricToolsEngine3p25.zip \
 && unzip -q ./GeometricToolsEngine3p25.zip \
 && cd GeometricTools/GTEngine \
 && cp -r ./Include /usr/local/include/Gte \
 && rm -rf /tmp/geometric-tools-engine

## Library ▸ Core [0.2.5]

RUN mkdir -p /tmp/library-core \
 && cd /tmp/library-core \
 && wget --quiet https://github.com/open-space-collective/library-core/releases/download/0.2.5/library-core-0.2.5-1.x86_64-runtime.rpm \
 && wget --quiet https://github.com/open-space-collective/library-core/releases/download/0.2.5/library-core-0.2.5-1.x86_64-devel.rpm \
 && dnf install -y ./*.rpm \
 && rm -rf /tmp/library-core

# Labels

ARG VERSION

ENV VERSION ${VERSION}

LABEL VERSION="${VERSION}"

# Execution

CMD ["/bin/bash"]

################################################################################################################################################################
