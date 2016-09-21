#!/bin/bash

mkdir -p lib
cd lib

gcc -c -I../include \
    ../src/net/http/client.cc \
	../src/net/http/request.cc \
	../src/net/http/response.cc \
	../src/net/http/header.cc \
	../src/net/url/url.cc

ar rcs libqtl-dep.a client.o header.o request.o response.o url.o
ar -M << EOF
    create libqtl.a
	addlib libqtl-dep.a
	addlib /usr/lib64/libboost_system-mt.a
	save
	end
EOF

echo 
echo done



