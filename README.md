### MINIDRONE QT

TODO
- [ ] Faire toute les commandes dans DroneController
- [ ] Gerer le systeme d'envoi


# Example:
```
backward() {
	send(BACKWARD);
}
```
```
send(BASE::TYPE move) {
	write(uuid, move);
}
```

# First
TAKEOFF

#Workflow
1) Device -> DiscoverService()

2) Liste des Uuid Services = Device -> services()

3) Display all services

4) Create new Service Object [service*] = createServiceObject(uuid)

5) [service*] -> writeCharacteristic(QLowEnergyCharacteristic*, QByteArray newValue)


