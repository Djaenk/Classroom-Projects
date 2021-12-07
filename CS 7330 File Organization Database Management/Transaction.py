from collections import deque

class Transaction:

  def __init__(self, tid, k, operations):
    self.tid = tid
    self.local = [None] * k
    self.operations = deque(tuple(op.split()) for op in operations)

  def Read(self, db, source, dest):
    self.local[dest] = db.Read(source)

  def Write(self, db, source, dest):
    db.Write(dest, self.local[source])

  def Add(self, source, v):
    self.local[source] += v

  def Sub(self, source, v):
    self.local[source] -= v

  def Copy(self, s1, s2):
    self.local[s1] = self.local[s2]

  def Combine(self, s1, s2):
    self.local[s1] += self.local[s2]

  def Display(self):
    print(*self.local, sep=' ')