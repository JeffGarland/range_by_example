FROM ubuntu:16.04

# Install
RUN apt-get update -y
RUN apt-get install -y apt-utils | true
RUN apt-get install -y software-properties-common | true
RUN apt-get install -y python-software-properties
RUN apt-get update -y
RUN add-apt-repository -y ppa:jonathonf/gcc-7.1
RUN apt-get update -y 
RUN apt-get install -y cmake software-properties-common git make
RUN apt-get install -y gcc-7 g++-7 
RUN update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-7 90
RUN update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-7 90 

# Build Preparation
RUN mkdir -p /src/
RUN mkdir -p /src/build/
RUN git clone https://github.com/ericniebler/range-v3.git
RUN cp -r range-v3/include/* /usr/local/include/.

# Build
WORKDIR /src/build/
COPY . /src/
RUN cmake ..
RUN make

# clean crud then find and execute all examples
RUN rm -rf CMake* && find . -type f -executable -exec '{}' ';' 

