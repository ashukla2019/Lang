# Advanced C / System Design Interview Notes - Part 10

# Storage System Design (NetApp Style)

Topics covered:

1. Storage system architecture
2. RAID design
3. Snapshot mechanism
4. Copy-on-write
5. Deduplication engine
6. Replication system
7. Distributed file system basics
8. Failure handling

---

# 1. Storage System Architecture

A modern storage system contains:

```
              Client

                |
                |

          Network Layer

                |

                |

        Storage Controller

                |

     +----------+----------+

     |                     |

 Metadata Service     Data Service

     |                     |

     |                     |

  Disks / SSDs       Cache Layer

```

---

# Main Components

## 1. Frontend

Handles:

- NFS
- SMB
- iSCSI
- FC

Responsibilities:

- Authentication
- Request processing

---

## 2. Storage Controller

Main brain.

Handles:

- IO scheduling
- Cache management
- RAID
- Metadata
- Recovery

---

## 3. Cache

Two types:

## Read Cache

Stores frequently accessed data.

Example:

```
Disk -> Cache -> Client

```

---

## Write Cache

Stores writes before disk.

Example:

```
Client

 |

Cache

 |

Disk later

```

Advantages:

- Lower latency

Risk:

- Power failure

Solution:

Battery-backed cache.

---

# 2. Read/Write IO Path

## Read Path

```
Client

 |

Controller

 |

Check Cache

 |

Cache Hit

 |

Return Data


Cache Miss

 |

Read Disk

 |

Update Cache

 |

Return Data

```

---

# Write Path

```
Client

 |

Controller

 |

Write Cache

 |

Acknowledge


Later:

Cache

 |

RAID

 |

Disk

```

---

# 3. RAID Design

RAID provides:

- Performance
- Fault tolerance

---

# RAID 0

Striping.

```
Data:

A B C D


Disk1:
A C


Disk2:
B D

```

Advantages:

- High performance

Disadvantage:

- No protection

---

# RAID 1

Mirroring.

```
Disk1:

A B C


Disk2:

A B C

```

Advantages:

- High availability

Disadvantage:

- 50% capacity

---

# RAID 5

Striping + parity.

Example:

```
Disk1 Disk2 Disk3

 A      B      P

 C      P      D

 P      E      F

```

Can tolerate:

```
1 disk failure

```

---

# RAID 6

Two parity blocks.

Can tolerate:

```
2 disk failures

```

---

# RAID 10

Combination:

```
Mirror + Stripe

```

Used in:

- Databases
- Enterprise storage

---

# 4. RAID Write Operation

Problem:

Parity update.

Example:

Existing:

```
Data = 10

Parity = 5

```

New:

```
Data = 20

```

Need:

```
New parity calculation

```

---

# Read Modify Write

Steps:

1. Read old data.
2. Read old parity.
3. Calculate difference.
4. Write new data.
5. Write new parity.

---

# RAID Optimization

Techniques:

- Full stripe writes
- Write batching
- Cache
- Parallel disks

---

# 5. Snapshot Design

## Requirement

Create point-in-time copy without copying all data.

---

# Naive Approach

Copy entire volume.

Problem:

```
100 TB volume

Snapshot = 100 TB copy

```

Expensive.

---

# Solution

Copy-on-Write Snapshot.

---

# Copy-On-Write

Initial:

```
Volume

Block A

Block B

Block C

```

Snapshot created:

```
Snapshot

A B C


Volume

A B C

```

No data copied.

---

# Write Operation

Client modifies block B.

Before:

```
Volume

A B C

```

Step 1:

Copy old B.

```
Snapshot

A B(old) C

```

Step 2:

Write new B.

```
Volume

A B(new) C

```

---

# Snapshot Metadata

Need:

- Block mapping
- Reference count
- Snapshot timestamp

---

# 6. Deduplication Engine

## Goal

Remove duplicate blocks.

Example:

```
File1:

ABCDEF


File2:

ABCDEF

```

Store once.

---

# Architecture

```
Incoming Data

      |

Chunking

      |

Hash Calculation

      |

Fingerprint Index

      |

Existing?

      |

Yes --> Reference existing block

No  --> Store new block

```

---

# Chunking Types

## Fixed Size

Example:

```
4 KB blocks

```

Simple.

---

## Variable Size

Uses:

- Content-defined chunking

Better for:

- Changed files

---

# Hash Index

Example:

```
SHA256(block)

        |

        v

Physical location

```

---

# Deduplication Challenges

## Hash collision

Solution:

- Verify data

---

## Garbage Collection

Remove unused blocks.

---

# 7. Replication System

Purpose:

Disaster recovery.

---

# Types

## Synchronous Replication

Write:

```
Primary

 |

Secondary

 |

ACK

 |

Client success

```

Advantages:

- Zero data loss

Disadvantage:

- Higher latency

---

## Asynchronous Replication

Write:

```
Primary

 |

ACK

 |

Replicate later

```

Advantages:

- Faster

Disadvantage:

- Possible data loss

---

# Replication Terms

## RPO

Recovery Point Objective.

Maximum data loss.

Example:

```
RPO = 5 minutes

```

---

## RTO

Recovery Time Objective.

Time to recover.

Example:

```
RTO = 30 minutes

```

---

# 8. Distributed File System

Examples:

- Google File System
- Hadoop DFS
- Enterprise storage systems

---

# Architecture

```
Client

 |

Metadata Server

 |

Data Nodes


```

---

# Metadata Server

Stores:

- File names
- Permissions
- Block locations


Example:

```
file.txt

Block1 -> Node A

Block2 -> Node B

```

---

# Data Nodes

Store actual blocks.

---

# 9. Failure Handling

Enterprise systems assume:

"Failures will happen."

---

# Disk Failure

Detection:

- Heartbeat
- Error counters

Recovery:

- Rebuild RAID

---

# Controller Failure

Solution:

High Availability Pair.

```
Controller A

       |

       |

Controller B

```

---

# Network Failure

Solutions:

- Retry
- Timeout
- Quorum
- Failover

---

# 10. Storage Interview Questions

## Q1. How do snapshots work?

Answer:

- Metadata copy
- Copy-on-write
- Block reference tracking

---

## Q2. How to handle power failure?

Answer:

- Write-ahead logging
- Battery-backed cache
- Journaling

---

## Q3. How to improve write performance?

Answer:

- Write batching
- Cache
- Parallel IO
- RAID optimization

---

## Q4. How to scale metadata?

Answer:

- Partition metadata
- Distributed metadata servers
- Caching
- B+ Tree indexing

---

# NetApp-Level Follow-up Questions

Be ready for:

1. Design a storage controller.
2. Design snapshots for a 1 PB system.
3. Handle simultaneous disk failures.
4. Remove a global lock from storage metadata.
5. Design crash recovery.
6. Design deduplication for millions of files.
7. Optimize random IO workload.

---

# Next Part

## Part 11

Will cover:

1. Distributed systems fundamentals
2. Consensus basics
3. Leader election
4. CAP theorem
5. Replication algorithms
6. Distributed key-value store design

