from Database import Database

class LockManager:

  def __init__(self, db):
    self.x_locks = [None] * len(db.data)
    self.s_locks = [set() for value in db.data]

  def Request(self, tid, k, is_s_lock):
    lock_type = 'S' if is_s_lock else 'X'
    print(f'T{tid} request {lock_type} on item {k} : ', end="")

    if self.x_locks[k] == tid:
      granted = True
    elif self.x_locks[k] is not None:
      granted = False
    elif is_s_lock:
      self.s_locks[k].add(tid)
      granted = True
    elif len(self.s_locks[k]) == 0:
      self.x_locks[k] = tid
      granted = True
    elif len(self.s_locks[k]) == 1 and tid in self.s_locks[k]:
      self.s_locks[k].remove(tid)
      self.x_locks[k] = tid
      granted = True
    else:
      granted = False

    print("G" if granted else "D")
    return granted

  def ReleaseAll(self, tid):
    self.x_locks = [id if id != tid else None for id in self.x_locks]
    for lock in self.s_locks:
      lock.discard(tid)

  def ShowLocks(self, tid):
    locks = []
    for i in range(len(self.x_locks)):
      if self.x_locks[i] == tid:
        locks.append((i, False))
      elif tid in self.s_locks[i]:
        locks.append((i, True))
    return locks