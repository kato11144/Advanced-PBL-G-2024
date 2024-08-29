FROM ubuntu/mysql:latest

WORKDIR /workspace

RUN apt-get update \
    && apt-get install -y \
    nano \
    vim \
    make \
    g++ \
    libmysqlclient-dev \
    locales \
    && locale-gen en_US.UTF-8 \
    && update-locale LANG=en_US.UTF-8 \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

RUN ln -sf /usr/share/zoneinfo/Asia/Tokyo /etc/localtime \
    && echo "Asia/Tokyo" > /etc/timezone \
    && dpkg-reconfigure -f noninteractive tzdata

ENV LANG=en_US.UTF-8 \
    LC_ALL=en_US.UTF-8

RUN echo "set locale" > /root/.nanorc

RUN echo "set encoding=utf-8" > /root/.vimrc

RUN dpkg-reconfigure --frontend noninteractive locales && \
    update-locale LANG=en_US.UTF-8
