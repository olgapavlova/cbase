#!/bin/bash

# Create project folder
mkdir $1
cd $1


# Empty files
empty_files=(
	.backlog
	Dockerfile
	docker-compose.yml
	docker-compose.override.yml
	.dockerignore
	Makefile
	README.md
	LICENSE
)
for item in "${empty_files[@]}"; do
	touch $item
done


# Dirs
dirs=(
	.env
	.local
	src
	include
	lib
	bin
	build
	docs
	data
	logs
	tests
)
for item in "${dirs[@]}"; do
	mkdir $item
	cd $item
	touch .gitkeep
	cd ..
done


# Git ignore
touch .gitignore
gitignore_lines=(
	"# Custom"
	docker-compose.override.yml
	.DS_Store
	.env/
	.local/
	logs/
	bin/
	build/
	lib/
	*.swp
	*.a
	*.o
	*.out
	*.run
)
for item in "${gitignore_lines[@]}"; do
	echo $item >> .gitignore
done

