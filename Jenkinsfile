pipeline {
    agent any

    stages {
        stage('Install stuff') { 
            steps{
                sh "docker-compose -v"
            } 
        }
        stage('Test') {
            steps {
                echo 'Testing..'
            }
        }
        stage('Deploy') {
            steps {
                echo 'Deploying....'
            }
        }
    }
}