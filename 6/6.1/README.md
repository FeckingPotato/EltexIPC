# Wireshark analysis of 5.1

## Example message

![console.png](img%2Fconsole.png)

## UDP packets

![packets.png](img%2Fpackets.png)

### 78 (outbound)

![78.png](img%2F78.png)

### 79 (inbound)

![79.png](img%2F79.png)

## Packet 78 analysis

![78hl.png](img%2F78hl.png)

### Hex fragments

1. **00 00 00 00 00 00** (Ethernet)

   Destination MAC address: 00:00:00_00:00:00
2. **00 00 00 00 00 00**

   Source MAC address: 00:00:00_00:00:00
3. **08 00**

    Type: IPv4
4. **45** (IPv4)

   Version: 4 (0100)
   Header length: 20 bytes (0101)
5. **00**

   ECN: Not ECN-Capable Transport
6. **00 22**

   Total length: 34 bytes
7. **00**

   ECN: Not ECN-Capable Transport
8. **F0 0E**

   Identification: 0xF00E
9. **40 00**

   Fragment offset: 0
10. **40**

    TTL: 64 hops
11. **11**

    Protocol: UDP
12. **64 89**

    Header checksum: 0x6489
13. **C0 A8 32 71**

    Source IP address: 192.168.50.113
14. **C0 A8 32 71**

    Destination IP address: 192.168.50.113
15. **D0 8C** (UDP)

    Source port: 53388
16. **04 D2**

    Destination port: 1234
17. **00 0E**

    Length: 14
18. **E6 52**

    Checksum: 0xE652
19. **74 65 73 74 0a 00**

    Data: test

## Packet differences

- Identification
  - 78: 0xF00E
  - 79: 0xF00F
- Header checksum
  - 78: 0x6489
  - 79: 0x6488
- Source port
  - 78: 53388
  - 79: 1234
- Destination port
  - 78: 1234
  - 79: 53388