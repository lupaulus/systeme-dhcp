pipeline {
    agent any

    stages {
        stage('Install stuff') { 
            steps{
                sh "docker-compose -v"
                sh "docker -v"
                sh "docker network prune -f"
                sh "docker-compose down"
                sh "docker rmi -f ${docker images -a -q}"
                sh "docker-compose build"
            } 
        }
        stage('Deploy') {
            steps {
                sh "docker-compose up -d"
            }
        }
    }
}