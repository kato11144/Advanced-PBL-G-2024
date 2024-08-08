FROM ubuntu/mysql:latest

WORKDIR /workspace

RUN apt-get update \
    && apt-get install -y \
    nano \
    make \
    g++ \
    libmysqlclient-dev \
    locales \
    && locale-gen en_US.UTF-8 \
    && update-locale LANG=en_US.UTF-8 \
    && echo "set utf8" > /root/.nanorc

ENV LANG=en_US.UTF-8 \
    LC_ALL=en_US.UTF-8
