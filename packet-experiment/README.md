### Packet Components
- uses two cache lines
- header structure is kept as small as possible
- rte-mbuf can be extended to other types

### Design of Packets

- embed metadata within a single memory buffer with fixed size area for the packet
    - only need one operation to allocate and free memory
    - meta data contains message type length offset

- use separate memory buffer for metadata and for packet
    -



| component | detail |
| -- |  -- |  
| RTE_PKTMBUF_HEADROOM | beginning of the buffer |
| | | 
