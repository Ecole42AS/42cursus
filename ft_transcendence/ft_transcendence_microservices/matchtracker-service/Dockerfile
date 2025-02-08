FROM python:3.10.12-slim


WORKDIR /usr/src/app


RUN apt-get update && apt-get install -y \
    curl \
    iputils-ping \
    --no-install-recommends && \
    rm -rf /var/lib/apt/lists/*


COPY requirements.txt .
RUN pip install --upgrade pip
RUN pip install --no-cache-dir -r requirements.txt


COPY . .


ENV PYTHONUNBUFFERED 1


CMD ["python", "manage.py", "runserver", "0.0.0.0:8000"]
