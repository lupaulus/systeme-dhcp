FROM tomcat:9.0
#on pourra ajouter '-slim' pour avoir le minimum de package (normalement conseillé 
# que si on utilise que tomcat mais ça coutera rien de tester)
#USER root

LABEL maintainer="LP-BS-YW"

COPY ./jenkins.war /usr/local/tomcat/webapps/
#CMD ./java -jar jenkins.war


#CATALINA_BASE:   /usr/local/tomcat
#CATALINA_HOME:   /usr/local/tomcat            environnement de base dans l'image
#CATALINA_TMPDIR: /usr/local/tomcat/temp
#JRE_HOME:        /usr
CMD [ "catalina.sh", "run" ]
EXPOSE 8080

