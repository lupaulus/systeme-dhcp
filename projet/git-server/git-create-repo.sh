#!/bin/bash
 
GIT_DIR="/var/www/git"
REPO_NAME=$1
 
mkdir -p "${GIT_DIR}/${REPO_NAME}.git"
cd "${GIT_DIR}/${REPO_NAME}.git"
 
git init --bare &> /dev/null

cp hooks/post-update.sample hooks/post-update
echo "curl -X POST -H \"Content-Type: application/json\" -H \"headerWithNumber: \" -H \"headerWithString: \" -d '{ \"ref\": \"refs/heads/master\" }' -vs \"http://172.20.0.3/generic-webhook-trigger/invoke\"" >> hooks/post-update
git update-server-info
chmod 777 -R "${GIT_DIR}/${REPO_NAME}.git"
chown -Rf www-data:www-data "${GIT_DIR}/${REPO_NAME}.git"
echo "Git repository '${REPO_NAME}' created in ${GIT_DIR}/${REPO_NAME}.git"