FROM debian:9

RUN apt update 2>/dev/null
RUN apt-get install -y --no-install-recommends apt-utils 2>/dev/null
RUN apt-get install -y --no-install-recommends software-properties-common 2>/dev/null
RUN apt-get update 2>/dev/null && rm -rf /var/lib/apt/lists/*
RUN apt-get install -y --no-install-recommends git vim mc gosu apache2 apache2-utils openssh-server 2>/dev/null


RUN a2enmod env cgi alias rewrite
RUN mkdir /var/www/git
RUN chmod 777 -R /var/www/git/
RUN chown -Rfv www-data:www-data /var/www/git
RUN rm -rf /var/www/html/index.html

RUN git config --system http.receivepack true
RUN git config --system http.uploadpack true


RUN chown -Rfv www-data:www-data /var/www/git
COPY ./git-server/git.conf /etc/apache2/sites-available/git.conf
COPY ./git-server/git-create-repo.sh /usr/bin/mkrepo
RUN chmod +x /usr/bin/mkrepo
RUN a2dissite 000-default.conf
RUN a2ensite git.conf




ENV APACHE_RUN_USER www-data
ENV APACHE_RUN_GROUP www-data
ENV APACHE_LOG_DIR /var/log/apache2
ENV APACHE_LOCK_DIR /var/lock/apache2
ENV APACHE_PID_FILE /var/run/apache2.pid





RUN useradd -rm -d /home/ssh -s /bin/bash -g root -G root,www-data,sudo -u 1000 ssh
RUN  echo 'ssh:ssh' | chpasswd
COPY ./git-server/id_rsa.pub /home/ssh/.ssh/authorized_keys
COPY ./git-server/id_rsa /home/ssh/.ssh/id_rsa
CMD gosu root service ssh start && \
    /usr/sbin/apache2ctl -D FOREGROUND 

RUN mkrepo projet  

EXPOSE 80/tcp 
EXPOSE 22/tcp