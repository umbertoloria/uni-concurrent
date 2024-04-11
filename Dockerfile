FROM ubuntu:24.04

ENV LANG C.UTF-8
ENV LC_ALL C.UTF-8

VOLUME /volume

RUN apt --yes -qq update
RUN apt --yes upgrade
RUN apt --yes install gcc libopenmpi-dev openmpi-bin

CMD [ "/bin/bash", "/volume/build-and-run.sh" ]
