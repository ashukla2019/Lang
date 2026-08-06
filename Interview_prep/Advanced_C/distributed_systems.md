# Advanced C / System Design Interview Notes - Part 11

# Distributed Systems Fundamentals

Topics covered:

1. Distributed system architecture
2. CAP theorem
3. Consistency models
4. Leader election
5. Consensus basics
6. Replication algorithms
7. Distributed key-value store
8. Failure handling

---

# 1. Distributed System

A distributed system consists of:

```
Multiple computers

        |

Network communication

        |

Single logical service

```

Examples:

- Distributed file systems
- Cloud storage
- Databases
- Object storage

---

# Challenges

A distributed system must handle:

- Network failures
- Machine failures
- Data consistency
- Scalability
- Latency
- Partial failures

---

# 2. Distributed System Components

Typical architecture:

```
              Client

                |

             Gateway

                |

       +--------+--------+

       |                 |

    Node 1            Node 2

       |                 |

    Storage          Storage

```

---

# 3. CAP Theorem

CAP states that during a network partition, a distributed system can guarantee only one of:

```
C - Consistency

A - Availability

P - Partition tolerance

```

---

# Consistency

Every read sees latest data.

Example:

Write:

```
x = 10

```

All nodes return:

```
10

```

---

# Availability

Every request receives a response.

Even if some nodes fail.

---

# Partition Tolerance

System continues when communication breaks.

Example:

```
Node A  X  Node B

Network failure

```

---

# CAP Trade-offs

## CP System

Consistency + Partition tolerance.

Example:

- Banking systems

During failure:

```
Reject requests

```

---

## AP System

Availability + Partition tolerance.

Example:

- DNS
- Some NoSQL systems

May return stale data.

---

# 4. Consistency Models

## Strong Consistency

Read always returns latest write.

Example:

```
Write

 |

Read

 |

Same value

```

---

## Eventual Consistency

Data becomes consistent over time.

Example:

```
Node1 updated

Node2 updated later

```

---

## Sequential Consistency

Operations appear in global order.

---

# 5. Replication

Why replicate?

- Availability
- Performance
- Disaster recovery

---

# Replication Model

```
        Primary

          |

   +------+------+


Replica1      Replica2

```

---

# Primary-Replica

Writes:

```
Primary

```

Reads:

```
Replica

```

---

# Problem

Replica lag.

Example:

```
Write X=10

Primary updated

Replica delayed

Read returns old value

```

---

# 6. Leader Election

Used when:

```
Leader fails

```

Need a new leader.

---

# Election Requirements

1. Unique leader
2. Agreement
3. Failure detection

---

# Simple Election Algorithm

Example:

Nodes:

```
A B C D

```

Highest ID wins.

```
D becomes leader

```

---

# Problems

Network partition:

```
A thinks D failed

B thinks D failed

```

Two leaders possible.

Solution:

Consensus.

---

# 7. Consensus Basics

Goal:

Multiple nodes agree on value.

Example:

```
Who is leader?

What is committed?

```

---

# Consensus Properties

## Agreement

All nodes decide same value.

---

## Validity

Chosen value was proposed.

---

## Termination

Decision eventually happens.

---

# 8. Raft Algorithm

Common consensus algorithm.

Components:

- Leader
- Followers
- Candidates

---

# States

```
Follower

    |

Timeout

    |

Candidate

    |

Election

    |

Leader

```

---

# Leader Responsibilities

- Accept writes
- Replicate logs
- Maintain order

---

# Log Replication

Client:

```
SET A=10

```

Leader:

```
Log entry created

```

Followers:

```
Copy log

```

Commit:

```
Majority acknowledged

```

---

# Majority Rule

Example:

5 nodes.

Need:

```
3 votes

```

---

# Why Majority?

Prevents split brain.

---

# 9. Distributed Key Value Store

Example:

```
PUT user1 John

GET user1

```

---

# Architecture

```
Client

 |

Router

 |

+------+------+


Node1 Node2 Node3


 |

Storage Engine

```

---

# Data Partitioning

Need distribute keys.

---

# Hash Partitioning

Example:

```
hash(key) % number_of_nodes

```

Problem:

Adding nodes changes many mappings.

---

# Consistent Hashing

Better approach.

---

# Consistent Hash Ring

```
        Node A

     /          \

Node D          Node B


        Node C

```

Keys mapped to ring.

---

# Benefits

Adding node:

- Small data movement

Removing node:

- Limited impact

---

# 10. Write Path

Example:

```
Client

 |

Coordinator

 |

Replica nodes

 |

Storage

```

---

# Write Steps

1. Receive request.
2. Select replicas.
3. Write data.
4. Wait for acknowledgement.
5. Return success.

---

# 11. Read Path

```
Client

 |

Coordinator

 |

Read replicas

 |

Return latest version

```

---

# Versioning

Use:

- Timestamp
- Sequence number
- Vector clock

---

# 12. Failure Handling

## Node Failure

Detection:

- Heartbeat
- Timeout

Recovery:

- Replica promotion

---

# Network Partition

Possible:

```
Split brain

```

Solutions:

- Quorum
- Consensus
- Fencing

---

# 13. Quorum

For N replicas:

Write quorum:

```
W

```

Read quorum:

```
R

```

Strong consistency if:

```
R + W > N

```

Example:

N = 3

W = 2

R = 2

```
2 + 2 > 3

```

---

# 14. Distributed Locking

Used for:

- Metadata updates
- Resource ownership

Solutions:

- ZooKeeper
- Consensus based locks
- Lease mechanism

---

# 15. Senior Interview Questions

## Q1. How do you handle leader failure?

Answer:

- Detect failure
- Start election
- Select new leader
- Resume replication

---

## Q2. How prevent split brain?

Answer:

- Majority quorum
- Fencing
- Consensus

---

## Q3. How scale a key-value store?

Answer:

- Partition data
- Add nodes
- Consistent hashing
- Replication

---

## Q4. What happens if acknowledgement is lost?

Example:

```
Write succeeded

ACK lost

Client retries

```

Solution:

- Request IDs
- Idempotency

---

# Next Part

## Part 12

Will cover:

1. Thread pool implementation
2. Producer-consumer pattern
3. Circular buffer implementation
4. Condition variables
5. High-performance C concurrency patterns

