import jwt

token = "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJ0b2tlbl90eXBlIjoiYWNjZXNzIiwiZXhwIjoxNzM2MTAzNDg4LCJpYXQiOjE3MzYxMDEwODgsImp0aSI6IjYxMWYyMzM0MzQ4YTQxNDRhZWYwNTRkMDM1NGQxZjI0IiwidXNlcl9pZCI6MX0.Rs1kj0Yula3EKmx0pNrWxuRXqqGAbeGQHWzmwb6hwwI"

try:
    secret_key = "npacm^8-v00vfe9_3i7mlykn(728ajqzgfjsnx7io+(i^0g^q*"
    decoded = jwt.decode(token, secret_key, algorithms=["HS256"], leeway=60)  # Tolérance de 60 secondes
    print("Token décodé avec succès :", decoded)
except jwt.ExpiredSignatureError:
    print("Le token a expiré")
except jwt.InvalidTokenError:
    print("Token invalide")
