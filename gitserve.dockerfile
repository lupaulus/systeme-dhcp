FROM ubuntu:18.04

RUN apt update 2>/dev/null

RUN apt-get install -y software-properties-common 2>/dev/null
RUN add-apt-repository universe
RUN apt-get update 2>/dev/null
RUN apt-get install -y git vim mc apache2 apache2-utils 2>/dev/null

RUN a2enmod env cgi alias rewrite
RUN mkdir /var/www/git
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


CMD /usr/sbin/apache2ctl -D FOREGROUND



EXPOSE 80/tcp