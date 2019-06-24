################################################################################################################################################################

# @project        Library/Mathematics
# @file           tools/python/docker/Dockerfile
# @author         Lucas Brémond <lucas@loftorbital.com>
# @license        Apache License 2.0

################################################################################################################################################################

FROM jupyter/scipy-notebook:latest

LABEL maintainer="lucas@loftorbital.com"

USER root

RUN apt-get update \
 && apt-get install -y libssl1.0.0 libssl-dev \
 && rm -rf /var/lib/apt/lists/*

COPY ./shortcuts-extension /home/jovyan/.jupyter/lab/user-settings/@jupyterlab/shortcuts-extension

RUN jupyter labextension install @jupyterlab/plotly-extension

RUN python -m pip install --quiet numpy --upgrade \
 && python -m pip install --quiet plotly

RUN chown -R ${NB_UID}:${NB_UID} /home/jovyan/.jupyter

USER ${NB_UID}

RUN pip install LibraryMathematicsPy

RUN mkdir -p /home/jovyan/.library

ENV JUPYTER_ENABLE_LAB yes

ENV LD_LIBRARY_PATH "/usr/local/lib:/opt/conda/lib/python3.7/site-packages:/home/jovyan/lib"

ENV PYTHONPATH "/opt/conda/lib/python3.7/site-packages:/home/jovyan/lib"

################################################################################################################################################################
