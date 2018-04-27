

```

sudo tshark -n -i p5p1 -T fields -e frame.time_relative -e ip.src -Y "ip.src == 10.107.30.33 || ip.src == 10.107.30.34" -e data.data >> receiver_asu

sudo tshark -n -i p5p1 -T fields -e frame.time_relative -e ip.src -Y "ip.src == 10.107.30.33 || ip.src == 10.107.30.34" -e data.data >> sender_asu

```
