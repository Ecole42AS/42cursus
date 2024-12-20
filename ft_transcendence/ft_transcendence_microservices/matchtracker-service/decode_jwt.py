import jwt

token = "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJ0b2tlbl90eXBlIjoiYWNjZXNzIiwiZXhwIjoxNzM0Njg4MzE3LCJpYXQiOjE3MzQ2ODgwMTcsImp0aSI6IjJhNDkwZjZiNzU2MjRkNzViN2UzM2VjMjI3Yjc3OTEzIiwidXNlcl9pZCI6MX0.Y5sMK_Z81UP3wCACfwCnF8V5o0ydQ34yJmyCg1jPNwk"

try:
    secret_key = "npacm^8-v00vfe9_3i7mlykn(728ajqzgfjsnx7io+(i^0g^q*"
    decoded = jwt.decode(token, secret_key, algorithms=["HS256"])
    print("Token décodé avec succès :", decoded)
except jwt.ExpiredSignatureError:
    print("Le token a expiré")
except jwt.InvalidTokenError:
    print("Token invalide")
