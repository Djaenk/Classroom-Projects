from Database import Database
from LockManager import LockManager
from Transaction import Transaction

if __name__ == "__main__":
  from random import randrange
  import sys

  k = int(sys.argv[1])
  db = Database(k, True)
  lock_manager = LockManager(db)
  transactions = []
  for file_name in sys.argv[2:]:
    with open(file_name) as file:
      lines = file.readlines()
    op_count = int(lines[0].split()[0])
    var_count = int(lines[0].split()[1])
    transactions.append(Transaction(len(transactions), var_count, lines[1:]))

  while len(transactions):
    t = randrange(0, len(transactions))
    if transactions[t].attempt_operation(db, lock_manager):
      if lock_manager.x_locks[transactions[t].last_request] is not None:
        if lock_manager.x_locks[transactions[t].last_request] < transactions[t].tid:
          pass
      elif max(lock_manager.s_locks[transactions[t].last_request]) > transactions[t].tid:
        pass
      else:
        transactions[t].roll_back(db)
        lock_manager.ReleaseAll(transactions[t].tid)
        print(f'T{transactions[t].tid} rolled back')
        del transactions[t]
    elif not len(transactions[t].operations):
      lock_manager.ReleaseAll(transactions[t].tid)
      del transactions[t]

  db.Print()