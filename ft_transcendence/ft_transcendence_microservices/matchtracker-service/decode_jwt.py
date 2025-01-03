import jwt

token = "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJ0b2tlbl90eXBlIjoiYWNjZXNzIiwiZXhwIjoxNzM0Njg5MTg2LCJpYXQiOjE3MzQ2ODg4ODYsImp0aSI6IjM5MmYxMDEyZTcwMjRhMjFhZDc2M2NjZGU1MmFmOGJjIiwidXNlcl9pZCI6MX0.mAXzTVA4fB1m8rTwaPAHfUscARb7YNBOgC4D5AH7pJk"

try:
    secret_key = "npacm^8-v00vfe9_3i7mlykn(728ajqzgfjsnx7io+(i^0g^q*"
    decoded = jwt.decode(token, secret_key, algorithms=["HS256"])
    print("Token décodé avec succès :", decoded)
except jwt.ExpiredSignatureError:
    print("Le token a expiré")
except jwt.InvalidTokenError:
    print("Token invalide")
