from Database import Database
from collections import deque

class Transaction:

  def __init__(self, tid, k, operations):
    self.tid = tid
    self.local = [0] * k
    self.operations = deque(tuple(op.split()) for op in operations)
    self.original_data = deque()

  def attempt_operation(self, db, lock_manager): # Returns true if blocked
    print(f'T{self.tid} execute {" ".join(self.operations[0])}')
    op = self.operations[0][0]
    x = int(self.operations[0][1])
    y = int(self.operations[0][2])
    if op == "W":
      self.last_request = y
      if not lock_manager.Request(self.tid, y, False):
        return True
      self.original_data.appendleft((y, db.Read(y)))
      self.Write(db, x, y)
    elif op == "R":
      self.last_request = x
      if not lock_manager.Request(self.tid, x, True):
        return True
      self.Read(db, x, y)
    elif op == "A":
      self.Add(x, y)
    elif op == "S":
      self.Sub(x, y)
    elif op == "M":
      self.Mult(x, y)
    elif op == "C":
      self.Copy(x, y)
    elif op == "O":
      self.Combine(x, y)
    elif op == "P":
      self.Display()
    self.operations.popleft()
    return False

  def roll_back(self, db):
    while len(self.original_data):
      original = self.original_data[0]
      db.Write(original[0], original[1])
      self.original_data.popleft()

  def Read(self, db, source, dest):
    self.local[dest] = db.Read(source)

  def Write(self, db, source, dest):
    db.Write(dest, self.local[source])

  def Add(self, source, v):
    self.local[source] += v

  def Sub(self, source, v):
    self.local[source] -= v

  def Mult(self, source, v):
    self.local[source] *= v

  def Copy(self, s1, s2):
    self.local[s1] = self.local[s2]

  def Combine(self, s1, s2):
    self.local[s1] += self.local[s2]

  def Display(self):
    print(*self.local, sep=' ')