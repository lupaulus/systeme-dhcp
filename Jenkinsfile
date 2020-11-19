pipeline {
    agent any

    stages {
        stage('Install stuff') { 
            steps{
                sh "docker-compose -v"
                sh "docker -v"
                sh "docker network prune -f"
                sh "docker-compose build"
            } 
        }
        stage('Deploy') {
            steps {
                sh "docker-compose up -d"
            }
        }
        stage('Stop') {
            steps {
                sh "docker-compose down"
            }
        }
    }
}