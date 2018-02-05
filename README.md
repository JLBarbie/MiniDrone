### MINIDRONE QT

TODO
- [ ] Faire toute les commandes dans DroneController
- [ ] Gerer le systeme d'envoi

### Build Docker
```
docker build -t airborne .
docker run -v `pwd`/build-docker:/build-docker -u `id -u $USER` airborne
```
