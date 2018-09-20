################################################################################################################################################################

# @project        Library/Mathematics
# @file           tools/development/docker/Dockerfile
# @author         Lucas Brémond <lucas@loftorbital.com>
# @license        TBD

################################################################################################################################################################

FROM openspacecollective/library-core:0.1.7

LABEL maintainer="lucas@loftorbital.com"

# Arguments

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

## Geometric Tools Engine [3.15]

# RUN dnf -y update \
#  && dnf install -y libX11-devel mesa-libGL-devel mesa-libEGL-devel libpng-devel \
#  && dnf clean all

# RUN mkdir /tmp/geometric-tools-engine \
#  && pushd /tmp/geometric-tools-engine > /dev/null \
#  && wget --quiet https://www.geometrictools.com/Downloads/GeometricToolsEngine3p15.zip \
#  && unzip -q ./GeometricToolsEngine3p15.zip \
#  && cd GeometricTools/GTEngine \
#  && export GTE_PATH=$(pwd) \
#  && make CFG=Release -j ${cpu_count} -f makeengine.gte \
#  && cp -r ./Include /usr/local/include/Gte \
#  && cp ./lib/Release/libgtengine.a /usr/local/lib \
#  && rm -rf /tmp/geometric-tools-engine \
#  && popd > /dev/null

RUN mkdir /tmp/geometric-tools-engine \
 && pushd /tmp/geometric-tools-engine > /dev/null \
 && wget --quiet https://www.geometrictools.com/Downloads/GeometricToolsEngine3p15.zip \
 && unzip -q ./GeometricToolsEngine3p15.zip \
 && cd GeometricTools/GTEngine \
 && cp -r ./Include /usr/local/include/Gte \
 && rm -rf /tmp/geometric-tools-engine \
 && popd > /dev/null

## Library ▸ Core [0.1.15]

RUN mkdir -p /tmp/library-core \
 && pushd /tmp/library-core > /dev/null \
 && wget --quiet https://github.com/open-space-collective/library-core/releases/download/0.1.15/library-core-0.1.15-1.x86_64-runtime.rpm \
 && wget --quiet https://github.com/open-space-collective/library-core/releases/download/0.1.15/library-core-0.1.15-1.x86_64-devel.rpm \
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