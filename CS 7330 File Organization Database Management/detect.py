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

  blocked = [False] * len(transactions)
  while len(transactions):
    t = randrange(0, len(transactions))
    blocked[t] = transactions[t].attempt_operation(db, lock_manager) 
    if all(blocked):
      print("Deadlock")
      break
    if not len(transactions[t].operations):
      lock_manager.ReleaseAll(transactions[t].tid)
      del transactions[t]
      blocked[t] = True

  db.Print()