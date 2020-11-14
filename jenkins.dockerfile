FROM jenkins/jenkins

USER root

RUN curl -fsSL https://get.docker.com -o get-docker.sh \
    sh get-docker.sh

# see https://docs.docker.com/compose/install/
RUN curl -L \
  "https://github.com/docker/compose/releases/download/1.25.3/docker-compose-$(uname -s)-$(uname -m)" \
  -o /usr/local/bin/docker-compose \
  && chmod +x /usr/local/bin/docker-compose
