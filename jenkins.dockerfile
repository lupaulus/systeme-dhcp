FROM jenkins/jenkins

USER root

RUN curl -fsSL https://get.docker.com -o get-docker.sh 
RUN bash get-docker.sh


RUN curl -L \
  "https://github.com/docker/compose/releases/download/1.25.3/docker-compose-$(uname -s)-$(uname -m)" \
  -o /usr/local/bin/docker-compose \
  && chmod +x /usr/local/bin/docker-compose
