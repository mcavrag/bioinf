# Bioinformatics - project

Project name: A representation of a compressed de Bruijn graph for pan-genome analysis that enables search (Beller and Ohlebusch, 2016)

Goals: Implementation of algorithms A1 and A2 and comparison with the original implementation (https://www.uni-ulm.de/in/theo/research/seqana.html)

Original paper: https://almob.biomedcentral.com/articles/10.1186/s13015-016-0083-7

Course website: http://www.fer.unizg.hr/predmet/bio

## Installation

### Install cmake (Version 3.10.1)

```sh
cd REPO_NAME/install
tar -xzvf cmake-3.10.1.tar.gz
cd cmake-3.10.1
sudo ./bootstrap --prefix=/usr
make
sudo make install
```

### Install sdsl-lite

```sh
cd REPO_NAME/install
tar -xzvf sdsl-lite.tar.gz
cd sdsl-lite/
sudo ./install.sh /usr/local
```

## Compiling

```sh
mkdir build
cd build
cmake --target debruijn.exe ..
make -j4
```

## Running

```sh
cd REPO_NAME
./debruijn.exe input/XXX.fa -k=<Integer> --printMode

--printMode
	--originalPrint
	--lastYearPrint
	<without argument>	- print in file
```

## Testing

```sh
cd REPO_NAME
./test.sh
```