from Database import Database
from LockManager import LockManager
from Transaction import Transaction
from random import randrange

def attempt_operation(db, lock_manager, transaction):
  operation = transaction.operations[0]
  if operation[0] == "W":
    if not lock_manager.Request(transaction.tid, operation[2], False):
      return False
    transaction.Write(db, operation[1], operation[2])
  elif operation[0] == "R":
    if not lock_manager.Request(transaction.tid, operation[1], True):
      return False
    transaction.Read(db, operation[1], operation[2])
  elif operation[0] == "A":
    transaction.Add(operation[1], operation[2])
  elif operation[0] == "S":
    transaction.Sub(operation[1], operation[2])
  elif operation[0] == "M":
    transaction.Sub(operation[1], operation[2])
  elif operation[0] == "C":
    transaction.Copy(operation[1], operation[2])
  elif operation[0] == "O":
    transaction.Combine(operation[1], operation[2])
  elif operation[0] == "P":
    transaction.Display()
  transaction.operations.popleft(0)
  return True

if __name__ == "__main__":
  import sys

  k = int(sys.argv[2])
  db = Database(k)
  lock_manager = LockManager()
  transactions = []
  for file_name in sys.argv[2:]:
    with open(file_name) as file:
      lines = file.readlines()
    op_count = int(lines[1])
    transactions.append(Transaction(len(transactions), op_count, lines[2:]))
  
  while len(transactions):
    t = randrange(0, len(transactions))
    if attempt_operation(db, lock_manager, transactions[t]) and not len(transactions[t].operations):
      del transactions[t]