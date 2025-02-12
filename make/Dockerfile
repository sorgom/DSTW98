FROM ubuntu:24.04
LABEL Description="Build environment"

ENV HOME=/root

SHELL ["/bin/bash", "-c"]

EXPOSE 8080/tcp
EXPOSE 8081/tcp
EXPOSE 8082/tcp

RUN apt-get update && apt-get -y --no-install-recommends install \
    build-essential \
    gcc \
    cloc \
    valgrind \
    net-tools 

CMD /bin/bash
