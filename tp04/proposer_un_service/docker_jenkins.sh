id_conteneur=$(docker run --name jenkins-master -d -p 8080:8080 -p 50000:50000 -v /var/jenkins_home jenkins/jenkins:lts);
docker logs $id_conteneur;
secs=25
echo "pour cause de préparation, on ouvre jenkins dans:"
while [ $secs -gt 0 ]
do
  printf "$secs...\n"
  secs=$((secs-1))
  sleep 1
done
echo "LEROOOOOOOOOOOOY JENKINS !";
sleep 1;
firefox http://127.0.0.1:8080;
