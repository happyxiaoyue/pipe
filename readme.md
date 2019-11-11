# pipe.c

C has historically had minimal support for multithreading, and even less
for concurrency. pthreads was the first step to bringing threading
constructs to C, and it has served us well. However, threads and mutexes
alone aren't the only concurrency paradigm available to us. Very few
paradigms map nicely onto heavyweight threads and locking. For example,
the Actor model has no explicit locking at all.

Let's imagine a classic problem. We want to write a simple download
manager. First, we need to get the data from a high-latency internet
connection, then dump that data to a high-latency hard disk. In
classic C, waiting for one resource to finish transferring data is time
you can't spend on the other one! This is unacceptable since you're
dealing with two very slow connections. When the disk starts spinning
up, you don't want your download to slow down!

To solve this problem, we introduce a new data structure called a pipe.
We create two threads: one for receiving the data from the network,
and one for dumping the data to disk.

Whenever data is received, it will be pushed into the pipe instead of
directly to the disk. In the disk thread, it will read from the pipe,
dumping any data onto the disk *without blocking the networking thread*.
Since the two processes are decoupled by a fast in-memory pipe (which
is implemented with simple memcpy's), when one thread lags behind, the
other one is free to continue its operation. If the producer is lagging,
the consumer will block until there is data. If the consumer is lagging,
requests will just pile up in the queue to be handled "eventually". If
memory usage becomes a problem, we can limit the size of the pipe to
block the producer when the pipe gets too full.

Although this sample seems a bit trivial, the pipe is a lot more powerful
than it lets on. No matter how many producers or consumers you have, pipe
will behave predictably (although not necessarily fairly). Therefore, you
can use pipe for serialization, pipelining tasks, parallel processing,
futures, multiplexing, and so much more. It does this extremely quickly,
to the point where anything except trivial code will be the bottleneck,
not the pipe. It can do all this and more in under 1000 lines of C!

My true hope is that this library will spur development of concurrent
systems in all languages, and the creation of new ideas in the field.
Since C is so pervasive, I hope to see these concepts leaking into other
languages and libraries, hopefully being expanded upon and becoming a
building block of the next generation of concurrent programming.

Integration
------------

1. Copy pipe.c and pipe.h into your project's directory.
2. Get your compiler to build it (pipe.c needs -std=c99)
3. Use it!


# There are a few things you can do to get the most speed out of the pipe.

 1. Use a vectorizing compiler, and an SSE-enabled memcpy. It's a lot
   faster, trust me. I recommend icc.
 2. Tweak `MUTEX_SPINS` in pipe.c. Set it to a low value if you tend to
   push large quantities of data at once, and a high value if you tend to
   push small quantities of data. Feel free to set it to zero to disable
   spin locking altogether and just use the native lock implementation.
 3. Turn on your compiler's link-time optimization.
 4. Do profile-guided optimization.
 5. Large buffers are preferable to small ones, unless your use case
   dictates otherwise. Emptying the pipe frequently tends to be faster
   and use less memory.
 6. Avoid limiting the size of the pipe unless you get serious memory
   issues.
 7. If you are always pushing predictable amounts of data into the pipe
   (such as 1000 elements at a time), you should consider using
   `pipe_reserve` to keep the pipe from needlessly growing and
   shrinking.
 8. If you can combine a whole bunch of elements into a single struct, it
   will be faster to push and pop one large struct at a time rather than
   a push/pop of many small structs.
 9. Read through the source code, and find bottlenecks! Don't forget to
   submit changes upstream, so the rest of the world can be in awe of
   your speed-hackery. I have also left a couple optimization hints
   in-source as a reward for actually reading it.

## API Overview

## The API is fully documented in pipe.h