FROM ubuntu:24.04
LABEL Description="build environment"


SHELL ["/bin/bash", "-c"]

ENV HOME=/home/ms

RUN <<EOF
# create user ms and set home directory
mkdir -p $HOME
useradd -ms /bin/bash -d $HOME ms
chown -R ms:ms $HOME
# grant root privileges
echo "ms ALL=(ALL) NOPASSWD: ALL" >> /etc/sudoers

# install packages
apt-get update
apt-get -y --no-install-recommends install g++ make cloc valgrind net-tools git vim sudo
apt-get clean
rm -rf /var/lib/apt/lists/*
EOF

USER ms
WORKDIR $HOME
