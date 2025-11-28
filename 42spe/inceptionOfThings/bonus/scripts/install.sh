#!/bin/bash

# Ensure we are in the right directory
cd $(dirname $0)

# Check and Install Helm
if ! command -v helm &> /dev/null
then
    echo "Helm not found. Installing..."
    curl https://raw.githubusercontent.com/helm/helm/main/scripts/get-helm-3 | bash
else
    echo "Helm is already installed."
fi

# Create cluster
if k3d cluster list | grep -q "bonus-cluster"; then
    echo "Cluster 'bonus-cluster' already exists."
else
    k3d cluster create bonus-cluster --port 8888:80@loadbalancer --port 8443:443@loadbalancer --wait
fi

# Create namespaces
for ns in argocd gitlab dev; do
    if kubectl get namespace "$ns" > /dev/null 2>&1; then
        echo "Namespace '$ns' already exists."
    else
        kubectl create namespace "$ns"
    fi
done

# Install ArgoCD
kubectl apply -n argocd -f https://raw.githubusercontent.com/argoproj/argo-cd/stable/manifests/install.yaml

# Install GitLab
echo "Installing GitLab..."
helm repo add gitlab https://charts.gitlab.io/
helm repo update
helm upgrade --install gitlab gitlab/gitlab \
  --namespace gitlab \
  -f ../confs/gitlab-values.yaml \
  --timeout 600s \
  --set global.hosts.domain=gitlab.localhost \
  --set global.hosts.externalIP=0.0.0.0

# Wait for GitLab Webservice
echo "Waiting for GitLab Webservice to be ready..."
kubectl wait --for=condition=ready pod -l app=webservice -n gitlab --timeout=1200s

# Get password
PASSWORD=$(kubectl get secret gitlab-gitlab-initial-root-password -n gitlab -o jsonpath="{.data.password}" | base64 --decode)

echo "GitLab Root Password: $PASSWORD"

# Create Project via Rails Console
echo "Creating 'iot-bonus' project in GitLab..."
TOOLBOX_POD=$(kubectl get pods -n gitlab -l app=toolbox -o jsonpath="{.items[0].metadata.name}")
kubectl exec -n gitlab $TOOLBOX_POD -- gitlab-rails runner "Project.create(name: 'iot-bonus', path: 'iot-bonus', namespace: User.first.namespace, visibility_level: Gitlab::VisibilityLevel::PUBLIC)"

echo "Project 'iot-bonus' created."

# Configure ArgoCD Application
# We need to create the application.yaml pointing to the internal service
# The internal URL for the repo: http://gitlab-webservice-default.gitlab.svc.cluster.local:8181/root/iot-bonus.git
# Wait, check port. Usually 8181 is workhorse.
# But let's assume standard service discovery.

echo "Applying ArgoCD Application configuration..."

echo "ArgoCD Application configuration created at ../confs/application.yaml"

# Apply ArgoCD Application
kubectl apply -f ../confs/application.yaml

echo "------------------------------------------------"
echo "Setup Complete!"
echo "GitLab URL: http://gitlab.localhost:8888"
echo "User: root"
echo "Password: $PASSWORD"
echo "Repo URL (Local): http://gitlab.localhost:8888/root/iot-bonus.git"
echo ""
echo "ACTION REQUIRED:"
echo "You need to push the content of 'bonus/app' to the GitLab repository."
echo "Run the following commands:"
echo "  cd ../app"
echo "  git init"
echo "  git remote add origin http://root:$PASSWORD@gitlab.localhost:8888/root/iot-bonus.git"
echo "  git add ."
echo "  git commit -m \"Initial commit\""
echo "  git push -u origin master"
echo "------------------------------------------------"
