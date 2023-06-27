# Apache License 2.0

ARG JUPYTER_NOTEBOOK_IMAGE_REPOSITORY="jupyter/scipy-notebook:latest"

FROM ${JUPYTER_NOTEBOOK_IMAGE_REPOSITORY}

LABEL maintainer="lucas@loftorbital.com"

USER root

# Install extensions

RUN pip install "plotly" "numpy" "ipywidgets>=7.6"

RUN jupyter labextension install --no-build \
        @jupyterlab/shortcuts-extension

COPY ./shortcuts-extension /home/jovyan/.jupyter/lab/user-settings/@jupyterlab/shortcuts-extension

RUN chown -R ${NB_UID}:${NB_UID} /home/jovyan/.jupyter

USER ${NB_UID}

ENV JUPYTER_ENABLE_LAB="yes"

RUN pip install open-space-toolkit-mathematics
