FROM ubuntu/mysql:latest

WORKDIR /workspace

RUN apt-get update \
    && apt-get install -y \
    make \
    g++ \
    libmysqlclient-dev
