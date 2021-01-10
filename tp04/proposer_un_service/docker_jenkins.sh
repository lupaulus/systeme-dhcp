mkdir -p jenkins
cd jenkins
id_conteneur=$(docker run --name jenkins-master -d -p 8080:8080 -p 50000:50000 -v $(pwd):/var/jenkins_home jenkins/jenkins:lts);
docker logs $id_conteneur;
echo "Ouvrons JENKINS !";
sleep 1;
firefox http://127.0.0.1:8080;
