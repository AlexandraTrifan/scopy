#!/bin/bash

BRANCH=${1:-master}
REPO=${2:-analogdevicesinc/scopy}

sudo apt-get -qq update
sudo service docker restart
sudo docker pull alexandratr/scopy-flatpak-bionic:scopy

echo "starting the docker repo ========================== " $BRANCH " ==== " $REPO

# Start the docker in detached state
# We need to keep it open after build, to copy the build artifact
commit_nb=$(sudo docker run -d \
		--privileged \
		--rm=true \
		-v `pwd`:/scopy:rw \
		-e "BRANCH=$BRANCH" \
		-e "REPO=$REPO" \
		alexandratr/scopy-flatpak-bionic:scopy \
		/bin/bash -xe /scopy/CI/appveyor/inside_ubuntu_flatpak_docker.sh)

# Attach ourselves to the running docker and wait for it to finish
sudo docker attach $commit_nb

# Extract the build artifact
#sudo docker cp $commit_nb:/home/docker/scopy-flatpak/Scopy.flatpak .
echo "=================================================================="
pwd
ls 
echo "=================================================================="

