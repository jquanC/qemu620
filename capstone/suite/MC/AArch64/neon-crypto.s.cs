# CS_ARCH_ARM64, 0, None
0x20,0x48,0x28,0x4e = aese v0.16b, v1.16b
0x20,0x58,0x28,0x4e = aesd v0.16b, v1.16b
0x20,0x68,0x28,0x4e = aesmc v0.16b, v1.16b
0x20,0x78,0x28,0x4e = aesimc v0.16b, v1.16b
0x20,0x08,0x28,0x5e = sha1h s0, s1
0x20,0x18,0x28,0x5e = sha1su1 v0.4s, v1.4s
0x20,0x28,0x28,0x5e = sha256su0 v0.4s, v1.4s
0x20,0x00,0x02,0x5e = sha1c q0, s1, v2.4s
0x20,0x10,0x02,0x5e = sha1p q0, s1, v2.4s
0x20,0x20,0x02,0x5e = sha1m q0, s1, v2.4s
0x20,0x30,0x02,0x5e = sha1su0 v0.4s, v1.4s, v2.4s
0x20,0x40,0x02,0x5e = sha256h q0, q1, v2.4s
0x20,0x50,0x02,0x5e = sha256h2 q0, q1, v2.4s
0x20,0x60,0x02,0x5e = sha256su1 v0.4s, v1.4s, v2.4s
