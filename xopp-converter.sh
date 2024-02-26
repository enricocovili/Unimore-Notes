#!/bin/bash

for file in *.xopp ; do xournalpp -p "${file%.xopp}.pdf" "${file}" ; done ;
