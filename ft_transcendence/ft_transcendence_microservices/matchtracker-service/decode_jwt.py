import jwt

token = "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJ0b2tlbl90eXBlIjoiYWNjZXNzIiwiZXhwIjoxNzM0NDY3NDE3LCJpYXQiOjE3MzQ0NjY1MTcsImp0aSI6IjhhMTQ5ZGY5YzcyYzQ4Zjg5ZjQyNzRkOTQ1ZGQzOWJjIiwidXNlcl9pZCI6MX0.Wry776U7iEQrxV5oVYYrLCenmWJy4z-9muQ8zNzDMnQ"

try:
    secret_key = "npacm^8-v00vfe9_3i7mlykn(728ajqzgfjsnx7io+(i^0g^q*"
    decoded = jwt.decode(token, secret_key, algorithms=["HS256"])
    print("Token décodé avec succès :", decoded)
except jwt.ExpiredSignatureError:
    print("Le token a expiré")
except jwt.InvalidTokenError:
    print("Token invalide")
