pipeline {
    agent any

    stages {
        stage('Install stuff') { 
            steps{
                sh "docker-compose -v"
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