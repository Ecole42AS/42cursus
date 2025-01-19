#!/bin/bash
apt update && apt upgrade -y
apt install -y docker.io docker-compose
usermod -aG docker $USER

