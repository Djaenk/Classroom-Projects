from Database import Database

class LockManager:

  def __init__(self):
    self.x_locks = [None] * len(Database.data)
    self.s_locks = []
    for k in Database.data:
      self.s_locks.append(set())

  def Request(self, tid, k, is_s_lock):
    if self.x_locks[k] is not None:
      return False
    elif is_s_lock:
      self.s_locks[k].add(tid)
      return True
    elif len(self.s_locks[k]) == 0:
      self.x_locks[k] = tid
      return True
    else:
      return False
    
  def ReleaseAll(self, tid):
    self.x_locks = [id if id != tid else None for id in self.x_locks]
    for lock in self.s_locks:
      lock.discard(tid)
  
  def ShowLocks(self, tid):
    locks = []
    for i in range(len(self.x_locks)):
      if self.x_locks(i) == tid:
        locks.append((i, False))
      elif tid in self.s_locks(i):
        locks.append((i, True))
    return locks