# Fixes:

1. A custom port can be picked (used to be two non-matching ports in server and client)
2. Made the server send the message with the size of strlen(line)+1 (instead of strlen(line)) to add the forgotten \0